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
#include "sceneX.h"
//------------------------------------------------------------------------------
//�N���X��`
//------------------------------------------------------------------------------
class CTimer;

class CModule_Parts_Lamp : public CModule_Parts_Base,public CSceneX
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
	virtual void Uninit()			override;			//�I��
	virtual void Update()			override;			//�X�V
	virtual void Draw()				override;			//�`��
	virtual void ShowDebugInfo()	override;			//�f�o�b�O���\�L

	void SetLampState(LAMP_STATE lampstate)		{ m_LampState = lampstate; };
	LAMP_STATE GetLampState()					{ return m_LampState; };

	static std::shared_ptr<CModule_Parts_Lamp> Create(D3DXVECTOR3 const pos,D3DXMATRIX* const pModuleMtx);
private:
	int m_nCntLampCnt;					//�����v�p�̃J�E���g
	LAMP_STATE m_LampState;				//�����v�̏��
};
#endif