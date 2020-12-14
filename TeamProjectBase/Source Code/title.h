//------------------------------------------------------------------------------
//
//�^�C�g������  [title.h]
//Author:Yoshiki Hosoya
//
//------------------------------------------------------------------------------
#ifndef _TITLE_H_
#define _TITLE_H_
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
class CScene2D;
class CBomb;

class CTitle : public CBaseMode
{
public:
	//���
	enum STATE
	{
		STATE_NONE = -1,				//����
		STATE_START,					//�ŏ��̉��o
		STATE_NORMAL,					//�ʏ���
		STATE_BLACKOUT,					//�Ó]
		STATE_FADE,						//�t�F�[�h
		STATE_GAMEEND,					//�Q�[���I��
	};
	CTitle();							//�R���X�g���N�^
	~CTitle();							//�f�X�g���N�^

	HRESULT Init(HWND hWnd);			//������
	void Update();						//�X�V
	void Draw();						//�`��
	void ShowDebugInfo(){};				//�f�o�b�O���\�L

	void Collision();					//�����蔻�菈��
	void StateUpdate();					//�X�e�[�g�X�V
	void SetState(STATE state);			//�X�e�[�g�؂�ւ�

private:
	STATE m_titlestate;					//�X�e�[�g
	int m_nCntState;					//�X�e�[�g�̃J�E���g

	S_ptr<CScene2D> m_pStart;			//�X�^�[�g
	S_ptr<CScene2D> m_pEnd;				//�G���h


	S_ptr<CBomb>     m_pBomb;			//�{���̃|�C���^


};

#endif