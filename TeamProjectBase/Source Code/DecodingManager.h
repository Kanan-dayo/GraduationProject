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
class CDecodingWindow;
class CHash;
class CMouse;
//-------------------------------------------------------------------------------------------------------------
// �N���X��`
//-------------------------------------------------------------------------------------------------------------
class CDecodingManager : public CScene
{
public:
	/* �񋓌^��` */
	// UI
	enum
	{
		UI_NONE = -1,			// ����
		UI_BACKLIGHT,			// �o�b�N���C�g
		UI_TELLTHEPICTURE,		// �ʐ^�������Ă�������
		UI_SHAPEMEMORIZATION,	// �`�̈ËL
		UI_CORDCUTTING,			// �R�[�h��؂�
		UI_MAZE,				// ���H
		UI_SIMON,				// �T�C�����Q�[��
		UI_MAX					// �ő吔
	};
	// �E�B���h�E
	enum
	{
		WIND_NONE = -1,			// ����
		WIND_TELLTHEPICTURE,	// �ʐ^�������Ă�������
		WIND_SHAPEMEMORIZATION,	// �`�̈ËL
		WIND_CORDCUTTING,		// �R�[�h��؂�
		WIND_MAZE,				// ���H
		WIND_SIMON,				// �T�C�����Q�[��
		WIND_MAX,				// �ő吔
	};
	// �e�N�X�`��
	enum
	{
		TEX_NONE = -1,			// ����
		TEX_BACKLIGHT,			// �o�b�N���C�g
		TEX_TELLTHEPICTURE,		// �G�������Ă��炤
		TEX_SHAPEMEMORIZATION,	// �`�̈ËL
		TEX_CORDCUTTING,		// �R�[�h��؂�
		TEX_MAZE,				// ���H
		TEX_SIMON,				// �T�C�����Q�[��
		TEX_MAX					// �ő吔
	};
	// ���[�h
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
	void CreateWind(void);								// �E�B���h�E�̐���
	void SetPosAccordingParent(void);					// �e�ɏ]���Ĉʒu��ݒ肷��
	void InitConnect(void);								// �ڑ����[�h�̏�����
	void UpdateSelect(void);							// �I������Ƃ��̍X�V����
	void UpdateConnect(void);							// �ڑ����[�h�X�V����
	void UpdateShow(void);								// ��Ǐ���\�����Ă���Ƃ��̍X�V����

	static void UiInfoReadFromLine(CONST_STRING cnpLine, CONST_STRING cnpEntryType, CONST_STRING cnpEntryData);		// 1�s�������ǂݎ��
	static void WindInfoReadFromLine(CONST_STRING cnpLine, CONST_STRING cnpEntryType, CONST_STRING cnpEntryData);	// 1�s�������ǂݎ��

	/* �����o�ϐ� */
	static CHash *                   m_pHash;					// �n�b�V���̃|�C���^
	static LPDIRECT3DTEXTURE9        m_pTexture[TEX_MAX];		// �e�N�X�`�����
	static SETINGINFO                m_Seting[UI_MAX];			// �ݒ���
	static WINDOW_SETING             m_WindSeting[WIND_MAX];	// �E�B���h�E�̐ݒ���
	std::shared_ptr<CDecodingUI>     m_pUi[UI_MAX];				// UI
	std::shared_ptr<CDecodingWindow> m_pWind[WIND_MAX];			// �E�B���h�E
	MODE                             m_mode;					// ���[�h
	MODE                             m_modeNext;				// ���̃��[�h
	int                              m_nSelectIndex;			// �I�����Ă���ԍ�
	CDecodingWindow*                 m_pActiveWind;				// �A�N�e�B�u�ȃE�B���h�E�̃|�C���^
};

#endif
