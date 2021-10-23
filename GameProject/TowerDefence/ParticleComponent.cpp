#include "pch.h"

// ビルボード行列
Matrix4 ParticleComponent::mStaticBillboardMat;
// カメラのワールド座標
Vector3 ParticleComponent::mStaticCameraWorldPos;

/*
 @param _offset 親オブジェクトクラスと画像を描画する位置の差
 @param _scale 画像の描画サイズ
*/
ParticleComponent::ParticleComponent(GameObject* _owner, Texture* _texture, float _scale, int _updateOrder)
	: Component(_owner, _updateOrder)
	, mScale(_scale)
	, mAlpha(1.0f)
	, mBlendType(PARTICLE_BLEND_ENUM::PARTICLE_BLEND_ENUM_ALPHA)
	, mVisible(true)
	, mDrawOrder(_updateOrder)
	, mColor(Vector3(1, 1, 1))
	, mReverce(false)
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

/*
 @param _offset 親オブジェクトクラスと画像を描画する位置の差
 @param _scale 画像の描画サイズ
*/
ParticleComponent::ParticleComponent(GameObject* _owner, Texture* _texture, HitPointGaugeController* _hitPointGaugeController, float _scale, int _updateOrder)
	: Component(_owner, _updateOrder)
	, mScale(_scale)
	, mAlpha(1.0f)
	, mBlendType(PARTICLE_BLEND_ENUM::PARTICLE_BLEND_ENUM_ALPHA)
	, mVisible(true)
	, mDrawOrder(_updateOrder)
	, mColor(Color::White)
	, mReverce(false)
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

ParticleComponent::~ParticleComponent()
{
	//レンダラーからポインタを削除する
	RENDERER->RemoveParticle(this);
}

/*
@brief　描画処理
@param	_shader 使用するシェーダークラスのポインタ
*/
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

	Matrix4 matScale = Matrix4::CreateScale(
		static_cast<float>(mTextureWidth),
		static_cast<float>(mTextureHeight),
		1.0f);

	Matrix4 mat = Matrix4::CreateTranslation(mOwner->GetPosition());

	Matrix4 world = matScale * mat;

	_shader->SetMatrixUniform("uWorldTransform", world * mStaticBillboardMat);
	_shader->SetFloatUniform("uAlpha", mAlpha);
	_shader->SetVectorUniform("uColor", mColor);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, mTexture->GetTextureID());
	_shader->SetIntUniform("uParticleTexture", 0);

	RENDERER->SetParticleVertex();
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
}

Matrix4 ParticleComponent::GetBillboardMatrix()
{
	Matrix4 ret;
	ret = RENDERER->GetViewMatrix();
	ret.mat[3][0] = ret.mat[3][1] = ret.mat[3][2] = 0.0f;
	ret.Transpose();
	ret.mat[1][1] *= -1;
	ret.mat[2][2] *= -1;

	return Matrix4(ret);
}

//// カメラ距離でのソート用
//bool ParticleComponent::operator<(const ParticleComponent& _rhs) const
//{
//	float lenThis, lenRhs;
//	lenThis = (mStaticCameraWorldPos - mOffset).LengthSq();
//	lenRhs = (mStaticCameraWorldPos - _rhs.mOffset).LengthSq();
//	return lenThis < lenRhs;
//}
//
//// カメラ距離でのソート用
//bool ParticleComponent::operator>(const ParticleComponent& _rhs) const
//{
//	float lenThis, lenRhs;
//	lenThis = (mStaticCameraWorldPos - mOffset).LengthSq();
//	lenRhs = (mStaticCameraWorldPos - _rhs.mOffset).LengthSq();
//	return lenThis > lenRhs;
//}