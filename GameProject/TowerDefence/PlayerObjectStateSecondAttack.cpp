#include "pch.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
PlayerObjectStateSecondAttack::PlayerObjectStateSecondAttack()
	: MBoxEnableTiming(15)
	, MBoxDisableTiming(25)
	, MDamageValueEnemyAttack(25)
	, MAttackSpeed(100.0f)
	, MPlayRate(1.8f)
	, MValidComboFrame(5)
	, mIsCollisionState(false)
	, mDamageValue(0)
	, mHitUntilCount(0)
	, mNumFrame(0)
	, mPosition(Vector3::Zero)
	, mForwardVec(Vector3::Zero)
{
}

/// <summary>
/// �X�V����
/// </summary>
/// <param name="_owner"> �v���C���[(�e)�̃|�C���^ </param>
/// <param name="_DeltaTime"> �Ō�̃t���[������������̂ɗv�������� </param>
/// <returns> �v���C���[�̏�� </returns>
PlayerState PlayerObjectStateSecondAttack::Update(PlayerObject* _owner, const float _DeltaTime)
{
	// �J�n���x
	float startSpeed = MAttackSpeed * _DeltaTime;
	// �I�����x
	float endSpeed = -MAttackSpeed * _DeltaTime;

	// �U�����ݍ��݈ړ��̂��߂̃A�j���[�V�����Đ����Ԃ̌o�ߊ������v�Z
	mElapseTime += _DeltaTime;
	// �o�ߊ��������ƂɈړ�����
	mPosition += Quintic::EaseIn(mElapseTime, startSpeed, endSpeed, mTotalAnimTime) * mForwardVec;

	_owner->SetPosition(mPosition);

	// �t���[���������炵�Ă���
	if (mNumFrame > 0)
	{
		--mNumFrame;
	}

	++mHitUntilCount;

	if (mHitUntilCount == MBoxEnableTiming)
	{
		// 2�i�K�ڂ̒ʏ�U���̓����蔻���L���ɂ���
		mIsCollisionState = true;
	}

	if (mHitUntilCount == MBoxDisableTiming)
	{
		// 2�i�K�ڂ̒ʏ�U���̓����蔻��𖳌��ɂ���
		mIsCollisionState = false;
	}

	if (mIsHit)
	{
		return PlayerState::ePlayerStateDamage;
	}

	// �A�j���[�V�������I��������A�C�h����Ԃ��A���̃R���{��
	if (!_owner->GetSkeletalMeshComponentPtr()->IsPlaying())
	{
		if (mIsNextCombo)
		{
			return PlayerState::ePlayerStateThirdAttack;
		}
		return PlayerState::ePlayerStateIdle;
	}

	return PlayerState::ePlayerStateSecondAttack;
}

/// <summary>
/// ���͏���
/// </summary>
/// <param name="_owner"> �v���C���[(�e)�̃|�C���^ </param>
/// <param name="_KeyState"> �L�[�{�[�h�A�}�E�X�A�R���g���[���[�̓��͏�� </param>
void PlayerObjectStateSecondAttack::Input(PlayerObject* _owner, const InputState& _KeyState)
{
	// �U���{�^�������ꂽ�玟�̃X�e�[�g�ֈڍs���鏀��
	if (mNumFrame <= MValidComboFrame && _KeyState.m_controller.GetButtonState(SDL_CONTROLLER_BUTTON_Y) == Released ||
		mNumFrame <= MValidComboFrame && _KeyState.m_keyboard.GetKeyState(SDL_SCANCODE_SPACE) == Released)
	{
		mIsNextCombo = true;
	}
}

/// <summary>
/// �v���C���[�̏�Ԃ��ύX���āA�ŏ���1�񂾂��Ăяo�����֐�
/// </summary>
/// <param name="_owner"> �v���C���[(�e)�̃|�C���^ </param>
/// <param name="_DeltaTime"> �Ō�̃t���[������������̂ɗv�������� </param>
void PlayerObjectStateSecondAttack::Enter(PlayerObject* _owner, const float _DeltaTime)
{
	// 2�i�K�ڂ̒ʏ�U����Ԃ̃A�j���[�V�����Đ�
	SkeletalMeshComponent* meshComp = _owner->GetSkeletalMeshComponentPtr();
	meshComp->PlayAnimation(_owner->GetAnimPtr(PlayerState::ePlayerStateSecondAttack), MPlayRate);
	mIsNextCombo = false;
	mIsHit = false;

	// �A�j���[�V�����Đ����Ԏ擾
	mTotalAnimTime = _owner->GetAnimPtr(PlayerState::ePlayerStateSecondAttack)->GetDuration();
	mNumFrame = _owner->GetAnimPtr(PlayerState::ePlayerStateDashAttack)->GetNumFrames();
	mElapseTime = 0.0f;
	mHitUntilCount = 0;

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
void PlayerObjectStateSecondAttack::OnCollision(PlayerObject* _owner, const GameObject& _HitObject)
{
	// �I�u�W�F�N�g�̃^�O
	Tag tag = _HitObject.GetTag();

	if (tag == Tag::eEnemyAttackDecision)
	{
		mDamageValue = MDamageValueEnemyAttack;
		mIsHit = true;
	}

	_owner->SetDamageValue(mDamageValue);
}