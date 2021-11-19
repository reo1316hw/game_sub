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
	/// <param name="_DefeatEnemyNum">  �|���G�l�~�[�̐� </param>
	/// <param name="_enemysControlerPtr"> �G�l�~�[�����𐧌䂷��N���X�̃|�C���^ </param>
	DeadEnemyCounterDisable(GameObject* _owner, const int& _DefeatEnemyNum, EnemysControler* _enemysControlerPtr);

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

	// �|���G�l�~�[�̐�
	const int MDefeatEnemyNum;

	// �G�l�~�[�𐧌䂷��N���X�̃|�C���^
	EnemysControler* mEnemysControlerPtr;
};

