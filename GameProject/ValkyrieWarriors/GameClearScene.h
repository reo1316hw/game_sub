#pragma once

/// <summary>
/// �Q�[���N���A�V�[��
/// </summary>
class GameClearScene : public SceneBase
{
public:

	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	GameClearScene();

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~GameClearScene();

	/// <summary>
	/// �V�[���̍X�V
	/// </summary>
	/// <param name="_KeyState"> �L�[�{�[�h�A�}�E�X�A�R���g���[���[�̓��͏�� </param>
	/// <returns> �V�[���N���X�̃|�C���^ </returns>
	SceneBase* Update(const InputState& _KeyState)override;

private:

	// �X�v���C�g�̊g��T�C�Y
	const Vector3 MSpriteScale;
	// �^�C�g���V�[���ɑJ�ڂ���^�C�~���O
	const int MTimingTransitionTitle;

	// �^�C�g���V�[���ɑJ�ڂ���܂ł̃J�E���g
	int mTitleTransitionUntilCount;
};

