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

//------------------------------------------------------------------------------
//�N���X��`
//------------------------------------------------------------------------------
class CModule_Parts_No3_Button : public CModule_Parts_Base
{
public:

	//�{�^���̎��
	enum BUTTONTYPE
	{
		NONE = -1,		//����
		UP,				//��
		DOWN,			//��
	};


	CModule_Parts_No3_Button();
	virtual ~CModule_Parts_No3_Button();

	virtual HRESULT Init()			override;						//������
	virtual void Update()			override;						//�X�V
	virtual void Draw()				override;						//�`��
	virtual void ShowDebugInfo()	override;						//�f�o�b�O���\�L

	void SetButtonType(BUTTONTYPE type);							//�{�^���^�C�v�ݒ�

	BUTTONTYPE GetButtonType() { return m_ButtonType; };			//�{�^���^�C�v�擾

protected:

private:
	BUTTONTYPE m_ButtonType;										//�{�^���^�C�v
	int m_nNumber_To_Left;											//�����牽�Ԗڂ̃{�^����
};
#endif