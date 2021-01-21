//------------------------------------------------------------------------------
//
//�`���[�g���A������  [tutorial.h]
//Author:Yoshiki Hosoya
//
//------------------------------------------------------------------------------
#ifndef _TUTORIAL_H_
#define _TUTORIAL_H_
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
class CUI_Base;
class CTimer;

class CTutorial : public CBaseMode
{
public:
	CTutorial();
	~CTutorial();

	enum TUTORIL_TYPE
	{
		TUTORIAL_NONE = 0,
		TUTORIAL_REMOVE,	// ����
		TUTORIAL_SOLVE,		// ���
	};

	HRESULT Init(HWND hWnd);			//������
	void Update();						//�X�V
	void Draw();						//�`��
	void ShowDebugInfo() {};			//�f�o�b�O���\�L

	void CreateUI();					//�t�h����
	void UpdateState();					//�X�e�[�g�X�V
	void Collision();					//����

	void PageChange();					//�y�[�W�ύX
	void Ready();						//��������

	static void GuestEndTutorial() { m_bGuestFlag = true; }		// �Q�X�g�̏�������

private:
	int m_nCntState;					//�J�E���^
	int m_nPage;						//�y�[�W
	TUTORIL_TYPE m_type;				//�^�C�v

	bool m_bTutorialEndFlag;			//�I���t���O
	static bool m_bGuestFlag;			// �Q�X�g�̏I���t���O

	S_ptr<CScene2D> m_pReady;
	S_ptr<CScene2D> m_pTutorialPolygon;
	S_ptr<CScene2D> m_pNextPage;

};

#endif