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
//�}�N��
//------------------------------------------------------------------------------
#define MODULE_INTERVAL (D3DXVECTOR3(120.0f,50.0f,40.0f))
#define MAX_MODULE_NUM	 (12)
//------------------------------------------------------------------------------
//�N���X��`
//------------------------------------------------------------------------------
class CModule_Base;

class CBomb : public CSceneX , public std::enable_shared_from_this<CBomb>
{
public:

	CBomb();
	virtual ~CBomb();

	virtual HRESULT Init()			override;			//������
	virtual void Update()			override;			//�X�V
	virtual void Draw()				override;			//�`��
	virtual void ShowDebugInfo()	override;			//�f�o�b�O���\�L

	static S_ptr<CBomb> CreateBomb(D3DXVECTOR3 const pos, D3DXVECTOR3 const rot,int const nModuleNum);
	void Operator();							//����
	void ModuleClearCheck();
	void ModuleMiss();							//���W���[���~�X����

private:
	int m_nModuleNum;																	//���W���[����
	int m_nSelectModuleNum;																//�I�����Ă��郂�W���[����
	Vec<S_ptr<CModule_Base>> m_pModuleList;												//���W���[���̃��X�g


	void CreateModule(int const nModuleNum);											//���W���[������
	void CreateModule_Random(int const nModuleNum);

#ifdef _DEBUG
	void CreateModuleDebug();
	static bool m_bCanExplosion;
#endif

	//------------------------------------------------------------------------------
	//���W���[�������֐�
	//------------------------------------------------------------------------------
	template<class Module> bool CreateModuleOne()
	{
		//���W���[�����ő吔�ɒB�����Ƃ�
		if (m_pModuleList.size() >= MAX_MODULE_NUM)
		{
			return false;
		}

		//�ϐ��錾
		int nX = m_pModuleList.size() % 3;
		int nY = m_pModuleList.size() / 3;
		int nZ = m_pModuleList.size() / 6;

		m_pModuleList.emplace_back(CModule_Base::Create_Module<Module>
									(D3DXVECTOR3((-MODULE_INTERVAL.x + (MODULE_INTERVAL.x * nX)) * (1 - (nZ * 2)),
												MODULE_INTERVAL.y - (MODULE_INTERVAL.y * ((nY % 2) * 2)),
												-MODULE_INTERVAL.z + (MODULE_INTERVAL.z * nZ * 2)),
									D3DXVECTOR3(0.0f, (D3DX_PI)* nZ, 0.0f), GetMtxWorldPtr()));

		return true;
	}
};
#endif