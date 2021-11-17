#pragma once

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

	// �v���C���[�̃|�C���^
	PlayerObject* mPlayerPtr;
	// �{�X�̃|�C���^
	BossObject* mBossPtr;
	// �{�X���X�V�����邽�߂̓����蔻��p��`�I�u�W�F�N�g�̃|�C���^
	BossActiveBox* mBossActiveBoxPtr;
	// �J�����̃|�C���^
	MainCameraObject* mMainCameraPtr;
};

