//------------------------------------------------------------------------------
//
//���W���[���̃����v�ƃ��C���[�̂�̏���  [Module_No2_LampAndWire.h]
//Author:Yoshiki Hosoya
//
//------------------------------------------------------------------------------
#ifndef _MODULE_NO3_PASSWORD_H_
#define _MODULE_NO3_PASSWORD_H_
//------------------------------------------------------------------------------
//�C���N���[�h
//------------------------------------------------------------------------------
#include "main.h"
#include "module_base.h"
//------------------------------------------------------------------------------
//�N���X��`
//------------------------------------------------------------------------------
class CModule_Parts_No3_Button;
class CScene3D;

class CModule_No3_PassWord : public CModule_Base
{
public:

	CModule_No3_PassWord();
	virtual ~CModule_No3_PassWord();

	virtual HRESULT Init()				override;			//������
	virtual void Update()				override;			//�X�V
	virtual void Draw()					override;			//�`��
	virtual void ShowDebugInfo()		override;			//�f�o�b�O���\�L
	void Operation_Keyboard()			override;			//���W���[������ �L�[�{�[�h
	void Operation_Mouse()				override;			//���W���[������ �}�E�X
	void ModuleAction()					override;			//���W���[���̃A�N�V����
	void ModuleCancel()					override;			//���W���[���̑I������

private:
	Vec<S_ptr<CModule_Parts_No3_Button>> m_pButtonList;		//�{�^���̃��X�g
	int m_nSelectPlace;										//���ݑI�����Ă���ꏊ

	void CreateButton();									//���C���[����

	void CheckClear();										//�N���A�������`�F�b�N
};
#endif