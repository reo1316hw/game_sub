#include "pch.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>	
/// <param name="_playerPtr"> �v���C���[�̃|�C���^ </param>
/// <param name="_Scale"> �傫�� </param>
/// <param name="_ObjectTag"> �I�u�W�F�N�g�̃^�O </param>
/// <param name="_secondAttackPtr"> 2�i�K�ڂ̒ʏ�U����Ԃ̃N���X�̃|�C���^ </param>
SecondAttackEffect::SecondAttackEffect(PlayerObject* _playerPtr, const Vector3& _Scale, const Tag& _ObjectTag, PlayerObjectStateSecondAttack* _secondAttackPtr)
	: GameObject(_ObjectTag)
	, mHitTagList{ Tag::eEnemy, Tag::eBoss }
	, MOffset(10.0f)
	, mHitEnemyCount(0)
	, mHitTagListSize(sizeof(mHitTagList) / sizeof(int))
	, mFaceInEnemyVec(Vector3::Zero)
	, mFaceInFlockCenterVec(Vector3::Zero)
	, mHitTag(Tag::eOther)
	, mPlayerPtr(_playerPtr)
	, mEffectComponentPtr(nullptr)
	, mSecondAttackPtr(_secondAttackPtr)
{
	// �G�t�F�N�g�̋�`�����蔻��
	mBox = AABB(Vector3(0.0f, -40.0f, 50.0f), Vector3(100.0f, 40.0f, 50.0f));
	mBoxColliderPtr = new BoxCollider(this, _ObjectTag, GetOnCollisionFunc());
	mBoxColliderPtr->SetObjectBox(mBox);
	// �ŏ��͓����蔻����s��Ȃ��悤�ɂ���
	mBoxColliderPtr->SetCollisionState(CollisionState::eDisableCollision);

	// �G�t�F�N�g����
	mEffectComponentPtr = new EffectComponent(this, _Scale, u"Assets/Effect/SecondAttack.efk", true, true);
}

/// <summary>
/// �I�u�W�F�N�g�̍X�V����
/// </summary>
/// <param name="_deltaTime"> �Ō�̃t���[������������̂ɗv�������� </param>
void SecondAttackEffect::UpdateGameObject(float _deltaTime)
{
	mFaceInFlockCenterVec = Vector3::Zero;

	// �G�l�~�[�Ƀq�b�g��������
	if (mHitEnemyCount != 0)
	{
		// �q�b�g�����G�l�~�[�̌Q��̒��S�Ɍ����x�N�g��
		mFaceInFlockCenterVec = mFaceInEnemyVec / mHitEnemyCount;

		mFaceInEnemyVec = Vector3::Zero;
		mHitEnemyCount = 0;
	}

	// �O�ɂ��炷�x�N�g��
	Vector3 offsetVec = mPlayerPtr->GetForward() * MOffset;
	mPosition = mPlayerPtr->GetPosition() + offsetVec;

	SetPosition(mPosition);
	SetRotation(mPlayerPtr->GetRotation());

	// �����蔻��𖳌��ɂ���
	if (!mSecondAttackPtr->GetIsCollisionState())
	{
		mBoxColliderPtr->SetCollisionState(CollisionState::eDisableCollision);
		return;
	}

	// �����蔻���L���ɂ���
	if (mSecondAttackPtr->GetIsCollisionState())
	{
		// �Đ��ς݂���Ȃ�������G�t�F�N�g���Đ�����
		if (mEffectComponentPtr->IsPlayedEffect())
		{
			// �G�t�F�N�g���Đ�
			mEffectComponentPtr->PlayEffect();
		}

		mBoxColliderPtr->SetCollisionState(CollisionState::eEnableCollision);
	}
}

/// <summary>
/// �q�b�g�������̏���
/// </summary>
/// <param name="_HitObject"> �q�b�g�����Q�[���I�u�W�F�N�g </param>
void SecondAttackEffect::OnCollision(const GameObject& _HitObject)
{
	// �I�u�W�F�N�g�̃^�O
	mHitTag = _HitObject.GetTag();

	for (int i = 0; i < mHitTagListSize; i++)
	{
		// �U�����󂯂����̏���
		HitAttack(_HitObject, mHitTagList[i]);
	}
}

/// <summary>
/// �U���������������̏���
/// </summary>
/// <param name="_HitObject"> �q�b�g�����I�u�W�F�N�g </param>
/// <param name="_HitTag"> �q�b�g�����I�u�W�F�N�g�̃^�O </param>
void SecondAttackEffect::HitAttack(const GameObject& _HitObject, const Tag& _HitTag)
{
	// �q�b�g�����I�u�W�F�N�g�Ɍ����x�N�g���̎Z�o�Ɠ��������G�l�~�[�̃J�E���g���s��
	if (mHitTag == _HitTag)
	{
		// �q�b�g�����I�u�W�F�N�g�̍��W
		Vector3 hitObjectPosition = _HitObject.GetPosition();
		// �v���C���[�̍��W
		Vector3 playerPosition = mPlayerPtr->GetPosition();

		mFaceInEnemyVec += hitObjectPosition - playerPosition;
		++mHitEnemyCount;
	}
}