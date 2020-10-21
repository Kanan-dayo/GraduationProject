//------------------------------------------------------------------------------
//
//���W���[���̃{�^������  [module_Button.cpp]
//Author:Yoshiki Hosoya
//
//------------------------------------------------------------------------------
#ifndef _MODULE_KEYPAD_H_
#define _MODULE_KEYPAD_H_
//------------------------------------------------------------------------------
//�C���N���[�h
//------------------------------------------------------------------------------
#include "main.h"
#include "module_base.h"
//------------------------------------------------------------------------------
//�N���X��`
//------------------------------------------------------------------------------
class CModule_Parts_Key;

class CModule_KeyPad : public CModule_Base
{
public:
	CModule_KeyPad();
	virtual ~CModule_KeyPad();

	virtual HRESULT Init()			override;			//������
	virtual void Uninit()			override;			//�I��
	virtual void Update()			override;			//�X�V
	virtual void Draw()				override;			//�`��
	virtual void ShowDebugInfo()	override;			//�f�o�b�O���\�L
	void Operation()				override;			//���W���[������
	void CreateKeyPad();								//�L�[�p�b�h����

private:
	std::vector<std::shared_ptr<CModule_Parts_Key>> m_pKeyPadList;				//�L�[�p�b�h�̃|�C���^�̔z��

};
#endif