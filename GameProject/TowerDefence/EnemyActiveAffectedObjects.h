#pragma once

/// <summary>
/// �G�l�~�[���A�N�e�B�u�ɂȂ邱�Ƃɂ���ĉe������I�u�W�F�N�g�̐e�N���X
/// </summary>
class EnemyActiveAffectedObjects : public GameObject
{
public:
	
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="_ObjectTag"> �I�u�W�F�N�g�̃^�O </param>
	/// <param name="_enemyActiveBoxPtr"> �G�l�~�[���X�V�����邽�߂̓����蔻��p��`�I�u�W�F�N�g�̃|�C���^ </param>
	/// <param name="_enemyBootSemitransparentWallPtr"> �G�l�~�[���N�����邱�Ƃɂ���ďo�����锼�����̕ǂ̃|�C���^ </param>
	EnemyActiveAffectedObjects(const Tag& _ObjectTag, EnemyActiveBox* _enemyActiveBoxPtr,
		EnemyBootSemitransparentWall* _enemyBootSemitransparentWallPtr);

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~EnemyActiveAffectedObjects() {};

private:
};