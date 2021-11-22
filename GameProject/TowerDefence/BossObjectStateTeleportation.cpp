#include "pch.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="_playerPtr"> �v���C���[�̃|�C���^ </param>
BossObjectStateTeleportation::BossObjectStateTeleportation(PlayerObject* _playerPtr)
	: MTimingTeleportationEnding(120)
	, MTransitionStateDistance(30000.0f)
	, mIsDamage(false)
	, mUntilTeleportationEndingCount(0)
	, mTeleportationVec(Vector3::Zero)
	, mPosition(Vector3::Zero)
	, mPlayerPtr(_playerPtr)
{
}

/// <summary>
/// �X�V����
/// </summary>
/// <param name="_owner"> �{�X(�e)�̃|�C���^ </param>
/// <param name="_DeltaTime"> �Ō�̃t���[������������̂ɗv�������� </param>
/// <returns> �{�X�̏�� </returns>
BossState BossObjectStateTeleportation::Update(BossObject* _owner, const float _DeltaTime)
{
	// �v���C���[�̍��W
	Vector3 playerPos = mPlayerPtr->GetPosition();
	// �v���C���[�Ɍ������x�N�g��sd
	Vector3 dirPlayerVec = playerPos - mPosition;

	mPosition = playerPos + mTeleportationVec * 100.0f;

	++mUntilTeleportationEndingCount;

	_owner->SetPosition(mPosition);

	if (mUntilTeleportationEndingCount >= MTimingTeleportationEnding)
	{
		if (dirPlayerVec.LengthSq() < MTransitionStateDistance)
		{
			// �����_���l
			int randNum = rand() % 100;

			if (randNum < 30)
			{
				return BossState::eBossStateAreaAttack;
			}
			else if (randNum >= 30 && randNum < 60)
			{
				return BossState::eBossStateFrontAttack;
			}
			else if (randNum >= 60 && randNum < 90)
			{
				return BossState::eBossStateOverheadAttack;
			}
			else
			{
				return BossState::eBossStateWait;
			}
		}

		return BossState::eBossStateTrack;
	}
	
	return BossState::eBossStateTeleportation;
}

/// <summary>
/// �{�X�̏�Ԃ��ύX���āA�ŏ���1�񂾂��Ăяo�����֐�
/// </summary>
/// <param name="_owner"> �{�X(�e)�̃|�C���^ </param>
/// <param name="_DeltaTime"> �Ō�̃t���[������������̂ɗv�������� </param>
void BossObjectStateTeleportation::Enter(BossObject* _owner, const float _DeltaTime)
{
	SkeletalMeshComponent* meshcomp = _owner->GetSkeletalMeshComponentPtr();
	meshcomp->PlayAnimation(_owner->GetAnimPtr(BossState::eBossStateTeleportation));

	mIsDamage = false;
	mUntilTeleportationEndingCount = 0;

	// ���W
	mPosition = _owner->GetPosition();

	int randnum = rand() % 4;

	switch (randnum)
	{
	case 0:

		mTeleportationVec = Vector3::UnitX + Vector3::UnitY;

		break;
	case 1:

		mTeleportationVec = Vector3::NegUnitX + Vector3::UnitY;

		break;
	case 2:

		mTeleportationVec = Vector3::NegUnitX + Vector3::NegUnitY;

		break;
	case 3:

		mTeleportationVec = Vector3::UnitX + Vector3::NegUnitY;

		break;
	}

	// �v���C���[�̉�]�l
	Quaternion playerRotation = mPlayerPtr->GetRotation();
	// �e���|�[�g�������
	mTeleportationVec = Vector3::Transform(mTeleportationVec, playerRotation);

	// �����ɂ���
	_owner->GetSkeletalMeshComponentPtr()->SetVisible(false);
}

/// <summary>
/// �{�X�̏�Ԃ��ύX���āA�Ō��1�񂾂��Ăяo�����֐�
/// </summary>
/// <param name="_owner"> �{�X(�e)�̃|�C���^ </param>
/// <param name="_DeltaTime"> �Ō�̃t���[������������̂ɗv�������� </param>
void BossObjectStateTeleportation::Exit(BossObject* _owner, const float _DeltaTime)
{
	// �s�����ɂ���
	_owner->GetSkeletalMeshComponentPtr()->SetVisible(true);
}