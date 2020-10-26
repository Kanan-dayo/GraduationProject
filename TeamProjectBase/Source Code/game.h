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
class CBomb;

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
	virtual void Uninit();									//�I��
	virtual void Update();									//�X�V
	virtual void Draw();									//�`��
	virtual void ShowDebugInfo();							//�f�o�b�O���\�L
	void UpdateState();										//�X�e�[�g�ɉ���������

	void SetState(STATE state);								//�Q�[���̏�Ԑݒ�
	void SetGaze(GAZE gaze);								//�����ݒ�

	STATE GetState() { return m_State; };					//�Q�[���̏�Ԏ擾
	GAZE GetGaze() { return m_Gaze; };						//���݂̎����擾
	CBomb *GetBombPtr() { return m_pBomb.get(); };			//�{���̃|�C���^�擾
protected:

private:
	STATE m_State;											//�Q�[���X�e�[�g
	GAZE m_Gaze;											//����
	int m_nCntState;										//�X�e�[�g�̃J�E���^
	std::shared_ptr<CBomb>	m_pBomb;						//�{���̃|�C���^

};

#endif