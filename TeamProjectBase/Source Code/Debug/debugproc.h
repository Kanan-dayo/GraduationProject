//------------------------------------------------------------------------------
//
//�f�o�b�O�\�L����  [debugproc.h]
//Author:Yoshiki Hosoya
//
//------------------------------------------------------------------------------
#ifndef _DEBUGPROC_H_
#define _DEBUGPROC_H_
//------------------------------------------------------------------------------
//�C���N���[�h
//------------------------------------------------------------------------------
#include "../main.h"

//------------------------------------------------------------------------------
//�}�N��
//------------------------------------------------------------------------------
#define MAX_DATA (4096)

//------------------------------------------------------------------------------
//�N���X��`
//------------------------------------------------------------------------------
//�O���錾
class CDebugProc
{
public:
	//�ꏊ
	enum PLACE
	{
		PLACE_LEFT = 0,	//��
		PLACE_RIGHT,	//�E
		PLACE_MAX,		//
	};

	HRESULT Init(HWND hWnd);							//������
	void Uninit();										//�I��
	static void Print(PLACE place ,char* fmt, ...);		//�f�o�b�O���i�[
	static void Draw(void);								//�`��
	static void ResetStr();								//�z�񏉊���

private:
	static LPD3DXFONT m_pFont;							//�t�H���g�ւ̃|�C���^
	static char m_aStr[PLACE_MAX][MAX_DATA];			//�����i�[����z��
	static RECT m_rect[PLACE_MAX];						//�`��ʒu
};

#endif