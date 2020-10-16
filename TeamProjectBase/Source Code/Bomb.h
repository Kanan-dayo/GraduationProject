//------------------------------------------------------------------------------
//
//���e�̏���  [Bomb.cpp]
//Author:Yoshiki Hosoya
//
//------------------------------------------------------------------------------
#ifndef _BOMB_H_
#define _BOMB_H_
//------------------------------------------------------------------------------
//�C���N���[�h
//------------------------------------------------------------------------------
#include "main.h"
#include "SceneX.h"

//------------------------------------------------------------------------------
//�N���X��`
//------------------------------------------------------------------------------
class CModule_Base;

class CBomb : public CSceneX
{
public:
	CBomb();
	virtual ~CBomb();

	virtual HRESULT Init()			override;			//������
	virtual void Uninit()			override;			//�I��
	virtual void Update()			override;			//�X�V
	virtual void Draw()				override;			//�`��
	virtual void ShowDebugInfo()	override;			//�f�o�b�O���\�L

	static std::shared_ptr<CBomb> Create(D3DXVECTOR3 const pos, D3DXVECTOR3 const rot,int const nModuleNum);

private:
	int m_nModuleNum;																		//���W���[����
	std::vector<std::shared_ptr<CModule_Base>> m_pModuleList;							//���W���[���̃��X�g

	void CreateModule(int const nModuleNum);											//���W���[������
};
#endif