#pragma once

/// <summary>
/// �{�X���A�N�e�B�u�ɂȂ邱�Ƃɂ���ĉe������I�u�W�F�N�g�̐e�N���X
/// </summary>
class BossActiveAffectedObjects : public GameObject
{
public:

	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="_ObjectTag"> �I�u�W�F�N�g�̃^�O </param>
	/// <param name="_bossActiveBoxPtr"> �{�X���X�V�����邽�߂̓����蔻��p��`�I�u�W�F�N�g�̃|�C���^ </param>
	/// <param name="_bossBootSemitransparentWallPtr"> �{�X���N�����邱�Ƃɂ���ďo�����锼�����̕ǂ̃|�C���^ </param>
	BossActiveAffectedObjects(const Tag& _ObjectTag, BossActiveBox* _bossActiveBoxPtr,
		BossBootSemitransparentWall* _bossBootSemitransparentWallPtr);

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~BossActiveAffectedObjects() {};

private:
};