#pragma once

/// <summary>
/// �͈͍U���G�t�F�N�g
/// </summary>
class AreaMagicEffect : public GameObject
{
public:

	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="_bossPtr"> �{�X�̃|�C���^ </param>
	/// <param name="_Scale"> �傫�� </param>
	/// <param name="_ObjectTag"> �I�u�W�F�N�g�̃^�O </param>
	AreaMagicEffect(BossObject* _bossPtr, const Vector3& _Scale, const Tag& _ObjectTag);

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~AreaMagicEffect() {};

	/// <summary>
	/// �I�u�W�F�N�g�̍X�V����
	/// </summary>
	/// <param name="_deltaTime"> �Ō�̃t���[������������̂ɗv�������� </param>
	void UpdateGameObject(float _deltaTime)override;

private:

	// �����␳�l
	const Vector3 MHeightCorrection;

	// �{�X�̌��݂̃X�e�[�g
	BossState mNowState;

	// �{�X�̃|�C���^
	BossObject* mBossPtr;
	// �G�t�F�N�g�R���|�[�l���g�N���X�̃|�C���^
	EffectComponent* mEffectComponentPtr;
};