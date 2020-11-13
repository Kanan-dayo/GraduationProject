//*************************************************************************************************************
//
// �G�p�̃y������[PaintingPen.h]
// Author:IKUTO SEKINE
//
//*************************************************************************************************************
#ifndef _PAINTINGPEN_H_
#define _PAINTINGPEN_H_

//-------------------------------------------------------------------------------------------------------------
// �C���N���[�h�t�@�C��
//-------------------------------------------------------------------------------------------------------------
#include "Mylibrary.h"

//-------------------------------------------------------------------------------------------------------------
// �N���X��`
//-------------------------------------------------------------------------------------------------------------
class CMouse;
class CPaintingPen
{
public:
	typedef enum
	{
		MODE_NONE = - 1,													// ����
		MODE_BRUSH,															// �u���V
		MODE_ERASER,														// �����S��
		MODE_MAX															// �ő�
	}MODE;

	CPaintingPen() {};														// �R���X�g���N�^
	~CPaintingPen() {};														// �f�X�g���N�^
	
	static void Load(void);													// �ǂݍ���
	static HRESULT          LoadError(void);								// �G���[�̌��o

	void Init(void);														// ������
	void Uninit(void);														// �I��
	void Update(void);														// �X�V

	void PaintCol(D3DXCOLOR *pCol);											// �F��h��

	void PosCalculation(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPlaneNor);			// �ʒu���Z�o

	static CPaintingPen *Create(void);										// ����

	// �ݒ�֐�
	static void SetFromString(CONST_STRING str);							// �����񂩂�ݒ肷��
	void SetCapsule(void);													// �J�v�Z���̐ݒ�
	void SetMode(MODE mode);												// ���[�h�̐ݒ�
	inline void SetRadius(const float &fRadius) { m_Capsule.fRadius = fRadius; }
	inline void SetPosOld(void) { m_posOld = m_pos; }						// �O��ʒu�̐ݒ�

	// �擾�֐�
	inline FLOAT2 *GetPos(void) { return &m_pos; }							// �ʒu�̎擾
	inline FLOAT2 *GetPosOld(void) { return &m_posOld; }					// �O��ʒu�̎擾
	inline CAPSULE_2D *GetCapsule(void) { return &m_Capsule; }				// �J�v�Z���̎擾
	inline MODE &GetMode(void) { return m_mode; }							// ���[�h�̎擾

private:
	/* �����o�֐� */
	static int ConvModeToCursorType(MODE& mode);							// �y���̃��[�h����J�[�\���^�C�v�ɕϊ�
	void PaintBrush(D3DXCOLOR *pCol);										// �u���V�œh��
	void PaintEraser(D3DXCOLOR *pCol);										// �����S���œh��

	/* �����o�ϐ� */
	static float m_aSetingRadius[MODE_MAX];									// �ݒ�p���a
	D3DXMATRIX*  m_pMtxView;												// �}�g���b�N�X�����[
	D3DXMATRIX*  m_pMtxProj;												// �v���W�F�N�V�����}�g���b�N�X
	bool         m_bPaint;													// �h��t���O
	MODE         m_mode;													// ���[�h
	FLOAT2       m_pos;														// �ʒu
	FLOAT2       m_posOld;													// �O��̈ʒu
	CAPSULE_2D   m_Capsule;													// �J�v�Z�����
};


#endif