//------------------------------------------------------------------------------
//
//���W���[���̐i���x�̃����v  [module_parts_Progresslamp.h]
//Author:Yoshiki Hosoya
//
//------------------------------------------------------------------------------
#ifndef _MODULE_PARTS_PROGRESSLAMP_H_
#define _MODULE_PARTS_PROGRESSLAMP_H_
//------------------------------------------------------------------------------
//�C���N���[�h
//------------------------------------------------------------------------------
#include "main.h"
#include "module_parts_base.h"
//------------------------------------------------------------------------------
//�N���X��`
//------------------------------------------------------------------------------
class CTimer;

class CModule_Parts_ProgressLamp : public CModule_Parts_Base
{
public:

	CModule_Parts_ProgressLamp();
	virtual ~CModule_Parts_ProgressLamp();

	virtual HRESULT Init()			override;			//������
	virtual void Update()			override;			//�X�V
	virtual void Draw()				override;			//�`��
	virtual void ShowDebugInfo()	override;			//�f�o�b�O���\�L

private:

};
#endif