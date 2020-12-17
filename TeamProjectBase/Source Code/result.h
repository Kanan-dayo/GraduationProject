//------------------------------------------------------------------------------
//
//���U���g����  [result.h]
//Author:Yoshiki Hosoya
//
//------------------------------------------------------------------------------
#ifndef _RESULT_H_
#define _RESULT_H_
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

class CResult : public CBaseMode
{
public:
	CResult();
	~CResult();

	enum RESULT_STATE
	{
		UP_BAR_IN,
		RESULT_DISP,
		PLAYTIME_DISP,
		STAY,
		SELECT,
		FADE,
	};


	enum RESULT_POLYGON_TYPE
	{
		LOGO = 0,
		UP_BAR,
		JUDGE,

		PLAYTIME,
		SEMICOLON,
		COMMMA,
		UNDER_BAR,

		SELECTION_WINDOW,
		RETRY,
		END,
		MAX,
	};



	HRESULT Init(HWND hWnd);			//������
	void Update();						//�X�V
	void Draw();						//�`��
	void ShowDebugInfo() {};			//�f�o�b�O���\�L

	void UpdateState();
	void Collision();
	void SetState(RESULT_STATE state);

private:
	int m_nCntState;	//�J�E���^

	S_ptr<CTimer> m_pTimer;
	RESULT_STATE m_state;

	Vec<S_ptr<CUI_Base>> m_pPolygonList;
};

#endif