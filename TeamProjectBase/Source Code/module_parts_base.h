//------------------------------------------------------------------------------
//
//���W���[���̃p�[�c�̊��N���X  [module_parts_base.cpp]
//Author:Yoshiki Hosoya
//
//------------------------------------------------------------------------------
#ifndef _MODULE_PARTS_BASE_H_
#define _MODULE_PARTS_BASE_H_
//------------------------------------------------------------------------------
//�C���N���[�h
//------------------------------------------------------------------------------
#include "main.h"
#include "sceneX.h"
//------------------------------------------------------------------------------
//�N���X��`
//------------------------------------------------------------------------------
class CModule_Parts_Base : public CSceneX
{
public:
	CModule_Parts_Base()
	{
		m_bClearFlag = false;
	};
	virtual ~CModule_Parts_Base() {};

	virtual HRESULT Init() = 0;						//������
	virtual void Update() = 0;						//�X�V
	virtual void Draw() = 0;						//�`��
	virtual void ShowDebugInfo() = 0;				//�f�o�b�O���\�L

	void SetClearFlag(bool bClearFlag)		{ m_bClearFlag = bClearFlag; };		//�N���A�t���O�ݒ�

	bool GetClearFlag() { return m_bClearFlag; };								//�N���A�t���O�擾

	//Create�֐�
	template<class Module> static S_ptr<Module> Create_ModuleParts(D3DXVECTOR3 const pos, D3DXMATRIX * const pModuleMtxPtr)
	{
		//�������m��
		S_ptr<Module> pPtr = std::make_shared<Module>();

		//������
		pPtr->Init();

		//���W�ƃT�C�Y�ݒ�
		pPtr->SetPos(pos);
		pPtr->SetParentMtxPtr(pModuleMtxPtr);

		//Scene���ŊǗ�
		pPtr->SetObjType(CScene::OBJTYPE_MODULE_PARTS);
		pPtr->AddSharedList(pPtr);

		return pPtr;
	}

private:
	bool m_bClearFlag;				//�N���A����ׂɎg���t���O
};
#endif

////�e���v���[�g�֐�
////���W���[���̏����z�u�p�̊֐�
////�Ăяo�����ɃN���X�^�������Ă�����K�v������
////��) CModule_Base::Create<CModule_Timer>(...)
//template<class Module>
//inline S_ptr<Module> static CModule_Parts_Base::Create_ModuleParts(D3DXVECTOR3 const pos, D3DXMATRIX * const pModuleMtxPtr)
