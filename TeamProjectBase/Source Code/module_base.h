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
#include "module_parts_lamp.h"

//------------------------------------------------------------------------------
//�N���X��`
//------------------------------------------------------------------------------
class CModule_Base
{
public:
	CModule_Base();
	virtual ~CModule_Base();

	virtual HRESULT Init()			= 0;						//������
	virtual void Uninit()			= 0;						//�I��
	virtual void Update()			= 0;						//�X�V
	virtual void Draw()				= 0;						//�`��
	virtual void ShowDebugInfo()	= 0;						//�f�o�b�O���\�L
	void CreateLamp(D3DXMATRIX *pModuleMtx);											//�����v����

	template <class T> static void Create(D3DXVECTOR3 const pos, D3DXVECTOR3 const rot, D3DXMATRIX * const pBomb)
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

		//return pPtr;
	}


private:
	std::shared_ptr<CModule_Parts_Base> m_pLamp;				//�����v�̃|�C���^

};
#endif