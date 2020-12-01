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
	//�����̃p�^�[��
	enum ANSWER_PATTERN
	{
		ANSWER_1 = 0,		//�ӂ�͂��� 26816
		ANSWER_2,			//���΂����� 48390
		ANSWER_3,			//�����Ђ�� 55163
		ANSWER_4,			//�Ȃ₷�� 72843
		ANSWER_5,			//��܂����� 80390
		ANSWER_6,			//����ނ� 92864
		ANSWER_MAX,
	};

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
	Vec<S_ptr<CScene3D>> m_pDisplayNum;						//�f�B�X�v���C�ɕ\�L����鐔�l

	S_ptr<CSceneX>	m_pDecitionButton;						//���M�{�^��
	Vec<int> m_nDisplayNum;									//�f�B�X�v���C�̔ԍ�
	int m_nSelectNum;										//���ݑI�����Ă���ꏊ
	int m_nAnswerNum;										//�����̔ԍ�
	ANSWER_PATTERN m_AnswerPattern;							//�����̃p�^�[��

	void SetAnswer();										//�����p�^�[���ݒ�
	void CreateDisplayNum();								//�f�B�X�v���C�ɕ\�L����鐔�l
	void CreateButton();									//���C���[����
	void CheckClear();										//�N���A�������`�F�b�N

	void ChangeDisplayNum();								//�f�B�X�v���C�̔ԍ��ύX


};
#endif