//------------------------------------------------------------------------------
//
//���W���[���̃����v  [module_parts_lamp.cpp]
//Author:Yoshiki Hosoya
//
//------------------------------------------------------------------------------
#ifndef _MODULE_PARTS_LAMP_H_
#define _MODULE_PARTS_LAMP_H_
//------------------------------------------------------------------------------
//�C���N���[�h
//------------------------------------------------------------------------------
#include "main.h"
#include "module_parts_base.h"
//------------------------------------------------------------------------------
//�N���X��`
//------------------------------------------------------------------------------
class CTimer;

class CModule_Parts_Lamp : public CModule_Parts_Base
{
public:
	enum class LAMP_STATE
	{
		OFF,
		RED,
		GREEN,
	};

	CModule_Parts_Lamp();
	virtual ~CModule_Parts_Lamp();

	virtual HRESULT Init()			override;			//������
	virtual void Update()			override;			//�X�V
	virtual void Draw()				override;			//�`��
	virtual void ShowDebugInfo()	override;			//�f�o�b�O���\�L

	void SetLampState(LAMP_STATE lampstate);
	LAMP_STATE GetLampState()		{ return m_LampState; };
private:
	int m_nCntLampCnt;					//�����v�p�̃J�E���g
	LAMP_STATE m_LampState;				//�����v�̏��
};
#endif