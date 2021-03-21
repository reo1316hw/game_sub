#include "SpriteComponent.h"
#include "Texture.h"
#include "Shader.h"
#include "GameObject.h"
#include "Game.h"
#include "Renderer.h"

SpriteComponent::SpriteComponent(GameObject * _owner, int _drawOrder)
    :Component(_owner)
    ,texture(nullptr)
    ,drawOrder(_drawOrder)
    ,textureWidth(0)
    ,textureHeight(0)
	, visible(true)
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
	if (texture&& mOwner->GetState()!=State::Dead)
	{
		Matrix4 scaleMatrix = Matrix4::CreateScale(
			static_cast<float>(textureWidth),
			static_cast<float>(textureHeight),
			1.0f);

		Matrix4 world = scaleMatrix * mOwner->GetWorldTransform();

		_shader->SetMatrixUniform("uWorldTransform",world);
		
	/*	_shader->SetFloatUniform("uLuminance", texture->GetLuminace());*/

		//texture->SetActive();

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture->GetTextureID());
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
	texture = _texture;
	textureWidth = texture->GetWidth();
	textureHeight = texture->GetHeight();
}
