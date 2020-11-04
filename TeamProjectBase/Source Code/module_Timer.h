//------------------------------------------------------------------------------
//
//���W���[���̃^�C�}�[����  [module_timer.h]
//Author:Yoshiki Hosoya
//
//------------------------------------------------------------------------------
#ifndef _MODULE_TIMER_H_
#define _MODULE_TIMER_H_
//------------------------------------------------------------------------------
//�C���N���[�h
//------------------------------------------------------------------------------
#include "main.h"
#include "module_base.h"
//------------------------------------------------------------------------------
//�N���X��`
//------------------------------------------------------------------------------
class CTimer;
class CScene3D;

class CModule_Timer : public CModule_Base
{
public:
	CModule_Timer();
	virtual ~CModule_Timer();

	virtual HRESULT Init()			override;							//������
	virtual void Update()			override;							//�X�V
	virtual void Draw()				override;							//�`��
	virtual void ShowDebugInfo()	override;							//�f�o�b�O���\�L

	bool MissCountUp();										//�~�X�J�E���^�[�J�E���g�A�b�v

private:
	U_ptr<CTimer> m_pTimer;									//�^�C�}�[�̃|�C���^
	Vec<S_ptr<CScene3D>> m_pMissCounter;				//�~�X�J�E���^�[�̃|�C���^

	int m_nMissCount;

};
#endif