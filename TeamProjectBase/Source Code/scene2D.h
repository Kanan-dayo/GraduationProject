//------------------------------------------------------------------------------
//
//�V�[��2D����  [scene2D.h]
//Author:Yoshiki Hosoya
//
//------------------------------------------------------------------------------
#ifndef _SCENE2D_H_
#define _SCENE2D_H_
//------------------------------------------------------------------------------
//�C���N���[�h
//------------------------------------------------------------------------------
#include "main.h"
#include "scene.h"
#include "SceneBase.h"

//------------------------------------------------------------------------------
//�N���X��`
//------------------------------------------------------------------------------
class CScene2D : public CSceneBase
{
public:
	CScene2D();
	virtual ~CScene2D();

	virtual HRESULT Init()												override;						//������
	virtual void Uninit()												override;						//�I��
	virtual void Update()												override;						//�X�V
	virtual void Draw()													override;						//�`��
	virtual void ShowDebugInfo()										override;						//�f�o�b�O���\�L
	void SetAnimation(D3DXVECTOR2 const UV, D3DXVECTOR2 const size)		override;						//�e�N�X�`��UV���W�ݒ�
	void SetSize(D3DXVECTOR3 const size)								override;						//�T�C�Y�ݒ�

	static std::shared_ptr<CScene2D> Create_Shared			(D3DXVECTOR3 const pos, D3DXVECTOR3 const size,D3DXCOLOR const col, OBJTYPE const objtype);		//���������iScene��Return��ŋ��L�Ǘ�
	static void Create_SceneManagement						(D3DXVECTOR3 const pos, D3DXVECTOR3 const size,D3DXCOLOR const col, OBJTYPE const objtype);		//���������iCScene�݂̂ŊǗ�
	static std::unique_ptr<CScene2D> Create_SelfManagement	(D3DXVECTOR3 const pos, D3DXVECTOR3 const size,D3DXCOLOR const col);							//���������iReturn��ŊǗ�

	static int GetNumScene2D()	{ return m_nNumScene2D; };		//2D�̑����擾

protected:
	HRESULT MakeVertex(D3DXVECTOR3 const pos, D3DXVECTOR3 const size, D3DXCOLOR const col);		//���_�o�b�t�@�쐬

private:
	static int m_nNumScene2D;								//����
	float m_fAngle;											//�p�x�@2D�|���S������]���鎞�Ɏg��
	float m_fLength;										//����

};

#endif