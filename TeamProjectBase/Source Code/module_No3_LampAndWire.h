//------------------------------------------------------------------------------
//
//���W���[���̃����v�ƃ��C���[�̂�̏���  [Module_No3_LampAndWire.h]
//Author:Yoshiki Hosoya
//
//------------------------------------------------------------------------------
#ifndef _MODULE_NO3_LAMPANDWIRE_H_
#define _MODULE_NO3_LAMPANDWIRE_H_
//------------------------------------------------------------------------------
//�C���N���[�h
//------------------------------------------------------------------------------
#include "main.h"
#include "module_base.h"
//------------------------------------------------------------------------------
//�N���X��`
//------------------------------------------------------------------------------
class CModule_Parts_No3_Wire;

class CModule_No3_LampAndWire : public CModule_Base
{
public:

	enum WIRE
	{
		NONE = -1,
		RED,			//��
		BLUE,			//��
		GREEN,			//��
		YELLOW,			//��
		WHITE,			//��
		BLACK,			//��
		MAX,
	};

	CModule_No3_LampAndWire();
	virtual ~CModule_No3_LampAndWire();

	virtual HRESULT Init()			override;			//������
	virtual void Update()			override;			//�X�V
	virtual void Draw()				override;			//�`��
	virtual void ShowDebugInfo()	override;			//�f�o�b�O���\�L
	void Operation()					override;			//���W���[������
private:
	Vec<S_ptr<CModule_Parts_No3_Wire>> m_pWireList;		//���C���[�̃��X�g
	WIRE m_NowSelectWire;								//���ݑI�����Ă��郏�C���[
	int m_nSelectPlace;									//���ݑI�����Ă���ꏊ

	int m_nRedLampNum;									//�Ԃ������v��
	int m_nBlueLampNum;									//�������v��

	void CreateWire();									//���C���[����
	void CreateLamp();									//�����v����
	void SetToCutWire();								//�J�b�g���郏�C���[�ݒ�

	void SetCutWire_FromColor(WIRE wire);						//�F����ɐ؂郏�C���[�ݒ�
	void SetCutWire_FromPlace(int nPlace);						//�ꏊ����ɐ؂郏�C���[�ݒ�
};
#endif