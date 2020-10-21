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
#define MODULE_INTERVAL (D3DXVECTOR3(120.0f,50.0f,60.0f))
#define MAX_MODULE_NUM	 (12)
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

	static std::shared_ptr<CBomb> CreateBomb(D3DXVECTOR3 const pos, D3DXVECTOR3 const rot,int const nModuleNum);

private:
	int m_nModuleNum;																		//���W���[����
	std::vector<std::shared_ptr<CModule_Base>> m_pModuleList;							//���W���[���̃��X�g

	void CreateModule(int const nModuleNum);											//���W���[������

	//�e���v���[�g�֐�
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