//-----------------------------------------------------------------------------
//
//�e�N�X�`���Ǘ�  [texture.cpp]
// Author : Yoshiki Hosoya
//
//-----------------------------------------------------------------------------
#include "texture.h"
#include "manager.h"
#include "renderer.h"
//-----------------------------------------------------------------------------
//�ÓI�����o�ϐ��̏�����
//-----------------------------------------------------------------------------
std::vector<LPDIRECT3DTEXTURE9> CTexture::m_apTextureList = {};

//�e�N�X�`�����̐ݒ�
FILENAME_LIST CTexture::m_aTexFileName =
{
	{ "data/TEXTURE/other/TexNone.png" },					//����
	{ "data/TEXTURE/Effect/particle.jpg" },					//�p�[�e�B�N���p�̊ۂ���

	{ "data/TEXTURE/Material/field000.jpg" },					//�p�[�e�B�N���p�̊ۂ���
	{ "data/TEXTURE/Material/field001.jpg" },					//�p�[�e�B�N���p�̊ۂ���
	{ "data/TEXTURE/Material/field002.jpg" },					//�p�[�e�B�N���p�̊ۂ���
	{ "data/TEXTURE/Material/field003.jpg" },					//�p�[�e�B�N���p�̊ۂ���
	{ "data/TEXTURE/Material/field004.jpg" },					//�p�[�e�B�N���p�̊ۂ���
};

//�e�N�X�`�����̐ݒ�
FILENAME_LIST CTexture::m_aSeparateTexFileNameList =
{
	{ "data/TEXTURE/other/TexNone.png"},						//����
	{ "data/TEXTURE/other/Number.png" },						//�i���o�[
	{ "data/TEXTURE/Effect/Explosion00.png" },					//����
};


//�e�N�X�`�����̐ݒ�
std::vector<CTexture::SEPARATE_TEX_INFO> CTexture::m_apSeparateTexInfoList =
{
	//�e�N�X�`���̃|�C���^�A�e�N�X�`���̃p�X�A�e�N�X�`���̃^�C�v�A�e�N�X�`���̕������A�e�N�X�`����UV�T�C�Y
	//�|�C���^��UV�T�C�Y�Ɋւ��Ă�Load�֐��œǂݍ��݁��v�Z����
	{ nullptr, CTexture::SEPARATE_TEX_NONE,					D3DXVECTOR2(1,1),	ZeroVector2 },		//����
	{ nullptr, CTexture::SEPARATE_TEX_EFFECT_EXPLOSION00,	D3DXVECTOR2(4,2),	ZeroVector2 },		//����
	{ nullptr, CTexture::SEPARATE_TEX_UI_NUMBER,		D3DXVECTOR2(10,1),	ZeroVector2 },		//����

};

//-----------------------------------------------------------------------------
//�e�N�X�`���ꊇ���[�h
//-----------------------------------------------------------------------------
void CTexture::TexLoad(HWND hwnd)
{
	//�f�o�C�X�擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();
	LPDIRECT3DTEXTURE9 pTexture;

	//�e�N�X�`�����̃��X�g�̃T�C�Y��
	for (size_t nCnt = 0; nCnt < m_aTexFileName.size(); nCnt++)
	{
		//null
		pTexture = nullptr;

		//�e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice,
			m_aTexFileName[nCnt].data(),
			&pTexture);

		//debug
		std::cout << "Tex Load - " << nCnt << m_aTexFileName[nCnt].data() << NEWLINE;

		//nullcheck
		if (!pTexture)
		{
			//debug
			std::cout << "LOADFAILED!!! Tex - " << nCnt << m_aTexFileName[nCnt].data() << NEWLINE;

			//���s
			MessageBox(hwnd, "�e�N�X�`���ǂݍ��ݎ��s", m_aTexFileName[nCnt].data(), MB_OK | MB_ICONHAND);
		}

		//���X�g�ɒǉ�
		m_apTextureList.emplace_back(pTexture);
	}

	//�e�N�X�`�����̃��X�g�̃T�C�Y��
	for (size_t nCnt = 0; nCnt < m_apSeparateTexInfoList.size(); nCnt++)
	{
		//�e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice,
			m_aSeparateTexFileNameList[nCnt].data(),
			&m_apSeparateTexInfoList[nCnt].m_apSeparateTexture);

		//debug
		std::cout << "SeparateTex Load - " << nCnt << m_aSeparateTexFileNameList[nCnt].data() << NEWLINE;

		//nullcheck
		if (!m_apSeparateTexInfoList[nCnt].m_apSeparateTexture)
		{
			//debug
			std::cout << "LOADFAILED!!! SeparateTex - " << nCnt << m_aSeparateTexFileNameList[nCnt].data() << NEWLINE;

			//���s
			MessageBox(hwnd, "�e�N�X�`���ǂݍ��ݎ��s", m_aSeparateTexFileNameList[nCnt].data(), MB_OK | MB_ICONHAND);
		}

		//�ǂ��炩�̒l��0�������ꍇ�͌v�Z���Ȃ�
		//0���Z�h�~
		if (m_apSeparateTexInfoList[nCnt].m_UVCnt.x * m_apSeparateTexInfoList[nCnt].m_UVCnt.y)
		{
			//UV�T�C�Y�v�Z
			m_apSeparateTexInfoList[nCnt].m_UVSize = D3DXVECTOR2(1.0f / m_apSeparateTexInfoList[nCnt].m_UVCnt.x, 1.0f / m_apSeparateTexInfoList[nCnt].m_UVCnt.y);
		}
		else
		{
			m_apSeparateTexInfoList[nCnt].m_UVSize = ZeroVector2;
			//�x����
			MessageBox(hwnd, "0���Z�����悤�Ƃ��܂����@�l���m�F���Ă�������", m_aSeparateTexFileNameList[nCnt].data(), MB_OK | MB_ICONHAND);
		}
	}
}

//-----------------------------------------------------------------------------
//�e�N�X�`���ꊇ�j��
//-----------------------------------------------------------------------------
void CTexture::TexUnload()
{
	//�T�C�Y��
	for (size_t nCnt = 0; nCnt < m_apTextureList.size(); nCnt++)
	{
		//nullcheck
		if (m_apTextureList[nCnt])
		{
			//�e�N�X�`���̊J��
			m_apTextureList[nCnt]->Release();
			m_apTextureList[nCnt] = nullptr;
		}
	}

	//�T�C�Y��
	for (size_t nCnt = 0; nCnt < m_apSeparateTexInfoList.size(); nCnt++)
	{
		//nullcheck
		if (m_apSeparateTexInfoList[nCnt].m_apSeparateTexture)
		{
			//�e�N�X�`���̊J��
			m_apSeparateTexInfoList[nCnt].m_apSeparateTexture->Release();
			m_apSeparateTexInfoList[nCnt].m_apSeparateTexture = nullptr;
		}
	}

	//�z��̊J��
	m_apTextureList.clear();
	m_apSeparateTexInfoList.clear();
}

//-----------------------------------------------------------------------------
//�e�N�X�`���擾�@�ʏ�
//----------------------------------------------------------------------------
LPDIRECT3DTEXTURE9 CTexture::GetTexture(TEX_TYPE textype)
{
	//�z���菬�����l��
	if (textype < (int)m_apTextureList.size())
	{
		//nullcheck
		if (m_apTextureList[textype])
		{
			return m_apTextureList[textype];
		}
	}
	return nullptr;
}

//-----------------------------------------------------------------------------
//�e�N�X�`���擾�@��������Ă���
//----------------------------------------------------------------------------
LPDIRECT3DTEXTURE9 CTexture::GetSeparateTexture(SEPARATE_TEX_TYPE textype)
{
	//�z���菬�����l��
	if (textype < (int)m_apSeparateTexInfoList.size())
	{
		//nullcheck
		if (m_apSeparateTexInfoList[textype].m_apSeparateTexture)
		{
			return m_apSeparateTexInfoList[textype].m_apSeparateTexture;
		}
	}
	return nullptr;
}
//-----------------------------------------------------------------------------
//�e�N�X�`����UV�T�C�Y�擾
//----------------------------------------------------------------------------
D3DXVECTOR2 CTexture::GetSparateTex_UVSize(SEPARATE_TEX_TYPE textype)
{
	//�z���菬�����l��
	//�z��O�̃��m���w�肳��Ă����ꍇ�̓A�N�Z�X�ᔽ�Ȃ�̂Œ���
	if (textype < (int)m_apSeparateTexInfoList.size())
	{
		return m_apSeparateTexInfoList[textype].m_UVSize;
	}
	return ZeroVector2;
}

//-----------------------------------------------------------------------------
//�e�N�X�`����UV�����擾
//----------------------------------------------------------------------------
D3DXVECTOR2 CTexture::GetSparateTex_UVCnt(SEPARATE_TEX_TYPE textype)
{
	//�z���菬�����l��
	//�z��O�̃��m���w�肳��Ă����ꍇ�̓A�N�Z�X�ᔽ�Ȃ�̂Œ���
	if (textype < (int)m_apSeparateTexInfoList.size())
	{
		return m_apSeparateTexInfoList[textype].m_UVCnt;
	}
	return ZeroVector2;
}