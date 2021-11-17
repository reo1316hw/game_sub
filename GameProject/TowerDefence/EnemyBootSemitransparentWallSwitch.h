#pragma once

/// <summary>
/// �G�l�~�[���N�����邱�Ƃɂ���ďo�����锼�����̕ǂ�ON/OFF���s���R���|�[�l���g
/// </summary>
class EnemyBootSemitransparentWallSwitch : public Component
{
public:

	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="_owner"> �A�^�b�`����Q�[���I�u�W�F�N�g�̃|�C���^ </param>
	/// <param name="_enemyActiveBoxPtr"> �G�l�~�[���X�V�����邽�߂̓����蔻��p��`�I�u�W�F�N�g�̃|�C���^ </param>
	/// <param name="_enemyBootSemitransparentWallPtr"> �G�l�~�[���N�����邱�Ƃɂ���ďo�����锼�����̕ǂ̃|�C���^ </param>
	EnemyBootSemitransparentWallSwitch(GameObject* _owner, EnemyActiveBox* _enemyActiveBoxPtr,
		EnemyBootSemitransparentWall* _enemyBootSemitransparentWallPt);

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~EnemyBootSemitransparentWallSwitch() {};

	/// <summary>
	/// �t���[�����̏���
	/// </summary>
	/// <param name="_deltaTime"> �Ō�̃t���[������������̂ɗv�������� < /param>
	void Update(float _deltaTime)override;

private:

	// �G�l�~�[���X�V�����邽�߂̓����蔻��p��`�I�u�W�F�N�g�̃|�C���^
	EnemyActiveBox* mEnemyActiveBoxPtr;
	// �G�l�~�[���N�����邱�Ƃɂ���ďo�����锼�����̕ǂ̃|�C���^
	EnemyBootSemitransparentWall* mEnemyBootSemitransparentWallPtr;
};