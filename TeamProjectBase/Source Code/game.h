//------------------------------------------------------------------------------
//
//�Q�[������  [game.h]
//Author:Yoshiki Hosoya
//
//------------------------------------------------------------------------------
#ifndef _GAME_H_
#define _GAME_H_
//------------------------------------------------------------------------------
//�C���N���[�h
//------------------------------------------------------------------------------
#include "main.h"
#include "basemode.h"
#include "Bomb.h"

//------------------------------------------------------------------------------
//�}�N��
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//�N���X��`
//------------------------------------------------------------------------------
class CBomb;
class CChatBase;
class CPicture;
class CTablet;
class CGame : public CBaseMode
{
public:
	//�Q�[���̏�ԑJ��
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

	//�Q�[�����̎���
	enum GAZE
	{
		GAZE_DEFAULT,	//�f�t�H���g�̎���
		GAZE_BOMB,		//���e�����Ă�
		GAZE_MODULE		//���W���[�������Ă�
	};


	CGame();
	~CGame();
	virtual HRESULT Init(HWND hWnd);						//������
	virtual void Update();									//�X�V
	virtual void Draw();									//�`��
	virtual void ShowDebugInfo();							//�f�o�b�O���\�L
	void UpdateState();										//�X�e�[�g�ɉ���������

	void SetState(STATE state);								//�Q�[���̏�Ԑݒ�
	void SetGaze(GAZE gaze);								//�����ݒ�

	STATE GetState() { return m_State; };					//�Q�[���̏�Ԏ擾
	GAZE GetGaze() { return m_Gaze; };						//���݂̎����擾
	CBomb *GetBombPtr() { return m_pBomb.get(); };			//�{���̃|�C���^�擾
	CPicture *GetPicture(void) { return m_pPicture.get(); }	// �s�N�`���|�C���^�̎擾
	CTablet * GetTablet(void) { return m_pTablet.get(); }	// �^�u���b�g�|�C���^�̎擾
	CChatBase *GetChatBase() { return m_pChatBase.get(); };	// �`���b�g�x�[�X�|�C���^�擾

	static bool GetClearFlag() { return m_bClear; };			//�N���A�t���O�擾
	static void SetDifficulty(CBomb::DIFFICULTY Diff) { m_bDifficulty = Diff; }	// ��Փx�̐ݒ�
protected:

private:
	STATE            m_State;								//�Q�[���X�e�[�g
	GAZE             m_Gaze;								//����
	int              m_nCntState;							//�X�e�[�g�̃J�E���^
	S_ptr<CBomb>     m_pBomb;								//�{���̃|�C���^
	S_ptr<CChatBase> m_pChatBase;							// �`���b�g�̃|�C���^
	S_ptr<CPicture>  m_pPicture;							// �s�N�`���|�C���^
	S_ptr<CTablet>   m_pTablet;								// �^�u���b�g�|�C���^

	static bool m_bClear;									//�N���A�t���O
	static CBomb::DIFFICULTY m_bDifficulty;					// �Q�[���̓�Փx
};

#endif