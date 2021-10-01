#include "pch.h"

SpriteComponent::SpriteComponent(GameObject * _owner, int _drawOrder)
    : Component(_owner)
    , mTexture(nullptr)
    , mDrawOrder(_drawOrder)
    , mTextureWidth(0)
    , mTextureHeight(0)
	, mVisible(true)
{
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
	if (mTexture&&mOwner->GetState()!=State::Dead)
	{
		Matrix4 scaleMatrix = Matrix4::CreateScale(
			static_cast<float>(mTextureWidth),
			static_cast<float>(mTextureHeight),
			1.0f);

		Matrix4 world = scaleMatrix * mOwner->GetWorldTransform();

		_shader->SetMatrixUniform("uWorldTransform",world);
		
	/*	_shader->SetFloatUniform("uLuminance", texture->GetLuminace());*/

		//texture->SetActive();

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, mTexture->GetTextureID());
		_shader->SetIntUniform("uSpriteTexture", 0);

	/*	glActiveTexture(GL_TEXTURE3);
		glBindTexture(GL_TEXTURE_2D, emissiveTexture->GetTextureID());
		_shader->SetIntUniform("uEmissiveMap", 3);*/

		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);	
	}
}

/*
@fn �e�N�X�`�����Z�b�g���c���̒������v�Z����
@param _texture �g�p����e�N�X�`���̃|�C���^
*/
//void SpriteComponent::SetTexture(Texture * _texture, Texture* _emissiveTexture)
//{
//	texture = _texture;
//	textureWidth = texture->GetWidth();
//	textureHeight = texture->GetHeight();
//
//	emissiveTexture = _emissiveTexture;
//	emissiveTextureWidth = emissiveTexture->GetWidth();
//	emissiveTextureHeight = emissiveTexture->GetHeight();
//}

void SpriteComponent::SetTexture(Texture* _texture)
{
	mTexture = _texture;
	mTextureWidth = mTexture->GetWidth();
	mTextureHeight = mTexture->GetHeight();
}
