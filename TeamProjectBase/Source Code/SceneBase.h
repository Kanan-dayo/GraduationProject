//------------------------------------------------------------------------------
//
//Scene�̃x�[�X�N���X  [SceneBase.cpp]
//Author:Yoshiki Hosoya
//
//------------------------------------------------------------------------------
#ifndef _SCENEBASE_H_
#define _SCENEBASE_H_

//------------------------------------------------------------------------------
//�C���N���[�h
//------------------------------------------------------------------------------
#include "main.h"
#include "scene.h"

//------------------------------------------------------------------------------
//�N���X��`
//------------------------------------------------------------------------------
class CSceneBase :public CScene
{
public:
	CSceneBase();													//�R���X�g���N�^
	virtual	~CSceneBase();											//�f�X�g���N�^
	virtual	HRESULT Init()			= 0;							//������
	virtual	void Update()			= 0;							//�X�V
	virtual	void Draw()				= 0;							//�`��
	virtual void ShowDebugInfo()	= 0;							//�f�o�b�O���\�L

	virtual HRESULT MakeVertex() { return E_FAIL; };	//���_�o�b�t�@�����֐� �|���S���̏ꍇ�͂��̊֐����I�[�o�[���C�h

	//Set�֐�
	//���z�֐��@���_�o�b�t�@�̍Ē����Ƃ��I�[�o�[���C�h�ł��Ă��炤
	virtual void SetPos(D3DXVECTOR3 const &pos)					{ m_pos = pos; };							//���W
	virtual void SetSize(D3DXVECTOR3 const &size)				{ m_size = size; };							//�T�C�Y
	virtual void SetColor(D3DXCOLOR const &col)					{ m_col = col; };							//�F
	virtual void SetRot(D3DXVECTOR3 const &rot)					{ m_rot = rot; };							//��]��
	virtual void SetScale(D3DXVECTOR3 const &scale)				{ m_scale = scale; };						//�g�嗦
	virtual void SetAnimation(D3DXVECTOR2 const UV, D3DXVECTOR2 const UVsize) {};

	void BindTexture(LPDIRECT3DTEXTURE9 const tex)				{ m_pTexture = tex; };						//�e�N�X�`��
	void BindVtxBuff(LPDIRECT3DVERTEXBUFFER9 const pVtxBuff)	{ m_pVtxBuff = pVtxBuff; };					//���_�o�b�t�@
	void SetMtxWorld(D3DXMATRIX const mtxWorld)					{ m_mtxWorld = mtxWorld; };					//���[���h�}�g���b�N�X
	void SetParentMtxPtr(D3DXMATRIX *pMtx)						{ m_pParentMtx = pMtx; };					//�e�̃}�g���b�N�X�ݒ�
	void SetDisp(bool bDisp)									{ m_bDisp = bDisp; };						//�\����\��
	void SetLighting(bool bLighting)							{ m_bLighting = bLighting; };				//���C�e�B���O�ݒ�

	//Get�֐�
	D3DXVECTOR3 &GetPos()										{ return m_pos; };							//���W
	D3DXVECTOR3 &GetSize()										{ return m_size; };							//�T�C�Y
	D3DXCOLOR &GetColor()										{ return m_col; };							//�F
	D3DXVECTOR3 &GetRot()										{ return m_rot; };							//��]��
	D3DXVECTOR3 &GetScale()										{ return m_scale; };						//�g�嗦
	bool &GetDisp()												{ return m_bDisp; };						//�\����\��
	bool &GetLighting()											{ return m_bLighting; };					//���C�e�B���O���Ă��邩�ǂ���

	LPDIRECT3DTEXTURE9 GetTexture()								{ return m_pTexture; };						//�e�N�X�`���̃|�C���^
	LPDIRECT3DVERTEXBUFFER9 GetVtxBuff()						{ return m_pVtxBuff; };						//���_�o�b�t�@�̃|�C���^
	D3DXVECTOR3 *GetPosPtr()									{ return &m_pos; };							//���W�̃|�C���^�@�����蔻��Ƃ��͂�����g��
	D3DXMATRIX *GetMtxWorldPtr()								{ return &m_mtxWorld; };					//���[���h�}�g���b�N�X
	D3DXMATRIX *GetParentMtxPtr()								{ return m_pParentMtx; };					//�e�̃}�g���b�N�X

	void CalcMtx_IncludeParentMtx();


	//�e���v���[�g�֐�
	//�|���S�������֐�
	//2D3D�����\
	//SharedPtr�𗘗p���ċ��p�Ǘ�����|�C���^
	template<class T>
	static S_ptr<T> ScenePolygonCreateShared
	(D3DXVECTOR3 const & pos, D3DXVECTOR3 const & size, D3DXCOLOR const & col,
		LPDIRECT3DTEXTURE9 const tex, CScene::OBJTYPE const objtype)
	{
		//�������m��
		S_ptr<T> ptr = std::make_shared<T>();

		//���ݒ�
		ptr->SetPos(pos);
		ptr->SetSize(size);
		ptr->SetColor(col);
		ptr->SetObjType(objtype);
		ptr->BindTexture(tex);

		//����������
		ptr->Init();

		//Scene�Ƀ|�C���^��n��
		ptr->SetObjType(objtype);
		ptr->AddSharedList(ptr);
		return ptr;
	}

	//�e���v���[�g�֐�
	//�|���S�������֐�
	//2D3D�����\
	//UniquePtr�ŌĂяo���������Ǘ�
	template<class T>
	static U_ptr<T> ScenePolygonCreateSelfManagement
	(D3DXVECTOR3 const & pos, D3DXVECTOR3 const & size, D3DXCOLOR const & col,
		LPDIRECT3DTEXTURE9 const tex)
	{
		//�������m��
		U_ptr<T> ptr = std::make_unique<T>();

		//���ݒ�
		ptr->SetPos(pos);
		ptr->SetSize(size);
		ptr->SetColor(col);
		ptr->BindTexture(tex);

		//����������
		ptr->Init();

		//return
		return std::move(ptr);
	}

	//�e���v���[�g�֐�
	//�|���S�������֐�
	//2D3D�����\
	//UniquePtr��Scene���Ǘ�
	template<class T>
	static void ScenePolygonCreateSceneManagement
	(D3DXVECTOR3 const & pos, D3DXVECTOR3 const & size, D3DXCOLOR const & col,
		LPDIRECT3DTEXTURE9 const tex, CScene::OBJTYPE const objtype)
	{
		//�������m��
		U_ptr<T> ptr = std::make_unique<T>();

		//���ݒ�
		ptr->SetPos(pos);
		ptr->SetSize(size);
		ptr->SetColor(col);
		ptr->BindTexture(tex);

		//����������
		ptr->Init();

		//Scene�Ƀ|�C���^��n��
		ptr->SetObjType(objtype);
		ptr->AddUniqueList(std::move(ptr));
	}



private:
	LPDIRECT3DTEXTURE9 m_pTexture;							//�e�N�X�`���ւ̃|�C���^
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;						//���_�o�b�t�@�ւ̃|�C���^
	D3DXVECTOR3 m_pos;										//���W
	D3DXVECTOR3 m_size;										//�T�C�Y
	D3DXCOLOR m_col;										//�F
	D3DXVECTOR3 m_rot;										//��]��
	D3DXVECTOR3 m_scale;									//�g�嗦
	D3DXMATRIX m_mtxWorld;									//���[���h�}�g���b�N�X
	D3DXMATRIX *m_pParentMtx;								//�e�̃}�g���b�N�X
	bool m_bDisp;											//�\����\���̐ݒ�
	bool m_bLighting;										//���C�e�B���O���邩�ǂ���

};
#endif

