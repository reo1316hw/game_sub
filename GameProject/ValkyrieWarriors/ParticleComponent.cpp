#include "pch.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="_owner"> �A�^�b�`����Q�[���I�u�W�F�N�g�̃|�C���^ </param>
/// <param name="_texture"> �e�N�X�`���̃|�C���^ </param>
/// <param name="_UpdateOrder"> �R���|�[�l���g�̍X�V���ԁi���l���������قǑ����X�V�����j</param>
ParticleComponent::ParticleComponent(GameObject* _owner, Texture* _texture, const int& _UpdateOrder)
	: Component(_owner, _UpdateOrder)
	, mAlpha(1.0f)
	, mBlendType(ParticleType::eParticleBlendAlpha)
	, mVisible(true)
	, mDrawOrder(_UpdateOrder)
	, mScale(Vector3::Zero)
	, mColor(Vector3(1.0f, 1.0f, 1.0f))
	, mTextureWidth(0)
	, mTextureHeight(0)
	, mTexture(_texture)
{
	mTextureWidth = mTexture->GetWidth();
	mTextureHeight = mTexture->GetHeight();

	//�����_���[�Ƀ|�C���^�[�𑗂�
	RENDERER->AddParticle(this);
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
ParticleComponent::~ParticleComponent()
{
	//�����_���[����|�C���^���폜����
	RENDERER->RemoveParticle(this);
}

/// <summary>
/// �`�揈��
/// </summary>
/// <param name="_shader"> �g�p����V�F�[�_�[�N���X�̃|�C���^ </param>
void ParticleComponent::Draw(Shader* _shader)
{
	// �摜��񂪋�łȂ����A�e�I�u�W�F�N�g�����X�V��ԂłȂ���
	if (mTexture && mOwner->GetState() == State::eDead)
	{
		return;
	}

	mScale = mOwner->GetScale();

	// �g��k���s��
	Matrix4 matScale = Matrix4::CreateScale(
		static_cast<float>(mTextureWidth) * mScale.x,
		static_cast<float>(mTextureHeight) * mScale.y,
		1.0f * mScale.z);

	// ���s�ړ��s��
	Matrix4 mat = Matrix4::CreateTranslation(mOwner->GetPosition());

	// �r���{�[�h�s��쐬
	mBillboardMat = CreateBillboardMatrix();

	// ���[���h���W
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
/// �r���{�[�h�s��쐬
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