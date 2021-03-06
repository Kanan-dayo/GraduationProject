//=============================================================================
//
// チャットの基盤処理 [ chatBase.cpp ]
// Author : KANAN NAGANAWA
//
//=============================================================================
#include "chatBase.h"
#include "chatTab.h"
#include "scene.h"
#include "chatText.h"
#include "ImGui/imgui.h"			// Imguiの実装に必要
#include "ImGui/imgui_impl_dx9.h"	// Imguiの実装に必要
#include "ImGui/imgui_impl_win32.h"	// Imguiの実装に必要

//=============================================================================
// マクロ定義
//=============================================================================

//=============================================================================
// 静的メンバ変数の初期化
//=============================================================================

//=============================================================================
// コンストラクタ
//=============================================================================
CChatBase::CChatBase()
{
	CChatText::LoadFont();
}

//=============================================================================
// デストラクタ
//=============================================================================
CChatBase::~CChatBase()
{
	CChatText::UnloadFont();

	if (m_pTab)
	{
		delete m_pTab;
		m_pTab = nullptr;
	}
}

//=============================================================================
// 生成
//=============================================================================
std::shared_ptr<CChatBase> CChatBase::Create(void)
{
	// メモリ確保
	std::shared_ptr<CChatBase> pBase = std::make_shared<CChatBase>();

	// 確保失敗
	if (!pBase)
		return nullptr;

	// 初期化
	pBase->Init();

	//Sceneにポインタを渡す
	pBase->SetObjType(OBJTYPE_UI);
	pBase->AddSharedList(pBase);

	// 値を返す
	return pBase;
}

//=============================================================================
// 初期化
//=============================================================================
HRESULT CChatBase::Init(void)
{
	m_pTab = CChatTab::Create();

	return S_OK;
}

//=============================================================================
// 更新
//=============================================================================
void CChatBase::Update(void)
{
	if (m_pTab)
		m_pTab->Update();
}

//=============================================================================
// 描画
//=============================================================================
void CChatBase::Draw(void)
{
	if (m_pTab)
		m_pTab->Draw();
}
