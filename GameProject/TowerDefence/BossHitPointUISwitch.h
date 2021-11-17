#pragma once

/// <summary>
/// �{�X�̗̑�UI��ON/OFF���s���R���|�[�l���g
/// </summary>
class BossHitPointUISwitch : public Component
{
public:

	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="_owner"> �A�^�b�`����Q�[���I�u�W�F�N�g�̃|�C���^ </param>
	/// <param name="_bossActiveBoxPtr"> �{�X���X�V�����邽�߂̓����蔻��p��`�I�u�W�F�N�g�̃|�C���^ </param>
	/// <param name="_bossHitPointGaugePtr"> �{�X��hp�Q�[�W�̃|�C���^ </param>
	/// <param name="_bossHitPointFramePtr"> �{�X��hp�̘g�̃|�C���^ </param>
	BossHitPointUISwitch(GameObject* _owner, BossActiveBox* _bossActiveBoxPtr,
		BossHitPointGauge* _bossHitPointGaugePtr, BossHitPointFrame* _bossHitPointFramePtr);

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~BossHitPointUISwitch() {};

	/// <summary>
	/// �t���[�����̏���
	/// </summary>
	/// <param name="_deltaTime"> �Ō�̃t���[������������̂ɗv�������� < /param>
	void Update(float _deltaTime)override;

private:

	// �{�X���X�V�����邽�߂̓����蔻��p��`�I�u�W�F�N�g�̃|�C���^
	BossActiveBox* mBossActiveBoxPtr;
	// �{�X��hp�Q�[�W�̃|�C���^
	BossHitPointGauge* mBossHitPointGaugePtr;
	// �{�X��hp�̘g�̃|�C���^
	BossHitPointFrame* mBossHitPointFramePtr;
};