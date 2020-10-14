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

		TEX_MAX									//MAX
	};

	//�A�j���[�V�����p�̃e�N�X�`��
	//��������Ă���e�N�X�`��
	enum SEPARATE_TEX_TYPE
	{
		SEPARATE_TEX_NONE = 0,

		//UI
		SEPARATE_TEX_UI_NUMBER,						//�i���o�[

		//�G�t�F�N�g
		SEPARATE_TEX_EFFECT_EXPLOSION00,			//����

		SEPARATE_TEX_MAX							//MAX
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