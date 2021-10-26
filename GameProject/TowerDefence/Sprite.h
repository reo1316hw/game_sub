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
	Sprite(const std::string _TextureName, const bool& _ReUseGameObject = false);

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~Sprite() {};

private:

	// �X�N���[����ɕ`�悷��N���X�̃|�C���^
	SpriteComponent* mSpriteComponent;
};

