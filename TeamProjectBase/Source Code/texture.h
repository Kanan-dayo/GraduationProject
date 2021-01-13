//------------------------------------------------------------------------------
//
//�e�N�X�`���Ǘ�  [texture.cpp]
//Author:Yoshiki Hosoya
//
//------------------------------------------------------------------------------

#ifndef _TEXTURE_H_
#define _TEXTURE_H_
//------------------------------------------------------------------------------
//�C���N���[�h
//------------------------------------------------------------------------------
#include "main.h"

//------------------------------------------------------------------------------
//�N���X��`
//------------------------------------------------------------------------------
//�O���錾
class CTexture
{
public:
	CTexture() {};
	~CTexture() {};

	//�ʏ�̃e�N�X�`��
	enum TEX_TYPE
	{
		TEX_NONE = 0,

		TEX_EFFECT_PARTICLE,					//�p�[�e�B�N��

		//�}�e���A��
		TEX_MATERIAL_FIELD000,					//�}�e���A��
		TEX_MATERIAL_FIELD001,					//�}�e���A��
		TEX_MATERIAL_FIELD002,					//�}�e���A��
		TEX_MATERIAL_FIELD003,					//�}�e���A��
		TEX_MATERIAL_FIELD004,					//�}�e���A��

		TEX_MODULEPARTS_MODULE03_SENDBUTTON,	//���M�{�^��

		TEX_CHAT_BACK,							// �`���b�g�^�u�̔w�i
		TEX_CHAT_TITLE,							// �`���b�g�^�u�̃^�C�g��
		TEX_CHAT_WRITEWINDOW,					// �`���b�g�^�u�̏������݃E�B���h�E
		TEX_CHAT_TABOPEN,						// �`���b�g�^�u (�J��)
		TEX_CHAT_TABCLOSE,						// �`���b�g�^�u (����)
		TEX_CHAT_TABLETOPEN,					// �^�u���b�g (�J��)
		TEX_CHAT_TABLETCLOSE,					// �^�u���b�g (����)
		TEX_CHAT_BOX_00,						// �`���b�g�{�b�N�X00
		TEX_CHAT_BOX_01,						// �`���b�g�{�b�N�X01
		TEX_CHAT_BOX_02,						// �`���b�g�{�b�N�X02
		TEX_CHAT_BOX_03,						// �`���b�g�{�b�N�X03

		TEX_CONNECT_LOAD,						// �ڑ����̃��[�h�A�C�R��
		TEX_CONNECT_BACK_00,					// �ڑ����̔w�i(1P)
		TEX_CONNECT_BACK_01,					// �ڑ����̔w�i(2P)
		TEX_CONNECT_CONNECTING,					// �ڑ����̕\�L
		TEX_CONNECT_CONNECTED,					// �ڑ������̕\�L
		TEX_CONNECT_SELECT_MODE,				// ���[�h�I��
		TEX_CONNECT_SELECT_LEVEL,				// ���x���I��
		TEX_CONNECT_SELECT_REMOVE,				// ���[�h(����)
		TEX_CONNECT_SELECT_SOLVE,				// ���[�h(���)
		TEX_CONNECT_SELECT_EASY,				// �C�[�W�[
		TEX_CONNECT_SELECT_NORMAL,				// �m�[�}��
		TEX_CONNECT_SELECT_HARD,				// �n�[�h
		TEX_CONNECT_GUEST_SELECTING,			// �Q�X�g�̑I��
		TEX_CONNECT_GUEST_SELECTED,				// �Q�X�g�̑I��
		TEX_CONNECT_DECIDE,						// ����
		TEX_CONNECT_COMMENT_REMOVE,				// �����̐���
		TEX_CONNECT_COMMENT_SOLVE,				// ��ǂ̐���
		TEX_CONNECT_COMMENT_EASY,				// �C�[�W�[�̐���
		TEX_CONNECT_COMMENT_NORMAL,				// �m�[�}�������
		TEX_CONNECT_COMMENT_HARD,				// �n�[�h�̐���
		TEX_CONNECT_CAUTION_MODE,				// ���[�h�I�����̒���
		TEX_CONNECT_CAUTION_LEVEL,				// ���x���I�����̒���

		TEX_UI_PRESSBUTTON,						//UI �v���X

		TEX_UI_TITLE_LOGO,						//UI �^�C�g�����S
		TEX_UI_TITLE_START,						//UI �^�C�g���@�X�^�[�g
		TEX_UI_TITLE_END,						//UI �^�C�g���@�G���h

		TEX_UI_RESULT_LOGO,						//UI ���U���g���S
		TEX_UI_RESULT_TIMER,					//UI ���U���g�@�^�C��
		TEX_UI_RESULT_CLEAR,					//UI ���U���g�@�N���A
		TEX_UI_RESULT_FAILED,					//UI ���U���g�@���s
		TEX_UI_RESULT_BAR,						//UI ���U���g�@�o�[
		TEX_UI_RESULT_WINDOW,					//UI ���U���g�@�o�[
		TEX_UI_RESULT_RETRY,					//UI ���U���g�@���g���C
		TEX_UI_RESULT_END,						//UI ���U���g�@�I��
		TEX_UI_RESULT_COMMA,					//UI ���U���g�@�R���}
		TEX_UI_RESULT_SEMICOLON,				//UI ���U���g�@�Z�~�R����





		TEX_UI_BRUSHCURSOR,						// �u���V�J�[�\��
		TEX_UI_ERASERCURSOR,					// �����S���J�[�\��
		TEX_UI_BRUSHBUTTON,						// �u���V
		TEX_UI_ERASERBUTTON,					// �����S��
		TEX_UI_SENDBUTTON,						// ���M

		TEX_UI_DECODING_T00,					// ���UI
		TEX_UI_DECODING_T01,					// ���UI
		TEX_UI_DECODING_T02,					// ���UI
		TEX_UI_DECODING_T03,					// ���UI
		TEX_UI_DECODING_T04,					// ���UI
		TEX_UI_DECODING_T05,					// ���UI
		TEX_UI_DECODING_BACKLIGHT,				// ���UI�o�b�N���C�g

		TEX_UI_DECODING_D00,					// ��Ǐ�(Document)
		TEX_UI_DECODING_D01,					// ��Ǐ�(Document)
		TEX_UI_DECODING_D02,					// ��Ǐ�(Document)
		TEX_UI_DECODING_D03,					// ��Ǐ�(Document)
		TEX_UI_DECODING_D04,					// ��Ǐ�(Document)
		TEX_UI_DECODING_D05,					// ��Ǐ�(Document)

		TEX_UI_DECODING_CLOSE,					// ����{�^��
		TEX_UI_DECODING_S_BAR,					// �X�N���[���o�[
		TEX_UI_DECODING_S_HANDLE,				// �X�N���[���n���h��

		TEX_MAX									//MAX
	};

	//�A�j���[�V�����p�̃e�N�X�`��
	//��������Ă���e�N�X�`��
	enum SEPARATE_TEX_TYPE
	{
		SEPARATE_TEX_NONE = 0,

		//UI
		SEPARATE_TEX_UI_NUMBER,								//�i���o�[
		SEPARATE_TEX_UI_RESULT_NUMBER,						//�i���o�[ ���U���g�p

		//�G�t�F�N�g
		SEPARATE_TEX_EFFECT_EXPLOSION00,					//����

		//���W���[���̃p�[�c
		SEPARATE_TEX_MODULEPARTS_MODULE00,					//���W���[���i���o�[0 �Í��݂����Ȃ��
		SEPARATE_TEX_MODULEPARTS_MODULE01,					//���W���[���i���o�[1 �Z�~����
		SEPARATE_TEX_MODULEPARTS_MODULE03,					//���W���[���i���o�[3 �p�X���[�h�̖͗l


		SEPARATE_TEX_MAX									//MAX
	};

	typedef struct
	{
		LPDIRECT3DTEXTURE9 m_apSeparateTexture;		//�����e�N�X�`���ւ̃|�C���^
		SEPARATE_TEX_TYPE type;						//�e�N�X�`���̎��
		D3DXVECTOR2 m_UVCnt;						//UV�̖���
		D3DXVECTOR2 m_UVSize;						//UV�̑傫��

	}SEPARATE_TEX_INFO;

	static void TexLoad(HWND hwnd);						//�e�N�X�`������
	static void TexUnload();							//�e�N�X�`���j��

	static LPDIRECT3DTEXTURE9 GetTexture(TEX_TYPE textype);							//�ʏ�e�N�X�`���̎擾

	static std::vector<std::string> &GetTexFileName() { return m_aTexFileName; };						//�e�N�X�`�����擾
	static std::vector<std::string> &GetSeparateFileName() { return m_aSeparateTexFileNameList; };		//�����e�N�X�`�����擾

	static LPDIRECT3DTEXTURE9 GetSeparateTexture(SEPARATE_TEX_TYPE textype);		//�����e�N�X�`���擾
	static D3DXVECTOR2 GetSparateTex_UVSize(SEPARATE_TEX_TYPE textype);				//�����e�N�X�`���@UV�̃T�C�Y�擾
	static D3DXVECTOR2 GetSparateTex_UVCnt(SEPARATE_TEX_TYPE textype);				//�����e�N�X�`���@UV�̖����擾


private:
	static std::vector<LPDIRECT3DTEXTURE9> m_apTextureList;							//�ʏ�e�N�X�`���ւ̃|�C���^�̃��X�g
	static std::vector<std::string> m_aTexFileName;											//�ʏ�e�N�X�`���̃t�@�C����


	static std::vector<std::string> m_aSeparateTexFileNameList;								//�����e�N�X�`���̃t�@�C����
	static std::vector<SEPARATE_TEX_INFO> m_apSeparateTexInfoList;					//�����e�N�X�`���Ɋւ�����̃|�C���^

};

#endif