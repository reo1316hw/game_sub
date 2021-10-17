#pragma once

/*
 @file CubeMapComponent.h
 @brief �L���[�u�}�b�v�̊Ǘ��ƕ`����s��
*/
class CubeMapComponent : public Component
{
public:

	/*
	@fn �R���X�g���N�^
	@param _owner �e�N���X�̃|�C���^
	*/
	CubeMapComponent(GameObject* _owner);

	/*
	@fn �f�X�g���N�^
	@brief  Component�̍폜���s��
	*/
	~CubeMapComponent();

	/*
	@brief�@texture��������
	@param	_TextureName �g�p����texture�̃t�@�C���p�X
	*/
	void CreateTexture(const std::string& _TextureName);

	/*
	@brief�@�`�揈��
	@param	in_shader �g�p����V�F�[�_�[�N���X�̃|�C���^
	*/
	void Draw(Shader* _shader);

	/*
	@brief�@�X�J�C�{�b�N�X�Ɏg�p���Ă���texture��getter
	@param	texture �g�p���Ă���texture�N���X�̃|�C���^
	*/
	class Texture* GetSkyBoxTexture() { return mTexture; }

	// �L���[�u��\�����邩���Ȃ����̃Z�b�g
	void SetIsVisible(bool _isVisible) { mIsVisible = _isVisible; }

	// �P�x���̃Z�b�g
	void SetLuminance(float _luminance) { mLuminance = _luminance; }


private:

	// texture�N���X�̃|�C���^
	Texture* mTexture;

	// �P�x���
	float mLuminance;

	// �`�悷�邩���Ȃ����̃t���O
	bool mIsVisible;

};

