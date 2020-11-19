//*************************************************************************************************************
//
// ��Ǐ��̃}�l�[�W���[[���� [DecodingManager.h]
// Author:IKUTO SEKINE
//
//*************************************************************************************************************
#ifndef _DECODINGMANAGER_H_
#define _DECODINGMANAGER_H_

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
class CDecodingManager : public CScene
{
public:
	/* �񋓌^��` */
	enum
	{
		UI_NONE = -1,			// ����
		UI_BACKLIGHT,			// �o�b�N���C�g
		UI_TELLTHEPICTURE,		// �ʐ^�������Ă�������
		UI_SHAPEMEMORIZATION,	// �`�̈ËL
		UI_CORDCUTTING,			// �R�[�h��؂�
		UI_MAZE,				// ���H
		UI_SIMON,				// �T�C�����Q�[��
		UI_NOWMAKING,			// ���쒆
		//UI_DOCUMENT,			// �h�L�������g
		//UI_CLOSE,				// ����
		//UI_SCROLLBAR,			// �X�N���[���o�[
		//UI_SCROLLHANDLE,		// �X�N���[���n���h��
		UI_MAX					// �ő吔
	};

	enum
	{
		TEX_BACKLIGHT,
		TEX_TELLTHEPICTURE,
		TEX_SHAPEMEMORIZATION,
		TEX_CORDCUTTING,
		TEX_MAZE,
		TEX_SIMON,
		TEX_NOWMAKING,
		//TEX_D_TELLTHEPICTURE,
		//TEX_D_SHAPEMEMORIZATION,
		//TEX_D_CORDCUTTING,
		//TEX_D_MAZE,
		//TEX_D_SIMON,
		//TEX_D_NOWMAKING,
		//TEX_CLOSE,
		//TEX_SCROLLBAR,
		//TEX_SCROLLHANDLE,
		TEX_MAX
	};

	enum MODE
	{
		MODE_SELECT,			// �I��
		MODE_CONNECT,			// �ڑ�
		MODE_SHOW,				// ��Ǐ���\�����Ă���
		MODE_MAX				// �ő�
	};

	/* �����o�֐� */
	CDecodingManager();									// �R���X�g���N�^
	~CDecodingManager();								// �f�X�g���N�^

	static void    MakeHash(void);						// �n�b�V���̍쐬
	static void    ReleaseHash(void);					// �n�b�V���̊J��

	static HRESULT Load(void);							// �ǂݍ���
	static void    Unload(void);						// �J��

	static std::shared_ptr<CDecodingManager>Create(void);	// ����

	HRESULT        Init();								//������
	void           Update();							//�X�V
	void           Draw();								//�`��
	void           ShowDebugInfo() {}					//�f�o�b�O���\�L

	void           SstMode(MODE mode);					// ���[�h�̐ݒ�

	static CHash * GetHash(void) { return m_pHash; }	// �n�b�V���|�C���^�̎擾
	CDecodingUI * GetUi(int nIndex) { return m_pUi[nIndex].get(); }

private:
	/* �����o�֐� */
	void CreateUi(void);								// UI�̐���
	void SetPosAccordingParent(void);					// �e�ɏ]���Ĉʒu��ݒ肷��
	void InitDocumentUVInfo(void);						// �h�L�������g��UV���̏�����
	void InitConnect(void);								// �ڑ����[�h�̏�����
	void UpdateSelect(void);							// �I������Ƃ��̍X�V����
	void UpdateConnect(void);							// �ڑ����[�h�X�V����
	void UpdateShow(void);								// ��Ǐ���\�����Ă���Ƃ��̍X�V����

	void CloseButtonProc(CMouse *pMouse, D3DXVECTOR2 *pMousePos);		// ����{�^���̏���
	void ScrollProc(CMouse *pMouse, D3DXVECTOR2 *pMousePos);			// �X�N���[���̏���
	void PinchScrollHandle(CMouse * pMouse, D3DXVECTOR2 * pMousePos);	// �X�N���[���n���h�����܂�
	void MoveScrollHandle(CMouse * pMouse, D3DXVECTOR2 * pMousePos);	// �X�N���[���n���h���𓮂���
	void MouseWheelScroll(D3DXVECTOR2 * pMousePos);						// �}�E�X�z�C�[���X�N���[��
	float ScrollClamp(D3DXVECTOR2 *pMousePos, float fPosY);				// �X�N���[���̃N�����v
	void ScrollThroughDocument(void);									// �h�L�������g�̃X�N���[��

	void DisplayDocumentsInPlace(void);					// �h�L�������g�����̈ʒu�ɕ\������

	void AppeaDocument(int nCntUi);						// �h�L�������g�̏o��
	void DisAppeaDocument(void);						// �h�L�������g�̏���

	static void ReadFromLine(CONST_STRING cnpLine, CONST_STRING cnpEntryType, CONST_STRING cnpEntryData);	// 1�s�������ǂݎ��

	/* �����o�ϐ� */
	static CHash *               m_pHash;				// �n�b�V���̃|�C���^
	static LPDIRECT3DTEXTURE9    m_pTexture[TEX_MAX];	// �e�N�X�`�����
	static SETINGINFO            m_Seting[UI_MAX];		// �ݒ���
	static int                   m_nFrameMax;			// �ő�t���[��
	std::shared_ptr<CDecodingUI> m_pUi[UI_MAX];			// UI
	MODE                         m_mode;				// ���[�h
	MODE                         m_modeNext;			// ���̃��[�h
	int                          m_nSelectIndex;		// �I�����Ă���ԍ�

	int                          m_nFrame;				// �t���[���J�E���g
	//int                          m_nSign;				// ����
	//float                        m_fScalValue;			// �g��l�ω��l
	//float                        m_fScal;				// �g��l

	//VEC2                         m_VecPinch_center;		// �܂񂾓_���璆�S�ւ̂̃x�N�g��

	//RANGE                        m_ScrollRange;			// �X�N���[���̉��̈�
	//float                        m_fScrollRangeValue;	// �X�N���[���̉���l

};

#endif
