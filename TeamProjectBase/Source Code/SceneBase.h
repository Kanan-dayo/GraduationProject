//------------------------------------------------------------------------------
//
//�V�[��2D����  [scene2D.h]
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
	virtual	void Uninit()			= 0;							//�I��
	virtual	void Update()			= 0;							//�X�V
	virtual	void Draw()				= 0;							//�`��
	virtual void ShowDebugInfo()	= 0;							//�f�o�b�O���\�L

	//Set�֐�
	//���z�֐��@���_�o�b�t�@�̍Ē����Ƃ��I�[�o�[���C�h�ł��Ă��炤
	virtual void SetPos(D3DXVECTOR3 const &pos)					{ m_pos = pos; };							//���W
	virtual void SetSize(D3DXVECTOR3 const &size)				{ m_size = size; };							//�T�C�Y
	virtual void SetColor(D3DXCOLOR const &col)					{ m_col = col; };							//�F
	virtual void SetRot(D3DXVECTOR3 const &rot)					{ m_rot = rot; };							//��]��
	virtual void SetDisp(bool bDisp)							{ m_bDisp = bDisp; };						//�\����\��
	virtual void SetAnimation(D3DXVECTOR2 const UV, D3DXVECTOR2 const UVsize) {};

	void BindTexture(LPDIRECT3DTEXTURE9 const tex)				{ m_pTexture = tex; };						//�e�N�X�`��
	void BindVtxBuff(LPDIRECT3DVERTEXBUFFER9 const pVtxBuff)	{ m_pVtxBuff = pVtxBuff; };					//���_�o�b�t�@
	void SetMtxWorld(D3DXMATRIX const mtxWorld)					{ m_mtxWorld = mtxWorld; };					//���[���h�}�g���b�N�X
	void SetParentMtxPtr(D3DXMATRIX *pMtx)						{ m_pParentMtx = pMtx; };					//�e�̃}�g���b�N�X�ݒ�

	//Get�֐�
	D3DXVECTOR3 &GetPos()										{ return m_pos; };							//���W
	D3DXVECTOR3 &GetSize()										{ return m_size; };							//�T�C�Y
	D3DXCOLOR &GetColor()										{ return m_col; };							//�F
	D3DXVECTOR3 &GetRot()										{ return m_rot; };							//��]��
	bool &GetDisp()												{ return m_bDisp; };						//�\����\��

	LPDIRECT3DTEXTURE9 GetTexture()								{ return m_pTexture; };						//�e�N�X�`���̃|�C���^
	LPDIRECT3DVERTEXBUFFER9 GetVtxBuff()						{ return m_pVtxBuff; };						//���_�o�b�t�@�̃|�C���^
	D3DXVECTOR3 *GetPosPtr()									{ return &m_pos; };							//���W�̃|�C���^�@�����蔻��Ƃ��͂�����g��
	D3DXMATRIX *GetMtxWorldPtr()								{ return &m_mtxWorld; };					//���[���h�}�g���b�N�X
	D3DXMATRIX *GetParentMtxPtr()								{ return m_pParentMtx; };					//�e�̃}�g���b�N�X

protected:

private:
	LPDIRECT3DTEXTURE9 m_pTexture;							//�e�N�X�`���ւ̃|�C���^
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;						//���_�o�b�t�@�ւ̃|�C���^
	D3DXVECTOR3 m_pos;										//���W
	D3DXVECTOR3 m_size;										//�T�C�Y
	D3DXCOLOR m_col;										//�F
	D3DXVECTOR3 m_rot;										//��]��
	D3DXMATRIX m_mtxWorld;									//���[���h�}�g���b�N�X
	D3DXMATRIX *m_pParentMtx;								//�e�̃}�g���b�N�X
	bool m_bDisp;											//�\����\���̐ݒ�

};
#endif