#include "pch.h"

SpriteComponent::SpriteComponent(GameObject * _owner, Texture* _texture, int _drawOrder)
    : Component(_owner)
    , mDrawOrder(_drawOrder)
    , mTextureWidth(0)
    , mTextureHeight(0)
	, mVisible(true)
	, mHitPointGaugeControllerPtr(nullptr)
    , mTexture(_texture)
{
	mTextureWidth = mTexture->GetWidth();
	mTextureHeight = mTexture->GetHeight();

	//�����_���[�Ƀ|�C���^�[�𑗂�
	RENDERER->AddSprite(this);
}

SpriteComponent::SpriteComponent(GameObject* _owner, Texture* _texture, HitPointGaugeController* _hitPointGaugeController, int _drawOrder)
	: Component(_owner)
	, mDrawOrder(_drawOrder)
	, mTextureWidth(0)
	, mTextureHeight(0)
	, mVisible(true)
	, mHitPointGaugeControllerPtr(_hitPointGaugeController)
	, mTexture(_texture)
{
	mTextureWidth = mTexture->GetWidth();
	mTextureHeight = mTexture->GetHeight();

	//�����_���[�Ƀ|�C���^�[�𑗂�
	RENDERER->AddSprite(this);
}

SpriteComponent::~SpriteComponent()
{
	//�����_���[����|�C���^���폜����
	RENDERER->RemoveSprite(this);
}

/*
@brief	�`�揈��
@param _shader �g�p����V�F�[�_�[�N���X�̃|�C���^
*/
void SpriteComponent::Draw(Shader * _shader)
{
	//�摜��񂪋�łȂ����A�e�I�u�W�F�N�g�����X�V��ԂłȂ���
	if (mTexture && mOwner->GetState() == State::eDead)
	{
		return;
	}

	// hp�Q�[�W�𐧌䂷��R���|�[�l���g�N���X����������e�N�X�`���̉������X�V����
	if (mHitPointGaugeControllerPtr != nullptr)
	{
		mTextureWidth = mHitPointGaugeControllerPtr->GetTextureWidthAfterChange();
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