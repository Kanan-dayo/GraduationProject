//------------------------------------------------------------------------------
//
//���W���[���̃^�C�}�[����  [module_timer.cpp]
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
#include "sceneX.h"
//------------------------------------------------------------------------------
//�N���X��`
//------------------------------------------------------------------------------
class CTimer;

class CModule_Timer : public CModule_Base,public CSceneX
{
public:
	CModule_Timer();
	virtual ~CModule_Timer();

	virtual HRESULT Init()			override;			//������
	virtual void Uninit()			override;			//�I��
	virtual void Update()			override;			//�X�V
	virtual void Draw()				override;			//�`��
	virtual void ShowDebugInfo()	override;			//�f�o�b�O���\�L
private:
	std::unique_ptr<CTimer> m_pTimer;


};
#endif