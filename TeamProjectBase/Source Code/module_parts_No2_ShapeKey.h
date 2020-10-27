//------------------------------------------------------------------------------
//
//���W���[���p�[�c�̃L�[�p�b�h  [module_parts_key.cpp]
//Author:Yoshiki Hosoya
//
//------------------------------------------------------------------------------
#ifndef _MODULE_PARTS_KEY_H_
#define _MODULE_PARTS_KEY_H_
//------------------------------------------------------------------------------
//�C���N���[�h
//------------------------------------------------------------------------------
#include "main.h"
#include "module_parts_base.h"
#include "module_No2_ShapeKeypad.h"
//------------------------------------------------------------------------------
//�N���X��`
//------------------------------------------------------------------------------
class CTimer;
class CScene3D;

class CModule_Parts_No2_ShapeKey : public CModule_Parts_Base
{
public:

	CModule_Parts_No2_ShapeKey();
	virtual ~CModule_Parts_No2_ShapeKey();

	virtual HRESULT Init()			override;			//������
	virtual void Uninit()			override;			//�I��
	virtual void Update()			override;			//�X�V
	virtual void Draw()				override;			//�`��
	virtual void ShowDebugInfo()	override;			//�f�o�b�O���\�L

	void SetShape(CModule_No2_ShapeKeyPad::SHAPE shape);

	CModule_No2_ShapeKeyPad::SHAPE GetShape() { return m_Shape; };
protected:

private:
	std::shared_ptr<CScene3D> m_pShape;			//�V���{��
	CModule_No2_ShapeKeyPad::SHAPE m_Shape;							//�V���{���̔ԍ�
};
#endif