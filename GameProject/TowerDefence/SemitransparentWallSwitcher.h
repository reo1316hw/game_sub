#pragma once

/// <summary>
/// �������̕ǂ�ON/OFF����I�u�W�F�N�g
/// </summary>
class SemitransparentWallSwitcher : public GameObject
{
public:

	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="_ObjectTag"> �I�u�W�F�N�g�̃^�O </param>
	/// <param name="_bossActiveBoxPtr"> �X�V���Ă��Ȃ��I�u�W�F�N�g���X�V�����邽�߂̓����蔻��p��`�I�u�W�F�N�g�̃|�C���^ </param>
	/// <param name="_bossBootSemitransparentWallPtr"> �������̕ǂ̃|�C���^ </param>
	SemitransparentWallSwitcher(const Tag& _ObjectTag, DeadObjectActiveBox* _deadObjectActiveBoxPtr,
		GameObject* _semitransparentWallPtr);

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~SemitransparentWallSwitcher() {};

private:
};