#pragma once

// �O���錾
class Texture;
class SpriteComponent;

/// <summary>
/// �X�v���C�g
/// </summary>
class Sprite : public GameObject
{
public:

	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="_TextureName"> �e�N�X�`���̃p�X </param>
    /// <param name="_ReUseGameObject"> �ė��p���邩 </param>
	/// <param name="_Alpha"> �e�N�X�`���̓����x </param>
	/// <param name="_Scale"> �e�N�X�`���̊g��T�C�Y </param>
	Sprite(const std::string _TextureName, const bool& _ReUseGameObject = false, const float _Alpha = 1.0f, const Vector3& _Scale = Vector3(1.0f, 1.0f, 1.0f));

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~Sprite() {};

	/// <summary>
	/// �X�v���C�g�摜��ύX����
	/// </summary>
	/// <param name="_TextureName"> �e�N�X�`���̃p�X </param>
	void ChangeSprite(const std::string _TextureName);

private:

	// �X�N���[����ɕ`�悷��N���X�̃|�C���^
	SpriteComponent* mSpriteComponent;

public:// �Q�b�^�[�Z�b�^�[

	/// <summary>
	/// �X�N���[����ɕ`�悷��N���X�̃|�C���^�擾
	/// </summary>
	/// <returns> �X�N���[����ɕ`�悷��N���X�̃|�C���^ </returns>
	SpriteComponent* GetSpriteComponentPtr() { return mSpriteComponent; }
};
