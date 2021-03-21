#include "ParticleComponent.h"
#include "Shader.h"
#include "Renderer.h"
#include "GameObject.h"

// �r���{�[�h�s��
Matrix4 ParticleComponent::mStaticBillboardMat;
// �J�����̃��[���h���W
Vector3 ParticleComponent::mStaticCameraWorldPos;

/*
 @param _offset �e�I�u�W�F�N�g�N���X�Ɖ摜��`�悷��ʒu�̍�
 @param _scale �摜�̕`��T�C�Y
*/
ParticleComponent::ParticleComponent(GameObject* _owner, const Vector3& _offset, float _scale, int _updateOrder)
	: Component(_owner, _updateOrder)
	, mOffset(_offset)
	, mScale(_scale)
	, mAlpha(1.0f)
	, mBlendType(PARTICLE_BLEND_ENUM::PARTICLE_BLEND_ENUM_ALPHA)
	, mVisible(true)
	, mDrawOrder(_updateOrder)
	, mColor(Vector3(1, 1, 1))
	, mReverce(false)
	, mTextureID(0)

{
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
	//�e�I�u�W�F�N�g�����X�V��ԂłȂ���
	if (mOwner->GetState() == State::Dead)
	{
		return;
	}
	Matrix4 mat, matScale;
	Vector3 reverceVec = Vector3(1, 1, 1);
	//�T�C�Y�𔽓]������
	if (mReverce)
	{
		reverceVec.x *= -1;
	}
	matScale = Matrix4::CreateScale(mScale*reverceVec* mOwner->GetScale());
	mat = Matrix4::CreateTranslation(mOffset + mOwner->GetPosition());

	_shader->SetMatrixUniform("uWorldTransform", matScale * mStaticBillboardMat * mat);
	_shader->SetFloatUniform("uAlpha", mAlpha);
	_shader->SetVectorUniform("uColor", mColor);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, mTextureID);
	_shader->SetIntUniform("uParticleTexture", 0);

	RENDERER->SetParticleVertex();
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
}

// �J���������ł̃\�[�g�p
bool ParticleComponent::operator<(const ParticleComponent& rhs) const
{
	float lenThis, lenRhs;
	lenThis = (mStaticCameraWorldPos - mOffset).LengthSq();
	lenRhs = (mStaticCameraWorldPos - rhs.mOffset).LengthSq();
	return lenThis < lenRhs;
}

// �J���������ł̃\�[�g�p
bool ParticleComponent::operator>(const ParticleComponent& rhs) const
{
	float lenThis, lenRhs;
	lenThis = (mStaticCameraWorldPos - mOffset).LengthSq();
	lenRhs = (mStaticCameraWorldPos - rhs.mOffset).LengthSq();
	return lenThis > lenRhs;
}


Matrix4 GetBillboardMatrix()
{
	Matrix4 ret;
	ret = RENDERER->GetViewMatrix();
	ret.mat[3][0] = ret.mat[3][1] = ret.mat[3][2] = 0.0f;
	ret.Transpose();
	ret.mat[1][1] *= -1;
	ret.mat[2][2] *= -1;

	return Matrix4(ret);
}
