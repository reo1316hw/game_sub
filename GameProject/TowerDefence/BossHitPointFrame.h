#pragma once

// �O���錾
class SpriteComponent;

/// <summary>
/// �{�X��hp�̘g
/// </summary>
class BossHitPointFrame : public GameObject
{
public:

	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="_Pos"> UI�̐����ꏊ(�X�N���[�����W) </param>
	/// <param name="_TextureName"> �e�N�X�`���̃p�X </param>
	/// <param name="_ObjectTag"> �A�^�b�`�����Q�[���I�u�W�F�N�g�̃^�O </param>
	/// <param name="_Scale"> �摜�̊g��T�C�Y </param>
	BossHitPointFrame(const Vector3& _Pos, const std::string& _TextureName,
		const Tag& _ObjectTag, const float& _Scale = 1.0f);

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~BossHitPointFrame() {};

private:

	// �X�N���[����ɕ`�悷��R���|�[�l���g�N���X�̃|�C���^
	SpriteComponent* mSpritePtr;
};