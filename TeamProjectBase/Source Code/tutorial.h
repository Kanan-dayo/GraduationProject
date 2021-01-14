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

	void CreateUI();
	void UpdateState();
	void Collision();

private:
	int m_nCntState;	//�J�E���^
	TUTORIL_TYPE m_state;

	Vec<S_ptr<CScene2D>> m_pPolygonList;
};

#endif