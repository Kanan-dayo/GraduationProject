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
#define MODULE_INTERVAL (D3DXVECTOR3(125.0f,100.0f,80.0f))
#define MAX_MODULE_NUM	 (12)
//------------------------------------------------------------------------------
//�N���X��`
//------------------------------------------------------------------------------
class CModule_Base;
class CBomb_Exterior;

class CBomb : public CSceneX , public std::enable_shared_from_this<CBomb>
{
public:

	//��Փx
	enum DIFFICULTY
	{
		EASY,
		NORMAL,
		HARD,
	};

	CBomb();
	virtual ~CBomb();

	virtual HRESULT Init()			override;									//������
	virtual void Update()			override;									//�X�V
	virtual void Draw()				override;									//�`��
	virtual void ShowDebugInfo()	override;									//�f�o�b�O���\�L

	static S_ptr<CBomb> CreateBomb(D3DXVECTOR3 const pos, D3DXVECTOR3 const rot, DIFFICULTY const difficulty);
	void Operation_Keyboard();													//����@�L�[�{�[�h
	void Operation_Mouse();														//����@�}�E�X
	void Operation_Camera();													//�J��������

	void ModuleClearCheck();													//�N���A�������`�F�b�N
	void ModuleMiss();															//���W���[���~�X����

	CBomb_Exterior *GetBombExterior() { return m_pBombExterior.get(); };		//���W���[���O���̃|�C���^�擾
private:
	D3DXVECTOR3 m_RotDest;														//��]�̌����
	int m_nModuleNum;															//���W���[����
	int m_nSelectModuleNum;														//�I�����Ă��郂�W���[����
	bool m_bCameraDir;															//�J���������ʌ����Ă��邩
	DIFFICULTY m_difficulty;													//��Փx
	Vec<S_ptr<CModule_Base>> m_pModuleList;										//���W���[���̃��X�g
	U_ptr<CBomb_Exterior> m_pBombExterior;										//���e�̊O���̃|�C���^

	void CreateModule();								//���W���[������
	void CreateModule_Random();													//���W���[�������@�����_���z�u
	void ModuleSelect();														//���W���[���̐��󏈗�
	void SearchHeadCanSelectNum(int nStartNum);									//��ԍŏ��̑I���\�ԍ�����
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
		int nY = (m_pModuleList.size() / 3) % 2;
		int nZ = m_pModuleList.size() / 6;

		if (nZ)
		{
			nX = 2 - nX;
		}

		m_pModuleList.emplace_back(CModule_Base::Create_Module<Module>
					(D3DXVECTOR3(CHossoLibrary::CalcEvenPosition(3, nX, MODULE_INTERVAL.x),
									CHossoLibrary::CalcEvenPosition(2, nY, -MODULE_INTERVAL.y),
									CHossoLibrary::CalcEvenPosition(2, nZ, MODULE_INTERVAL.z)),
				D3DXVECTOR3(0.0f, (D3DX_PI)* nZ, 0.0f), GetMtxWorldPtr()));

		return true;
	}
};
#endif