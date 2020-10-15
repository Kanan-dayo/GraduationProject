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

//------------------------------------------------------------------------------
//�N���X��`
//------------------------------------------------------------------------------
class CModule_Parts_Base
{
public:
	CModule_Parts_Base()
	{
	};
	virtual ~CModule_Parts_Base() {};

	virtual HRESULT Init() = 0;					//������
	virtual void Uninit() = 0;					//�I��
	virtual void Update() = 0;					//�X�V
	virtual void Draw() = 0;					//�`��
	virtual void ShowDebugInfo() = 0;			//�f�o�b�O���\�L
private:


};
#endif