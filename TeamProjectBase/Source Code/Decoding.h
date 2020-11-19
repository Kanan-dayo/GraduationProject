//------------------------------------------------------------------------------
//
//��Ǐ���  [Decoding.h]
//Author:Ikuto Sekine
//
//------------------------------------------------------------------------------
#ifndef _DECODING_H_
#define _DECODING_H_

//------------------------------------------------------------------------------
//�C���N���[�h
//------------------------------------------------------------------------------
#include "main.h"
#include "basemode.h"

//------------------------------------------------------------------------------
//�}�N��
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//�N���X��`
//------------------------------------------------------------------------------
class CChatBase;
class CPicture;
class CTablet;
class CDecodingManager;
class CDecoding : public CBaseMode
{
public:
	// ��ԑJ��
	enum STATE
	{
		STATE_NONE = -1,				//�n�܂��ĂȂ�
		STATE_READY,					//�J�n�O�̏��
		STATE_NORMAL,					//�ʏ��ԁ@�i�s��
		STATE_PAUSE,					//�|�[�Y���
		STATE_GAMEOVER,					//�Q�[���I�[�o�[
		STATE_GAMECLEAR,				//�Q�[���N���A

		STATE_DEBUG,
		STATE_MAX
	};

	// ����
	enum GAZE
	{
		GAZE_DEFAULT,	//�f�t�H���g�̎���
	};

	// ����
	enum ROLE
	{
		ROLE_DECODING = 0,		// ���
		ROLE_BOMBRELEASE,		// ���e����
		ROLE_MAX				// �ő�
	};

	CDecoding();											// �R���X�g���N�^
	~CDecoding();											// �f�X�g���N�^
	virtual HRESULT Init(HWND hWnd);						//������
	virtual void Update();									//�X�V
	virtual void Draw();									//�`��
	virtual void ShowDebugInfo();							//�f�o�b�O���\�L
	void UpdateState();										//�X�e�[�g�ɉ���������

	void SetState(STATE state);								//�Q�[���̏�Ԑݒ�
	void SetGaze(GAZE gaze);								//�����ݒ�

	STATE GetState() { return m_State; };					//�Q�[���̏�Ԏ擾
	GAZE GetGaze() { return m_Gaze; };						//���݂̎����擾
	CPicture *GetPicture(void) { return m_pPicture.get(); }	// �s�N�`���|�C���^�̎擾
	CTablet * GetTablet(void) { return m_pTablet.get(); }	// �^�u���b�g�|�C���^�̎擾
	CDecodingManager * GetDecodingManager(void) { return m_pDecodingManager.get(); }
protected:

private:
	STATE            m_State;								// �Q�[���X�e�[�g
	GAZE             m_Gaze;								// ����
	int              m_nCntState;							//�X�e�[�g�̃J�E���^
	S_ptr<CChatBase> m_pChatBase;							// �`���b�g�̃|�C���^
	S_ptr<CPicture>  m_pPicture;							// �s�N�`���|�C���^
	S_ptr<CTablet>   m_pTablet;								// �^�u���b�g�|�C���^
	S_ptr<CDecodingManager> m_pDecodingManager;				// ��Ǐ��}�l�[�W���[
};

#endif