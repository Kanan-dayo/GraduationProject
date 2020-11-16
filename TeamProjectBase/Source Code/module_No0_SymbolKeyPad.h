//------------------------------------------------------------------------------
//
//���W���[���̃{�^������  [Module_No0_SymbolKeypad.h]
//Author:Yoshiki Hosoya
//
//------------------------------------------------------------------------------
#ifndef _MODULE_NO1_SYMBOLKEYPAD_H_
#define _MODULE_NO1_SYMBOLKEYPAD_H_
//------------------------------------------------------------------------------
//�C���N���[�h
//------------------------------------------------------------------------------
#include "main.h"
#include "module_base.h"
//------------------------------------------------------------------------------
//�N���X��`
//------------------------------------------------------------------------------
class CModule_Parts_No0_SymbolKey;

class CModule_No0_SymbolKeyPad : public CModule_Base
{
public:
	enum ANSWER_PATTERN
	{
		ANSWER_1 = 0,
		ANSWER_2,
		ANSWER_3,
		ANSWER_4,
		ANSWER_5,
		ANSWER_6,
		ANSWER_MAX,
	};

	CModule_No0_SymbolKeyPad();
	virtual ~CModule_No0_SymbolKeyPad();

	virtual HRESULT Init()			override;			//������
	virtual void Update()			override;			//�X�V
	virtual void Draw()				override;			//�`��
	virtual void ShowDebugInfo()	override;			//�f�o�b�O���\�L
	void Operation_Keyboard()		override;			//���W���[������ �L�[�{�[�h
	void Operation_Mouse()			override;			//���W���[������ �}�E�X
	void ModuleAction()				override;			//���W���[���̃A�N�V����
	void ModuleCancel()				override;			//���W���[���̑I������

	void CreateKeyPad(ANSWER_PATTERN answer);			//�L�[�p�b�h����
	void CheckClear();									//�N���A�������m�F
private:
	Vec<S_ptr<CModule_Parts_No0_SymbolKey>> m_pKeyPadList;				//�L�[�p�b�h�̃|�C���^�̔z��
	ANSWER_PATTERN m_Answer;											//�����̃p�^�[��
	int m_nNextSymbolNum;												//���̃V���{���ԍ�
	int m_nSelectNum;													//���݂̑I��ԍ�
};
#endif