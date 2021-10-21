#pragma once

/// <summary>
/// hpゲージを制御する
/// </summary>
class HitPointGaugeController : public Component
{
public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="_owner"> アタッチしたオブジェクトのポインタ </param>
	/// <param name="_texture"> テクスチャ情報 </param>
	HitPointGaugeController(GameObject* _owner, Texture* _texture);
	
	/// <summary>
	/// デストラクタ
	/// </summary>
	~HitPointGaugeController() {};

	/// <summary>
	/// フレーム毎の処理
	/// </summary>
	/// <param name="_deltaTime"> 最後のフレームを完了するのに要した時間 </param>
	void Update(float _deltaTime)override;

private:

	// 変更後のテクスチャの横幅
	int mTextureWidthAfterChange;
	// テクスチャの最大横幅
	int mTextureMaxWidth;
	// 現在の体力
	int mNowHp;

	// 最大体力
	float mMaxHp;

public:// ゲッターセッター

	/// <summary>
	/// 変更後のテクスチャの横幅を取得する
	/// </summary>
	/// <returns> 変更後のテクスチャの横幅 </returns>
	int GetTextureWidthAfterChange() { return mTextureWidthAfterChange; }
};