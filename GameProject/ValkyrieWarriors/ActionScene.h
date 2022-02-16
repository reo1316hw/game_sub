#pragma once

/// <summary>
/// �t�F�[�h�C���p�X�v���C�g�̎��
/// </summary>
enum FadeInSpriteType
{
	eWhite,
    eBlack
};

/// <summary>
/// �A�N�V�����V�[��
/// </summary>
class ActionScene : public SceneBase
{
public:

	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	ActionScene();

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~ActionScene();

	/// <summary>
	/// �V�[���̍X�V
	/// </summary>
	/// <param name="_KeyState"> �L�[�{�[�h�A�}�E�X�A�R���g���[���[�̓��͏�� </param>
	/// <returns> �V�[���N���X�̃|�C���^ </returns>
	SceneBase* Update(const InputState& _KeyState)override;

private:

	// �����x�𑫂��Ă������߂̒l
	const float MPlusAlpha;
	// ��p
	const float MAngleOfView;
	// �����܂ł̋���
	const float MLightDistance;
	// �X�v���C�g�̊g��T�C�Y
	const Vector3 MSpriteScale;

	// �X�v���C�g�R���|�[�l���g�̃��X�g
	std::vector<SpriteComponent*> mSpriteComponentList;

	// �v���C���[�̃|�C���^
	PlayerObject* mPlayerPtr;
	// �{�X�̃|�C���^
	BossObject* mBossPtr;
	// �J�����̃|�C���^
	MainCameraObject* mMainCameraPtr;
};

