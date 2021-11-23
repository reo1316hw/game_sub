#pragma once

/// <summary>
/// �v���C���[����U�����̊댯�M���G�t�F�N�g
/// </summary>
class DangerSignalEffect : public GameObject
{
public:

	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="_bossPtr"> �{�X�̃|�C���^ </param>
	/// <param name="_playerPtr"> �v���C���[�̃|�C���^ </param>
	/// <param name="_Scale"> �傫�� </param>
	/// <param name="_ObjectTag"> �I�u�W�F�N�g�̃^�O </param>
	DangerSignalEffect(BossObject* _bossPtr, PlayerObject* _playerPtr, const Vector3& _Scale, const Tag& _ObjectTag);

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~DangerSignalEffect() {};

	/// <summary>
	/// �I�u�W�F�N�g�̍X�V����
	/// </summary>
	/// <param name="_deltaTime"> �Ō�̃t���[������������̂ɗv�������� </param>
	void UpdateGameObject(float _deltaTime)override;

private:

	// �G�t�F�N�g�̍��W���X�V���Ȃ��^�C�~���O
	const float MEffectPositionUnUpdateTiming;
	// �����␳�l
	const Vector3 MHeightCorrection;

	// �o�ߎ���
	float mElapseTime;

	// �{�X�̃|�C���^
	BossObject* mBossPtr;
	// �v���C���[�̃|�C���^
	PlayerObject* mPlayerPtr;
	// �G�t�F�N�g�R���|�[�l���g�N���X�̃|�C���^
	EffectComponent* mEffectComponentPtr;
};