#include "Pch.h"

int UIComponent::mUIid = 0;

UIComponent::UIComponent(GameObject* _owner, int _drawOrder)
	: Component(_owner)
	, mTexture(nullptr)
	, mDrawOrder(_drawOrder)
	, mTextureWidth(0)
	, mTextureHeight(0)
	, mVisible(true)
	, mMyUIid(mUIid)
{
	mUIid++;
	//�����_���[�Ƀ|�C���^�[�𑗂�
	RENDERER->AddUI(this);
}

UIComponent::~UIComponent()
{
	mUIid--;
	//�����_���[����|�C���^���폜����
	RENDERER->RemoveUI(this);
}

/*
@brief	�`�揈��
@param _shader �g�p����V�F�[�_�[�N���X�̃|�C���^
*/
void UIComponent::Draw(Shader* _shader, const Vector3& _offset)
{
	//�摜��񂪋�łȂ����A�e�I�u�W�F�N�g�����X�V��ԂłȂ���
	if (mTexture && mOwner->GetState() != State::Dead)
	{
		Matrix4 scaleMatrix = Matrix4::CreateScale(
			static_cast<float>(mTextureWidth),
			static_cast<float>(mTextureHeight),
			1.0f);

		// �X�N���[���ʒu�̕��s�ړ�
		Matrix4 transMat = Matrix4::CreateTranslation(
			Vector3(_offset.x - (mTextureWidth * 8.5f),
				(mTextureHeight * 5.0f) - _offset.y, 0.0f));

		Matrix4 world = scaleMatrix * transMat;

		/*Matrix4 scaleMatrix = Matrix4::CreateScale(
			static_cast<float>(textureWidth),
			static_cast<float>(textureHeight),
			1.0f);

		Matrix4 world = scaleMatrix * owner->GetWorldTransform();*/

		_shader->SetMatrixUniform("uWorldTransform", world);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, mTexture->GetTextureID());
		_shader->SetIntUniform("uSpriteTexture", 0);

		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);

	}
}

/*
@fn �e�N�X�`�����Z�b�g���c���̒������v�Z����
@param _texture �g�p����e�N�X�`���̃|�C���^
*/
void UIComponent::SetTexture(Texture* _texture)
{
	mTexture = _texture;
	mTextureWidth = mTexture->GetWidth();
	mTextureHeight = mTexture->GetHeight();
}
