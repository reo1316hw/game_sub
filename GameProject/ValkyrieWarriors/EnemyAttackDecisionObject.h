#pragma once

/// <summary>
/// �G�l�~�[�̍U������I�u�W�F�N�g
/// </summary>
class EnemyAttackDecisionObject : public GameObject
{
public:

	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="_owner"> �e�N���X�̃|�C���^ </param>
	/// <param name="_ObjectTag"> �I�u�W�F�N�g�̃^�O </param>
	EnemyAttackDecisionObject(GameObject* _owner, const Tag& _ObjectTag);

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~EnemyAttackDecisionObject() {};

	/// <summary>
	/// �I�u�W�F�N�g�̍X�V����
	/// </summary>
	/// <param name="_deltaTime"> �Ō�̃t���[������������̂ɗv�������� </param>
	void UpdateGameObject(float _deltaTime)override;

private:

	// ���S���W�Ƃ̍�
	const float MCenterOffset;

	// �e�N���X�̃|�C���^
	GameObject* mOwner;
};