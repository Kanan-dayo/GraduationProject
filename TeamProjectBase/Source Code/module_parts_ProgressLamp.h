//------------------------------------------------------------------------------
//
//モジュールの進捗度のランプ  [module_parts_Progresslamp.h]
//Author:Yoshiki Hosoya
//
//------------------------------------------------------------------------------
#ifndef _MODULE_PARTS_PROGRESSLAMP_H_
#define _MODULE_PARTS_PROGRESSLAMP_H_
//------------------------------------------------------------------------------
//インクルード
//------------------------------------------------------------------------------
#include "main.h"
#include "module_parts_base.h"
//------------------------------------------------------------------------------
//クラス定義
//------------------------------------------------------------------------------
class CScene3D;

class CModule_Parts_ProgressLamp : public CModule_Parts_Base
{
public:

	CModule_Parts_ProgressLamp();
	virtual ~CModule_Parts_ProgressLamp();

	virtual HRESULT Init()			override;			//初期化
	virtual void Update()			override;			//更新
	virtual void Draw()				override;			//描画
	virtual void ShowDebugInfo()	override;			//デバッグ情報表記

	void CreateProgressLamp();							//ランプ生成

	void SetProgress(int nProgress);					//進捗度設定
	int GetProgess() { return m_nProgress; };			//進捗度取得

private:
	Vec<S_ptr<CScene3D>> m_pProgressLamp;				//進捗度のランプ
	int m_nProgress;									//進捗度

};
#endif