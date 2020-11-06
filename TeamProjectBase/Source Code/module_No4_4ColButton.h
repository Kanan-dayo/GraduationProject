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

class CModule_No4_4ColButton : public CModule_Base
{
public:

	//�{�^���̐F
	enum BUTTON
	{
		RED = 0,			//��
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

	virtual HRESULT Init()			override;			//������
	virtual void Update()			override;			//�X�V
	virtual void Draw()				override;			//�`��
	virtual void ShowDebugInfo()	override;			//�f�o�b�O���\�L
	void Operation()				override;			//���W���[������

	void SetButtonState(STATE state);


	void NextButtonSet();
	void PlayerInputReset();


	void ButtonPushSuccess();
	bool CheckModuleClear();


private:
	Vec<S_ptr<CModule_Parts_No4_ColButton>> m_pColButtonList;
	BUTTON m_nNowSelectButton;										//���݂̐���ԍ�
	STATE m_buttonState;											//�{�^���̃X�e�[�g
	Vec<BUTTON> m_QuestionButtonList;								//�����̃p�^�[��

	int m_nNowFlashNumber;											//���݂̓_�����Ă�o�^�[��
	int m_nClearNum;												//�N���A������
	int m_nButtonLightingCnt;										//�{�^���̃��C�g�_�ŗp�̃J�E���g

	int m_nPlayerPushNum;											//�v���C���[�̓��͂�����



};
#endif