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
		UI_MAX					// �ő吔
	};

	enum MODE
	{
		MODE_SELECT,			// �I��
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

private:
	/* �����o�֐� */
	void UpdateSelect(void);							// �I������Ƃ��̍X�V����
	void UpdateShow(void);								// ��Ǐ���\�����Ă���Ƃ��̍X�V����
	static void ReadFromLine(CONST_STRING cnpLine, CONST_STRING cnpEntryType, CONST_STRING cnpEntryData);	// 1�s�������ǂݎ��

	/* �����o�ϐ� */
	static CHash *               m_pHash;				// �n�b�V���̃|�C���^
	static LPDIRECT3DTEXTURE9    m_pTexture[UI_MAX];	// �e�N�X�`�����
	static SETINGINFO            m_Seting[UI_MAX];		// �ݒ���
	std::shared_ptr<CDecodingUI> m_pUi[UI_MAX];			// UI
	MODE                         m_mode;				// ���[�h
};

#endif
