//------------------------------------------------------------------------------
//
//X�t�@�C�����f������  [SceneX.cpp]
//Author:Yoshiki Hosoya
//
//------------------------------------------------------------------------------
#ifndef _MODEL_H_
#define _MODEL_H_
//------------------------------------------------------------------------------
//�C���N���[�h
//------------------------------------------------------------------------------
#include "main.h"
#include "SceneBase.h"

//------------------------------------------------------------------------------
//�N���X��`
//------------------------------------------------------------------------------
class CModelInfo;

class CSceneX : public CSceneBase
{
public:
	CSceneX();
	virtual ~CSceneX();

	virtual HRESULT Init();						//������
	virtual void Update();						//�X�V
	virtual void Draw();						//�`��
	virtual void ShowDebugInfo();				//�f�o�b�O���\�L

	void DrawMesh();							//���f���̃��b�V���`��
	void DrawStencil();							//�X�e���V���p�̕`�揈���@�}�e���A���̐ݒ薳��
	void DrawMesh_SetMaterial(D3DXCOLOR col);	//�����̐F�ɉ������}�e���A���ŕ`��
	void DrawShadow();							//�e�̕`��
	void DrawHardEdgeStencil();					//�n�[�h�G�b�W�`��p�̐[�x�o�b�t�@�`��

	void SetSelect(bool Select) { m_bSelecting = Select; };
	bool GetSelect() { return m_bSelecting; };

	static int GetNumSceneX() { return m_nNumSceneX; };												//���擾


	void BindModelInfo(S_ptr<CModelInfo> pSceneXInfo) { m_SceneXInfo = pSceneXInfo; };	//���f���Z�b�g

private:
	static int m_nNumSceneX;									//�����J�E���g
	S_ptr<CModelInfo>	m_SceneXInfo;					//���f�����
	bool m_bSelecting;											//�I������Ă���
};
#endif