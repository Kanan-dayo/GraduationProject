//------------------------------------------------------------------------------
//
//���W���[���p�[�c�̐F�̃{�^��  [module_parts_No4_ColButton.h]
//Author:Yoshiki Hosoya
//
//------------------------------------------------------------------------------
#ifndef _MODULE_PARTS_NO4_COLBUTTON_H_
#define _MODULE_PARTS_NO4_COLBUTTON_H_
//------------------------------------------------------------------------------
//�C���N���[�h
//------------------------------------------------------------------------------
#include "main.h"
#include "module_parts_base.h"
#include "module_No4_4ColButton.h"
//------------------------------------------------------------------------------
//�N���X��`
//------------------------------------------------------------------------------
class CModule_Parts_No4_ColButton : public CModule_Parts_Base
{
public:

	CModule_Parts_No4_ColButton();
	virtual ~CModule_Parts_No4_ColButton();

	virtual HRESULT Init()			override;			//������
	virtual void Update()			override;			//�X�V
	virtual void Draw()				override;			//�`��
	virtual void ShowDebugInfo()	override;			//�f�o�b�O���\�L

	void SetButtonCol(CModule_No4_4ColButton::BUTTON button);
	void SetButtonLighting(bool bLight);

	CModule_No4_4ColButton::BUTTON GetButton()				{ return m_Button; };
	bool GetButtonLighting()								{ return m_bLight; };

protected:

private:
	CModule_No4_4ColButton::BUTTON m_Button;	//�{�^��
	D3DXCOLOR m_ButtonCol;						//�{�^���̐F
	bool m_bLight;								//���C�g���_�����Ă��邩�ǂ���
	int m_nCntLight;							//���C�g�̓_���̃J�E���g
};
#endif