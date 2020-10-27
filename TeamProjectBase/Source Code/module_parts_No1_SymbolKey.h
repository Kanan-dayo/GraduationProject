//------------------------------------------------------------------------------
//
//���W���[���p�[�c�̃L�[�p�b�h  [module_parts_key.cpp]
//Author:Yoshiki Hosoya
//
//------------------------------------------------------------------------------
#ifndef _MODULE_PARTS_KEY_H_
#define _MODULE_PARTS_KEY_H_
//------------------------------------------------------------------------------
//�C���N���[�h
//------------------------------------------------------------------------------
#include "main.h"
#include "module_parts_base.h"
//------------------------------------------------------------------------------
//�N���X��`
//------------------------------------------------------------------------------
class CTimer;
class CScene3D;

class CModule_Parts_No1_SymbolKey : public CModule_Parts_Base
{
public:

	enum class KEYPAD_STATE
	{
		NORMAL,
		FAILED,
		CLEAR,
	};

	CModule_Parts_No1_SymbolKey();
	virtual ~CModule_Parts_No1_SymbolKey();

	virtual HRESULT Init()			override;			//������
	virtual void Uninit()			override;			//�I��
	virtual void Update()			override;			//�X�V
	virtual void Draw()				override;			//�`��
	virtual void ShowDebugInfo()	override;			//�f�o�b�O���\�L

	void SetSymbol(int nSymbol);
	void SetKeypadState(KEYPAD_STATE keypadstate);

	KEYPAD_STATE GetKeyPadState()				{ return m_KeyPadState; };
	int GetSymbolNum()							{ return m_nSymbolNum; };
protected:

private:
	std::unique_ptr<CScene3D> m_pLight;			//���C�g
	std::shared_ptr<CScene3D> m_pSymbol;		//�V���{��

	KEYPAD_STATE m_KeyPadState;					//���C�g�̏��
	int m_nCntLampCnt;							//���C�g�p�̃J�E���g
	int m_nSymbolNum;							//�V���{���̔ԍ�

};
#endif