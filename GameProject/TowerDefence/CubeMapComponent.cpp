#include "pch.h"

/*
@fn �R���X�g���N�^
@param _owner �e�N���X�̃|�C���^
*/
CubeMapComponent::CubeMapComponent(GameObject* _owner)
	: Component(_owner)
	, mTexture(nullptr)
	, mLuminance(1.0f)
	, mIsVisible(true)
{
}

/*
@fn �f�X�g���N�^
@brief  Component�̍폜���s��
*/
CubeMapComponent::~CubeMapComponent()
{
	delete mTexture;
}

/*
@brief�@texture��������
@param	_TextureName �g�p����texture�̃t�@�C���p�X
*/
void CubeMapComponent::CreateTexture(const std::string& _TextureName)
{
	mTexture = new Texture();
	mTexture->LoadCubeMap(_TextureName);
}

/*
@brief�@�`�揈��
@param	in_shader �g�p����V�F�[�_�[�N���X�̃|�C���^
*/
void CubeMapComponent::Draw(Shader*_shader)
{
	// �����ɂ��Ă��Ȃ����
	if (mIsVisible)
	{
		// �[�x�ݒ�
		glDepthFunc(GL_LEQUAL);
		// �P�x�����V�F�[�_�ɓn��
		_shader->SetFloatUniform("u_skyLuminance", mLuminance);
		// �e�N�X�`���o�C���h
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_CUBE_MAP, mTexture->GetTextureID());
		// �L���[�u�}�b�v�p���_�z��̃A�N�e�B�u��
		RENDERER->GetCubeMapVerts()->SetActive();
		// �`��
		glDrawArrays(GL_TRIANGLES, 0, 36);

		// �O�̂��߃o�C���h����
		glBindVertexArray(0);

		glDepthFunc(GL_LESS);
	}
}