//------------------------------------------------------------------------------
//
//���W���[���̉����Ȃ��Ƃ�  [module_none.cpp]
//Author:Yoshiki Hosoya
//
//------------------------------------------------------------------------------
#ifndef _MODULE_NONE_H_
#define _MODULE_NONE_H_
//------------------------------------------------------------------------------
//�C���N���[�h
//------------------------------------------------------------------------------
#include "main.h"
#include "module_base.h"
#include "sceneX.h"
//------------------------------------------------------------------------------
//�N���X��`
//------------------------------------------------------------------------------
class CModule_None : public CModule_Base
{
public:
	CModule_None();
	virtual ~CModule_None();

	virtual HRESULT Init()			override;			//������
	virtual void Uninit()			override;			//�I��
	virtual void Update()			override;			//�X�V
	virtual void Draw()				override;			//�`��
	virtual void ShowDebugInfo()	override;			//�f�o�b�O���\�L
private:

};
#endif