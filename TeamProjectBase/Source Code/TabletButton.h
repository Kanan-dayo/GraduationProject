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
class CTabletButton : public CSceneX
{
public:
	typedef enum
	{
		TYPE_NOEN = -1,	// ����
		TYPE_PEN,		// �y��
		TYPE_ERASER,	// �����S��
		TYPE_SEND,		// ���M
		TYPE_MAX,		// �ő�
	} TYPE;
	CTabletButton();															// �R���X�g���N�^
	~CTabletButton();															// �f�X�g���N�^

	static void Load(void);														// �ǂݍ���
	static void Unload(void);													// �J��
	HRESULT             Init();													// ������
	void                Update();												// �X�V
	void                Draw();													// �`��
	inline void         ShowDebugInfo() {};										// �f�o�b�O���\�L

	void SetMode(void);															// ���[�h�̐ݒ�

	void SetChangeFlag(void);													// �ύX�t���O�̐ݒ�

	// �ݒ�֐�
	inline void SetType(TYPE type) { m_Type = type; }							// �^�C�v�̐ݒ�
	inline void SetToOffPressFlag(void) { if (m_bPress)m_bPress = false; }		// �����ꂽ�t���O�������ݒ�
	inline void SetToSetPressFlag(void) { if (!m_bPress)m_bPress = true; }		// �����ꂽ�t���O�𗧂Ă�ݒ�
	inline void SetToOffChangeFlag(void) { if (m_bChange)m_bChange = false; }	// �ύX�t���O�������ݒ�
	inline void SetToSetChangeFlag(void) { if (!m_bChange)m_bChange = true; }	// �ύX�t���O�𗧂Ă�ݒ�


	// �擾�֐�
	inline TYPE &GetType(void) { return m_Type; }								// �^�C�v�̎擾

	// ����
	static std::shared_ptr<CTabletButton> Create(D3DXMATRIX *pMtxParent,CONST D3DXVECTOR3 &pos, TYPE type);	// ����
private:
	static LPDIRECT3DTEXTURE9 m_aTexture[TYPE_MAX];

	std::shared_ptr<CScene3D> m_pImage;
	TYPE m_Type;
	bool m_bPress;
	bool m_bChange;
	bool m_bInPress;

};

#endif