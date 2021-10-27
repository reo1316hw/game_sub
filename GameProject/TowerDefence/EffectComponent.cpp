#include "pch.h"

EffectComponent::EffectComponent(GameObject* owner, bool moveOn, bool rotateOn, int updateOrder)
	: Component(owner)
	, mIsMove(moveOn)
	, mIsRotate(rotateOn)
	, mHandle(0)
	, mRelativePos(0, 0, 0)
{
}

EffectComponent::~EffectComponent()
{
	RENDERER->GetEffekseerManager()->StopEffect(mHandle);
}

void EffectComponent::LoadEffect(const char16_t* effkseerFilename)
{
	EffekseerEffect* effect = RENDERER->GetEffect(effkseerFilename);

	Vector3 pos = Vector3(0, 0, 0);
	mHandle = effect->CreateInstanceHandle(pos);
}

void EffectComponent::Update(float deltaTime)
{
	// �G�t�F�N�g�����݂������Ă��邩�H
	if (!(RENDERER->GetEffekseerManager()->Exists(mHandle)))
	{
		mOwner->SetState(State::eDead);
		return;
	}

	// �G�t�F�N�g���ړ������邩�H
	Matrix4 trans, rot;
	if (mIsMove)
	{
		Vector3 ownerPos;
		ownerPos = mOwner->GetPosition();
		trans = Matrix4::CreateTranslation(ownerPos);
	}
	// �G�t�F�N�g�̓I�[�i�[�̉�]�ɉe�����󂯂邩
	if (mIsRotate)
	{
		Quaternion q = mOwner->GetRotation();
		rot = Matrix4::CreateFromQuaternion(q);
	}
	Effekseer::Matrix43 eMat;

	// Effecseer -> GL ��100�{ + Zup �ɍ��킹��
	Matrix4 base, convertScale, convertRot;
	convertScale = Matrix4::CreateScale(100, -100, 100);
	convertRot = Matrix4::CreateRotationX(Math::ToRadians(-90.0f));
	base = convertScale * convertRot * mRelativeRot;

	//�G�t�F�N�g�Ɉړ��E��]�i����΁j�Z�b�g
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
