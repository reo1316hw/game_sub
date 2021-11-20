#include "pch.h"

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="_Scale"> 画像の拡大サイズ </param>
/// <param name="_TextureName"> テクスチャのパス </param>
/// <param name="_ObjectTag"> アタッチしたゲームオブジェクトのタグ </param>
/// <param name="_enemyPtr"> プレイヤーのポインタ </param>
EnemyHitPointGauge::EnemyHitPointGauge(const Vector3& _Scale, const std::string& _TextureName,
	const Tag& _ObjectTag, EnemyObject* _enemyPtr)
	: GameObject(_ObjectTag)
	, MOffset(Vector3(0.0f, 0.0f, 100.0f))
	, mEnemyPtr(_enemyPtr)
{
	SetScale(_Scale);
	SetState(eDead);

	// テクスチャの取得
	Texture* texture = RENDERER->GetTexture(_TextureName);

	// hpゲージを制御するコンポーネントクラス
	HitPointGaugeController* hitPointGaugeControllerPtr = new HitPointGaugeController(this, mEnemyPtr);

	// スクリーン上に描画するコンポーネントクラス
	new ParticleComponent(this, texture);
}

/// <summary>
/// ゲームオブジェクトのアップデート
/// </summary>
/// <param name="_deltaTime"> 最後のフレームを完了するのに要した時間 </param>
void EnemyHitPointGauge::UpdateGameObject(float _deltaTime)
{
	mPosition = mEnemyPtr->GetPosition() + MOffset;
	SetPosition(mPosition);
}