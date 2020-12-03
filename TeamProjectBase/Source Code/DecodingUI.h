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
	/* �񋓌^�\�� */
	typedef enum
	{
		STATE_NONE = -1,
		STATE_NORMAL,
		STATE_OVERLAP,
		STATE_MAX
	} STATE;

	/* �\���̒�` */
	// �|���S���̒��_���
	typedef struct _POLYVERTEXS
	{
		_POLYVERTEXS() {}																						// �R���X�g���N�^
		_POLYVERTEXS(FLOAT3 rhs) : pos0(rhs), pos1(rhs), pos2(rhs), pos3(rhs) {}								// �R���X�g���N�^
		_POLYVERTEXS(FLOAT3 _0, FLOAT3 _1, FLOAT3 _2, FLOAT3 _3) :pos0(_0), pos1(_1), pos2(_2), pos3(_3) {}		// �R���X�g���N�^
		~_POLYVERTEXS() {}																						// �f�X�g���N�^
		union {
			struct {
				FLOAT3 pos0;
				FLOAT3 pos1;
				FLOAT3 pos2;
				FLOAT3 pos3;
			};
			FLOAT3 m[4];
		};
	} POLYVERTEXS;

	typedef struct _PARENT
	{
		_PARENT()
		{
			pParent = nullptr;
			vecParent = MYLIB_VEC3_UNSET;
		}
		~_PARENT()
		{

		}
		CDecodingUI* pParent;				// �e���
		VEC3         vecParent;				// �e�Ƃ̃x�N�g��
	}PARENT;



	/* �����o�֐� */
	CDecodingUI();
	~CDecodingUI();

	static std::shared_ptr<CDecodingUI>Create(SETINGINFO Seting);												// ����

	HRESULT                   Init();																			//������
	void                      Update();																			//�X�V
	void                      Draw();																			//�`��
	void                      ShowDebugInfo() {}																//�f�o�b�O���\�L

	void                      UpdateVertex(bool bPos, bool bCol = false, bool bTex = false);												// ���_���̍X�V
	void                      UpdateVertex(D3DXVECTOR3* pPos, D3DXVECTOR2* pSize = NULL, D3DXCOLOR *pCol = NULL, POLYVERTEXSUVINFO * pTex = NULL);				// ���_���̍X�V

	void                      UpdateState(void);

	// �Փ˔���
	bool Collision2D(CONST D3DXVECTOR2 &pos);

	// �ݒ�֐�
	void                      SetParent(CDecodingUI *pParent);
	void                      SetFromSetingInfo(CONST SETINGINFO & Seting);																// �ݒ�p��񂩂�ݒ肷��
	inline void               BindTexture(LPDIRECT3DTEXTURE9 pTexture) { m_pTexture = pTexture; }										// �e�N�X�`�������т���
	inline void               SetPos(CONST D3DXVECTOR3 &pos) { m_pos = pos; }															// �ʒu�̐ݒ�
	inline void               SetPosX(const float posX) { m_pos.x = posX; }															// �ʒu�̐ݒ�
	inline void               SetPosY(const float posY) { m_pos.y = posY; }															// �ʒu�̐ݒ�
	inline void               SetSize(CONST D3DXVECTOR2 &size) { m_size = size; }														// �T�C�Y�̐ݒ�
	inline void               SetCol(CONST D3DXCOLOR &col) { m_col = col; }																// �F�̐ݒ�
	inline void               SetAngle(const float &fAngle) { m_fAngle = fAngle; }														// �p�x�̐ݒ�
	inline void               SetOriginType(const ORIGINVERTEXTYPE nOriginType) { m_OriginType = nOriginType; }							// ���_�^�C�v�̐ݒ�
	inline void               SetDispFlag(const bool bDisp) { m_bDisp = bDisp; }														// �`��t���O�̐ݒ�
	inline void               SetTex(POLYVERTEXSUVINFO & tex) { m_tex = tex; }															// UV���W
	inline bool               SetWithPosPtr(D3DXVECTOR3 *pPos)   { if (pPos != NULL) { m_pos = *pPos; return true; } return false; }	// �ʒu�|�C���^�ňʒu��ݒ�
	inline bool               SetWithSizePtr(D3DXVECTOR2 *pSize) { if (pSize != NULL) { m_size = *pSize; return true; } return false; }	// �傫���|�C���^�ő傫����ݒ�
	inline bool               SetWithColPtr(D3DXCOLOR *pCol)     { if (pCol != NULL) { m_col = *pCol; return true; } return false; }	// �F�|�C���^�ŐF��ݒ�
	inline bool               SetWithTexPtr(POLYVERTEXSUVINFO * pTex) { if (pTex != NULL) { m_tex = *pTex; return true; } return false; }
	inline void               SetSelectFlag(bool bSelect) { m_bSelect = bSelect; }														// �I���t���O�̐ݒ�
	inline void               SetState(STATE state) { m_state = state; }																// ��Ԃ̐ݒ�
	inline void               SetStateOld(STATE state) { m_stateOld = state; }															// �O��̏�Ԃ̐ݒ�
	inline void               SetStateSwitchFlag(bool bStateSwitch) { m_bStateSwitch = bStateSwitch; }									// ��Ԑ؂�ւ��t���O

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
	inline bool               GetSelectFlag(void) { return m_bSelect; }											// �I���t���O�̎擾
	inline PARENT*            GetParent(void) { return &m_Parent; }
	inline POLYVERTEXSUVINFO* GetTex(void) { return &m_tex; }
	inline STATE&             GetState(void) { return m_state; }
	inline STATE&             GetStateOld(void) { return m_stateOld; }
	inline bool               GetStateSwitchFlag(void) { return m_bStateSwitch; }

private:
	/* �����o�֐� */
	void MakeVertex(LPDIRECT3DDEVICE9 pDevice);																	// ���_���̍쐬
	void SetVatexPos(VERTEX_2D *pVtx, ORIGINVERTEXTYPE type, D3DXVECTOR3 * pPos, D3DXVECTOR2 * pSize, float fRotation);	// ���_�ʒu�̐ݒ�
	void SetVatexCol(VERTEX_2D *pVtx);																			// ���_�J���[�̐ݒ�
	void SetVatexUV(VERTEX_2D *pVtx);
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
	POLYVERTEXS             m_Vertexs;				// ���_���
	PARENT                  m_Parent;				// �e���
	POLYVERTEXSUVINFO       m_tex;					// UV���W
	bool                    m_bSelect;				// �I������Ă���
	STATE                   m_state;				// ���
	STATE                   m_stateOld;				// �O��̏��
	bool                    m_bStateSwitch;			// ��Ԃ��؂�ւ�����t���O
};

#endif