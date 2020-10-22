//------------------------------------------------------------------------------
//
//モジュールのキーパッド処理  [module_keypad.cpp]
//Author:Yoshiki Hosoya
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//インクルード
//------------------------------------------------------------------------------
#include "module_keypad.h"
#include "module_parts_key.h"
#include "renderer.h"
#include "manager.h"
#include "modelinfo.h"
#include "timer.h"
#include "keyboard.h"
#include "game.h"
#include "Mylibrary.h"
#include <algorithm>
//------------------------------------------------------------------------------
//静的メンバ変数の初期化
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//マクロ
//------------------------------------------------------------------------------
#define MAX_KEYPAD (9)
#define KEYPAD_INTERVAL (D3DXVECTOR3(20.0f,20.0f,0.0f))
#define KEYPAD_OFFSET (D3DXVECTOR3(-10.0f,0.0f,-20.0f))

//------------------------------------------------------------------------------
//コンストラクタ
//------------------------------------------------------------------------------
CModule_KeyPad::CModule_KeyPad()
{
	m_pKeyPadList = {};
	m_nNextSymbolNum = 0;
}

//------------------------------------------------------------------------------
//デストラクタ
//------------------------------------------------------------------------------
CModule_KeyPad::~CModule_KeyPad()
{
	m_pKeyPadList.clear();
}
//------------------------------------------------------------------------------
//初期化処理
//------------------------------------------------------------------------------
HRESULT CModule_KeyPad::Init()
{
	//モデル情報設定
	BindModelInfo(CModelInfo::GetModelInfo(CModelInfo::MODEL_MODULE_KEYPAD));

	//ランプ生成
	CModule_Base::CreateLamp();

	//キーパッド生成
	CreateKeyPad(CModule_KeyPad::ANSWER_1);

	CSceneX::Init();
	return S_OK;
}
//------------------------------------------------------------------------------
//終了処理
//------------------------------------------------------------------------------
void CModule_KeyPad::Uninit()
{
	CSceneX::Uninit();
}
//------------------------------------------------------------------------------
//更新処理
//------------------------------------------------------------------------------
void CModule_KeyPad::Update()
{
	CSceneX::Update();
}
//------------------------------------------------------------------------------
//描画処理
//------------------------------------------------------------------------------
void CModule_KeyPad::Draw()
{
	CSceneX::Draw();
}
//------------------------------------------------------------------------------
//デバッグ情報表記
//------------------------------------------------------------------------------
void CModule_KeyPad::ShowDebugInfo()
{
#ifdef _DEBUG

#endif //DEBUG
}
//------------------------------------------------------------------------------
//キーパッド操作
//------------------------------------------------------------------------------
void CModule_KeyPad::Operation()
{
	static int nSelectNum = 0;

	int nSelectNumOld = nSelectNum;
	int nCntClearPad = 0;

	//入力が無かった時はbreak
	CHossoLibrary::Selecting(nSelectNum, nSelectNumOld, 3, 3);

	for (size_t nCnt = 0; nCnt < m_pKeyPadList.size(); nCnt++)
	{
		//nullcheck
		if (m_pKeyPadList[nCnt].get())
		{
			//現在の選択番号と同じモノだけtrueにしておく
			nCnt == nSelectNum ?
				m_pKeyPadList[nCnt]->SetSelect(true) :
				m_pKeyPadList[nCnt]->SetSelect(false);

			//クリアしていた時
			if (m_pKeyPadList[nCnt]->GetKeyPadState() == CModule_Parts_Key::KEYPAD_STATE::CLEAR)
			{
				//クリアカウント++
				nCntClearPad++;
			}
		}
	}

	if (nCntClearPad >= 4)
	{
		CModule_Base::Module_Clear();
	}

	if (CManager::GetKeyboard()->GetTrigger(DIK_RETURN))
	{
		if (m_pKeyPadList[nSelectNum].get())
		{
			if (m_nNextSymbolNum == m_pKeyPadList[nSelectNum]->GetSymbolNum())
			{
				m_pKeyPadList[nSelectNum]->SetKeypadState(CModule_Parts_Key::KEYPAD_STATE::CLEAR);
				m_nNextSymbolNum++;
			}
			else
			{
				m_pKeyPadList[nSelectNum]->SetKeypadState(CModule_Parts_Key::KEYPAD_STATE::FAILED);
				CModule_Base::Module_Failed();

			}

		}
	}

	//nullcheck
	if (CManager::GetKeyboard()->GetTrigger(DIK_BACKSPACE))
	{
		for (size_t nCnt = 0; nCnt < m_pKeyPadList.size(); nCnt++)
		{
			if (m_pKeyPadList[nCnt].get())
			{
				//現在の選択番号と同じモノだけtrueにしておく
				m_pKeyPadList[nCnt]->SetSelect(false);

				CManager::GetGame()->SetGaze(CGame::GAZE_BOMB);
			}
		}
	}

}
//------------------------------------------------------------------------------
//キーパッド生成
//------------------------------------------------------------------------------
void CModule_KeyPad::CreateKeyPad(ANSWER_PATTERN answer)
{
	//シンボルのナンバーのリスト
	std::vector<int> nAllSymbolPatternList(24);
	std::vector<int> nSymbolNumList = {};

	//初期化
	for (int nCnt = 0; nCnt < (int)nAllSymbolPatternList.size(); nCnt++)
	{
		nAllSymbolPatternList[nCnt] = nCnt;
	}

	//答え設定
	for (int nCnt = 0; nCnt < 4; nCnt++)
	{
		//配列に追加
		nSymbolNumList.emplace_back(nAllSymbolPatternList[answer * 4]);

		//削除
		nAllSymbolPatternList.erase(nAllSymbolPatternList.begin() + (answer * 4));
	}

	while (nSymbolNumList.size() <= 9)
	{
		int nNum = rand() % nAllSymbolPatternList.size();

		//ランダムで番号設定
		nSymbolNumList.emplace_back(nAllSymbolPatternList[nNum]);
		nAllSymbolPatternList.erase(nAllSymbolPatternList.begin() + nNum);
	}



	//for (auto iterator = nAllSymbolPatternList.begin(); iterator != nAllSymbolPatternList.end(); iterator++)
	//{
	//	//std::find_if()
	//}

	////答えの設定
	//for (int nCnt = 0; nCnt < 4; nCnt++)
	//{
	//	//答えの分を設定
	//	nSymbolNumList.emplace_back();
	//	nAllSymbolPatternList.erase(nAllSymbolPatternList.begin() + nCnt + answer * 4);
	//}


	for (int nCnt = 0; nCnt < MAX_KEYPAD; nCnt++)
	{
		INTEGER2 Value;

		Value.nX = nCnt % 3;
		Value.nY = nCnt / 3;

		m_pKeyPadList.emplace_back(CModule_Parts_Base::Create_ModuleParts<CModule_Parts_Key>
			(KEYPAD_OFFSET + D3DXVECTOR3(	-KEYPAD_INTERVAL.x + KEYPAD_INTERVAL.x * Value.nX,
											KEYPAD_INTERVAL.y - KEYPAD_INTERVAL.y * Value.nY, 0.0f), GetMtxWorldPtr()));

		m_pKeyPadList[m_pKeyPadList.size() - 1]->SetSymbol(nSymbolNumList[nCnt]);

	}
}
