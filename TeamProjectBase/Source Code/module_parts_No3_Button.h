//------------------------------------------------------------------------------
//
//���W���[���p�[�c�̃{�^��  [module_parts_No3_Button.h]
//Author:Yoshiki Hosoya
//
//------------------------------------------------------------------------------
#ifndef _MODULE_PARTS_NO3_WIRE_H_
#define _MODULE_PARTS_NO3_WIRE_H_
//------------------------------------------------------------------------------
//�C���N���[�h
//------------------------------------------------------------------------------
#include "main.h"
#include "module_parts_base.h"
#include "module_No2_LampAndWire.h"

//------------------------------------------------------------------------------
//�N���X��`
//------------------------------------------------------------------------------
class CModule_Parts_No3_Button : public CModule_Parts_Base
{
public:

	CModule_Parts_No3_Button();
	virtual ~CModule_Parts_No3_Button();

	virtual HRESULT Init()			override;			//������
	virtual void Update()			override;			//�X�V
	virtual void Draw()				override;			//�`��
	virtual void ShowDebugInfo()	override;			//�f�o�b�O���\�L

	void SetWire(CModule_No2_LampAndWire::WIRE wire);			//���C���[�ݒ�
	void SetWireCut(bool bCut) { m_bCut = bCut; };					//���C���[�J�b�g�������ݒ�

	CModule_No2_LampAndWire::WIRE GetWire() { return m_Wire; };		//���C���[���擾
	bool GetWireCut() { return m_bCut; };							//���C���[�J�b�g�������擾
protected:

private:
	CModule_No2_LampAndWire::WIRE m_Wire;				//���C���[
	D3DXCOLOR m_WireColor;								//���C���[�̐F
	bool m_bCut;										//�؂������ǂ���
};
#endif