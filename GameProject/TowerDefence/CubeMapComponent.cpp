#include "pch.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="_owner"> �e�N���X�̃|�C���^ </param>
CubeMapComponent::CubeMapComponent(GameObject* _owner)
	: Component(_owner)
	, mTexture(nullptr)
	, mLuminance(1.0f)
	, mIsVisible(true)
{
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
CubeMapComponent::~CubeMapComponent()
{
	delete mTexture;
}

/// <summary>
/// texture��������
/// </summary>
/// <param name="_TextureName"> �g�p����texture�̃t�@�C���p�X </param>
void CubeMapComponent::CreateTexture(const std::string& _TextureName)
{
	mTexture = new Texture();
	mTexture->LoadCubeMap(_TextureName);
}

/// <summary>
/// �`�揈��
/// </summary>
/// <param name="_shader"> �g�p����V�F�[�_�[�N���X�̃|�C���^ </param>
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