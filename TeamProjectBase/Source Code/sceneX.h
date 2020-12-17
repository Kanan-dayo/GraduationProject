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

	virtual HRESULT Init()				override;				//������
	virtual void Update()				override;				//�X�V
	virtual void Draw()					override;				//�`��
	virtual void ShowDebugInfo()		override;				//�f�o�b�O���\�L
	static S_ptr<CSceneX> CreateShared(D3DXVECTOR3 const &pos, D3DXVECTOR3 const &rot, D3DXMATRIX *pParentMtx, CScene::OBJTYPE objtype, int nModelType);

	void DrawMesh();											//���f���̃��b�V���`��
	void DrawStencil();											//�X�e���V���p�̕`�揈���@�}�e���A���̐ݒ薳��
	void DrawShadow();											//�e�̕`��
	void DrawHardEdgeStencil();									//�n�[�h�G�b�W�`��p�̐[�x�o�b�t�@�`��

	void DrawMesh_SetMaterial(D3DXCOLOR col, bool bAllCol, Vec<int> const&ChangeColMatNum = {});	//�����̐F�ɉ������}�e���A���ŕ`��

	void SetTextureNum(Vec<int> const &TexNumVec) { m_TexNumber = TexNumVec; };			//�e�N�X�`���ԍ��ݒ�

	void SetSelect(bool Select) { m_bSelecting = Select; };								//�I�����Ă��邩�ݒ�
	void SetCanModuleSelect(bool bSelect) { m_bCanSelect = bSelect; };					//�I���\���ǂ���
	void SetEmissive(bool bEmissive) { m_bEmissive = bEmissive; };						//Emissive�ݒ�
	void BindModelInfo(S_ptr<CModelInfo> pSceneXInfo) { m_SceneXInfo = pSceneXInfo; };	//���f���Z�b�g

	bool GetSelect() { return m_bSelecting; };											//�I�����Ă��邩
	bool GetCanModuleSelect() { return m_bCanSelect; };									//�I���\��
	bool GetEmissive() { return m_bEmissive; };											//Emissive���ǂ���

	static int GetNumSceneX() { return m_nNumSceneX; };									//���擾
	CModelInfo* GetModelInfo(void) { return m_SceneXInfo.get(); }						//���f�����擾

private:
	static int m_nNumSceneX;															//�����J�E���g
	S_ptr<CModelInfo>	m_SceneXInfo;													//���f�����
	bool m_bSelecting;																	//�I������Ă���
	bool m_bCanSelect;																	//�I���\���ǂ���

	bool m_bEmissive;																	//���������n�m���ǂ���

	Vec<int> m_TexNumber;																//�e�N�X�`���ԍ�
};
#endif