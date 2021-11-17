#pragma once

// �O���錾
class SpriteComponent;

/// <summary>
/// �v���C���[��hp�Q�[�W
/// </summary>
class PlayerHitPointGauge : public GameObject
{
public:

	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="_Pos"> UI�̐����ꏊ(�X�N���[�����W) </param>
	/// <param name="_TextureName"> �e�N�X�`���̃p�X </param>
	/// <param name="_ObjectTag"> �A�^�b�`�����Q�[���I�u�W�F�N�g�̃^�O </param>
	/// <param name="_playerPtr"> �v���C���[�̃|�C���^ </param>
	/// <param name="_Scale"> �e�N�X�`���̊g��T�C�Y </param>
	PlayerHitPointGauge(const Vector3& _Pos, const std::string& _TextureName, const Tag& _ObjectTag,
		                PlayerObject* _playerPtr, const Vector2& _Scale = Vector2(1.0f,1.0f));

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~PlayerHitPointGauge() {};

private:

	// hp�Q�[�W�𐧌䂷��R���|�[�l���g�N���X�̃|�C���^
	HitPointGaugeController* mHitPointGaugeControllerPtr;
	// �X�N���[����ɕ`�悷��R���|�[�l���g�N���X�̃|�C���^
	SpriteComponent* mSpritePtr;
};