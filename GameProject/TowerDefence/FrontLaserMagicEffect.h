#pragma once

/// <summary>
/// �O���U���G�t�F�N�g(���[�U�[�̕���)
/// </summary>
class FrontLaserMagicEffect : public GameObject
{
public:

	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="_bossPtr"> �{�X�̃|�C���^ </param>
	/// <param name="_Scale"> �傫�� </param>
	/// <param name="_ObjectTag"> �I�u�W�F�N�g�̃^�O </param>
	FrontLaserMagicEffect(BossObject* _bossPtr, const Vector3& _Scale, const Tag& _ObjectTag);

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~FrontLaserMagicEffect() {};

	/// <summary>
	/// �I�u�W�F�N�g�̍X�V����
	/// </summary>
	/// <param name="_deltaTime"> �Ō�̃t���[������������̂ɗv�������� </param>
	void UpdateGameObject(float _deltaTime)override;

private:

	// �����蔻���L���ɂ���^�C�~���O
	const float MBoxEnableTiming;

	// �����␳�l
	const Vector3 MHeightCorrection;

	// �G�t�F�N�g���Đ�������
	bool mIsPlayEffect;

	// �o�ߎ���
	float mElapseTime;
	
	// �{�X�̃|�C���^
	BossObject* mBossPtr;
	// �G�t�F�N�g�R���|�[�l���g�N���X�̃|�C���^
	EffectComponent* mEffectComponentPtr;
};