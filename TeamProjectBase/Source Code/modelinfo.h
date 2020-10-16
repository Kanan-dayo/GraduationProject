//------------------------------------------------------------------------------
//
//���f�����Ǘ�  [modelinfo.cpp]
//Author:Yoshiki Hosoya
//
//------------------------------------------------------------------------------
#ifndef _MODELINFO_H_
#define _MODELINFO_H_
//------------------------------------------------------------------------------
//�C���N���[�h
//------------------------------------------------------------------------------
#include "main.h"

//------------------------------------------------------------------------------
//�N���X��`
//------------------------------------------------------------------------------
//�O���錾
class CModelInfo
{
public:
	CModelInfo();
	~CModelInfo();

	enum MODEL_TYPE
	{
		MODEL_NONE = -1,

		//�I�u�W�F�N�g 0�ԑ�
		MODEL_MAPOBJECT_BLOCK,					//�I�u�W�F�N�g�@�u���b�N
		MODEL_MAPOBJECT_SPHERE,					//�I�u�W�F�N�g�@�X�t�B�A

		//���e�֌W 100�ԑ�
		MODEL_BOMBOBJECT_BOMB,					//�I�u�W�F�N�g�@�{��
		MODEL_BOMBOBJECT_MODULE,				//�I�u�W�F�N�g�@���W���[��
		MODEL_BOMBOBJECT_MODULE_NONE,			//�I�u�W�F�N�g�@���W���[���@���������ĂȂ�
		MODEL_BOMBOBJECT_CLEARLAMP,				//�I�u�W�F�N�g�@�N���A�����v
		MODEL_BOMBOBJECT_TIMER,					//�I�u�W�F�N�g�@�^�C�}�[

	};


	typedef struct MODELNAME
	{
		std::string modelname;
		MODEL_TYPE modeltype;
	}MODELNAME;

	static void ModelLoad(HWND hwnd);			//���f������
	static void ModelUnload();					//���f������

	static std::shared_ptr<CModelInfo> GetModelInfo(CModelInfo::MODEL_TYPE modeltype);			//���f�����擾

	//Get�֐�
	std::string GetName()		{ return m_aName; };					//���f����
	LPD3DXMESH GetMesh()		{ return m_mesh; };						//���b�V�����
	LPD3DXBUFFER GetMatBuff()	{ return m_matBuff; };					//���_���
	DWORD GetMatNum()			{ return m_matNum; };					//�}�e���A����
	MODEL_TYPE GetModelType()	{ return m_modeltype; };				//���f���^�C�v

private:
	static std::vector<std::shared_ptr<CModelInfo>> m_apModelList;		//���f���ւ̃|�C���^�̃��X�g
	static std::vector<MODELNAME> m_aModelFileNameList;					//���f���̃t�@�C����

	MODEL_TYPE		m_modeltype;		//���f���̎��
	std::string		m_aName;			//���f����
	LPD3DXMESH		m_mesh;				//���b�V��
	LPD3DXBUFFER	m_matBuff;			//���_���
	DWORD			m_matNum;			//�}�e���A����

};

#endif


