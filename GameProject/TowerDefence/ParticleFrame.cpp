#include "pch.h"

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="_owner"> アタッチしたゲームオブジェクトのポインタ </param>
/// <param name="_Scale"> 画像の拡大サイズ </param>
/// <param name="_TextureName"> テクスチャのパス </param>
/// <param name="_ObjectTag"> ゲームオブジェクトのタグ </param>
ParticleFrame::ParticleFrame(GameObject* _owner, const Vector3& _Scale,
	const std::string& _TextureName, const Tag& _ObjectTag)
	: GameObject(_ObjectTag)
	, MOffset(Vector3(0.0f, 0.0f, 90.0f))
	, mOwner(_owner)
{
	SetScale(_Scale);
	SetState(eDead);

	// テクスチャの取得
	Texture* texture = RENDERER->GetTexture(_TextureName);

	// スクリーン上に描画するコンポーネントクラス
	new ParticleComponent(this, texture);
}

/// <summary>
/// ゲームオブジェクトのアップデート
/// </summary>
/// <param name="_deltaTime"> 最後のフレームを完了するのに要した時間 </param>
void ParticleFrame::UpdateGameObject(float _deltaTime)
{
	mPosition = mOwner->GetPosition() + MOffset;
	SetPosition(mPosition);
}