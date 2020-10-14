//------------------------------------------------------------------------------
//
//���W���[���̏���  [module.cpp]
//Author:Yoshiki Hosoya
//
//------------------------------------------------------------------------------
#ifndef _MODULE_H_
#define _MODULE_H_
//------------------------------------------------------------------------------
//�C���N���[�h
//------------------------------------------------------------------------------
#include "main.h"
#include "SceneX.h"

//------------------------------------------------------------------------------
//�N���X��`
//------------------------------------------------------------------------------
class CModule : public CSceneX
{
public:
	CModule();
	virtual ~CModule();

	virtual HRESULT Init()			override;			//������
	virtual void Uninit()			override;			//�I��
	virtual void Update()			override;			//�X�V
	virtual void Draw()				override;			//�`��
	virtual void ShowDebugInfo()	override;			//�f�o�b�O���\�L

	static std::shared_ptr<CModule> Create(D3DXVECTOR3 const pos,D3DXMATRIX* const pBombMtx);
	void SetParentMtx(D3DXMATRIX* const pBombMtx) { m_pBombMatrix = pBombMtx; };
private:
	D3DXMATRIX *m_pBombMatrix;


};
#endif