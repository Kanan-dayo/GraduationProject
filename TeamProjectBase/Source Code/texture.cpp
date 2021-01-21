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
Vec<LPDIRECT3DTEXTURE9> CTexture::m_apTextureList = {};

//�e�N�X�`�����̐ݒ�
FILENAME_LIST CTexture::m_aTexFileName =
{
	{ "data/TEXTURE/other/TexNone.png" },					//����
	{ "data/TEXTURE/Effect/particle.jpg" },					//�p�[�e�B�N���p�̊ۂ���

	{ "data/TEXTURE/Material/field000.jpg" },					//�}�e���A��
	{ "data/TEXTURE/Material/field001.jpg" },					//�}�e���A��
	{ "data/TEXTURE/Material/field002.jpg" },					//�}�e���A��
	{ "data/TEXTURE/Material/field003.jpg" },					//�}�e���A��
	{ "data/TEXTURE/Material/renga.jpg" },						//�}�e���A��

	{ "data/TEXTURE/ModuleParts/SendButton_Module03.png" },		//���M�{�^��

	{ "data/TEXTURE/CHAT/chatTab_back.png" },					// �`���b�g�^�u�̔w�i
	{ "data/TEXTURE/CHAT/chatTab_title.png" },					// �`���b�g�^�u�̃^�C�g��
	{ "data/TEXTURE/CHAT/chatTab_writeWindow.png" },			// �`���b�g�^�u�̏������݃E�B���h�E
	{ "data/TEXTURE/CHAT/chatTab_open.png" },					// �`���b�g�^�u (�J��)
	{ "data/TEXTURE/CHAT/chatTab_close.png" },					// �`���b�g�^�u (����)
	{ "data/TEXTURE/CHAT/chatTab_TabOpen.png" },				// �^�u���b�g (�J��)
	{ "data/TEXTURE/CHAT/chatTab_TabClose.png" },				// �^�u���b�g (����)
	{ "data/TEXTURE/CHAT/chatBox00.png" },						// �`���b�g�{�b�N�X00
	{ "data/TEXTURE/CHAT/chatBox01.png" },						// �`���b�g�{�b�N�X01
	{ "data/TEXTURE/CHAT/chatBox02.png" },						// �`���b�g�{�b�N�X02
	{ "data/TEXTURE/CHAT/chatBox03.png" },						// �`���b�g�{�b�N�X03

	{ "data/TEXTURE/CONNECTMODE/LoadIcon.png" },				// �ڑ����̃��[�h�A�C�R��
	{ "data/TEXTURE/CONNECTMODE/tab_00.png" },					// �ڑ����̔w�i(1P)
	{ "data/TEXTURE/CONNECTMODE/tab_01.png" },					// �ڑ����̔w�i(2P)
	{ "data/TEXTURE/CONNECTMODE/connecting.png" },				// �ڑ����̕\�L
	{ "data/TEXTURE/CONNECTMODE/connected.png" },				// �ڑ������̕\�L
	{ "data/TEXTURE/CONNECTMODE/select_mode.png" },				// ���[�h�I��
	{ "data/TEXTURE/CONNECTMODE/select_level.png" },			// ���x���I��
	{ "data/TEXTURE/CONNECTMODE/mode_remove.png" },				// ���[�h(����)
	{ "data/TEXTURE/CONNECTMODE/mode_solve.png" },				// ���[�h(���)
	{ "data/TEXTURE/CONNECTMODE/level_easy.png" },				// ���x��(�C�[�W�[)
	{ "data/TEXTURE/CONNECTMODE/level_normal.png" },			// ���x��(�m�[�}��)
	{ "data/TEXTURE/CONNECTMODE/level_hard.png" },				// ���x��(�n�[�h)
	{ "data/TEXTURE/CONNECTMODE/selecting.png" },				// �Q�X�g�̑I��
	{ "data/TEXTURE/CONNECTMODE/selected.png" },				// �Q�X�g�̑I��
	{ "data/TEXTURE/CONNECTMODE/decide.png" },					// ����
	{ "data/TEXTURE/CONNECTMODE/comment_remove.png" },			// �����̐���
	{ "data/TEXTURE/CONNECTMODE/comment_solve.png" },			// ��ǂ̐���
	{ "data/TEXTURE/CONNECTMODE/comment_easy.png" },			// �C�[�W�[�̐���
	{ "data/TEXTURE/CONNECTMODE/comment_normal.png" },			// �m�[�}�������
	{ "data/TEXTURE/CONNECTMODE/comment_hard.png" },			// �n�[�h�̐���
	{ "data/TEXTURE/CONNECTMODE/caution_mode.png" },			// ���[�h�I�����̒���
	{ "data/TEXTURE/CONNECTMODE/caution_level.png" },			// ���x���I�����̒���

	{ "data/TEXTURE/CONNECTMODE/loading.png" },					// ���[�h��
	{ "data/TEXTURE/CONNECTMODE/out_guest.png" },				// �Q�X�g���E�ɂ��Q�[���I��

	{ "data/TEXTURE/UI/gameclear.png" },						//UI �Q�[���N���A
	{ "data/TEXTURE/UI/gameover.png" },							//UI �Q�[���I�[�o�[

	{ "data/TEXTURE/UI/PressButton.png" },						//UI �v���X�{�^��

	{ "data/TEXTURE/UI/Title/Title.png" },						//UI �^�C�g��
	{ "data/TEXTURE/UI/Title/Start.png" },						//UI �^�C�g��
	{ "data/TEXTURE/UI/Title/End.png" },						//UI �^�C�g��

	{ "data/TEXTURE/UI/Tutorial/Remove01.png" },				//UI �`���[�g���A���@��ǂP
	{ "data/TEXTURE/UI/Tutorial/Remove02.png" },				//UI �`���[�g���A���@��ǂQ
	{ "data/TEXTURE/UI/Tutorial/Remove03.png" },				//UI �`���[�g���A���@��ǂR
	{ "data/TEXTURE/UI/Tutorial/Remove04.png" },				//UI �`���[�g���A���@��ǂR
	{ "data/TEXTURE/UI/Tutorial/Solve01.png" },					//UI �`���[�g���A���@�����P
	{ "data/TEXTURE/UI/Tutorial/Solve02.png" },					//UI �`���[�g���A���@�����Q
	{ "data/TEXTURE/UI/Tutorial/Solve03.png" },					//UI �`���[�g���A���@�����R
	{ "data/TEXTURE/UI/Tutorial/Solve04.png" },					//UI �`���[�g���A���@�����R

	{ "data/TEXTURE/UI/Tutorial/prepare.png" },					//UI �`���[�g���A���@������
	{ "data/TEXTURE/UI/Tutorial/end_prepare.png" },				//UI �`���[�g���A���@��������

	{ "data/TEXTURE/UI/Result/Result.png" },					//UI ���U���g
	{ "data/TEXTURE/UI/Result/PlayTime.png" },					//UI ���U���g
	{ "data/TEXTURE/UI/Result/Success.png" },					//UI ���U���g
	{ "data/TEXTURE/UI/Result/Failed.png" },					//UI ���U���g
	{ "data/TEXTURE/UI/Result/PlaytimeBar.png" },				//UI ���U���g
	{ "data/TEXTURE/UI/Result/Plate.png" },						//UI ���U���g
	{ "data/TEXTURE/UI/Result/Retry.png" },						//UI ���U���g
	{ "data/TEXTURE/UI/Result/End.png" },						//UI ���U���g
	{ "data/TEXTURE/UI/Result/Comma.png" },						//UI ���U���g
	{ "data/TEXTURE/UI/Result/Comma2.png" },					//UI ���U���g

	{ "data/TEXTURE/UI/Paint/Pen.png" },						// �u���V�J�[�\��
	{ "data/TEXTURE/UI/Paint/Eraser.png" },						// �����S���J�[�\��
	{ "data/TEXTURE/UI/Paint/Pen_Button.png" },					// �u���V
	{ "data/TEXTURE/UI/Paint/Eraser_Button.png" },				// �����S��
	{ "data/TEXTURE/UI/Paint/send.png" },						// ���M

	{ "data/TEXTURE/UI/DecodingBook/T00.png" },					// ���UI
	{ "data/TEXTURE/UI/DecodingBook/T01.png" },					// ���UI
	{ "data/TEXTURE/UI/DecodingBook/T02.png" },					// ���UI
	{ "data/TEXTURE/UI/DecodingBook/T03.png" },					// ���UI
	{ "data/TEXTURE/UI/DecodingBook/T04.png" },					// ���UI
	{ "data/TEXTURE/UI/DecodingBook/T05.png" },					// ���UI
	{ "data/TEXTURE/UI/DecodingBook/backLight.png" },			// ���UI�o�b�N���C�g

	{ "data/TEXTURE/UI/DecodingBook/D00.png" },					// ��Ǐ�(Document)
	{ "data/TEXTURE/UI/DecodingBook/D01.png" },					// ��Ǐ�(Document)
	{ "data/TEXTURE/UI/DecodingBook/D02.png" },					// ��Ǐ�(Document)
	{ "data/TEXTURE/UI/DecodingBook/D03.png" },					// ��Ǐ�(Document)
	{ "data/TEXTURE/UI/DecodingBook/D04.png" },					// ��Ǐ�(Document)
	{ "data/TEXTURE/UI/DecodingBook/D05.png" },					// ��Ǐ�(Document)

	{ "data/TEXTURE/UI/DecodingBook/close.png" },				// ����{�^��
	{ "data/TEXTURE/UI/DecodingBook/ScrollBar.png" },			// �X�N���[���o�[
	{ "data/TEXTURE/UI/DecodingBook/ScrollHandle.png" },		// �X�N���[���n���h��
};

//�e�N�X�`�����̐ݒ�
FILENAME_LIST CTexture::m_aSeparateTexFileNameList =
{
	{ "data/TEXTURE/other/TexNone.png"},						//����

	{ "data/TEXTURE/other/Number.png" },						//�i���o�[
	{ "data/TEXTURE/UI/Result/Time.png" },						//���U���g�p�i���o�[

	{ "data/TEXTURE/Effect/Explosion00.png" },					//����

	{ "data/TEXTURE/ModuleParts/Icon_Module00.png" },					//����
	{ "data/TEXTURE/ModuleParts/Icon_Module01.png" },					//����
	{ "data/TEXTURE/ModuleParts/Icon_Module03.png" },					//����

	{ "data/TEXTURE/CONNECTMODE/LoadIcon.png" },				// �ڑ����̃��[�h�A�C�R��

};


//�e�N�X�`�����̐ݒ�
std::vector<CTexture::SEPARATE_TEX_INFO> CTexture::m_apSeparateTexInfoList =
{
	//�e�N�X�`���̃|�C���^�A�e�N�X�`���̃p�X�A�e�N�X�`���̃^�C�v�A�e�N�X�`���̕������A�e�N�X�`����UV�T�C�Y
	//�|�C���^��UV�T�C�Y�Ɋւ��Ă�Load�֐��œǂݍ��݁��v�Z����
	{ nullptr, CTexture::SEPARATE_TEX_NONE,								D3DXVECTOR2(1,1),	ZeroVector2 },		//����
	{ nullptr, CTexture::SEPARATE_TEX_EFFECT_EXPLOSION00,				D3DXVECTOR2(4,2),	ZeroVector2 },		//����
	{ nullptr, CTexture::SEPARATE_TEX_UI_NUMBER,						D3DXVECTOR2(10,1),	ZeroVector2 },		//����
	{ nullptr, CTexture::SEPARATE_TEX_UI_RESULT_NUMBER,					D3DXVECTOR2(10,1),	ZeroVector2 },		//����
	{ nullptr, CTexture::SEPARATE_TEX_MODULEPARTS_MODULE00,				D3DXVECTOR2(12,2),	ZeroVector2 },		//����
	{ nullptr, CTexture::SEPARATE_TEX_MODULEPARTS_MODULE01,				D3DXVECTOR2(4,1),	ZeroVector2 },		//����
	{ nullptr, CTexture::SEPARATE_TEX_MODULEPARTS_MODULE03,				D3DXVECTOR2(6,1),	ZeroVector2 },		//����
	{ nullptr, CTexture::SEPARATE_TEX_LOADICON,							D3DXVECTOR2(8,1),	ZeroVector2 },		//����

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
