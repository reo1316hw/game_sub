#include "pch.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="_playerPtr"> �v���C���[�̃|�C���^ </param>
BossObjectStateAreaAttack::BossObjectStateAreaAttack(PlayerObject* _playerPtr)
	: MDamageValuePlayerFirstAttack(25)
	, MTransitionStateDistance(30000.0f)
	, MVecShortenVelue(0.1f)
	, MSeparationVecLength(4.0f)
	, mIsDamage(false)
	, mDamageValue(0)
	, mPosition(Vector3::Zero)
	, mVelocity(Vector3::Zero)
	, mPlayerPtr(_playerPtr)
{
}

/// <summary>
/// �X�V����
/// </summary>
/// <param name="_owner"> �{�X(�e)�̃|�C���^ </param>
/// <param name="_DeltaTime"> �Ō�̃t���[������������̂ɗv�������� </param>
/// <returns> �{�X�̏�� </returns>
BossState BossObjectStateAreaAttack::Update(BossObject* _owner, const float _DeltaTime)
{
	_owner->SetPosition(mPosition);

	// �v���C���[�̍��W
	Vector3 playerPos = mPlayerPtr->GetPosition();
	// �v���C���[�Ɍ������x�N�g��sd
	Vector3 dirPlayerVec = playerPos - mPosition;

	if (mIsDamage)
	{
	    return BossState::eBossStateDamage;
	}

	// �A�j���[�V�������I��������ړ���Ԃ�
	if (!_owner->GetSkeletalMeshComponentPtr()->IsPlaying())
	{
		if (dirPlayerVec.LengthSq() < MTransitionStateDistance)
		{
			// �����_���l
			int randNum = rand() % 100;

			if (randNum < 50)
			{
				return BossState::eBossStateWait;
			}
			else
			{
				return BossState::eBossStateTeleportation;
			}
		}

		return BossState::eBossStateTrack;
	}

	return BossState::eBossStateAreaAttack;
}

/// <summary>
/// �{�X�̏�Ԃ��ύX���āA�ŏ���1�񂾂��Ăяo�����֐�
/// </summary>
/// <param name="_owner"> �{�X(�e)�̃|�C���^ </param>
/// <param name="_DeltaTime"> �Ō�̃t���[������������̂ɗv�������� </param>
void BossObjectStateAreaAttack::Enter(BossObject* _owner, const float _DeltaTime)
{
	SkeletalMeshComponent* meshcomp = _owner->GetSkeletalMeshComponentPtr();
	meshcomp->PlayAnimation(_owner->GetAnimPtr(BossState::eBossStateAreaAttack));

	mIsDamage = false;

	// ���W
	mPosition = _owner->GetPosition();
}

/// <summary>
/// �{�X�ƃG�l�~�[�̈�������
/// </summary>
/// <param name="_owner"> �{�X(�e)�̃|�C���^ </param>
/// <param name="_DirTargetEnemyVec"> �ΏۂƂȂ�G�l�~�[�Ɍ������x�N�g�� </param>
void BossObjectStateAreaAttack::Separation(BossObject* _owner, const Vector3& _DirTargetEnemyVec)
{
	// ���W
	mPosition = _owner->GetPosition();
	// ���������x�N�g��
	Vector3 separationVec = MSeparationVecLength * _DirTargetEnemyVec;

	mVelocity -= separationVec;
	mVelocity *= MVecShortenVelue;
	mPosition += mVelocity;

	_owner->SetPosition(mPosition);
}

/// <summary>
/// �q�b�g�������̏���
/// </summary>
/// <param name="_owner"> �{�X(�e)�̃|�C���^ </param>
/// <param name="_HitObject"> �q�b�g�����Q�[���I�u�W�F�N�g </param>
void BossObjectStateAreaAttack::OnCollision(BossObject* _owner, const GameObject& _HitObject)
{
	// ���W
	mPosition = _owner->GetPosition();

	// �I�u�W�F�N�g�̃^�O
	Tag tag = _HitObject.GetTag();

	if (tag == Tag::eWeapon)
	{
		mDamageValue = MDamageValuePlayerFirstAttack;
		mIsDamage = true;
	}

	_owner->SetDamageValue(mDamageValue);
}