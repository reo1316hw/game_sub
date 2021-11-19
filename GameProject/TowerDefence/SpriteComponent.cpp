#include "pch.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="_owner"> �A�^�b�`����Q�[���I�u�W�F�N�g�̃|�C���^ </param>
/// <param name="_texture"> �e�N�X�`���̃|�C���^ </param>
/// <param name="_Scale"> �傫�� </param>
/// <param name="_DrawOrder"> �`��̏��� </param>
SpriteComponent::SpriteComponent(GameObject* _owner, Texture* _texture, const int& _DrawOrder)
    : Component(_owner)
    , mDrawOrder(_DrawOrder)
	, mVisible(true)
	, mTextureWidth(0)
	, mTextureHeight(0)
    , mTexture(_texture)
{
	mTextureWidth = mTexture->GetWidth();
	mTextureHeight = mTexture->GetHeight();

	//�����_���[�Ƀ|�C���^�[�𑗂�
	RENDERER->AddSprite(this);
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
SpriteComponent::~SpriteComponent()
{
	//�����_���[����|�C���^���폜����
	RENDERER->RemoveSprite(this);
}

/// <summary>
/// �`�揈��
/// </summary>
/// <param name="_shader"> �g�p����V�F�[�_�[�N���X�̃|�C���^ </param>
void SpriteComponent::Draw(Shader * _shader)
{
	//�摜��񂪋�łȂ����A�e�I�u�W�F�N�g�����X�V��ԂłȂ���
	if (mTexture && mOwner->GetState() == State::eDead)
	{
		return;
	}

	Matrix4 scaleMatrix = Matrix4::CreateScale(
		static_cast<float>(mTextureWidth),
		static_cast<float>(mTextureHeight),
		1.0f);

	Matrix4 world = scaleMatrix * mOwner->GetWorldTransform();

	_shader->SetMatrixUniform("uWorldTransform",world);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, mTexture->GetTextureID());
	_shader->SetIntUniform("uSpriteTexture", 0);

	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);	
}

/// <summary>
/// �e�N�X�`����ݒ肵�A�c���̒������v�Z����
/// </summary>
/// <param name="_texture"> �e�N�X�`���N���X�̃|�C���^ </param>
void SpriteComponent::SetTexture(Texture* _texture)
{
	mTexture = _texture;
	mTextureWidth = mTexture->GetWidth();
	mTextureHeight = mTexture->GetHeight();
}
