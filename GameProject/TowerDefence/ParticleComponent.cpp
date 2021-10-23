#include "pch.h"

Matrix4 ParticleComponent::mBillboardMat;

/*
 @param _offset �e�I�u�W�F�N�g�N���X�Ɖ摜��`�悷��ʒu�̍�
 @param _scale �摜�̕`��T�C�Y
*/
ParticleComponent::ParticleComponent(GameObject* _owner, Texture* _texture, const Vector3& _Scale, const int& _UpdateOrder)
	: Component(_owner, _UpdateOrder)
	, mScale(_Scale)
	, mAlpha(1.0f)
	, mBlendType(PARTICLE_BLEND_ENUM::PARTICLE_BLEND_ENUM_ALPHA)
	, mVisible(true)
	, mDrawOrder(_UpdateOrder)
	, mColor(Vector3(1, 1, 1))
	, mReverce(false)
	, mTextureWidth(0)
	, mTextureHeight(0)
	, mHitPointGaugeControllerPtr(nullptr)
	, mTexture(_texture)
{
	mTextureWidth = mTexture->GetWidth();
	mTextureHeight = mTexture->GetHeight();

	//�����_���[�Ƀ|�C���^�[�𑗂�
	RENDERER->AddParticle(this);
}

/*
 @param _offset �e�I�u�W�F�N�g�N���X�Ɖ摜��`�悷��ʒu�̍�
 @param _scale �摜�̕`��T�C�Y
*/
ParticleComponent::ParticleComponent(GameObject* _owner, Texture* _texture, HitPointGaugeController* _hitPointGaugeController, const Vector3& _Scale, const int& _UpdateOrder)
	: Component(_owner, _UpdateOrder)
	, mScale(_Scale)
	, mAlpha(1.0f)
	, mBlendType(PARTICLE_BLEND_ENUM::PARTICLE_BLEND_ENUM_ALPHA)
	, mVisible(true)
	, mDrawOrder(_UpdateOrder)
	, mColor(Color::White)
	, mReverce(false)
	, mTextureWidth(0)
	, mTextureHeight(0)
	, mHitPointGaugeControllerPtr(_hitPointGaugeController)
	, mTexture(_texture)
{
	mTextureWidth = mTexture->GetWidth();
	mTextureHeight = mTexture->GetHeight();

	//�����_���[�Ƀ|�C���^�[�𑗂�
	RENDERER->AddParticle(this);
}

ParticleComponent::~ParticleComponent()
{
	//�����_���[����|�C���^���폜����
	RENDERER->RemoveParticle(this);
}

/*
@brief�@�`�揈��
@param	_shader �g�p����V�F�[�_�[�N���X�̃|�C���^
*/
void ParticleComponent::Draw(Shader* _shader)
{
	// �摜��񂪋�łȂ����A�e�I�u�W�F�N�g�����X�V��ԂłȂ���
	if (mTexture && mOwner->GetState() == State::eDead)
	{
		return;
	}

	// hp�Q�[�W�𐧌䂷��R���|�[�l���g�N���X����������e�N�X�`���̉������X�V����
	if (mHitPointGaugeControllerPtr != nullptr)
	{
		mTextureWidth = mHitPointGaugeControllerPtr->GetTextureWidthAfterChange();
	}

	Matrix4 matScale = Matrix4::CreateScale(
		static_cast<float>(mTextureWidth) * mScale.x,
		static_cast<float>(mTextureHeight) * mScale.y,
		1.0f * mScale.z);

	Matrix4 mat = Matrix4::CreateTranslation(mOwner->GetPosition());

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

Matrix4 ParticleComponent::GetBillboardMatrix()
{
	Matrix4 ret;
	ret = RENDERER->GetViewMatrix();
	ret.mat[3][0] = ret.mat[3][1] = ret.mat[3][2] = 0.0f;
	ret.Transpose();
	ret.mat[2][2] *= -1.0f;

	Matrix4 rot = Matrix4::CreateRotationX(-0.5f * 3.14159f);
	ret = rot * ret;

	return Matrix4(ret);
}

//// �J���������ł̃\�[�g�p
//bool ParticleComponent::operator<(const ParticleComponent& _rhs) const
//{
//	float lenThis, lenRhs;
//	lenThis = (mStaticCameraWorldPos - mOffset).LengthSq();
//	lenRhs = (mStaticCameraWorldPos - _rhs.mOffset).LengthSq();
//	return lenThis < lenRhs;
//}
//
//// �J���������ł̃\�[�g�p
//bool ParticleComponent::operator>(const ParticleComponent& _rhs) const
//{
//	float lenThis, lenRhs;
//	lenThis = (mStaticCameraWorldPos - mOffset).LengthSq();
//	lenRhs = (mStaticCameraWorldPos - _rhs.mOffset).LengthSq();
//	return lenThis > lenRhs;
//}