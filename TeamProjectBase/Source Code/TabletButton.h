//*************************************************************************************************************
//
// �^�u���b�g�{�^���̊�ꏈ�� [TabletButton.h]
// Author:IKUTO SEKINE
//
//*************************************************************************************************************
#ifndef _TABLETBUTTON_H_
#define _TABLETBUTTON_H_

//-------------------------------------------------------------------------------------------------------------
// �C���N���[�h�t�@�C��
//-------------------------------------------------------------------------------------------------------------
#include "sceneX.h"
#include "Mylibrary.h"

//-------------------------------------------------------------------------------------------------------------
// �N���X��`
//-------------------------------------------------------------------------------------------------------------
class CScene3D;
class CPicture;
class CPaintingPen;
class CTabletButton : public CSceneX
{
public:
	/* �񋓌^��` */
	typedef enum
	{
		TYPE_NOEN = -1,	// ����
		TYPE_PEN,		// �y��
		TYPE_ERASER,	// �����S��
		TYPE_SEND,		// ���M
		TYPE_MAX,		// �ő�
	} TYPE;
	enum PRESS
	{
		PRESSED = 0,	// �����ꂽ
		UNPRESSED,		// ������Ă��Ȃ�
		PRESS_MAX,		// �ő�
	};


	/* �����o�֐� */
	CTabletButton();																// �R���X�g���N�^
	~CTabletButton();																// �f�X�g���N�^

	static void    Load(void);														// �ǂݍ���
	static void    Unload(void);													// �J��
	static HRESULT LoadError(void);													// �G���[�̌��o

	HRESULT     Init();																// ������
	void        Update();															// �X�V
	void        Draw();																// �`��
	inline void ShowDebugInfo() {};													// �f�o�b�O���\�L

	// �ݒ�֐�
	static void SetFromString(CONST_STRING str);									// �����񂩂�ݒ肷��
	void        FlagProcToChangeMode(void);											// ���[�h��ύX���邽�߂̃t���O����
	void        SetChangeFlagProc(void);											// �ύX�t���O�̐ݒ菈��
	inline void SetType(TYPE type) { m_Type = type; }								// �^�C�v�̐ݒ�
	inline void SetToOffPressFlag(void) { if (m_bPress)m_bPress = false; }			// �����ꂽ�t���O�������ݒ�
	inline void SetToSetPressFlag(void) { if (!m_bPress)m_bPress = true; }			// �����ꂽ�t���O�𗧂Ă�ݒ�
	inline void SetToOffChangeFlag(void) { if (m_bChange)m_bChange = false; }		// �ύX�t���O�������ݒ�
	inline void SetToSetChangeFlag(void) { if (!m_bChange)m_bChange = true; }		// �ύX�t���O�𗧂Ă�ݒ�
	inline void SetToOffInPressFlag(void) { if (m_bInPress)m_bInPress = false; }	// �����ŉ����ꂽ�t���O�������ݒ�
	inline void SetToSetInPressFlag(void) { if (!m_bInPress)m_bInPress = true; }	// �����ŉ����ꂽ�t���O�𗧂Ă�ݒ�

	// �擾�֐�
	inline TYPE &GetType(void) { return m_Type; }									// �^�C�v�̎擾
	inline bool GetPressFlag(void) { return m_bPress; }							// �����ꂽ�t���O�̎擾
	inline bool GetChangeFlag(void) { return m_bChange; }							// �ύX�t���O�t���O�̎擾
	inline bool GetInPressFlag(void) { return m_bInPress; }						// �����ŉ����ꂽ�t���O�̎擾

	// ����
	static std::shared_ptr<CTabletButton> Create(D3DXMATRIX *pMtxParent,CONST D3DXVECTOR3 &pos, TYPE type);	// ����

private:
	/* �����o�֐� */
	static CPicture *GetPicture(void);					// �s�N�`���̎擾
	static CPaintingPen *GetPen(void);					// �y���̎擾
	/* �����o�ϐ� */
	static LPDIRECT3DTEXTURE9 m_aTexture[TYPE_MAX];		// �e�N�X�`�����
	static float              m_aPressPos[PRESS_MAX];	// �����ꂽ�ʒu
	std::shared_ptr<CScene3D> m_pImage;					// �摜
	TYPE                      m_Type;					// �^�C�v
	bool                      m_bPress;					// �����ꂽ�t���O
	bool                      m_bChange;				// �ύX�t���O
	bool                      m_bInPress;				// �����ŉ����ꂽ�t���O

};

#endif