//------------------------------------------------------------------------------
//
//�V�[��3D����  [scene3D.h]
//Author:Yoshiki Hosoya
//
//------------------------------------------------------------------------------
#ifndef _SCENE3D_H_
#define _SCENE3D_H_
//------------------------------------------------------------------------------
//�C���N���[�h
//------------------------------------------------------------------------------
#include "main.h"
#include "scenebase.h"

//------------------------------------------------------------------------------
//�N���X��`
//------------------------------------------------------------------------------
class CScene3D : public CSceneBase
{
public:

	CScene3D();
	virtual ~CScene3D();

	virtual HRESULT Init();								//������
	virtual void Uninit();								//�I��
	virtual void Update();								//�X�V
	virtual void Draw();								//�`��
	virtual void ShowDebugInfo();						//�f�o�b�O���\�L

	void DrawSettingMtx(D3DXMATRIX const &Mtx);				//�n�����Ōv�Z�������[���h�}�g���b�N�X�����ɕ`��
	void DrawPolygon();										//�|���S���̕`��

	void SetAnimation(D3DXVECTOR2 const UV, D3DXVECTOR2 const size) override;		//�e�N�X�`��UV���W�ݒ�
	void SetBillBoard(bool bBillBoard)	{ m_bBillBoard = bBillBoard;};		//�r���{�[�h��

	bool BetBillBoard() { return m_bBillBoard; };
	static int GetNumScene3D() { return m_nNumScene3D; };												//3D�|���S�������擾

	static std::shared_ptr<CScene3D> Create_Shared			(D3DXVECTOR3 const pos, D3DXVECTOR3 const size,D3DXCOLOR const col, OBJTYPE const objtype);		//���������iScene��Return��ŋ��L�Ǘ�
	static void Create_SceneManagement						(D3DXVECTOR3 const pos, D3DXVECTOR3 const size,D3DXCOLOR const col, OBJTYPE const objtype);		//���������iCScene�݂̂ŊǗ�
	static std::unique_ptr<CScene3D> Create_SelfManagement	(D3DXVECTOR3 const pos, D3DXVECTOR3 const size,D3DXCOLOR const col);							//���������iReturn��ŊǗ�


protected:
	HRESULT MakeVertex(D3DXVECTOR3 const pos, D3DXVECTOR3 const size, D3DXCOLOR const col);		//���_�o�b�t�@�쐬

private:
	static int m_nNumScene3D;

	bool m_bBillBoard;										//�r���{�[�h���ǂ���
};
#endif