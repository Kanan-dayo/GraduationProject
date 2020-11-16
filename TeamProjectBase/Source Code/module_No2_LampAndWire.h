//------------------------------------------------------------------------------
//
//���W���[���̃����v�ƃ��C���[�̂�̏���  [Module_No2_LampAndWire.h]
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
class CModule_Parts_No2_Wire;
class CScene3D;

class CModule_No2_LampAndWire : public CModule_Base
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

	CModule_No2_LampAndWire();
	virtual ~CModule_No2_LampAndWire();

	virtual HRESULT Init()				override;			//������
	virtual void Update()				override;			//�X�V
	virtual void Draw()					override;			//�`��
	virtual void ShowDebugInfo()		override;			//�f�o�b�O���\�L
	void Operation_Keyboard()			override;			//���W���[������ �L�[�{�[�h
	void Operation_Mouse()				override;			//���W���[������ �}�E�X
	void ModuleAction()					override;			//���W���[���̃A�N�V����
	void ModuleCancel()					override;			//���W���[���̑I������

private:
	Vec<S_ptr<CModule_Parts_No2_Wire>> m_pWireList;		//���C���[�̃��X�g
	WIRE m_NowSelectWire;								//���ݑI�����Ă��郏�C���[
	int m_nSelectPlace;									//���ݑI�����Ă���ꏊ

	int m_nRedLampNum;									//�Ԃ������v��
	int m_nBlueLampNum;									//�������v��

	void CreateWire();									//���C���[����
	void CreateModuleLamp();							//�����v����
	void SetToCutWire();								//�J�b�g���郏�C���[�ݒ�

	void WireCut();										//���C���[�J�b�g
	void CheckClear();									//�N���A�������`�F�b�N

	//�F����ɐ؂郏�C���[�ݒ�
	void SetCutWire_FromPlace(int nPlace);						//�ꏊ����ɐ؂郏�C���[�ݒ�
	void SetCutWire_FromLampRule();								//�����v���[��

//�e���v���[�g�֐�
//�F����ɐ؂郏�C���[��ݒ�
//�w�肵���F�E���A�����ɂ��Ή�
//���C���F�@Itr_Begin Itr_End �؂�؂�Ȃ��t���O�@�w�肵���F�̐ݒ肩�@�����̃R�[�h���@�E���̃R�[�h��
	template<class Itr>
	inline void SetCutWire_FromColor(WIRE wire, Itr begin, Itr end, bool bFlag, bool bThisCode = true, bool bLeft = false, bool bRight = false)
	{
		//�w�肵���F�̃C�e���[�^�擾
		auto itr = std::find_if(begin, end,
			[wire](S_ptr<CModule_Parts_No2_Wire> &ptr) {return ptr->GetWire() == wire; });

		//�C�e���[�^�ł�����
		if (itr != end)
		{
			//���̃R�[�h���ǂ���
			if (bThisCode)
			{
				//�N���A�t���O�𗧂Ă�
				itr->get()->SetClearFlag(bFlag);
			}
			//�����̃R�[�h��
			if (bLeft)
			{
				//���ŃC�e���[�^����
				auto LocalItr = itr;

				//�C�e���[�^���͈͓���������
				if (LocalItr != begin)
				{
					//���O
					--LocalItr;

					//�N���A�t���O�ݒ�
					LocalItr->get()->SetClearFlag(true);
				}
			}
			//�E���̃R�[�h��
			if (bLeft)
			{
				//���ŃC�e���[�^����
				auto LocalItr = itr;


				++LocalItr;

				//����̃C�e���[�^���͈͓���������
				if (LocalItr < end)
				{

					//�N���A�t���O�ݒ�
					LocalItr->get()->SetClearFlag(true);
				}
			}
		}
	}
};
#endif