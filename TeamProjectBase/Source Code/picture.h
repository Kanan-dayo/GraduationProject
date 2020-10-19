//*************************************************************************************************************
//
// �G�̏��� [picture.h]
// Author:IKUTO SEKINE
//
//*************************************************************************************************************
#ifndef _PICTURE_H_
#define _PICTURE_H_

//-------------------------------------------------------------------------------------------------------------
// �C���N���[�h�t�@�C��
//-------------------------------------------------------------------------------------------------------------
#include "scene.h"
#include "Mylibrary.h"

//-------------------------------------------------------------------------------------------------------------
// �N���X��`
//-------------------------------------------------------------------------------------------------------------
class CPicture : public CScene
{
public:
	enum
	{
		FLAG_NONE = -1,
		FLAG_DISP,
		FLAG_UPDATE,
		FLAG_MAX
	};

	/* �\���̒�` */
	typedef struct MESHINFO
	{
		MESHINFO();
		~MESHINFO();
		LPDIRECT3DVERTEXBUFFER9  pVtexBuff;								// ���_�o�b�t�@�̃|�C���^
		LPDIRECT3DINDEXBUFFER9   pIdxBuff;								// �C���f�b�N�X�̃o�b�t�@�̃|�C���^
		LPDIRECT3DTEXTURE9       pTexture;								// �e�N�X�`���̃|�C���^
		TRANSFORM                trans;									// �g�����X���
	}MESHINFO;

	/* �����o�֐� */
	inline           CPicture() :CScene(){}
	inline           ~CPicture() {}
	HRESULT          Init();																	//������
	void             Uninit();																	//�I��
	void             Update();																	//�X�V
	void             Draw();																	//�`��
	inline void      ShowDebugInfo() {};														//�f�o�b�O���\�L

	static HRESULT   Load(void);																// �ǂݍ���
	static void      InitStaticMember(void);													// �ÓI�����o�̏�����

	void             MatrixCal(void);															// �}�g���b�N�X�̌v�Z

	// �ݒ�֐�
	inline void      SetPos(CONST D3DXVECTOR3 &pos) { m_mesh.trans.pos = pos; }					// �ʒu�̐ݒ�
	inline void      SetRot(CONST D3DXVECTOR3 &rot) { m_mesh.trans.rot = rot; }					// �����̐ݒ�
	inline void      SetScal(CONST D3DXVECTOR3 &scal) { m_mesh.trans.scal = scal; }				// �X�P�[���̐ݒ�
	inline void      SetFlag(int nIndex) { Mybfunc_bit_set(m_Flags.cValue, nIndex); }			// �t���O�̐ݒ�
	inline void      ClearFlag(int nIndex) { Mybfunc_bit_clear(m_Flags.cValue, nIndex); }		// �t���O�̍폜

	// �擾�֐�
	inline MESHINFO* GetInfo(void) { return &m_mesh; }											// ���̎擾
	inline bool      GetFlag(int nIndex) { return Mybfunc_bit_comp(m_Flags.cValue, nIndex) != 0; }	// �t���O�̎擾
	// �N���G�C�g�֐�
	static std::shared_ptr<CPicture> Create(CONST D3DXVECTOR3 &pos, CONST D3DXVECTOR3 &rot);			// ����
private:
	/* �����Ŏg���֐� */
	void        MakeVertex(LPDIRECT3DDEVICE9 pDevice);					// ���_���̍쐬
	void        MakeIndex(LPDIRECT3DDEVICE9 pDevice);					// �C���f�b�N�X���̍쐬
	static void ReadFromLine(CONST_STRING Line);						// 1�s�������ǂݎ��

	/* �����o�ϐ� */
	static INTEGER2    m_nNumPolyBlock;		// �|���S����(���炷�傫���̐ݒ��2�{�ɂ���)
	static UINT        m_nNumVertex;		// �����_��
	static UINT        m_nNumIndex;			// ���C���f�b�N�X��
	static UINT        m_nNumPolygon;		// ���|���S����
	static FLOAT2      m_size;				// �傫��
	static FLOAT2      m_sizeShift;			// ���炷�傫��

	MESHINFO           m_mesh;				// ���b�V�����
	UBITS_4            m_Flags;				// �t���O
};


#endif // !_PICTURE_H_
