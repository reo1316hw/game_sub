#pragma once

/// <summary>
/// �Q�[���I�[�o�[�V�[��
/// </summary>
class GameOverScene : public SceneBase
{
public:

	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	GameOverScene();

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~GameOverScene();

	/// <summary>
	/// �V�[���̍X�V
	/// </summary>
	/// <param name="_KeyState"> �L�[�{�[�h�A�}�E�X�A�R���g���[���[�̓��͏�� </param>
	/// <returns> �V�[���N���X�̃|�C���^ </returns>
	SceneBase* Update(const InputState& _KeyState)override;

private:
};