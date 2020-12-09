//------------------------------------------------------------------------------
//
//���W���[���̊��N���X  [module_base.h]
//Author:Yoshiki Hosoya
//
//------------------------------------------------------------------------------
#ifndef _MODULE_BASE_H_
#define _MODULE_BASE_H_
//------------------------------------------------------------------------------
//�C���N���[�h
//------------------------------------------------------------------------------
#include "main.h"
#include "sceneX.h"
//------------------------------------------------------------------------------
//�N���X��`
//------------------------------------------------------------------------------
class CModule_Parts_Lamp;
class CBomb;

class CModule_Base : public CSceneX
{
public:

	enum class MODULE_TYPE
	{
		NONE = 0,				//���W���[���Ȃ�
		TIMER,					//�^�C�}�[
		NO0_SYMBOL,				//�L��
		NO1_SHAPE,				//�}�`
		NO2_WIRE,				//���C���[
		NO3_PASSWORD,			//�p�X���[�h
		NO4_4COLBUTTON,			//4�F�{�^��
		MAX,
	};

	CModule_Base();																		//�R���X�g���N�^
	virtual ~CModule_Base();															//�f�X�g���N�^

	virtual HRESULT Init() = 0;															//������
	virtual void Update() = 0;															//�X�V
	virtual void Draw() = 0;															//�`��
	virtual void ShowDebugInfo();													//�f�o�b�O���\�L
	virtual void Operation_Keyboard();													//���W���[������@�L�[�{�[�h
	virtual void Operation_Mouse();														//���W���[������@�}�E�X
	virtual void ModuleAction(){};														//���W���[���ɑ΂��ĉ����A�N�V����������
	virtual void ModuleCancel(){};														//���W���[���̑I��������

	void CreateLamp();																	//�����v����
	void CameraApproach();																//�J�������߂Â���

	void SetModuleType(MODULE_TYPE module) { m_ModuleType = module; };					//���W���[���̃^�C�v�ݒ�
	void SetBombPtr(W_ptr<CBomb> pBombPtr) { m_pBomb = pBombPtr; };						//�{���̃|�C���^�ݒ�
	void SetOperating(bool bOperating) { m_bOperating = bOperating; };					//���삵�Ă�

	W_ptr<CBomb> GetBombWeakPtr() { return m_pBomb; };									//�{����weak�|�C���^�擾

	CModule_Parts_Lamp *GetLampPtr() { return m_pLamp.get(); };							//�����v�̃|�C���^�擾
	MODULE_TYPE GetModuleType() { return m_ModuleType; };								//���W���[���̎��
	bool GetModuleClearFlag() { return m_bModuleClearFlag; };							//���W���[���̃N���A�t���O�擾
	bool GetOperatin() { return m_bOperating; };										//���삵�Ă�

	void Module_Clear();																//�N���A
	void Module_Failed();																//���s

	//Create�֐�
	//�e���v���[�g�֐�
	//���W���[���̏����z�u�p�̊֐�
	//�Ăяo�����ɃN���X�^�������Ă�����K�v������
	//��) CModule_Base::Create<CModule_Timer>(...)
	template <class Module> static S_ptr<Module> Create_Module(D3DXVECTOR3 const pos, D3DXVECTOR3 const rot, D3DXMATRIX * const pBomb)
	{
		//�������m��
		S_ptr<Module> pPtr = std::make_shared<Module>();

		//������
		pPtr->Init();

		//���W�ƃT�C�Y�ݒ�
		pPtr->SetPos(pos);
		pPtr->SetRot(rot);
		pPtr->SetParentMtxPtr(pBomb);

		//Scene���ŊǗ�
		pPtr->SetObjType(CScene::OBJTYPE_MODULE);
		pPtr->AddSharedList(pPtr);

		return pPtr;
	}

	//�e���v���[�g�֐�
	//���W���[���̑I����Ԃ�ݒ肷��֐�
	//�S����������ꍇ��nSelectNum��-1�����Ďg��
	template <class ModuleParts> static void ModuleParts_Select(Vec<S_ptr<ModuleParts>> &rList,int nSelectNum)
	{
		//�z�񂪋󂩂ǂ����`�F�b�N
		if (rList.empty())
		{
			return;
		}

		for (int nCnt = 0; nCnt < (int)rList.size(); nCnt++)
		{
			//���݂̑I��ԍ��Ɠ������m����true�ɂ��Ă���
			nCnt == nSelectNum ?
				rList[nCnt]->SetSelect(true) :
				rList[nCnt]->SetSelect(false);

		}
	}

private:
	std::weak_ptr<CBomb> m_pBomb;								//���e�̃|�C���^
	S_ptr<CModule_Parts_Lamp> m_pLamp;							//�����v�̃|�C���^
	MODULE_TYPE m_ModuleType;									//���W���[���̎��
	bool	m_bModuleClearFlag;									//���W���[���̃N���A�t���O
	bool	m_bOperating;										//���W���[�����쒆

};
#endif