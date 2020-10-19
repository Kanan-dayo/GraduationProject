//------------------------------------------------------------------------------
//
//���W���[���̊��N���X  [module_base.cpp]
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

class CModule_Base : public CSceneX
{
public:
	CModule_Base();
	virtual ~CModule_Base();

	virtual HRESULT Init()			= 0;										//������
	virtual void Uninit()			= 0;										//�I��
	virtual void Update()			= 0;										//�X�V
	virtual void Draw()				= 0;										//�`��
	virtual void ShowDebugInfo()	= 0;										//�f�o�b�O���\�L
	void CreateLamp(D3DXMATRIX *pModuleMtx);									//�����v����

	CModule_Parts_Lamp *GetLampPtr() { return m_pLamp.get(); };					//�����v�̃|�C���^�擾
	bool GetModuleClearFlag() { return m_bModuleClearFlag; };					//���W���[���̃N���A�t���O�擾

	void Module_Clear();															//���W���[���N���A
	void Module_Failed();															//���W���[���N���A

	//�e���v���[�g�֐�
	//���W���[���̏����z�u�p�̊֐�
	//�Ăяo�����ɃN���X�^�������Ă�����K�v������
	//��) CModule_Base::Create<CModule_Timer>(...)
	template <class T> static std::shared_ptr<T> Create(D3DXVECTOR3 const pos, D3DXVECTOR3 const rot, D3DXMATRIX * const pBomb)
	{
		//�������m��
		std::shared_ptr<T> pPtr = std::make_shared<T>();

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
	std::shared_ptr<CModule_Parts_Lamp> m_pLamp;				//�����v�̃|�C���^
	bool	m_bModuleClearFlag;									//���W���[���̃N���A�t���O
};
#endif