//*************************************************************************************************************
//
// �G�̏��� [picture.h]
// Author:IKUTO SEKINE
//
//*************************************************************************************************************
#ifndef _PICTURE_H_
#define _PICTURE_H_

//-------------------------------------------------------------------------------------------------------------
// �C���N���[�h�t�@�C��
//-------------------------------------------------------------------------------------------------------------
#include "scene.h"
#include "Mylibrary.h"

//-------------------------------------------------------------------------------------------------------------
// �N���X��`
//-------------------------------------------------------------------------------------------------------------
class CPaintingPen;
class CPicture : public CScene
{
public:
	// �t���O
	enum
	{
		FLAG_NONE = -1,			// ����
		FLAG_DISP,				// �`��
		FLAG_UPDATE,			// �X�V
		FLAG_MAX				// �ő�
	};
	// �}�X�N�t���O�̒l
	enum
	{
		MASK_NONE = 0,			// �Ȃ�
		MASK_DISP = 0b0001,		// �`��
		MASK_UPDATE = 0b0010,	// �X�V
		MASK_MAX = 0b0011,		// �ő�
	};
	// ���[�h
	typedef enum
	{
		MODE_EDIT = 0,	// �ҏW
		MODE_EXHI,		// �W��
		MODE_MAX		// �ő吔
	} MODE;

	/* �����o�֐� */
	inline                  CPicture() :CScene(){}																			// �R���X�g���N�^
	inline                  ~CPicture();																					// �f�X�g���N�^
	HRESULT                 Init();																							// ������
	void                    Update();																						// �X�V
	void                    Draw();																							// �`��
	inline void             ShowDebugInfo() {};																				// �f�o�b�O���\�L

	static HRESULT          Load(void);																						// �ǂݍ���
	static void             InitStaticMember(void);																			// �ÓI�����o�̏�����
	static void             UninitStaticMember(void);																		// �ÓI�����o�̏I��

	void                    MatrixCal(void);																				// �}�g���b�N�X�̌v�Z
	void                    Writing(void);																					// �������ݏ���
	void                    Reading(CString& file);																			// �ǂݍ���
	static void             TexterReadFromLine(CONST_STRING cnpLine, void*pOut);											// �e�N�X�`������1�s�������ǂݎ��

	// �ݒ�֐�
	inline void             SetPos(CONST D3DXVECTOR3 &pos) { m_trans.pos = pos; }											// �ʒu�̐ݒ�
	inline void             SetRot(CONST D3DXVECTOR3 &rot) { m_trans.rot = rot; }											// �����̐ݒ�
	inline void             SetScal(CONST D3DXVECTOR3 &scal) { m_trans.scal = scal; }										// �X�P�[���̐ݒ�
	inline void             SetFlag(const int nMask) { m_Flags.cValue = nMask; }											// �t���O�̐ݒ�
	inline void             SetMode(MODE mode) {m_mode = mode; }															// ���[�h�̐ݒ�
	inline void             BuildFlag(const int nFlagIndex) { Mybfunc_bit_set(m_Flags.cValue, nFlagIndex); }				// �t���O�����Ă�
	inline void             BreakFlag(const int nFlagIndex) { Mybfunc_bit_clear(m_Flags.cValue, nFlagIndex); }				// �t���O����

	// �擾�֐�
	inline UVSHORT*         GetFlag(void) { return &m_Flags.cValue; }														// �t���O�̎擾

	// �N���G�C�g�֐�
	static std::shared_ptr<CPicture>Create(CONST D3DXVECTOR3 &pos, CONST D3DXVECTOR3 &rot , CONST MODE mode = MODE_EDIT);	// ����
private:
	/* �����Ŏg���֐� */
	void                    MakeTexture(LPDIRECT3DDEVICE9 pDevice);															// �e�N�X�`���̍쐬
	void                    MakeVertex(LPDIRECT3DDEVICE9 pDevice);															// ���_���̍쐬
	void                    InitTextureColor(void);																			// �e�N�X�`���J���[�̏�����
	static void             ReadFromLine(CONST_STRING Line);																// 1�s�������ǂݎ��
	static void             CreatePixelPos(void);																			// �s�N�Z���ʒu�̐���
	static void             ReleasePixelPos(void);																			// �s�N�Z���ʒu�̊J��
	static void             ReleasePen(void);																				// �y���̊J��
	void                    PaintProc(void);																				// �h�鏈��
	bool                    GetMousePosOnPicture(void);																		// �G��̃}�E�X�ʒu�̎擾

	/* �����o�ϐ� */
	static INTEGER2         m_nNumPixelBlock;																				// �s�N�Z����
	static FLOAT2           m_size;																							// �傫��
	static D3DXVECTOR3      m_PlaneNor;																						// ���ʂ̖@��
	static D3DXVECTOR2      m_PixelSize;																					// �s�N�Z���T�C�Y
	static UINT             m_nNumDataMax;																					// �ő�f�[�^��
	static CPaintingPen*    m_pPen;																							// �y���̃|�C���^
	static D3DXVECTOR2      m_PixelSizehalf;																				// �s�N�Z���T�C�Y�̔���
	static D3DXVECTOR2*     m_pPixelPos;																					// �s�N�Z���ʒu�̃|�C���^
	static UINT             m_nNumMakeFile;																					// �t�@�C�����������
	static CString          m_WriteToFile;																					// �������ݐ�̃@�C����
	LPDIRECT3DVERTEXBUFFER9 m_pVtexBuff;																					// ���_�o�b�t�@�̃|�C���^
	LPDIRECT3DTEXTURE9      m_pTexture;																						// �e�N�X�`���|�C���^
	UBITS_4                 m_Flags;																						// �t���O
	TRANSFORM               m_trans;																						// �g�����X���
	MODE                    m_mode;																							// ���[�h
};


#endif // !_PICTURE_H_
