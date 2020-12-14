//*************************************************************************************************************
//
// ��Ǐ��E�B���h�E[���� [DecodingWindow.h]
// Author:IKUTO SEKINE
//
//*************************************************************************************************************
#ifndef _DECODINGWINDOW_H_
#define _DECODINGWINDOW_H_

//-------------------------------------------------------------------------------------------------------------
// �C���N���[�h�t�@�C��
//-------------------------------------------------------------------------------------------------------------
#include "scene.h"
#include "Mylibrary.h"
#include "DecodingTypes.h"

//-------------------------------------------------------------------------------------------------------------
// �O���錾
//-------------------------------------------------------------------------------------------------------------
class CDecodingUI;
class CHash;
class CMouse;

//-------------------------------------------------------------------------------------------------------------
// �N���X��`
//-------------------------------------------------------------------------------------------------------------
class CDecodingWindow
{
public:
	/* �񋓌^��` */
	// UI�^�C�v
	typedef enum
	{
		TYPE_NONE = -1,				// ����
		TYPE_WINDOW ,				// �E�B���h�E
		TYPE_CLOSEBUTTON,			// ����{�^��
		TYPE_SCROLLBAR,				// �X�N���[���o�[
		TYPE_SCROLLHANDLE,			// �X�N���[���n���h��
		TYPE_MAX					// �ő�
	}TYPE;
	// UI�̃e�N�X�`��
	enum
	{
		TEX_NONE = -1,				// �Ȃ�
		TEX_CLOSEBUTTON,			// ����{�^��
		TEX_SCROLLBAR,				// �X�N���[���o�[
		TEX_SCROLLHANDLE,			// �X�N���[���n���h��
		TEX_MAX						// �ő�
	};
	// �E�B���h�E�^�C�v�̃e�N�X�`��
	enum
	{
		TEX_W_NONE = -1,			// �Ȃ�
		TEX_W_TELLTHEPICTURE,		// �ʐ^�������Ă�������
		TEX_W_SHAPEMEMORIZATION,	// �`�̈ËL
		TEX_W_CORDCUTTING,			// �R�[�h��؂�
		TEX_W_MAZE,					// ���H
		TEX_W_SIMON,				// �T�C�����Q�[��
		TEX_W_NOWMAKING,			// ���쒆
		TEX_W_MAX					// �ő�
	};
	/* [mome]
	CB -> CLOSEBUTTON
	SH -> SCROLLHANDLE
	*/
	enum
	{
		CHGCOL_NONE = -1,			// ����
		CHGCOL_CB_PUSH,				// ����{�^������������
		CHGCOL_SH_PINCH,			// �X�N���[���n���h�����܂񂾎�
		CHGCOL_SH_OVERLAP,			// �X�N���[���n���h���Əd�Ȃ�����
		CHGCOL_MAX					// �ő�
	};

	/* �����o�֐� */
	CDecodingWindow();																								// �R���X�g���N�^
	~CDecodingWindow();																								// �f�X�g���N�^

	static void        MakeHash(void);																				// �n�b�V���̍쐬
	static void        ReleaseHash(void);																			// �n�b�V���̊J��
	static HRESULT     Load(void);																					// �ǂݍ���
	static void        UnLoad(void);																				// �J��

	static std::shared_ptr<CDecodingWindow> Create(WINDOW_SETING &Seting);											// ����

	HRESULT            Init(WINDOW_SETING &Seting);																	//������
	void               Update();																					//�X�V
	void               Draw();																						//�`��
	void               InitAppearInfo(void);																		// �o�����̏�����
	void               InitDocumentUVInfo(WINDOW_SETING &Seting);													// �h�L�������g��UV���̏�����

	void               PreparingAppear(void);																		// �o������
	bool               Appearance(void);																			// �o��
	bool               Disappearance(void);																			// ����
	void               Display(void);																				// �\��������
	void               DoNotDisplay(void);																			// �\�������Ȃ�

	inline void        SetSign(int nSign) { if (nSign != 0)m_nSign = abs(nSign) / nSign; }							// �����̐ݒ�
	inline void        SetScal(float fScal) { m_fScal = fScal; }													// �X�P�[���̐ݒ�
	inline static void SetScalMax(float fScal) { m_fSclaMax = fScal; }												// �ő�X�P�[���̐ݒ�
	void               SetWindowTexture(int nIndex);																// �E�B���h�E�e�N�X�`���̐ݒ�
	bool               CloseButtonProc(CMouse *pMouse, D3DXVECTOR2 *pMousePos);										// ����{�^���̏���
	void               ScrollProc(CMouse *pMouse, D3DXVECTOR2 *pMousePos);											// �X�N���[������
	void               MoveScrollHandle(CMouse * pMouse, D3DXVECTOR2 * pMousePos);									// �X�N���[���n���h���𓮂���
	void               MouseWheelScroll(D3DXVECTOR2 * pMousePos);													// �}�E�X�z�C�[���X�N���[��
	void               ScrollHandleMove(D3DXVECTOR2 *pMousePos, float fPosY);										// �X�N���[���n���h���𓮂���
	float              ScrollClamp(D3DXVECTOR2 *pMousePos, float& fPosY);											// �X�N���[���̃N�����v
	void               ScrollScreen(void);																			// ��ʂ̃X�N���[��

private:
	/* �����o�֐� */
	void               InitSeting(WINDOW_SETING &Seting);															// �ݒ�̏�����
	void               MakeUI(void);																				// UI�̍쐬
	void               SetPosAccordingParent(void);																	// �e�ɏ]���Ĉʒu��ݒ肷��
	void               UpdateAppear(void);																			// �o���̍X�V
	bool               UpdateFrame(void);																			// �t���[���̍X�V
	void               ChangeColor(CDecodingUI *pUi, D3DXCOLOR &col);												// �F��ύX
	static void        ReadFromLine(CONST_STRING cnpLine, CONST_STRING cnpEntryType, CONST_STRING cnpEntryData);	// 1�s�������ǂݎ��

	/* �����o�ϐ� */
	static LPDIRECT3DTEXTURE9    m_pTexture[TEX_MAX];																// �e�N�X�`�����
	static LPDIRECT3DTEXTURE9    m_pDocTexture[TEX_W_MAX];															// �E�B���h�E�̃e�N�X�`�����
	static SETINGINFO            m_InitSeting[TYPE_MAX];															// �����ݒ���
	static CHash *               m_pHash;																			// �n�b�V���̃|�C���^
	static int                   m_nFrameMax;																		// �ő�t���[��
	static float                 m_fSclaMax;																		// �X�P�[���̍ő�
	static D3DXCOLOR             m_aChgCol[CHGCOL_MAX];																// �ύX�F
	static float                 m_fWheelForth;																		// �}�E�X�z�C�[���̓�������

	std::shared_ptr<CDecodingUI> m_pUi[TYPE_MAX];																	// UI
	SETINGINFO                   m_Seting[TYPE_MAX];																// �ݒ���
	TYPE                         m_nSelectIndex;																	// �I�����Ă���ԍ�
	int                          m_nFrame;																			// �t���[��
	int                          m_nSign;																			// ����
	float                        m_fScalValue;																		// �X�P�[���ω��l
	float                        m_fScal;																			// �X�P�[��

	// �X�N���[��
	VEC2                         m_VecPinch_Center;																	// �܂񂾓_���璆�S�ւ̃x�N�g��
	float                        m_fScrInitPos;																		// �X�N���[�������ʒu
	CRange<float>                m_ScrollRange;																		// �X�N���[���̉��̈�
	float                        m_fScrollRangeValue;																// �X�N���[���̉���l
	// UV
	FLOAT2                       m_AspectRatio;																		// UV�̃A�X�y�N�g��
	FLOAT2                       m_SizeScal;																		// UV�̃T�C�Y�X�P�[��
};

#endif