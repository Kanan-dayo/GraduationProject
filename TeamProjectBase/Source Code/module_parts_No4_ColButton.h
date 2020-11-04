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
//------------------------------------------------------------------------------
//�N���X��`
//------------------------------------------------------------------------------
class CModule_Parts_No4_ColButton : public CModule_Parts_Base
{
public:

	enum class BUTTON_COL
	{
		RED = 0,
		GREEN,
		BLUE,
		YELLOW
	};

	CModule_Parts_No4_ColButton();
	virtual ~CModule_Parts_No4_ColButton();

	virtual HRESULT Init()			override;			//������
	virtual void Update()			override;			//�X�V
	virtual void Draw()				override;			//�`��
	virtual void ShowDebugInfo()	override;			//�f�o�b�O���\�L

	void SetButtonCol(BUTTON_COL col);

protected:

private:
	BUTTON_COL m_buttoncol;
};
#endif