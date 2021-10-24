#include "pch.h"

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="_Scale"> 画像の拡大サイズ </param>
/// <param name="_TextureName"> テクスチャのパス </param>
/// <param name="_ObjectTag"> アタッチしたゲームオブジェクトのタグ </param>
/// <param name="_enemyPtr"> プレイヤーのポインタ </param>
EnemyHitPointFrame::EnemyHitPointFrame(const Vector3& _Scale, const std::string& _TextureName,
	const Tag& _ObjectTag, EnemyObject* _enemyPtr)
	: GameObject(_ObjectTag)
	, MOffset(Vector3(-25.0f, 0.0f, 200.0f))
	, mParticlePtr(nullptr)
	, mEnemyPtr(_enemyPtr)
{
	SetState(eDead);

	// テクスチャの取得
	Texture* texture = RENDERER->GetTexture(_TextureName);

	// スクリーン上に描画するコンポーネントクラス
	mParticlePtr = new ParticleComponent(this, texture, _Scale);
}

/// <summary>
/// ゲームオブジェクトのアップデート
/// </summary>
/// <param name="_deltaTime"> 最後のフレームを完了するのに要した時間 </param>
void EnemyHitPointFrame::UpdateGameObject(float _deltaTime)
{
	mPosition = mEnemyPtr->GetPosition() + MOffset;
	SetPosition(mPosition);
}