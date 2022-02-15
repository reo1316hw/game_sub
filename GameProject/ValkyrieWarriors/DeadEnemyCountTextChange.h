#pragma once

/// <summary>
/// �|�����G�l�~�[�̃J�E���gUI�̃e�N�X�`����ς���N���X
/// </summary>
class DeadEnemyCountTextChange : public Component
{
public:

	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="_owner"> �A�^�b�`����Q�[���I�u�W�F�N�g�̃|�C���^ </param>
	/// <param name="_spriteComponentPtr"> �摜�f�[�^�N���X���Ǘ����A�X�N���[����ɕ`�悷��R���|�[�l���g�̃|�C���^ </param>
	/// <param name="_enemysControlerPtr"> �G�l�~�[�𐧌䂷��R���|�[�l���g�̃|�C���^ </param>
	DeadEnemyCountTextChange(GameObject* _owner, SpriteComponent* _spriteComponentPtr, EnemysControler* _enemysControlerPtr);

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~DeadEnemyCountTextChange() {};

	/// <summary>
	/// �t���[�����̏���
	/// </summary>
	/// <param name="_deltaTime"> �Ō�̃t���[������������̂ɗv�������� < /param>
	void Update(float _deltaTime)override;

private:

	// ���݂̓|�����G�l�~�[�̐�
	int mNowDeadEnemyCount;

	// 10�̈�
	const int MTenPlace;
	// 100�̈�
	const int MOneHundredPlace;

	// �������W
	const Vector3 MInitPos;
	// �J�E���g��10�̈ʂɒB�����Ƃ��ɂ��炷�x�N�g��
	const Vector3 MTenPlaceShiftVec;
	// �J�E���g��100�̈ʂɒB�����Ƃ��ɂ��炷�x�N�g��
	const Vector3 MOneHundredPlaceShiftVec;

	// �摜�f�[�^�N���X���Ǘ����A�X�N���[����ɕ`�悷��R���|�[�l���g�̃|�C���^
	SpriteComponent* mSpriteComponentPtr;
	// �G�l�~�[�𐧌䂷��R���|�[�l���g�̃|�C���^
	EnemysControler* mEnemysControlerPtr;
};