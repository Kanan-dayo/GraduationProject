//------------------------------------------------------------------------------
//
//���W���[���̃����v�ƃ��C���[�̂�̏���  [Module_No3_LampAndWire.h]
//Author:Yoshiki Hosoya
//
//------------------------------------------------------------------------------
#ifndef _MODULE_NO3_LAMPANDWIRE_H_
#define _MODULE_NO3_LAMPANDWIRE_H_
//------------------------------------------------------------------------------
//�C���N���[�h
//------------------------------------------------------------------------------
#include "main.h"
#include "module_base.h"
//------------------------------------------------------------------------------
//�N���X��`
//------------------------------------------------------------------------------
class CModule_No3_LampAndWire : public CModule_Base
{
public:
	CModule_No3_LampAndWire();
	virtual ~CModule_No3_LampAndWire();

	virtual HRESULT Init()			override;			//������
	virtual void Update()			override;			//�X�V
	virtual void Draw()				override;			//�`��
	virtual void ShowDebugInfo()	override;			//�f�o�b�O���\�L
private:

};
#endif