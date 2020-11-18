//------------------------------------------------------------------------------
//
//���C�u��������  [hossolibrary.h]
//Author:Yoshiki Hosoya
//
//------------------------------------------------------------------------------
#ifndef _HOSSOLIBRARY_H_
#define _HOSSOLIBRARY_H_
//------------------------------------------------------------------------------
//�C���N���[�h
//------------------------------------------------------------------------------
#include "texture.h"
#include "Debug/debugproc.h"
#include "ImGui/Imgui.h"
#include "ImGui/imgui_impl_dx9.h"
#include "ImGui/imgui_impl_win32.h"

//------------------------------------------------------------------------------
//�}�N��
//------------------------------------------------------------------------------
#define ZeroVector4			(D3DXVECTOR4(0.0f, 0.0f, 0.0f, 0.0f))		//�������p �S��0.0f
#define ZeroVector3			(D3DXVECTOR3(0.0f, 0.0f, 0.0f))				//�������p �S��0.0f
#define ZeroVector2			(D3DXVECTOR2(0.0f, 0.0f))					//�������p �S��0.0f
#define OneVector3			(D3DXVECTOR3(1.0f, 1.0f, 1.0f))				//�������p �S��1.0f
#define OneVector2			(D3DXVECTOR2(1.0f, 1.0f))					//�������p �S��1.0f
#define ZeroColor			(D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f))			//����
#define WhiteColor			(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f))			//��
#define RedColor			(D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f))			//��
#define GreenColor			(D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f))			//��
#define BlueColor			(D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f))			//��
#define YellowColor			(D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f))			//��
#define OrangeColor			(D3DXCOLOR(1.0f, 0.5f, 0.0f, 1.0f))			//��
#define MagentaColor		(D3DXCOLOR(1.0f, 0.5f, 0.0f, 1.0f))			//�}�[���_
#define BlackColor			(D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f))			//��

#define MAX_TEXT			(128)
#define SCREEN_CENTER_POS	(D3DXVECTOR3(SCREEN_WIDTH * 0.5f , SCREEN_HEIGHT * 0.5f ,0.0f))			//��ʒ����̍��W
#define SCREEN_SIZE			(D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT,0.0f))							//��ʂ̃T�C�Y
#define NEWLINE				("\n")																	//���s
#define COMMENT01			("//\n")																//�e�L�X�g�p�@�R�����g�@���s
#define COMMENT02			("//------------------------------------------------------------\n")	//�e�L�X�g�p�@��
#define EQUAL				("=")																	//�e�L�X�g�p�@�C�R�[��

//------------------------------------------------------------------------------
//�\���̒�`
//------------------------------------------------------------------------------
//int�^��3�i�[�ł���
typedef struct MODEL_VTX
{
	D3DXVECTOR3 VtxMax;	//�ő咸�_
	D3DXVECTOR3 VtxMin;	//�ŏ����_

	//�R���X�g���N�^
	MODEL_VTX() {};
	MODEL_VTX(D3DXVECTOR3 MinSize, D3DXVECTOR3 MaxSize)
	{
		VtxMin = MinSize;
		VtxMax = MaxSize;
	};

}MODEL_VTX;

// �^�O
enum class TAG
{
	NONE = -1,
	PLAYER_1,			// �v���C���[1
	ENEMY,				// �G
};

enum class DIRECTION
{
	NONE = -1,
	LEFT,
	RIGHT,
	UP,
	DOWN,
};

//------------------------------------------------------------------------------
//�G�C���A�X�錾
//------------------------------------------------------------------------------
using FILENAME_LIST = std::vector<std::string>;		//�t�@�C�����̃��X�g

//------------------------------------------------------------------------------
//�N���X��`
//------------------------------------------------------------------------------
class CKeyboard;
class CPad_XInput;
class CModelInfo;


class CHossoLibrary
{
public:

	//���͂̎��
	enum INPUTTYPE
	{
		PRESS = 0,	//�v���X
		TRIGGER,	//�g���K�[
		MAX
	};

	static bool CheckMove(DIRECTION);								//�ړ��p�֐�(AWSD + CrossKey) Press
	static DIRECTION CheckSelect();									//�Z���N�g�p�֐�(AWSD + ARROW + LStick) Trigger

	static bool CheckDecision();									//����{�^��
	static bool CheckCancel();										//�L�����Z���{�^��
	static bool CheckPause();										//�|�[�Y
	static bool CheckAnyButton();									//�����{�^�����B�B
	static void ResetStickInfo();									//�X�e�B�b�N�̃g���K�[��񃊃Z�b�g

	static bool Check3DMoveStick(D3DXVECTOR3 &Move, float const fMove, float const fCameraRot, float &fRotGoal);	//3D�p�@LStick�@�ړ��ʌv�Z
	static bool Check3DCameraStick(D3DXVECTOR3 &Rot, float fHolizonMove, float fVerticalMove);					//3D�p�@RStick�@�ړ��ʌv�Z

	static void StartVibration(int nCntVibration);					//�o�C�u���[�V��������

	static void CalcMatrix(D3DXMATRIX *pMtx, D3DXVECTOR3 const &rPos, D3DXVECTOR3 const &rRot, D3DXVECTOR3 const &rScale);		//���[���h�}�g���b�N�X�v�Z
	static void CalcShadowMatrix(D3DXMATRIX &rShadowMtx, D3DXVECTOR3 const &rPos, D3DXVECTOR3 const &rNor);						//�V���h�[�}�g���b�N�X�̌v�Z
	static D3DXVECTOR3 CalcMtxToVector3(D3DXMATRIX const & rMtx);																//�}�g���b�N�X��Vector3�ɕϊ�
	static bool MouseRayCollision_Boolean(D3DXMATRIX *pMtx, LPD3DXMESH pMesh);											//�}�E�X�̃��C�̔���


	static void SetModelVertex(MODEL_VTX &pModelVtx, CModelInfo &pModelInfo);													//���f���̍ő咸�_�ƍŏ����_��ݒ�
	static void SetBillboard(D3DXMATRIX *pMtx);																					//�r���{�[�h�ݒ�
	static void SetBillboard_XZ_Only(D3DXMATRIX *pMtx);																			//�r���{�[�h�ݒ�@X��Z�̂�

	static void SelectVerticalMenu(int &nSelectNum, int const &nMaxSelect);														//�c���j���[�̑I��
	static void SelectHorizonMenu(int &nSelectNum, int const &nMaxSelect);														//�����j���[�̑I��

	static HRESULT InitImgui(HWND hWnd);	//Imgui��������

	static void UninitImgui();				//Imgui�I��
	static void ShowDebugInfo();			//�f�o�b�O���\��
	static void CheckWireMode();			//���C���[�t���[���m�F
	static void CheckCulling();				//�J�����O�m�F
	static void CheckLighting();			//���C�e�B���O�m�F

	static bool ImGui_Combobox(std::vector<std::string> aItemNameList, std::string aTitle, int & nValue);		//ImGui�̃R���{�{�b�N�X

	static int RandomRangeUnsigned(int nMin, int nMax);							//�����_���ɒl��Ԃ��֐��@int�^�@�����Ȃ�
	static float Random_PI();													//-3.14����3.14�܂ł̃����_���ŕԂ�
	static float Random(float fInputValue);										//���͂��ꂽ�l��+-�����_���Ȓl�ŕԂ�
	static D3DXVECTOR3 RandomVector3(float Max);								//�����_����vector3�^�Œl��Ԃ�
	static void CalcRotation(float &fRot);										//��]��360�x�ȓ��ɂ���v�Z
	static void CalcRotation_XYZ(D3DXVECTOR3 &rot);								//��]��360�x�ȓ��ɂ���v�Z

	static bool Selecting(int &nSelectNum, int const &nSelectNumOld, int const nNumX, int const nNumY);
	static D3DXVECTOR2 CalcUV_StaticFunc(int nNumUV, int tex);

	//------------------------------------------------------------------------------
	//�͈͓��̒l�ɏC������֐�
	//int�ł�float�ł�������悤�Ƀe���v���[�g
	//------------------------------------------------------------------------------
	template <class X> static bool RangeLimit_Equal(X &Value, X const &Min, X const &Max)
	{
		//�ŏ��l��菬������
		if (Value < Min)
		{
			//�ŏ��l�ɍ��킷
			Value = Min;
			return true;
		}
		//�ő�l���傫����
		if (Value > Max)
		{
			//�ő�l�ɍ��킷
			Value = Max;
			return true;
		}
		return false;
	}
	//------------------------------------------------------------------------------
	//A��B�����ւ��鏈��
	//int�ł�float�ł�������悤�Ƀe���v���[�g
	//------------------------------------------------------------------------------
	template <class X> static void Swap(X &ValueA, X &ValueB)
	{
		X SaveValue = ValueA;
		ValueA = ValueB;
		ValueB = SaveValue;
	}

	//------------------------------------------------------------------------------
	//vector�^�p�@�V���b�t������
	//------------------------------------------------------------------------------
	template <class X> static void Vec_Shuffle(std::vector<X> &vec)
	{
		//�T�C�Y��
		for (int nCnt = 0; nCnt < (int)vec.size(); nCnt++)
		{
			//������̔z��ԍ��������_���Őݒ�
			int SwapIterator = rand() % (vec.size() - 1);

			//����ւ�
			CHossoLibrary::Swap(vec[nCnt], vec[SwapIterator]);
		}
	}

	//------------------------------------------------------------------------------
	//Ray����p�@CSceneX�p���O��
	//Ray�Ŕ���������true���Ԃ��Ă�������
	//------------------------------------------------------------------------------
	template <class Itr> static bool RayCollision_ModuleSelect(Itr begin, Itr end, int &nSelectNum)
	{
		bool bModuleHit = false;
		int nCnt = -1;


		for (Itr itr = begin ; itr != end; itr++)
		{
			//�J�E���g�A�b�v
			nCnt++;

			//�I���ł��Ȃ����W���[���������ꍇ
			if (!itr->get()->GetCanModuleSelect() || bModuleHit)
			{
				//�v�Z���Ȃ�
				itr->get()->SetSelect(false);

				continue;
			}
			else
			{
				//�}�E�X��Ray�̔���
				bModuleHit = CHossoLibrary::MouseRayCollision_Boolean(itr->get()->GetMtxWorldPtr(), itr->get()->GetModelInfo()->GetMesh());

				// HIT������
				if (bModuleHit)
				{
					//�I�����
					itr->get()->SetSelect(true);

					//�I��ԍ��ݒ�
					nSelectNum = nCnt;
				}
				else
				{
					//�I������
					itr->get()->SetSelect(false);
				}
			}
		}
		//�����q�b�g���Ȃ��������̓J�E���g����
		if (!bModuleHit)
		{
			nSelectNum = -1;
		}

		//return
		return bModuleHit;
	}

private:
	static CKeyboard *m_pKeyboard;		//�L�[�{�[�h�ւ̃|�C���^
	static CPad_XInput *m_pXInput;		//XInput�̃p�b�h�ւ̃|�C���^
	static float m_fLeftStickX;			//���X�e�B�b�N�̏��
	static float m_fLeftStickY;			//���X�e�B�b�N�̏��
	static bool m_bStickX;				//�X�e�B�b�N���|��Ă邩�ǂ���
	static bool m_bStickY;				//�X�e�B�b�N���|��Ă邩�ǂ���6

	static bool m_WireFrame;			//���C���[�t���[����
	static bool m_Lighting;				//���C�e�B���O���邩
	static int m_Culling;				//�J�����O���


};

#endif