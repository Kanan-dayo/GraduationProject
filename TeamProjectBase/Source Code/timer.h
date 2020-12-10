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

	void SetStop(bool bStop) { m_bStop = bStop; };								//�^�C�}�[�X�g�b�v
	bool GetStop() { return m_bStop; };											//�^�C�}�[�X�g�b�v���Ă邩�ǂ���

	static int GetClearFlame() { return m_nClearFlame; };						//�N���A�^�C��
private:
	Vec<S_ptr<CMultiNumber>> m_pMultiNumber;									//�i���o�[�̃|�C���^
	int m_nCntFlame;															//�J�E���g �t���[��
	bool m_bStop;																//�X�g�b�v

	static int m_nClearFlame;													//�N���A�t���[��
};

#endif