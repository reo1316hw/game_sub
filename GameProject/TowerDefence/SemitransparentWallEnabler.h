#pragma once

/// <summary>
/// �������̕ǂ�L���ɂ���I�u�W�F�N�g
/// </summary>
class SemitransparentWallEnabler : public GameObject
{
public:

	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="_ObjectTag"> �I�u�W�F�N�g�̃^�O </param>
	/// <param name="_bossActiveBoxPtr"> �X�V���Ă��Ȃ��I�u�W�F�N�g���X�V�����邽�߂̓����蔻��p��`�I�u�W�F�N�g�̃|�C���^ </param>
	/// <param name="_bossBootSemitransparentWallPtr"> �������̕ǂ̃|�C���^ </param>
	SemitransparentWallEnabler(const Tag& _ObjectTag, DeadObjectActiveBox* _deadObjectActiveBoxPtr,
		GameObject* _semitransparentWallPtr);

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~SemitransparentWallEnabler() {};

private:
};