#include "pch.h"

EffectComponent::EffectComponent(GameObject* owner, const Vector3& _Scale, const char16_t* effkseerFilename, bool moveOn, bool rotateOn, int updateOrder)
	: Component(owner)
	, mIsMove(moveOn)
	, mIsRotate(rotateOn)
	, mHandle(0)
	, mScale(_Scale)
	, mRelativePos(Vector3::Zero)
	, mEffectPtr(nullptr)
{
	mEffectPtr = RENDERER->GetEffect(effkseerFilename);
}

void EffectComponent::PlayEffect()
{
	Vector3 pos = Vector3::Zero;
	mHandle = mEffectPtr->CreateInstanceHandle(pos);
}

/// <summary>
/// 再生済みか
/// </summary>
bool EffectComponent::IsPlayedEffect()
{
	// エフェクトが現在も生きているか？
	if (!(RENDERER->GetEffekseerManager()->Exists(mHandle)))
	{
		return true;
	}

	return false;
}

void EffectComponent::Update(float deltaTime)
{
	// エフェクトを移動させるか？
	Matrix4 trans, rot;
	if (mIsMove)
	{
		Vector3 ownerPos;
		ownerPos = mOwner->GetPosition();
		trans = Matrix4::CreateTranslation(ownerPos);
	}
	// エフェクトはオーナーの回転に影響を受けるか
	if (mIsRotate)
	{
		Quaternion q = mOwner->GetRotation();
		rot = Matrix4::CreateFromQuaternion(q);
	}
	Effekseer::Matrix43 eMat;

	// Effecseer -> GL の100倍 + Zup に合わせる
	Matrix4 base, convertScale, convertRot;
	convertScale = Matrix4::CreateScale(mScale);
	convertRot = Matrix4::CreateRotationX(Math::ToRadians(-90.0f));
	base = convertScale * convertRot * mRelativeRot;

	//エフェクトに移動・回転（あれば）セット
	Matrix4 relativeMoveMat = Matrix4::CreateTranslation(mRelativePos);
	Matrix4 final;
	final = base * relativeMoveMat * rot * trans;

	final.mat[0][0] *= -1;
	final.mat[1][0] *= -1;
	final.mat[2][0] *= -1;
	final.mat[3][0] *= -1;

	eMat = final;
	RENDERER->GetEffekseerManager()->SetBaseMatrix(mHandle, eMat);

}