#include "pch.h"

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="_owner"> アタッチするゲームオブジェクトのポインタ </param>
/// <param name="_texture"> テクスチャのポインタ </param>
/// <param name="_Scale"> 画像の描画サイズ </param>
/// <param name="_UpdateOrder"> コンポーネントの更新順番（数値が小さいほど早く更新される）</param>
ParticleComponent::ParticleComponent(GameObject* _owner, Texture* _texture, const Vector3& _Scale, const int& _UpdateOrder)
	: Component(_owner, _UpdateOrder)
	, mScale(_Scale)
	, mAlpha(1.0f)
	, mBlendType(ParticleType::eParticleBlendAlpha)
	, mVisible(true)
	, mDrawOrder(_UpdateOrder)
	, mColor(Vector3(1, 1, 1))
	, mTextureWidth(0)
	, mTextureHeight(0)
	, mHitPointGaugeControllerPtr(nullptr)
	, mTexture(_texture)
{
	mTextureWidth = mTexture->GetWidth();
	mTextureHeight = mTexture->GetHeight();

	//レンダラーにポインターを送る
	RENDERER->AddParticle(this);
}

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="_owner"> アタッチするゲームオブジェクトのポインタ </param>
/// <param name="_texture"> テクスチャのポインタ </param>
/// <param name="_hitPointGaugeControllerconst"> hpゲージを制御するクラスのポインタ </param>
/// <param name="_Scale"> 画像の描画サイズ </param>
/// <param name="_UpdateOrder"> コンポーネントの更新順番（数値が小さいほど早く更新される）</param>
ParticleComponent::ParticleComponent(GameObject* _owner, Texture* _texture, HitPointGaugeController* _hitPointGaugeController, const Vector3& _Scale, const int& _UpdateOrder)
	: Component(_owner, _UpdateOrder)
	, mScale(_Scale)
	, mAlpha(1.0f)
	, mBlendType(ParticleType::eParticleBlendAlpha)
	, mVisible(true)
	, mDrawOrder(_UpdateOrder)
	, mColor(Color::White)
	, mTextureWidth(0)
	, mTextureHeight(0)
	, mHitPointGaugeControllerPtr(_hitPointGaugeController)
	, mTexture(_texture)
{
	mTextureWidth = mTexture->GetWidth();
	mTextureHeight = mTexture->GetHeight();

	//レンダラーにポインターを送る
	RENDERER->AddParticle(this);
}

/// <summary>
/// デストラクタ
/// </summary>
ParticleComponent::~ParticleComponent()
{
	//レンダラーからポインタを削除する
	RENDERER->RemoveParticle(this);
}

/// <summary>
/// 描画処理
/// </summary>
/// <param name="_shader"> 使用するシェーダークラスのポインタ </param>
void ParticleComponent::Draw(Shader* _shader)
{
	// 画像情報が空でないか、親オブジェクトが未更新状態でないか
	if (mTexture && mOwner->GetState() == State::eDead)
	{
		return;
	}

	// hpゲージを制御するコンポーネントクラスがあったらテクスチャの横幅を更新する
	if (mHitPointGaugeControllerPtr != nullptr)
	{
		mTextureWidth = mHitPointGaugeControllerPtr->GetTextureWidthAfterChange();
	}

	// 拡大縮小行列
	Matrix4 matScale = Matrix4::CreateScale(
		static_cast<float>(mTextureWidth) * mScale.x,
		static_cast<float>(mTextureHeight) * mScale.y,
		1.0f * mScale.z);

	// 平行移動行列
	Matrix4 mat = Matrix4::CreateTranslation(mOwner->GetPosition());

	// ビルボード行列作成
	mBillboardMat = CreateBillboardMatrix();

	// ワールド座標
	Matrix4 world =  matScale * mBillboardMat * mat;

	_shader->SetMatrixUniform("uWorldTransform", world);
	_shader->SetFloatUniform("uAlpha", mAlpha);
	_shader->SetVectorUniform("uColor", mColor);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, mTexture->GetTextureID());
	_shader->SetIntUniform("uParticleTexture", 0);

	RENDERER->SetParticleVertex();
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
}

/// <summary>
/// ビルボード行列作成
/// </summary>
/// <returns></returns>
Matrix4 ParticleComponent::CreateBillboardMatrix()
{
	Matrix4 ret;
	ret = RENDERER->GetViewMatrix();
	ret.mat[3][0] = ret.mat[3][1] = ret.mat[3][2] = 0.0f;
	ret.Transpose();
	ret.mat[2][2] *= -1.0f;

	Matrix4 rot = Matrix4::CreateRotationX(-0.5f * Math::Pi);
	ret = rot * ret;

	return Matrix4(ret);
}