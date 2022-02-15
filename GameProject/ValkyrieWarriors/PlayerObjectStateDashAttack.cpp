#include "pch.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
PlayerObjectStateDashAttack::PlayerObjectStateDashAttack()
	: mHitTagList{ Tag::eEnemyAttackDecision, Tag::eFrontCoreMagicEffect, Tag::eAreaMagicEffect, Tag::eOverheadMagicEffect }
	, mDamageValueList{ 5, 15, 30, 20 }
	, MHitStopEndTiming(5)
	, MValidComboFrame(0.4f)
	, MBoxEnableTiming(0.15f)
	, MPlayRate(1.5f)
	, MAttackSpeed(300.0f)
	, mIsCollisionState(false)
	, mIsHitStop(false)
	, mIsDamage(false)
	, mDamageValue(0)
	, mHitTagListSize(sizeof(mHitTagList) / sizeof(int))
	, mHitStopCount(0)
	, mBoxDisableTiming(0.0f)
	, mPosition(Vector3::Zero)
	, mForwardVec(Vector3::Zero)
	, mHitTag(Tag::eOther)
	, mPlayerPtr(nullptr)
	, skeletalMeshCompPtr(nullptr)
	, mDashAttackEffectPtr(nullptr)
{
}

/// <summary>
/// �X�V����
/// </summary>
/// <param name="_owner"> �v���C���[(�e)�̃|�C���^ </param>
/// <param name="_DeltaTime"> �Ō�̃t���[������������̂ɗv�������� </param>
/// <returns> �v���C���[�̏�� </returns>
PlayerState PlayerObjectStateDashAttack::Update(PlayerObject* _owner, const float _DeltaTime)
{
	if (mIsDamage)
	{
		return PlayerState::ePlayerStateDamage;
	}

	// ���̃R���{��
	if (mIsNextCombo)
	{
		return PlayerState::ePlayerStateFirstAttack;
	}

	// �A�j���[�V�������I��������A�C�h����Ԃ��A���̃R���{��
	if (!_owner->GetSkeletalMeshComponentPtr()->IsPlaying())
	{
		return PlayerState::ePlayerStateIdle;
	}

	// �U�����ɕ��킪����������q�b�g�X�g�b�v���s��
	if (mDashAttackEffectPtr->IsHitCheck())
	{
		mIsHitStop = true;
		skeletalMeshCompPtr->SetIsHitStop(mIsHitStop);
	}

	// �q�b�g�X�g�b�v���Ɉړ������𖳌���
	if (mIsHitStop)
	{
		++mHitStopCount;

		if (mHitStopCount <= MHitStopEndTiming)
		{
			return PlayerState::ePlayerStateDashAttack;
		}

		mIsHitStop = false;
		mHitStopCount = 0;
	}

	// �J�n���x
	float startSpeed = MAttackSpeed * _DeltaTime;
	// �I�����x
	float endSpeed = -MAttackSpeed * _DeltaTime;

	// �U�����ݍ��݈ړ��̂��߂̃A�j���[�V�����Đ����Ԃ̌o�ߊ������v�Z
	mElapseTime += _DeltaTime;
	// �o�ߊ��������ƂɈړ�����
	mPosition += Quintic::EaseIn(mElapseTime, startSpeed, endSpeed, mTotalAnimTime) * mForwardVec;

	_owner->SetPosition(mPosition);

	if (mIsOneCollisionState)
	{
		return PlayerState::ePlayerStateDashAttack;
	}

	if (mElapseTime >= MBoxEnableTiming)
	{
		// �_�b�V���U���̓����蔻���L���ɂ���
		mIsCollisionState = true;
	}

	if (!mIsCollisionState)
	{
		return PlayerState::ePlayerStateDashAttack;
	}

	if (mElapseTime >= mBoxDisableTiming)
	{
		// �_�b�V���U���̓����蔻��𖳌��ɂ���
		mIsCollisionState = false;
		mIsOneCollisionState = true;
	}

	return PlayerState::ePlayerStateDashAttack;
}

/// <summary>
/// ���͏���
/// </summary>
/// <param name="_owner"> �v���C���[(�e)�̃|�C���^ </param>
/// <param name="_KeyState"> �L�[�{�[�h�A�}�E�X�A�R���g���[���[�̓��͏�� </param>
void PlayerObjectStateDashAttack::Input(PlayerObject* _owner, const InputState& _KeyState)
{
	// �U���{�^�������ꂽ�玟�̃X�e�[�g�ֈڍs���鏀��
	if (mElapseTime >= MValidComboFrame && _KeyState.m_controller.GetButtonState(SDL_CONTROLLER_BUTTON_X) == Released ||
		mElapseTime >= MValidComboFrame && _KeyState.m_keyboard.GetKeyState(SDL_SCANCODE_SPACE) == Released)
	{
		mIsNextCombo = true;
	}
}

/// <summary>
/// �v���C���[�̏�Ԃ��ύX���āA�ŏ���1�񂾂��Ăяo�����֐�
/// </summary>
/// <param name="_owner"> �v���C���[(�e)�̃|�C���^ </param>
/// <param name="_DeltaTime"> �Ō�̃t���[������������̂ɗv�������� </param>
void PlayerObjectStateDashAttack::Enter(PlayerObject* _owner, const float _DeltaTime)
{
	// �_�b�V���U����Ԃ̃A�j���[�V�����Đ�
	skeletalMeshCompPtr = _owner->GetSkeletalMeshComponentPtr();
	skeletalMeshCompPtr->PlayAnimation(_owner->GetAnimPtr(PlayerState::ePlayerStateDashAttack), MPlayRate);
	mIsNextCombo = false;
	mIsDamage = false;
	mIsOneCollisionState = false;

	// �A�j���[�V�����Đ����Ԏ擾
	mTotalAnimTime = _owner->GetAnimPtr(PlayerState::ePlayerStateDashAttack)->GetDuration() - 0.4f;
	mElapseTime = 0.0f;
	mBoxDisableTiming = MBoxEnableTiming + _DeltaTime;

	// �q�b�g�X�g�b�v�֌W������
	mIsHitStop = false;
	mHitStopCount = 0;

	// ���W
	mPosition = _owner->GetPosition();
	// �O���x�N�g��
	mForwardVec = _owner->GetForward();
}

/// <summary>
/// �q�b�g�������̏���
/// </summary>
/// <param name="_owner"> �v���C���[(�e)�̃|�C���^ </param>
/// <param name="_HitObject"> �q�b�g�����Q�[���I�u�W�F�N�g </param>
void PlayerObjectStateDashAttack::OnCollision(PlayerObject* _owner, const GameObject& _HitObject)
{
	mPlayerPtr = _owner;

	// ���W
	mPosition = mPlayerPtr->GetPosition();

	// �I�u�W�F�N�g�̃^�O
	mHitTag = _HitObject.GetTag();

	for (int i = 0; i < mHitTagListSize; i++)
	{
		// �U�����󂯂����̏���
		if (ReceivedAttack(mHitTagList[i], mDamageValueList[i]))
		{
			return;
		}
	}
}

/// <summary>
/// �U�����󂯂����̏���
/// </summary>
/// <param name="_HitTag"> �q�b�g�����I�u�W�F�N�g�̃^�O </param>
/// <param name="_DamageValuePlayerAttack"> �_���[�W�� </param>
/// <returns> �q�b�g������ </returns>
bool PlayerObjectStateDashAttack::ReceivedAttack(const Tag& _hitTag, const int& _DamageValuePlayerAttack)
{
	if (mHitTag == _hitTag)
	{
		mDamageValue = _DamageValuePlayerAttack;
		mIsDamage = true;

		mPlayerPtr->SetDamageValue(mDamageValue);
		return true;
	}

	return false;
}