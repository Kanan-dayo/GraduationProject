//------------------------------------------------------------------------------
//
//�V�[������  [scene.h]
//Author:Yoshiki Hosoya
//
//------------------------------------------------------------------------------
#ifndef _SCENE_H_
#define _SCENE_H_
//------------------------------------------------------------------------------
//�C���N���[�h
//------------------------------------------------------------------------------
#include "main.h"
//------------------------------------------------------------------------------
//�}�N��
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//�N���X��`
//------------------------------------------------------------------------------
class CScene2D;

class CScene
{
public:

	enum OBJTYPE
	{
		OBJTYPE_NONE = 0,					//���ݒ�
		OBJTYPE_BACK,						//���
		OBJTYPE_MESHFIELD,					//���b�V��
		OBJTYPE_MAPOBJECT,					//�}�b�v�ɔz�u�����I�u�W�F�N�g
		OBJTYPE_PICTURE,					// �s�N�`��
		OBJTYPE_PICTURE_SYMBOL,				// �s�N�`��3D�|���S��
		OBJTYPE_BOMB,						//���e
		OBJTYPE_BOMB_EXTERIOR,				//���e�̑����i
		OBJTYPE_MODULE,						//���W���[��
		OBJTYPE_MODULE_PARTS,				//���W���[���̃p�[�c
		OBJTYPE_MODULE_PARTS_SYMBOL,		//���W���[���̃p�[�c��̃|���S��
		OBJTYPE_EFFECT,						//�G�t�F�N�g
		OBJTYPE_UI,							//UI
		OBJTYPE_NUMBER,						//����
		OBJTYPE_PAUSE,						//�|�[�Y
		OBJTYPE_OPTION,						//�I�v�V����
		OBJTYPE_FRONT,						//�O��
		OBJTYPE_DEBUG,						//�f�o�b�O�n
		OBJTYPE_MAX							//�ő�l
	};

	CScene();

	//�������z�֐��@�I�[�o�[���C�h�p
	virtual ~CScene();
	virtual HRESULT Init() = 0;														//������
	virtual void Update() = 0;														//�X�V
	virtual void Draw() = 0;														//�`��
	virtual void ShowDebugInfo() = 0;												//�f�o�b�O���\�L

	static void ShowNumAll();

	static void ReleaseAll();															//�������J��
	static void UpdateAll();															//�X�V����
	static void DrawAll();																//�`�揈��
	static void ShowDebugInfoAll();														//�S�Ẵf�o�b�O���\�L����

	static void ReleaseSpecificObject(OBJTYPE objtype);									//�I�������I�u�W�F�N�g�^�C�v��S�ă����[�X


	void Release()								{ m_bDeadFlag = true; };				//�������J��
	void SetObjType(OBJTYPE objtype)			{ m_objtype = objtype; };				//�I�u�W�F�N�g�^�C�v�ݒ�֐�

	static void SetStop(bool bStop)				{ m_bStop = bStop; };					//�X�g�b�v����
	static void Set1FAction()					{ m_b1FAction = true; };				//�PF�����i�߂鏈��

	bool GetDeleteFlag()						{ return m_bDeadFlag; };				//���S�t���O�擾
	CScene::OBJTYPE GetObjType()				{ return m_objtype; };					//�I�u�W�F�N�g�̎�ގ擾

	static int GetNumAll()						{ return m_nNumAll; };					//�����擾
	static bool GetStop()						{ return m_bStop; };					//�X�g�b�v��Ԃ��擾
	static void GetSceneList(OBJTYPE objtype, Vec<S_ptr<CScene>> &SceneList);			//�V�[�����擾�i�z�񂲂Ɓj

	//Unique_ptr�̃��X�g�ɒǉ�
	template <class T> void AddUniqueList(T ptr)
	{
		//���j�[�N�|�C���^�̃��X�g�Ɏ�����ǉ�
		m_UniqueSceneList[ptr->m_objtype].emplace_back(std::move(ptr));
	};

	//Shared_ptr�̃��X�g�ɒǉ�
	template <class T> void AddSharedList(T ptr)
	{
		//���L�|�C���^�̃��X�g�Ɏ�����ǉ�
		m_SharedSceneList[m_objtype].emplace_back(ptr);
	};

protected:

private:
	static Vec<U_ptr<CScene>> m_UniqueSceneList[OBJTYPE_MAX];		//���j�[�N�|�C���^�@�Ɛ肷�ׂ��|�C���^
	static Vec<S_ptr<CScene>> m_SharedSceneList[OBJTYPE_MAX];		//�V�F�A�|�C���^	���L����鎖������Ǝv����|�C���^
	static int m_nNumAll;					//�I�u�W�F�N�g����
	static int m_nCntStop;					//�X�g�b�v�̃J�E���g
	static bool m_bStop;					//��ʃX�g�b�v���邩�ǂ���
	static bool m_b1FAction;				//1F�����A�N�V�������邩

	bool m_bNonStop;						//�X�g�b�v���Ȃ�
	bool m_bDeadFlag;						//���S�t���O
	OBJTYPE	m_objtype;						//�^�C�v

#ifdef _DEBUG
	static Vec<int> m_fUpdateTimeList;
	static Vec<int> m_fDrawTimeList;
#endif //_DEBUG
};

#endif

