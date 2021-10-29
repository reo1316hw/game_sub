#pragma once

// �O���錾
class SkeletalMeshComponent;
class BossObjectStateBase;
class BoxCollider;

/// <summary>
/// �{�X�̏��
/// </summary>
enum class BossState
{
	eBossStateWait = 0,             // �ҋ@
	eBossStateTrack,                // �ǐ�
	eBossStateFrontAttack,          // �O���U��
	eBossStateAreaAttack,           // �͈͍U��
	eBossStateOverheadAttack,    	// �v���C���[�̓���ɍU��
	eBossStateTeleportation,    	// �u�Ԉړ�
	eBossStateDamage,               // �_���[�W���󂯂�
	eBossStateDeath,                // ���S

	eBossStateNum,                  // ���A�j���[�V������
};

/// <summary>
/// �{�X
/// </summary>
class BossObject : public GameObject
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
	BossObject(const Vector3& _Pos, const Vector3& _Scale, const std::string _GpmeshName, const char* _GpskelName,
		const Tag& _ObjectTag, PlayerObject* _playerPtr);

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~BossObject() {};

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

	// �ő�̗�
	const int MMaxHp;
	// �A�j���[�V�����̍Đ����x
	const float MPlayRate;
	// �q�b�g�G�t�F�N�g�̑傫��
	const Vector3 MHitEffectScale;

	// �A�j���[�V�����ϒ��R���e�i
	std::vector<const Animation*>      mAnimTypes;
	// �X�e�[�g�N���X�v�[��
	std::vector<BossObjectStateBase*> mStatePools;

	// �������W
	Vector3 mInitPosition;

	// ���݂̃X�e�[�g
	BossState mNowState;
	// ���̃X�e�[�g
	BossState mNextState;

	//�Q�[���I�u�W�F�N�g�̃X�P���g�����b�V��
	SkeletalMeshComponent* mSkeltalMeshComponentPtr;

public://�Q�b�^�[�Z�b�^�[

	/// <summary>
	/// Animation�̃|�C���^���擾
	/// </summary>
	/// <param name="_State"> �{�X�̏�� </param>
	/// <returns> Animation�̃|�C���^ </returns>
	const Animation* GetAnimPtr(const BossState _State) const { return mAnimTypes[(int)_State]; }

	/// <summary>
	/// SkeletalMeshComponent�̃|�C���^���擾
	/// </summary>
	/// <returns> SkeletalMeshComponent�̃|�C���^ </returns>
	SkeletalMeshComponent* GetSkeletalMeshComponentPtr() { return mSkeltalMeshComponentPtr; }

	/// <summary>
	/// �������W���擾
	/// </summary>
	/// <returns> �������W </returns>
	Vector3 GetInitPosition() { return mInitPosition; }
};

