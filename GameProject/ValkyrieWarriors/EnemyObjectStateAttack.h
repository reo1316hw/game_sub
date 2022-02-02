#pragma once

/// <summary>
/// �G�l�~�[�̍U�����
/// </summary>
class EnemyObjectStateAttack : public EnemyObjectStateBase
{
public:
	
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="_enemyAttackPtr"> �G�l�~�[�̍U������I�u�W�F�N�g�̃|�C���^ </param>
	EnemyObjectStateAttack(EnemyAttackDecisionObject* _enemyAttackPtr);

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~EnemyObjectStateAttack() {};

	/// <summary>
	/// �X�V����
	/// </summary>
	/// <param name="_owner"> �G�l�~�[(�e)�̃|�C���^ </param>
	/// <param name="_DeltaTime"> �Ō�̃t���[������������̂ɗv�������� </param>
	/// <returns> �G�l�~�[�̏�� </returns>
	EnemyState Update(EnemyObject* _owner, const float _DeltaTime)override;

	/// <summary>
	/// �G�l�~�[�̏�Ԃ��ύX���āA�ŏ���1�񂾂��Ăяo�����֐�
	/// </summary>
	/// <param name="_owner"> �G�l�~�[(�e)�̃|�C���^ </param>
	/// <param name="_DeltaTime"> �Ō�̃t���[������������̂ɗv�������� </param>
	void Enter(EnemyObject* _owner, const float _DeltaTime)override;

	/// <summary>
	/// �G�l�~�[���m�̈�������
	/// </summary>
	/// <param name="_owner"> �G�l�~�[(�e)�̃|�C���^ </param>
	/// <param name="_DirTargetEnemyVec"> �ΏۂƂȂ�G�l�~�[�Ɍ������x�N�g�� </param>
	void Separation(EnemyObject* _owner, const Vector3& _DirTargetEnemyVec)override;

	/// <summary>
	/// �q�b�g�������̏���
	/// </summary>
	/// <param name="_owner"> �G�l�~�[(�e)�̃|�C���^ </param>
	/// <param name="_HitObject"> �q�b�g�����Q�[���I�u�W�F�N�g </param>
	void OnCollision(EnemyObject* _owner, const GameObject& _HitObject)override;

private:

	/// <summary>
	/// �U�����󂯂����̏���
	/// </summary>
	/// <param name="_HitTag"> �q�b�g�����I�u�W�F�N�g�̃^�O </param>
	/// <param name="_DamageValuePlayerAttack"> �_���[�W�� </param>
	/// <returns> �q�b�g������ </returns>
	bool ReceivedAttack(const Tag& _HitTag, const int& _DamageValuePlayerAttack);

	// �q�b�g����I�u�W�F�N�g�̃��X�g
	Tag mHitTagList[4];

	// �_���[�W�l�̃��X�g
	int mDamageValueList[4];

	// ��ԑJ�ڊm��
	const int MStateTransitionProbability;
	// �����蔻���L���ɂ���^�C�~���O
	const float MBoxEnableTiming;
	// �U�����̑��x
	const float MAttackSpeed;
	// �A�j���[�V�����̍Đ����x
	const float MPlayRate;
	// �x�N�g����Z������l
	const float MVecShortenVelue;
	// ���������x�N�g���̒���
	const float MSeparationVecLength;

	// �_���[�W���󂯂���
	bool mIsDamage;
	// �����蔻��̏��
	// true : �L��, false : ����
	bool mIsCollisionState;
	// ���݂̃X�e�[�g�ɓ�����1�񂾂������蔻���L���ɂ���
	bool mIsOneCollisionState;

	// �_���[�W�l
	int mDamageValue;
	// �q�b�g���鑊��̃��X�g�̗v�f��
	int mHitTagListSize;

	// ���̃X�e�[�g�ɓ����Ă���̌o�ߎ���
	float mElapseTime;
	// �A�j���[�V����������
	float mTotalAnimTime;
	// �����蔻��𖳌��ɂ���^�C�~���O
	float mBoxDisableTiming;

	// ���W
	Vector3 mPosition;
	// ���x
	Vector3 mVelocity;
	// �O���x�N�g��
	Vector3 mForwardVec;
	// �q�b�g�����I�u�W�F�N�g�̃^�O
	Tag mHitTag;

	// �G�l�~�[�̃|�C���^
	EnemyObject* mEnemyPtr;
	// �e�̋�`�����蔻����s���N���X�̃|�C���^
	BoxCollider* mOwnerBoxCollider;
};