//------------------------------------------------------------------------------
//
//�^�C�}�[�\������  [timer.h]
//Author:Yoshiki Hosoya
//
//------------------------------------------------------------------------------
#ifndef _TIMER_H_
#define _TIMER_H_
//------------------------------------------------------------------------------
//�C���N���[�h
//------------------------------------------------------------------------------
#include "main.h"
#include "scene.h"
//------------------------------------------------------------------------------
//�N���X��`
//------------------------------------------------------------------------------

//�O���錾
class CMultiNumber;

class CTimer
{
public:
	enum TIMER_TYPE
	{
		MINUTE = 0,			//��
		SECOND,				//�b
		COMMA,				//�C
		MAX,
	};
	CTimer();
	~CTimer();
	void UpdateTimer();															//�X�V
	void ChangeNumber();														//�f�B�X�v���C�̐��l�X�V
	void ShowDebugInfo();														//�f�o�b�O���\�L
	static std::unique_ptr<CTimer> Create(D3DXVECTOR3 const &TimerCenterPos,int const nTimer,D3DXMATRIX *pMtx);			//��������

	static int GetTimer() { return m_nTimer; };									//�^�C�}�[�擾
	void SetStop(bool bStop) { m_bStop = bStop; };								//�^�C�}�[�X�g�b�v
private:
	std::vector<std::shared_ptr<CMultiNumber>> m_pMultiNumber;					//�i���o�[�̃|�C���^
	static LPDIRECT3DTEXTURE9 m_pTexture;										//�e�N�X�`���̃|�C���^

	static int m_nTimer;														//�^�C�}�[ �b�ŊǗ�
	int m_nCntFlame;															//�J�E���g �t���[��
	bool m_bStop;																//�X�g�b�v
};

#endif