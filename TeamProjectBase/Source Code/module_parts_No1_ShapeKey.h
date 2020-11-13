//------------------------------------------------------------------------------
//
//���W���[���p�[�c�̃L�[�p�b�h  [module_parts_No1_ShapeKey.h]
//Author:Yoshiki Hosoya
//
//------------------------------------------------------------------------------
#ifndef _MODULE_PARTS_NO2_SHAPEKEY_H_
#define _MODULE_PARTS_NO2_SHAPEKEY_H_
//------------------------------------------------------------------------------
//�C���N���[�h
//------------------------------------------------------------------------------
#include "main.h"
#include "module_parts_base.h"
#include "module_No1_ShapeKeypad.h"
//------------------------------------------------------------------------------
//�N���X��`
//------------------------------------------------------------------------------
class CTimer;
class CScene3D;

class CModule_Parts_No1_ShapeKey : public CModule_Parts_Base
{
public:

	CModule_Parts_No1_ShapeKey();
	virtual ~CModule_Parts_No1_ShapeKey();

	virtual HRESULT Init()			override;			//������
	virtual void Update()			override;			//�X�V
	virtual void Draw()				override;			//�`��
	virtual void ShowDebugInfo()	override;			//�f�o�b�O���\�L

	void SetShape(CModule_No1_ShapeKeyPad::SHAPE shape);

	CModule_No1_ShapeKeyPad::SHAPE GetShape() { return m_Shape; };
protected:

private:
	S_ptr<CScene3D> m_pShape;			//�V���{��
	CModule_No1_ShapeKeyPad::SHAPE m_Shape;							//�V���{���̔ԍ�
};
#endif