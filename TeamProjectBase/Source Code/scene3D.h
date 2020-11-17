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

	virtual HRESULT Init()													override;			//������
	virtual void Update()													override;			//�X�V
	virtual void Draw()														override;			//�`��
	virtual void ShowDebugInfo()											override;			//�f�o�b�O���\�L
	void SetAnimation(D3DXVECTOR2 const UV, D3DXVECTOR2 const size)			override;			//�e�N�X�`��UV���W�ݒ�
	HRESULT MakeVertex()													override;			//���_�o�b�t�@�쐬

	void DrawSettingMtx(D3DXMATRIX const &Mtx);													//�n�����Ōv�Z�������[���h�}�g���b�N�X�����ɕ`��
	void DrawPolygon();																			//�|���S���̕`��

	void SetBillBoard(bool bBillBoard)	{ m_bBillBoard = bBillBoard;};							//�r���{�[�h��
	bool GetBillBoard() { return m_bBillBoard; };												//�r���{�[�h���ǂ����擾

	static int GetNumScene3D() { return m_nNumScene3D; };										//3D�|���S�������擾

protected:
private:
	static int m_nNumScene3D;		//3D�|���S���̑���
	bool m_bBillBoard;				//�r���{�[�h���ǂ���
};
#endif