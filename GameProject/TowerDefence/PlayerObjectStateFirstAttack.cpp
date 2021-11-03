#include "pch.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
PlayerObjectStateFirstAttack::PlayerObjectStateFirstAttack()
	: MBoxEnableTiming(15)
	, MBoxDisableTiming(16)
	, MDamageValueEnemyAttack(25)
	, MAttackSpeed(50.0f)
	, MPlayRate(1.8f)
	, MLeftAxisThreshold(0.5f)
	, MValidComboFrame(10)
	, mIsCollisionState(false)
	, mIsRotation(false)
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
PlayerState PlayerObjectStateFirstAttack::Update(PlayerObject* _owner, const float _DeltaTime)
{
	if (mIsHit)
	{
		return PlayerState::ePlayerStateDamage;
	}

	// �A�j���[�V�������I��������A�C�h����Ԃ��A���̃R���{��
	if (!_owner->GetSkeletalMeshComponentPtr()->IsPlaying())
	{
		if (mIsNextCombo)
		{
			return PlayerState::ePlayerStateSecondAttack;
		}

		return PlayerState::ePlayerStateIdle;
	}

	if (mDirVec == Vector3::Zero)
	{
		return PlayerState::ePlayerStateFirstAttack;
	}

	// �J�n���x
	float startSpeed = MAttackSpeed * _DeltaTime;
	// �I�����x
	float endSpeed = -MAttackSpeed * _DeltaTime;

	// �U�����ݍ��݈ړ��̂��߂̃A�j���[�V�����Đ����Ԃ̌o�ߊ������v�Z
	mElapseTime += _DeltaTime;
	mDirVec.Normalize();
	// �o�ߊ��������ƂɈړ�����
	mPosition += Quintic::EaseIn(mElapseTime, startSpeed, endSpeed, mTotalAnimTime) * mDirVec;

	_owner->SetPosition(mPosition);
	_owner->RotateToNewForward(mDirVec);

	// �t���[���������炵�Ă���
	if (mNumFrame > 0)
	{
		--mNumFrame;
	}

	++mHitUntilCount;

	if (mHitUntilCount == MBoxEnableTiming)
	{
		// 1�i�K�ڂ̒ʏ�U���̓����蔻���L���ɂ���
		mIsCollisionState = true;
	}

	if (mHitUntilCount == MBoxDisableTiming)
	{
		// 1�i�K�ڂ̒ʏ�U���̓����蔻��𖳌��ɂ���
		mIsCollisionState = false;
	}

	return PlayerState::ePlayerStateFirstAttack;
}

/// <summary>
/// ���͏���
/// </summary>
/// <param name="_owner"> �v���C���[(�e)�̃|�C���^ </param>
/// <param name="_KeyState"> �L�[�{�[�h�A�}�E�X�A�R���g���[���[�̓��͏�� </param>
void PlayerObjectStateFirstAttack::Input(PlayerObject* _owner, const InputState& _KeyState)
{
	// �O���x�N�g��
	mForwardVec = _owner->GetForward();

	// �J�����O���x�N�g���ƉE�����x�N�g���Z�o
	mRightVec = Vector3::Cross(Vector3::UnitZ, mForwardVec);

	//�����L�[�����͂��ꂽ��
	mIsRotation = _KeyState.m_keyboard.GetKeyValue(SDL_SCANCODE_W) ||
		_KeyState.m_keyboard.GetKeyValue(SDL_SCANCODE_S) ||
		_KeyState.m_keyboard.GetKeyValue(SDL_SCANCODE_A) ||
		_KeyState.m_keyboard.GetKeyValue(SDL_SCANCODE_D) ||
		_KeyState.m_controller.GetButtonValue(SDL_CONTROLLER_BUTTON_DPAD_UP) ||
		_KeyState.m_controller.GetButtonValue(SDL_CONTROLLER_BUTTON_DPAD_DOWN) ||
		_KeyState.m_controller.GetButtonValue(SDL_CONTROLLER_BUTTON_DPAD_LEFT) ||
		_KeyState.m_controller.GetButtonValue(SDL_CONTROLLER_BUTTON_DPAD_RIGHT);

	// �R���g���[���[�̏\����������̓L�[�{�[�h�AW�����͂��ꂽ��z�𑫂�
	if (_KeyState.m_controller.GetButtonState(SDL_CONTROLLER_BUTTON_DPAD_UP) == Held ||
		_KeyState.m_keyboard.GetKeyState(SDL_SCANCODE_W) == Held)
	{
		mDirVec = mForwardVec - mRightVec * 0.1f;
	}
	// �R���g���[���[�̏\�����������́A�L�[�{�[�hS�����͂��ꂽ��-z�𑫂�
	else if (_KeyState.m_controller.GetButtonState(SDL_CONTROLLER_BUTTON_DPAD_DOWN) == Held ||
		_KeyState.m_keyboard.GetKeyState(SDL_SCANCODE_S) == Held)
	{
		mDirVec = mForwardVec + mRightVec * 0.1f;
	}

	//�R���g���[���[�̏\�����������́A�L�[�{�[�hA�����͂��ꂽ��-x�𑫂�
	if (_KeyState.m_controller.GetButtonState(SDL_CONTROLLER_BUTTON_DPAD_LEFT) == Held ||
		_KeyState.m_keyboard.GetKeyState(SDL_SCANCODE_A) == Held)
	{
		mDirVec = mForwardVec - mRightVec * 0.1f;
	}
	// �R���g���[���[�̏\���E�������́A�L�[�{�[�hD�����͂��ꂽ��x�𑫂�
	else if (_KeyState.m_controller.GetButtonState(SDL_CONTROLLER_BUTTON_DPAD_RIGHT) == Held ||
		_KeyState.m_keyboard.GetKeyState(SDL_SCANCODE_D) == Held)
	{
		mDirVec = mForwardVec + mRightVec * 0.1f;
	}

	// ���X�e�B�b�N�̓��͒l���擾
	mleftAxis = _KeyState.m_controller.GetLAxisVec();

	if (mleftAxis.LengthSq() >= MLeftAxisThreshold)
	{
		mIsRotation = true;
	}

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
void PlayerObjectStateFirstAttack::Enter(PlayerObject* _owner, const float _DeltaTime)
{
	// 1�i�K�ڂ̒ʏ�U����Ԃ̃A�j���[�V�����Đ�
	SkeletalMeshComponent* meshComp = _owner->GetSkeletalMeshComponentPtr();
	meshComp->PlayAnimation(_owner->GetAnimPtr(PlayerState::ePlayerStateFirstAttack), MPlayRate);
	mIsNextCombo = false;
	mIsHit = false;

	// �A�j���[�V�����Đ����Ԏ擾
	mTotalAnimTime = _owner->GetAnimPtr(PlayerState::ePlayerStateFirstAttack)->GetDuration();
	mNumFrame = _owner->GetAnimPtr(PlayerState::ePlayerStateDashAttack)->GetNumFrames();
	mElapseTime = 0.0f;
	mHitUntilCount = 0;

	mDirVec = Vector3::Zero;
	// ���W
	mPosition = _owner->GetPosition();
}

/// <summary>
/// �q�b�g�������̏���
/// </summary>
/// <param name="_owner"> �v���C���[(�e)�̃|�C���^ </param>
/// <param name="_HitObject"> �q�b�g�����Q�[���I�u�W�F�N�g </param>
void PlayerObjectStateFirstAttack::OnCollision(PlayerObject* _owner, const GameObject& _HitObject)
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