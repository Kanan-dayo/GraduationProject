//*************************************************************************************************************
//
// ��Ǐ���UI[���� [DecodingUI.h]
// Author:IKUTO SEKINE
//
//*************************************************************************************************************
#ifndef _DECODINGUI_H_
#define _DECODINGUI_H_

//-------------------------------------------------------------------------------------------------------------
// �C���N���[�h�t�@�C��
//-------------------------------------------------------------------------------------------------------------
#include "scene.h"
#include "Mylibrary.h"
#include "DecodingTypes.h"

//-------------------------------------------------------------------------------------------------------------
// �N���X��`
//-------------------------------------------------------------------------------------------------------------
class CDecodingUI : public CScene
{
public:
	/* �\���̒�` */
	// �|���S���̒��_���
	//typedef struct POLYVERTEXS
	//{
	//	union {
	//		struct {
	//			FLOAT3 pos0;
	//			FLOAT3 pos1;
	//			FLOAT3 pos2;
	//			FLOAT3 pos3;
	//		};
	//		FLOAT3 m[4];
	//	};

	//} POLYVERTEXS;

	/* �����o�֐� */
	CDecodingUI();																								// �R���X�g���N�^
	~CDecodingUI();																								// �f�X�g���N�^

	static std::shared_ptr<CDecodingUI>Create(SETINGINFO Seting);												// ����

	HRESULT                   Init();																			//������
	void                      Update();																			//�X�V
	void                      Draw();																			//�`��
	void                      ShowDebugInfo() {}																//�f�o�b�O���\�L

	void                      UpdateVertex(bool bPos, bool bCol);												// ���_���̍X�V
	void                      UpdateVertex(D3DXVECTOR3* pPos, D3DXVECTOR2* pSize, D3DXCOLOR *pCol);				// ���_���̍X�V

	// �ݒ�֐�
	void                      SetFromSetingInfo(CONST SETINGINFO & Seting);																// �ݒ�p��񂩂�ݒ肷��
	inline void               BindTexture(LPDIRECT3DTEXTURE9 pTexture) { m_pTexture = pTexture; }										// �e�N�X�`�������т���
	inline void               SetPos(CONST D3DXVECTOR3 &pos) { m_pos = pos; }															// �ʒu�̐ݒ�
	inline void               SetSize(CONST D3DXVECTOR2 &size) { m_size = size; }														// �T�C�Y�̐ݒ�
	inline void               SetCol(CONST D3DXCOLOR &col) { m_col = col; }																// �F�̐ݒ�
	inline void               SetAngle(const float &fAngle) { m_fAngle = fAngle; }														// �p�x�̐ݒ�
	inline void               SetOriginType(const ORIGINVERTEXTYPE nOriginType) { m_OriginType = nOriginType; }							// ���_�^�C�v�̐ݒ�
	inline void               SetDispFlag(const bool bDisp) { m_bDisp = bDisp; }														// �`��t���O�̐ݒ�
	inline bool               SetWithPosPtr(D3DXVECTOR3 *pPos)   { if (pPos != NULL) { m_pos = *pPos; return true; } return false; }		// �ʒu�|�C���^�ňʒu��ݒ�
	inline bool               SetWithSizePtr(D3DXVECTOR2 *pSize) { if (pSize != NULL) { m_size = *pSize; return true; } return false; }	// �傫���|�C���^�ő傫����ݒ�
	inline bool               SetWithColPtr(D3DXCOLOR *pCol)     { if (pCol != NULL) { m_col = *pCol; return true; } return false; }		// �F�|�C���^�ŐF��ݒ�

	// �擾�֐�
	inline LPDIRECT3DTEXTURE9 GetTexture(void) { return m_pTexture; }											// �e�N�X�`���̎擾
	inline FLOAT3&            GetPos(void) { return m_pos; }													// �ʒu�̎擾
	inline FLOAT2&            GetSize(void) { return m_size; }													// �傫���̎擾
	inline D3DXCOLOR&         GetCol(void) { return m_col; }													// �F�̎擾
	inline float&             GetAngle(void) { return m_fAngle; }												// �p�x�̎擾
	inline ORIGINVERTEXTYPE&  GetOriginType(void) { return m_OriginType; }										// ���_�^�C�v�̎擾
	inline bool               GetDispFlag(void) { return m_bDisp; }												// �`��t���O�̎擾
	inline FLOAT3*            GetPosPtr(void) { return &m_pos; }												// �ʒu�|�C���^�̎擾
	inline FLOAT2*            GetSizePtr(void) { return &m_size; }												// �傫���|�C���^�̎擾
	inline D3DXCOLOR*         GetColPtr(void) { return &m_col; }												// �F�|�C���^�̎擾
	inline float*             GetAnglePtr(void) { return &m_fAngle; }											// �p�x�|�C���^�̎擾
	inline ORIGINVERTEXTYPE*  GetOriginTypePtr(void) { return &m_OriginType; }									// ���_�^�C�v�|�C���^�̎擾
	inline bool*              GetDispFlagPtr(void) { return &m_bDisp; }											// �`��t���O�|�C���^�̎擾
private:
	/* �����o�֐� */
	void MakeVertex(LPDIRECT3DDEVICE9 pDevice);																	// ���_���̍쐬
	void SetVatexPos(VERTEX_2D *pVtx, ORIGINVERTEXTYPE type, D3DXVECTOR3 * pPos, D3DXVECTOR2 * pSize, float fRotation);	// ���_�ʒu�̐ݒ�
	void SetVatexCol(VERTEX_2D *pVtx);																			// ���_�J���[�̐ݒ�



	/* �����o�ϐ� */
	static const float      m_fHalfPi;				// �~�����̔����̒l
	static const float      m_fMinHalfPi;			// �~�����̔����̕��̒l
	LPDIRECT3DTEXTURE9      m_pTexture;				//�e�N�X�`���ւ̃|�C���^
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;				//���_�o�b�t�@�ւ̃|�C���^
	FLOAT3                  m_pos;					// �ʒu
	FLOAT2                  m_size;					// �T�C�Y
	D3DXCOLOR               m_col;					// �F
	float                   m_fAngle;				// �p�x
	ORIGINVERTEXTYPE        m_OriginType;			// ���_�^�C�v
	bool                    m_bDisp;				// �`��t���t���O
};

#endif