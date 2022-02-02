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

	// �Q�[���N���A�V�[���ɑJ�ڂ���^�C�~���O
	const int MTimingTransitionGameClear;
	// �Q�[���I�[�o�[�V�[���ɑJ�ڂ���^�C�~���O
	const int MTimingTransitionGameOver;
	// ��p
	const float MAngleOfView;
	// �����܂ł̋���
	const float MLightDistance;

	// �Q�[���N���A�V�[���ɑJ�ڂ���܂ł̃J�E���g
	int mGameClearTransitionUntilCount;
	// �Q�[���I�[�o�[�V�[���ɑJ�ڂ���܂ł̃J�E���g
	int mGameOverTransitionUntilCount;

	// �v���C���[�̃|�C���^
	PlayerObject* mPlayerPtr;
	// �{�X�̃|�C���^
	BossObject* mBossPtr;
	// �J�����̃|�C���^
	MainCameraObject* mMainCameraPtr;
};

