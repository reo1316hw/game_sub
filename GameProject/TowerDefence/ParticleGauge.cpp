#include "pch.h"

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="_owner"> アタッチしたゲームオブジェクトのポインタ </param>
/// <param name="_Scale"> 画像の拡大サイズ </param>
/// <param name="_TextureName"> テクスチャのパス </param>
/// <param name="_ObjectTag"> ゲームオブジェクトのタグ </param>
ParticleGauge::ParticleGauge(GameObject* _owner, const Vector3& _Scale,
	const std::string& _TextureName, const Tag& _ObjectTag)
	: GameObject(_ObjectTag)
	, MOffset(Vector3(0.0f, 0.0f, 100.0f))
	, mOwner(_owner)
{
	SetScale(_Scale);
	SetState(eDead);

	// テクスチャの取得
	Texture* texture = RENDERER->GetTexture(_TextureName);

	// hpゲージを制御するコンポーネントクラスを生成
	new TextureSizeChanger(this, mOwner);

	// スクリーン上に描画するコンポーネントクラスを生成
	new ParticleComponent(this, texture);
}

/// <summary>
/// ゲームオブジェクトのアップデート
/// </summary>
/// <param name="_deltaTime"> 最後のフレームを完了するのに要した時間 </param>
void ParticleGauge::UpdateGameObject(float _deltaTime)
{
	mPosition = mOwner->GetPosition() + MOffset;
	SetPosition(mPosition);
}