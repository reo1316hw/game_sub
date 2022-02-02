#pragma once

/// <summary>
/// �v���C���[�̓���ɍU������G�t�F�N�g
/// </summary>
class OverheadMagicEffect : public GameObject
{
public:

	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="_bossPtr"> �{�X�̃|�C���^ </param>
	/// <param name="_playerPtr"> �v���C���[�̃|�C���^ </param>
	/// <param name="_Scale"> �傫�� </param>
	/// <param name="_ObjectTag"> �I�u�W�F�N�g�̃^�O </param>
	OverheadMagicEffect(BossObject* _bossPtr, PlayerObject* _playerPtr, const Vector3& _Scale, const Tag& _ObjectTag);

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~OverheadMagicEffect() {};

	/// <summary>
	/// �I�u�W�F�N�g�̍X�V����
	/// </summary>
	/// <param name="_deltaTime"> �Ō�̃t���[������������̂ɗv�������� </param>
	void UpdateGameObject(float _deltaTime)override;

private:

	// �G�t�F�N�g�̍��W���X�V���Ȃ��^�C�~���O
	const float MEffectPositionUnUpdateTiming;
	// �����蔻���L���ɂ���^�C�~���O
	const float MBoxEnableTiming;
	// �����蔻��𖳌��ɂ���^�C�~���O
	const float MBoxDisableTiming;

	// �����蔻��̏��
	// true : �L��, false : ����
	bool mIsCollisionState;
	// 1�񂾂������蔻���L���ɂ���t���O
	bool mIsOneCollisionState;
	// �G�t�F�N�g���Đ�������
	bool mIsPlayEffect;

	// �o�ߎ���
	float mElapseTime;

	// �{�X�̃|�C���^
	BossObject* mBossPtr;
	// �v���C���[�̃|�C���^
	PlayerObject* mPlayerPtr;
	// �G�t�F�N�g�R���|�[�l���g�N���X�̃|�C���^
	EffectComponent* mEffectComponentPtr;
};