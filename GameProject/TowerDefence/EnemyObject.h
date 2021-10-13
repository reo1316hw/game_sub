#pragma once

// �O���錾
class SkeletalMeshComponent;
class EnemyObjectStateBase;
class BoxCollider;

/// <summary>
/// �G�l�~�[�̏��
/// </summary>
enum class EnemyState
{
	eEnemyStateTrack = 0,       // �ǐ�
	eEnemyStateWait,            // �ҋ@
	eEnemyStateAttack,          // �U��
	eEnemyStateLeftMove,        // ���ړ�
	eEnemyStateRightMove,        // �E�ړ�
	eEnemyStateDamage,          // �_���[�W���󂯂�
	eEnemyStateDeath,           // ���S

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
    /// <param name="_ObjectTag"> �^�O </param>
    /// <param name="_SceneTag"> �V�[���^�O </param>
	/// <param name="_playerPtr"> �v���C���[�̃|�C���^ </param>
	EnemyObject(const Vector3& _Pos, const Vector3& _Scale, const std::string _GpmeshName, const char* _GpskelName,
		        const Tag& _ObjectTag, const SceneBase::Scene _SceneTag, PlayerObject* _playerPtr);

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~EnemyObject() {};

	/// <summary>
	/// �G�l�~�[���m�̈�������
	/// </summary>
	/// <param name="_DirTargetEnemyVec"> �ΏۂƂȂ�G�l�~�[�Ɍ������x�N�g�� </param>
	void Separation(const Vector3& _DirTargetEnemyVec);

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

	// �A�j���[�V�����̍Đ����x
	const float MPlayRate;

	// �A�j���[�V�����ϒ��R���e�i
	std::vector<const Animation*>       mAnimTypes;
	// �X�e�[�g�N���X�v�[��
	std::vector<EnemyObjectStateBase*> mStatePools;
	// ���݂̃X�e�[�g
	EnemyState mNowState;
	// ���̃X�e�[�g
	EnemyState mNextState;
	//�Q�[���I�u�W�F�N�g�̃X�P���g�����b�V��
	SkeletalMeshComponent* mSkeltalMeshComponentPtr;

public://�Q�b�^�[�Z�b�^�[

	/// <summary>
	/// Animation�̃|�C���^���擾
	/// </summary>
	/// <param name="_State"> �G�l�~�[�̏�� </param>
	/// <returns> Animation�̃|�C���^ </returns>
	const Animation* GetAnimPtr(const EnemyState _State) const { return mAnimTypes[(int)_State]; };

	/// <summary>
	/// SkeletalMeshComponent�̃|�C���^���擾
	/// </summary>
	/// <returns> SkeletalMeshComponent�̃|�C���^ </returns>
	SkeletalMeshComponent* GetSkeletalMeshComponentPtr() { return mSkeltalMeshComponentPtr; };
};

