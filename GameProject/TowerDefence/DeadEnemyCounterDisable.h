#pragma once

/// <summary>
/// �|�����G�l�~�[���J�E���g����I�u�W�F�N�g�𖳌��ɂ���N���X
/// </summary>
class DeadEnemyCounterDisable : public Component
{
public:

	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="_owner"> �A�^�b�`����Q�[���I�u�W�F�N�g�̃|�C���^ </param>
	/// <param name="_enemysControlerPtr"> �G�l�~�[�����𐧌䂷��N���X�̃|�C���^ </param>
	DeadEnemyCounterDisable(GameObject* _owner, EnemysControler* _enemysControlerPtr);

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~DeadEnemyCounterDisable() {};

	/// <summary>
	/// �t���[�����̏���
	/// </summary>
	/// <param name="_deltaTime"> �Ō�̃t���[������������̂ɗv�������� < /param>
	void Update(float _deltaTime)override;

private:

	// �ŏ��ɓ|���G�l�~�[�̐�
	const int MFirstDefeatEnemyNum;
	// ���ɓ|���G�l�~�[�̐�
	const int MNextDefeatEnemyNum;

	// �|���G�l�~�[�̐�
	int mDeadEnemyNum;

	// �G�l�~�[�𐧌䂷��N���X�̃|�C���^
	EnemysControler* mEnemysControlerPtr;
};

