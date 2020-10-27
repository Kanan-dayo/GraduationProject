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
class CPaintingPen
{
public:
	typedef enum
	{
		MODE_NONE,										// ����
		MODE_BRUSH,										// �u���V
		MODE_ERASER,									// �����S��
		MODE_MAX										// �ő�
	}MODE;

	CPaintingPen() {};									// �R���X�g���N�^
	~CPaintingPen() {};									// �f�X�g���N�^

	void Init(void);									// ������
	void Uninit(void);									// �I��
	void Update(void);									// �X�V

	void PaintCol(D3DXCOLOR *pCol);						// �F��h��

	inline void Set(MODE mode) { m_mode = mode; }		// �ݒ�
private:
	void PaintBrush(D3DXCOLOR *pCol);					// �u���V�œh��
	void PaintEraser(D3DXCOLOR *pCol);					// �����S���œh��

	MODE m_mode;
	VEC3 m_NomDire;
	FLOAT3 m_pos;
};


#endif