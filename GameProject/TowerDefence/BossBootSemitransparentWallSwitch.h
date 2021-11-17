#pragma once

/// <summary>
/// �{�X���N�����邱�Ƃɂ���ďo�����锼�����̕ǂ�ON/OFF���s���R���|�[�l���g
/// </summary>
class BossBootSemitransparentWallSwitch : public Component
{
public:

	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="_owner"> �A�^�b�`����Q�[���I�u�W�F�N�g�̃|�C���^ </param>
	/// <param name="_bossActiveBoxPtr"> �{�X���X�V�����邽�߂̓����蔻��p��`�I�u�W�F�N�g�̃|�C���^ </param>
	/// <param name="_bossBootSemitransparentWallPtr"> �{�X���N�����邱�Ƃɂ���ďo�����锼�����̕ǂ̃|�C���^ </param>
	BossBootSemitransparentWallSwitch(GameObject* _owner, BossActiveBox* _bossActiveBoxPtr,
		BossBootSemitransparentWall* _bossBootSemitransparentWallPtr);

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~BossBootSemitransparentWallSwitch() {};

	/// <summary>
	/// �t���[�����̏���
	/// </summary>
	/// <param name="_deltaTime"> �Ō�̃t���[������������̂ɗv�������� < /param>
	void Update(float _deltaTime)override;

private:

	// �{�X���X�V�����邽�߂̓����蔻��p��`�I�u�W�F�N�g�̃|�C���^
	BossActiveBox* mBossActiveBoxPtr;
	// �{�X���N�����邱�Ƃɂ���ďo�����锼�����̕ǂ̃|�C���^
	BossBootSemitransparentWall * mBossBootSemitransparentWallPtr;
};