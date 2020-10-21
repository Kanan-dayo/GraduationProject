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
//------------------------------------------------------------------------------
//�}�N��
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//�N���X��`
//------------------------------------------------------------------------------
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
	virtual HRESULT Init(HWND hWnd);								//������
	virtual void Uninit();											//�I��
	virtual void Update();											//�X�V
	virtual void Draw();											//�`��
	virtual void ShowDebugInfo();									//�f�o�b�O���\�L

	void SetGamestate(STATE gamestate);						//�Q�[���̏�Ԑݒ�
	STATE GetGamestate() { return m_gamestate; };			//�Q�[���̏�Ԏ擾

protected:

private:
	STATE m_gamestate;									//�Q�[���X�e�[�g
	int m_nCntState;									//�X�e�[�g�̃J�E���^
};

#endif