#pragma once

// �O���錾
class SkeletalMeshComponent;
class EnemyObjectStateBase;
class EnemyAttackDecisionObject;
class EnemyHitPointGauge;
class EnemyHitPointFrame;
class BoxCollider;

/// <summary>
/// �G�l�~�[�̏��
/// </summary>
enum class EnemyState
{
	eEnemyStateTrack = 0,        // �ǐ�
	eEnemyStateWait,             // �ҋ@
	eEnemyStateAttack,           // �U��
	eEnemyStateAttackReady,      // �U������
	eEnemyStateLeftMove,         // ���ړ�
	eEnemyStateRightMove,        // �E�ړ�
	eEnemyStateImpactDamage,     // �_���[�W���󂯂�(�������Ռ�)
	eEnemyStateSweepFallDamage,  // �_���[�W���󂯂�(�������ŗ�����)
	eEnemyStateFlyingBackDamage, // �_���[�W���󂯂�(�����܂Ŕ�s���ė�����)
	eEnemyStateStandUp,          // �N���オ��
	eEnemyStateFallingBackDeath, // ���S(���̏�ŕ��ꗎ����)
	eEnemyStateSweepFallDeath,   // ���S(�������ŗ�����)
	eEnemyStateFlyingBackDeath,  // ���S(�����܂Ŕ�s���ė�����)

	eEnemyStateNum,             // ���A�j���[�V������
};

/// <summary>
/// �G�l�~�[
/// </summary>
class EnemyObject : public GameObject
{
public:

	/// <summary>
    /// �R���X�g���N�^
    /// </summary>
    /// <param name="_Pos"> ���W </param>
    /// <param name="_Scale"> �傫�� </param>
    /// <param name="_GpmeshName"> gpmesh�̃p�X </param>
    /// <param name="_GpskelName"> gpskel�̃p�X </param>
    /// <param name="_ObjectTag"> �I�u�W�F�N�g�̃^�O </param>
	/// <param name="_playerPtr"> �v���C���[�̃|�C���^ </param>
	EnemyObject(const Vector3& _Pos, const Vector3& _Scale, const std::string _GpmeshName, const char* _GpskelName,
		        const Tag& _ObjectTag, PlayerObject* _playerPtr);

	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="_ShouldTutorialUse"> �`���[�g���A���Ŏg�p���邩 </param>
	/// <param name="_Pos"> ���W </param>
	/// <param name="_Scale"> �傫�� </param>
	/// <param name="_GpmeshName"> gpmesh�̃p�X </param>
	/// <param name="_GpskelName"> gpskel�̃p�X </param>
	/// <param name="_ObjectTag"> �I�u�W�F�N�g�̃^�O </param>
	/// <param name="_playerPtr"> �v���C���[�̃|�C���^ </param>
	EnemyObject(const bool& _ShouldTutorialUse, const Vector3& _Pos, const Vector3& _Scale, const std::string _GpmeshName,
		const char* _GpskelName, const Tag& _ObjectTag, PlayerObject* _playerPtr);

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~EnemyObject() {};

	/// <summary>
	/// �G�l�~�[���m�̈�������
	/// </summary>
	/// <param name="_DirTargetEnemyVec"> �ΏۂƂȂ�G�l�~�[�Ɍ������x�N�g�� </param>
	void Separation(const Vector3& _DirTargetEnemyVec)override;

	/// <summary>
    /// �I�u�W�F�N�g�̍X�V����
    /// </summary>
    /// <param name="_deltaTime"> �Ō�̃t���[������������̂ɗv�������� </param>
	void UpdateGameObject(float _deltaTime)override;

private:

	/// <summary>
    /// �q�b�g�������̏���
    /// </summary>
    /// <param name="_HitObject"> �q�b�g�����Q�[���I�u�W�F�N�g </param>
	void OnCollision(const GameObject& _HitObject)override;

	// �`���[�g���A���Ŏg�p���邩
	const bool MShouldTutorialUse;
	
	// �ő�̗�
	const int MMaxHp;

	// �A�j���[�V�����̍Đ����x
	const float MPlayRate;

	// hp�Q�[�W�̑傫��
	const Vector3 MHpGaugeScale;
	// �q�b�g�G�t�F�N�g�̑傫��
	const Vector3 MHitEffectScale;

	// �A�j���[�V�����ϒ��R���e�i
	std::vector<const Animation*>       mAnimTypes;
	// �X�e�[�g�N���X�v�[��
	std::vector<EnemyObjectStateBase*> mStatePools;

	// �������W
	Vector3 mInitPosition;

	// ���݂̃X�e�[�g
	EnemyState mNowState;
	// ���̃X�e�[�g
	EnemyState mNextState;

	//�Q�[���I�u�W�F�N�g�̃X�P���g�����b�V��
	SkeletalMeshComponent* mSkeltalMeshComponentPtr;
	// �G�l�~�[�̍U������I�u�W�F�N�g�̃|�C���^
	EnemyAttackDecisionObject* mEnemyAttackPtr;
	// �G�l�~�[��hp�Q�[�W�̃|�C���^
	EnemyHitPointGauge* mEnemyHitPointGaugePtr;
	// �G�l�~�[��hp�̘g�̃|�C���^
	EnemyHitPointFrame* mEnemyHitPointFramePtr;

public://�Q�b�^�[�Z�b�^�[

	/// <summary>
	/// �`���[�g���A���Ŏg�p���邩�t���O���擾
	/// </summary>
	/// <returns> �`���[�g���A���Ŏg�p���邩�t���O </returns>
	const bool GetShouldTutorialUse() const { return MShouldTutorialUse; }

	/// <summary>
	/// Animation�̃|�C���^���擾
	/// </summary>
	/// <param name="_State"> �G�l�~�[�̏�� </param>
	/// <returns> Animation�̃|�C���^ </returns>
	const Animation* GetAnimPtr(const EnemyState _State) const { return mAnimTypes[(int)_State]; }

	/// <summary>
	/// SkeletalMeshComponent�̃|�C���^���擾
	/// </summary>
	/// <returns> SkeletalMeshComponent�̃|�C���^ </returns>
	SkeletalMeshComponent* GetSkeletalMeshComponentPtr() { return mSkeltalMeshComponentPtr; }

	/// <summary>
	/// �G�l�~�[�̌��݂̃X�e�[�g���擾
	/// </summary>
	/// <returns> �G�l�~�[�̌��݂̃X�e�[�g </returns>
	EnemyState GetEnemyState() { return mNowState; }

	/// <summary>
	/// �������W���擾
	/// </summary>
	/// <returns> �������W </returns>
	Vector3 GetInitPosition() { return mInitPosition; }

	/// <summary>
	/// �G�l�~�[��hp�Q�[�W�̃|�C���^
	/// </summary>
	/// <returns> �G�l�~�[��hp�Q�[�W </returns>
	EnemyHitPointGauge* GetEnemyHitPointGaugePtr() {return mEnemyHitPointGaugePtr; }

	/// <summary>
	/// �G�l�~�[��hp�̘g�̃|�C���^
	/// </summary>
	/// <returns> �G�l�~�[��hp�̘g </returns>
	EnemyHitPointFrame* GetEnemyHitPointFramePtr() { return mEnemyHitPointFramePtr; }

};

