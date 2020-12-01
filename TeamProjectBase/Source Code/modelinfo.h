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

		//���e�֌W 100�ԑ�
		MODEL_BOMBBOX = 100,						//�{��
		MODEL_BATTERY_SMALL,						//�o�b�e���[
		MODEL_BATTERY_BIG,							//�o�b�e���[

		//���W���[�� 200�ԑ�
		MODEL_MODULE_DEFAULT = 200,					//���W���[��
		MODEL_MODULE_NONE,							//���W���[���@���������ĂȂ�
		MODEL_MODULE_TIMER,							//�^�C�}�[
		MODEL_MODULE_NO0,							//0�Ԗڂ̃��W���[��
		MODEL_MODULE_NO1,							//1�Ԗڂ̃��W���[��
		MODEL_MODULE_NO2,							//2�Ԗڂ̃��W���[��
		MODEL_MODULE_NO3,							//3�Ԗڂ̃��W���[��
		MODEL_MODULE_NO4,							//4�Ԗڂ̃��W���[��

		//���W���[���p�[�c 300�ԑ�
		MODEL_MODULEPARTS_CLEARLAMP = 300,			//�N���A�����v
		MODEL_MODULEPARTS_PROGRESSLAMP,				//�i���x�����v
		MODEL_MODULEPARTS_NO0_KEYPAD,				//1�Ԗڂ̃��W���[���̃p�[�c
		MODEL_MODULEPARTS_NO1_KEYPAD,				//2�Ԗڂ̃��W���[���̃p�[�c
		MODEL_MODULEPARTS_NO2_WIRE,					//2�Ԗڂ̃��W���[���̃p�[�c
		MODEL_MODULEPARTS_NO2_WIRE_CUT,				//2�Ԗڂ̃��W���[���̃p�[�c ���C���[�؂�Ă���
		MODEL_MODULEPARTS_NO3_BUTTON,				//3�Ԗڂ̃��W���[���p�[�c
		MODEL_MODULEPARTS_NO3_DECITION_BUTTON,		//3�Ԗڂ̃��W���[���p�[�c ���M�{�^��

		MODEL_MODULEPARTS_NO4_BUTTON,				//4�Ԗڂ̃��W���[���̃p�[�c

		// �^�u���b�g 400�ԑ�
		MODEL_TABLET = 400,							// �^�u���b�g
		MODEL_TABLET_BUTTON,						// �^�u���b�g�̃{�^��

		// �w�i�I�u�W�F�N�g 500�ԑ�
		MODEL_BACKGROUND = 500,						//�w�i
	};


	typedef struct MODELNAME
	{
		std::string modelname;
		MODEL_TYPE modeltype;
	}MODELNAME;

	static void ModelLoad(HWND hwnd);			//���f������
	static void ModelUnload();					//���f������

	static S_ptr<CModelInfo> GetModelInfo(CModelInfo::MODEL_TYPE modeltype);			//���f�����擾

	//Get�֐�
	std::string GetName()		{ return m_aName; };					//���f����
	LPD3DXMESH GetMesh()		{ return m_mesh; };						//���b�V�����
	LPD3DXBUFFER GetMatBuff()	{ return m_matBuff; };					//���_���
	DWORD GetMatNum()			{ return m_matNum; };					//�}�e���A����
	MODEL_TYPE GetModelType()	{ return m_modeltype; };				//���f���^�C�v

private:
	static Vec<S_ptr<CModelInfo>> m_apModelList;				//���f���ւ̃|�C���^�̃��X�g
	static Vec<MODELNAME> m_aModelFileNameList;					//���f���̃t�@�C����

	MODEL_TYPE		m_modeltype;		//���f���̎��
	std::string		m_aName;			//���f����
	LPD3DXMESH		m_mesh;				//���b�V��
	LPD3DXBUFFER	m_matBuff;			//���_���
	DWORD			m_matNum;			//�}�e���A����

};

#endif


