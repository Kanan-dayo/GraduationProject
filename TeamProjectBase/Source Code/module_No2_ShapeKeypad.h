//------------------------------------------------------------------------------
//
//���W���[���̐}�`�̃L�[�p�b�h����  [module_ShapeKeypad.cpp]
//Author:Yoshiki Hosoya
//
//------------------------------------------------------------------------------
#ifndef _MODULE_NO2_SHAPEKEYPAD_H_
#define _MODULE_NO2_SHAPEKEYPAD_H_
//------------------------------------------------------------------------------
//�C���N���[�h
//------------------------------------------------------------------------------
#include "main.h"
#include "module_base.h"
//------------------------------------------------------------------------------
//�N���X��`
//------------------------------------------------------------------------------
class CModule_Parts_No2_ShapeKey;
class CScene3D;

class CModule_No2_ShapeKeyPad : public CModule_Base
{
public:
	enum class SHAPE
	{
		CIRCLE = 0,
		CROSS,
		TRIANGLE,
		SQUARE,
		MAX,
	};


	//enum ANSWER_PATTERN
	//{
	//	ANSWER_1 = 0,
	//	ANSWER_2,
	//	ANSWER_3,
	//	ANSWER_4,
	//	ANSWER_5,
	//	ANSWER_6,
	//	ANSWER_MAX,
	//};

	CModule_No2_ShapeKeyPad();
	virtual ~CModule_No2_ShapeKeyPad();

	virtual HRESULT Init()			override;			//������
	virtual void Uninit()			override;			//�I��
	virtual void Update()			override;			//�X�V
	virtual void Draw()				override;			//�`��
	virtual void ShowDebugInfo()	override;			//�f�o�b�O���\�L
	void Operation()				override;			//���W���[������
	void CreateKeyPad();								//�L�[�p�b�h����
	void CheckClear();									//�N���A�������m�F
	void ShapeShuffle();								//�}�`�̃V���b�t��
	void SetDisplayShape(int nShape);					//�f�B�X�v���C�̐}�`�ݒ�

	void SetNextPushKey();								//���ɉ����L�[�̐ݒ�
	void SetNextPushKey_FromShape(SHAPE shape);			//�}�`����Ɏ��ɉ����L�[�ݒ�
	void SetNextPushKey_FromPlace(int nPlace);			//�ꏊ����Ɏ��ɉ����L�[�ݒ� �����牽�Ԗڂ�


private:
	std::vector<std::shared_ptr<CModule_Parts_No2_ShapeKey>> m_pKeyPadList;				//�L�[�p�b�h�̃|�C���^�̔z��
	std::unique_ptr<CScene3D> m_pDisplayShape;									//�f�B�X�v���C�ɉf��}�`�̃|���S���̃|�C���^

	SHAPE m_DisplayShape;														//�f�B�X�v���C�̐}�`

	//ANSWER_PATTERN m_Answer;													//�����̃p�^�[��
	//int m_nNextSymbolNum;														//���̃V���{���ԍ�
};
#endif