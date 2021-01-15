//------------------------------------------------------------------------------
//
//�}�l�[�W���[����  [manager.h]
//Author:Yoshiki Hosoya
//
//------------------------------------------------------------------------------
#ifndef _MANAGER_H_
#define _MANAGER_H_
//------------------------------------------------------------------------------
//�C���N���[�h
//------------------------------------------------------------------------------
#include "main.h"
#include "Mylibrary.h"

//------------------------------------------------------------------------------
//�}�N��
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//�N���X��`
//------------------------------------------------------------------------------

//�O���錾
class CRenderer;
class CSound;
class CKeyboard;
class CMouse;
class CBaseMode;
class CGame;
class CSound;
class CPad_XInput;
class CDecoding;
class CManager
{
public:

	enum MODE
	{
		MODE_NONE = -1,						//����
		MODE_TITLE,							//�^�C�g��
		MODE_DECODING,						// ���
		MODE_TUTORIAL,						//�`���[�g���A��
		MODE_GAME,							//�Q�[��
		MODE_RESULT,						//���U���g
		MODE_TEST,							//�e�X�g���
		MODE_CONNECT_SERVER,				//�T�[�o�[�ڑ�
		MODE_EFFECT_VIEWER,					//�G�t�F�N�g�r���[��
		MODE_END							//�Q�[���I��
	};

	typedef struct
	{
		FLOAT3 NearPos;		// �߂��ʒu
		FLOAT3 FarPos;		// �����ʒu
		VEC3 vec;			// ���C�̃x�N�g��
	} RAY;

	CManager() {};	// �R���X�g���N�^
	~CManager();	// �f�X�g���N�^

	HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow);					//������
	void Uninit();																//�I��
	void Update();																//�X�V
	void Draw();																//�`��
	static void SetMode(MODE nextmode);											//���[�h�ݒ�

	//Get�֐�
	static MODE GetMode()				{ return m_mode; };						//���[�h�擾
	static HWND GethWnd()				{ return m_hWnd; };						//�E�B���h�E�n���h���擾
	static CRenderer *GetRenderer()		{ return m_pRenderer.get();	};			//�����_���[�擾����
	static CSound *GetSound()			{ return m_pSound.get(); };				//�T�E���h�擾
	static CKeyboard *GetKeyboard()		{ return m_pKeyboard.get(); };			//�L�[�{�[�h�擾
	static CMouse *GetMouse()			{ return m_pMouse.get(); };				//�}�E�X�擾
	static CPad_XInput *GetXInput()		{ return m_pXInput.get(); };			//XInput�̎擾
	static RAY *GetRay()				{ return &m_ray; }						// ���C�̎擾

	static CBaseMode *GetBaseMode();											//�x�[�X�̃��[�h�擾
	static CGame *GetGame();													//�Q�[���擾 �ȒP�ɌĂяo����悤��
	static CDecoding *GetDecoding();											// ��ǂ̎擾
private:
	static std::unique_ptr<CRenderer> m_pRenderer;		//�����_���[�ւ̃|�C���^
	static std::unique_ptr <CSound > m_pSound;			//�T�E���h�ւ̃|�C���^
	static std::unique_ptr<CKeyboard> m_pKeyboard;		//�L�[�{�[�h�ւ̃|�C���^
	static std::unique_ptr<CMouse> m_pMouse;			//�}�E�X�ւ̃|�C���^
	static std::unique_ptr<CPad_XInput> m_pXInput;		//XInput�ւ̃|�C���^
	static std::unique_ptr<CBaseMode> m_pBaseMode;		//�x�[�X�̃��[�h�ւ̃|�C���^

	static MODE m_mode;		//���[�h
	static HWND m_hWnd;		//�E�B���h�E�n���h��

	static int m_nNumChangeMode;	//���[�h�ς�����

	static RAY m_ray;				// ���C�̏��
};

#endif