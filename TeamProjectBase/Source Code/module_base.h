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
		NONE = 0,
		TIMER,
		BUTTON,
		NO1_SYMBOL,
		NO2_SHAPE,
		NO3_WIRE,
		MAX,

	};

	CModule_Base();
	virtual ~CModule_Base();

	virtual HRESULT Init() = 0;															//������
	virtual void Update() = 0;															//�X�V
	virtual void Draw() = 0;															//�`��
	virtual void ShowDebugInfo() = 0;													//�f�o�b�O���\�L
	virtual void Operation() {};														//���W���[���̑���
	void CreateLamp();																	//�����v����
	void CameraApproach();																//�J�������߂Â���

	void SetCanModuleSelect(bool bSelect) { m_bCanSelect = bSelect; };					//���W���[����I���ł��邩
	void SetModuleType(MODULE_TYPE module) { m_ModuleType = module; };					//���W���[���̃^�C�v�ݒ�
	void SetBombPtr(std::weak_ptr<CBomb> pBombPtr) { m_pBomb = pBombPtr; };				//�{���̃|�C���^�ݒ�

	CModule_Parts_Lamp *GetLampPtr() { return m_pLamp.get(); };							//�����v�̃|�C���^�擾
	MODULE_TYPE GetModuleType() { return m_ModuleType; };								//���W���[���̎��
	bool GetModuleClearFlag() { return m_bModuleClearFlag; };							//���W���[���̃N���A�t���O�擾
	bool GetCanModuleSelect() { return m_bCanSelect; };									//���W���[���I���ł��邩�ǂ���

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
private:
	std::weak_ptr<CBomb> m_pBomb;								//���e�̃|�C���^
	S_ptr<CModule_Parts_Lamp> m_pLamp;							//�����v�̃|�C���^
	MODULE_TYPE m_ModuleType;									//���W���[���̎��
	bool	m_bModuleClearFlag;									//���W���[���̃N���A�t���O
	bool	m_bCanSelect;										//�I���ł��郂�W���[����
};
#endif