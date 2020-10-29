//------------------------------------------------------------------------------
//
//�������̐����̏���  [multinumber.h]
//Author:Yoshiki Hosoya
//
//------------------------------------------------------------------------------
#ifndef _MULTINUMBER_H_
#define _MULTINUMBER_H_
//------------------------------------------------------------------------------
//�C���N���[�h
//------------------------------------------------------------------------------
#include "main.h"
#include "scenebase.h"
//------------------------------------------------------------------------------
//�}�N��
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//�N���X��`
//------------------------------------------------------------------------------
class CSceneBase;

class CMultiNumber : public CSceneBase
{
public:

	//�i���o�[�̃G�t�F�N�g
	enum class NUMBER_TYPE
	{
		NUMBER_2D,							//2D
		NUMBER_3D,							//3D

	};
	//�i���o�[�̃G�t�F�N�g
	enum class NUMBER_EFFECT
	{
		NONE,								//�G�t�F�N�g����
		FLASHING,							//�_�� �\����\��
		FLASHING_RED_YELLOW,				//�_�� �ԉ��F

	};

	CMultiNumber();
	~CMultiNumber();
	virtual HRESULT Init()						override;				//������
	virtual void Uninit()						override;				//�I��
	virtual void Update()						override;				//�X�V
	virtual void Draw()							override;				//�`��
	virtual void ShowDebugInfo()				override;				//�f�o�b�O���\�L
	void SetPos(D3DXVECTOR3 const &pos)			override;				//���W�ݒ�
	void SetSize(D3DXVECTOR3 const &size)		override;				//�T�C�Y�ݒ�
	void SetColor(D3DXCOLOR const &col)			override;				//�F�ݒ�

	static S_ptr<CMultiNumber> Create(D3DXVECTOR3 const &pos, D3DXVECTOR3 const &onesize,
		int const nValue, int const  nDigits, NUMBER_TYPE const type, CScene::OBJTYPE const objtype);	//��������

	//Set�֐�
	void SetMultiNumber(int nValue);										//�X�R�A�ݒ菈��
	void Settype(NUMBER_EFFECT const effect);								//��ސݒ�

	const NUMBER_EFFECT GetNumberType() { return m_NumberEffect; };			//��ގ擾

private:
	Vec<U_ptr<CSceneBase>> m_pNumberList;					//�i���o�[�̃|�C���^�̃��X�g
	NUMBER_EFFECT m_NumberEffect;											//���
	int m_nValue;															//�l
	int m_nCnt;																//�_�ŃJ�E���g

};

#endif