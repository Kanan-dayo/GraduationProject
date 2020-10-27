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

	//�}�`
	enum class SHAPE
	{
		NONE = -1,
		CIRCLE,				//�Z
		CROSS,				//�~
		TRIANGLE,			//��
		SQUARE,				//��
		MAX,
	};

	//��萔
	enum class QUESTION
	{
		NONE = -1,
		Q_1,
		Q_2,
		Q_3,
		Q_4,
		MAX,
	};

	enum PLACE
	{
		NONE = -1,
		LEFT_TO_1ST,
		LEFT_TO_2ND,
		LEFT_TO_3RD,
		LEFT_TO_4TH,

	};

	//�ߋ��ɃN���A�����{�^���̏��
	typedef struct
	{
		SHAPE shape;
		PLACE place;
	}MEMORIES;


	CModule_No2_ShapeKeyPad();
	virtual ~CModule_No2_ShapeKeyPad();

	virtual HRESULT Init()			override;			//������
	virtual void Uninit()			override;			//�I��
	virtual void Update()			override;			//�X�V
	virtual void Draw()				override;			//�`��
	virtual void ShowDebugInfo()	override;			//�f�o�b�O���\�L
	void Operation()				override;			//���W���[������

	void CreateDisplayShape();							//�f�B�X�v���C�̐���
	void CreateKeyPad();								//�L�[�p�b�h����
	void CreateProgressLamp();							//�i���̃����v����

	void CheckClear();									//�N���A�������m�F
	void ShapeShuffle();								//�}�`�̃V���b�t��
	void SetDisplayShape(int nShape);					//�f�B�X�v���C�̐}�`�ݒ�

	void SetNextPushKey();								//���ɉ����L�[�̐ݒ�
	void SetNextPushKey_FromShape(SHAPE shape);			//�}�`����Ɏ��ɉ����L�[�ݒ�
	void SetNextPushKey_FromPlace(PLACE nPlace);			//�ꏊ����Ɏ��ɉ����L�[�ݒ� �����牽�Ԗڂ�

	void QuestionClear();								//���N���A

private:
	std::vector<std::shared_ptr<CModule_Parts_No2_ShapeKey>> m_pKeyPadList;				//�L�[�p�b�h�̃|�C���^�̔z��
	std::unique_ptr<CScene3D> m_pDisplayShape;									//�f�B�X�v���C�ɉf��}�`�̃|���S���̃|�C���^
	std::vector<MEMORIES> m_Memories;											//�ߋ��ɂǂ̃{�^�����������L������
	std::vector<std::shared_ptr<CScene3D>> m_pProgressLamp;						//�i���x�̃����v

	SHAPE m_DisplayShape;														//�f�B�X�v���C�̐}�`
	QUESTION m_NowQuestion;														//���݉���ڂ�
	PLACE m_nSelectNum;															//�I��ԍ�

	int m_nQuestionChangeCnt;													//���؂�ւ����̃J�E���g

};
#endif