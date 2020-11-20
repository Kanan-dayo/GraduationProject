//------------------------------------------------------------------------------
//
//���W���[���̐}�`�̃L�[�p�b�h����  [module_ShapeKeypad.h]
//Author:Yoshiki Hosoya
//
//------------------------------------------------------------------------------
#ifndef _MODULE_NO4_4COLBUTTON_H_
#define _MODULE_NO4_4COLBUTTON_H_
//------------------------------------------------------------------------------
//�C���N���[�h
//------------------------------------------------------------------------------
#include "main.h"
#include "module_base.h"
//------------------------------------------------------------------------------
//�N���X��`
//------------------------------------------------------------------------------
class CModule_Parts_No4_ColButton;
class CModule_Parts_ProgressLamp;

class CModule_No4_4ColButton : public CModule_Base
{
public:

	//�{�^���̐F
	enum BUTTON
	{
		NONE = -1,			//NONE
		RED,				//��
		GREEN,				//��
		BLUE,				//��
		YELLOW				//��
	};

	enum class STATE
	{
		START,				//�J�n
		LIGHTING,			//�_��
		INTERVAL,			//���̃{�^���_�ł܂ł̃C���^�[�o��
		PLAYER_INPUT,		//�v���C���[���͒�
		RESET_INTERVAL,		//���̎���ւ̃C���^�[�o��
		END,

	};


	CModule_No4_4ColButton();
	virtual ~CModule_No4_4ColButton();

	virtual HRESULT Init()			override;						//������
	virtual void Update()			override;						//�X�V
	virtual void Draw()				override;						//�`��
	virtual void ShowDebugInfo()	override;						//�f�o�b�O���\�L
	void Operation_Keyboard()		override;						//���W���[������ �L�[�{�[�h
	void Operation_Mouse()			override;						//���W���[������ �}�E�X
	void ModuleAction()				override;						//���W���[���̃A�N�V����
	void ModuleCancel()				override;						//���W���[���̑I������

	void SetButtonState(STATE state);								//�{�^���̏�Ԑݒ�

	void NextButtonSet();											//���̉����{�^���ݒ�
	void PlayerInputReset();										//�v���C��[�̓��̓��Z�b�g

	void ButtonPushSuccess();										//�����{�^������
	bool CheckModuleClear();										//���W���[���N���A�������`�F�b�N


private:
	Vec<S_ptr<CModule_Parts_No4_ColButton>> m_pColButtonList;		//�F�{�^���̃��X�g
	Vec<BUTTON> m_QuestionButtonList;								//�����̃p�^�[��
	S_ptr<CModule_Parts_ProgressLamp> m_pProgressLamp;				//�i���x�����v
	BUTTON m_nNowSelectButton;										//���݂̐���ԍ�
	STATE m_buttonState;											//�{�^���̃X�e�[�g

	int m_nNowFlashNumber;											//���݂̓_�����Ă�o�^�[��
	int m_nClearNum;												//�N���A������
	int m_nButtonLightingCnt;										//�{�^���̃��C�g�_�ŗp�̃J�E���g

	int m_nPlayerPushNum;											//�v���C���[�̓��͂�����


	void SetNextButton_NotBattery_NotSerialNo(BUTTON &NextButton);
	void SetNextButton_YesBattery_NotSerialNo(BUTTON &NextButton);

};
#endif