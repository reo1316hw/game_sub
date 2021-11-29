#include "pch.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>	
/// <param name="_playerPtr"> �v���C���[�̃|�C���^ </param>
/// <param name="_Scale"> �傫�� </param>
/// <param name="_ObjectTag"> �I�u�W�F�N�g�̃^�O </param>
/// <param name="_thirdAttackPtr"> 3�i�K�ڂ̒ʏ�U����Ԃ̃N���X�̃|�C���^ </param>
ThirdAttackEffect::ThirdAttackEffect(PlayerObject* _playerPtr, const Vector3& _Scale, const Tag& _ObjectTag, PlayerObjectStateThirdAttack* _thirdAttackPtr)
	: GameObject(_ObjectTag)
	, MOffset(10.0f)
	, mIsHit(false)
	, mDisableIsHit(false)
	, mIsPlayEffect(false)
	, mPlayerPtr(_playerPtr)
	, mEffectComponentPtr(nullptr)
	, mThirdAttackPtr(_thirdAttackPtr)
{
	// �G�t�F�N�g�̋�`�����蔻��
	mBox = AABB(Vector3(0.0f, -80.0f, 50.0f), Vector3(130.0f, 80.0f, 50.0f));
	mBoxColliderPtr = new BoxCollider(this, _ObjectTag, GetOnCollisionFunc());
	mBoxColliderPtr->SetObjectBox(mBox);
	// �ŏ��͓����蔻����s��Ȃ��悤�ɂ���
	mBoxColliderPtr->SetCollisionState(CollisionState::eDisableCollision);

	// �G�t�F�N�g����
	mEffectComponentPtr = new EffectComponent(this, _Scale, u"Assets/Effect/ThirdAttack.efk", true, true);
}

/// <summary>
/// �I�u�W�F�N�g�̍X�V����
/// </summary>
/// <param name="_deltaTime"> �Ō�̃t���[������������̂ɗv�������� </param>
void ThirdAttackEffect::UpdateGameObject(float _deltaTime)
{
	// �O�̃X�e�[�g
	PlayerState nowState = mPlayerPtr->GetNowState();

	if (nowState != PlayerState::ePlayerStateThirdAttack)
	{
		mBoxColliderPtr->SetCollisionState(CollisionState::eDisableCollision);
		mEffectComponentPtr->StopEffect();
		mIsPlayEffect = false;
		return;
	}

	// �O�ɂ��炷�x�N�g��
	Vector3 offsetVec = mPlayerPtr->GetForward() * MOffset;
	mPosition = mPlayerPtr->GetPosition() + offsetVec;

	SetPosition(mPosition);
	SetRotation(mPlayerPtr->GetRotation());

	// �����蔻��𖳌��ɂ���
	if (!mThirdAttackPtr->GetIsCollisionState())
	{
		mBoxColliderPtr->SetCollisionState(CollisionState::eDisableCollision);
		// �q�b�g�X�g�b�v���ł���悤�ɂ���
		mDisableIsHit = false;
		return;
	}

	// �����蔻���L���ɂ���
	if (mThirdAttackPtr->GetIsCollisionState())
	{
		if (!mIsPlayEffect)
		{
			// �G�t�F�N�g���Đ�
			mEffectComponentPtr->PlayEffect();
		}

		mIsPlayEffect = true;

		mBoxColliderPtr->SetCollisionState(CollisionState::eEnableCollision);
	}

	// �q�b�g�X�g�b�v���ɃI�u�W�F�N�g�Ə�ɓ������Ă��܂��̂ŁA�q�b�g�t���O����莞�Ԗ����ɂ���
	if (mDisableIsHit)
	{
		mIsHit = false;
	}
}

/// <summary>
/// �q�b�g�������̏���
/// </summary>
/// <param name="_HitObject"> �q�b�g�����Q�[���I�u�W�F�N�g </param>
void ThirdAttackEffect::OnCollision(const GameObject& _HitObject)
{
	// �I�u�W�F�N�g�̃^�O
	Tag tag = _HitObject.GetTag();

	if (tag == Tag::eEnemy && !mDisableIsHit && mPlayerPtr->GetNowState() == PlayerState::ePlayerStateThirdAttack ||
		tag == Tag::eBoss && !mDisableIsHit && mPlayerPtr->GetNowState() == PlayerState::ePlayerStateThirdAttack)
	{
		mIsHit = true;
		mDisableIsHit = true;
	}
}