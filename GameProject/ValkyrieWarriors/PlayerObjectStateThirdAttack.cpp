#include "pch.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
PlayerObjectStateThirdAttack::PlayerObjectStateThirdAttack()
	: mHitTagList{ Tag::eEnemyAttackDecision, Tag::eFrontCoreMagicEffect, Tag::eAreaMagicEffect, Tag::eOverheadMagicEffect }
	, mDamageValueList{ 5, 15, 30, 20 }
	, faceAngleList{ 0.0f, 45.0f, 90.0f, 135.0f, 180.0f, 225.0f, 270.0f, 315.0f }
	, MHitStopEndTiming(10)
	, MHalfRotation(180)
	, MAllRotation(360)
	, MAttackSpeed(150.0f)
	, MPlayRate(1.8f)
	, MBoxEnableTiming(0.5f)
	, MLeftAxisThreshold(0.5f)
	, MValueShortenVector(0.05f)
	, mIsCollisionState(false)
	, mIsOneCollisionState(false)
	, mIsHitStop(false)
	, mIsDamage(false)
	, mDamageValue(0)
	, mHitTagListSize(sizeof(mHitTagList) / sizeof(int))
	, mHitUntilCount(0)
	, mHitStopCount(0)
	, mTwoVectorAngle(0.0f)
	, mBoxDisableTiming(0.0f)
	, mLeftAxis(Vector2::Zero)
	, mPosition(Vector3::Zero)
	, mForwardVec(Vector3::Zero)
	, mRightVec(Vector3::Zero)
	, mHitTag(Tag::eOther)
	, mPlayerPtr(nullptr)
	, mMainCameraPtr(nullptr)
	, skeletalMeshCompPtr(nullptr)
	, mThirdAttackEffectPtr(nullptr)
{
}

/// <summary>
/// �X�V����
/// </summary>
/// <param name="_owner"> �v���C���[(�e)�̃|�C���^ </param>
/// <param name="_DeltaTime"> �Ō�̃t���[������������̂ɗv�������� </param>
/// <returns> �v���C���[�̏�� </returns>
PlayerState PlayerObjectStateThirdAttack::Update(PlayerObject* _owner, const float _DeltaTime)
{
	if (mIsDamage)
	{
		return PlayerState::ePlayerStateDamage;
	}

	// �A�j���[�V�������I��������cStopTime�d����AIDLE��Ԃ�
	if (!_owner->GetSkeletalMeshComponentPtr()->IsPlaying())
	{
		return PlayerState::ePlayerStateIdle;
	}

	// �U�����ɕ��킪����������q�b�g�X�g�b�v���s��
 	if (mThirdAttackEffectPtr->IsHitCheck())
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
			return PlayerState::ePlayerStateThirdAttack;
		}

		mIsHitStop = false;
		mHitStopCount = 0;
	}

	// �����̏�񂪂Ȃ�������O���x�N�g���ɂ���
	if (mDirVec == Vector3::Zero)
	{
		mDirVec = mForwardVec;
	}

	mDirVec.Normalize();

	// �J�n���x
	float startSpeed = MAttackSpeed * _DeltaTime;
	// �I�����x
	float endSpeed = -MAttackSpeed * _DeltaTime;

	// �U�����ݍ��݈ړ��̂��߂̃A�j���[�V�����Đ����Ԃ̌o�ߊ������v�Z
	mElapseTime += _DeltaTime;
	// �o�ߊ��������ƂɈړ�����
	mPosition += Quintic::EaseIn(mElapseTime, startSpeed, endSpeed, mTotalAnimTime) * mDirVec;

	_owner->SetPosition(mPosition);
	_owner->RotateToNewForward(mDirVec);

	if (mIsOneCollisionState)
	{
		return PlayerState::ePlayerStateThirdAttack;
	}

	if (mElapseTime >= MBoxEnableTiming)
	{
		// 3�i�K�ڂ̒ʏ�U���̓����蔻���L���ɂ���
		mIsCollisionState = true;
	}

	if (!mIsCollisionState)
	{
		return PlayerState::ePlayerStateThirdAttack;
	}

	if (mElapseTime >= mBoxDisableTiming)
	{
		// 3�i�K�ڂ̒ʏ�U���̓����蔻��𖳌��ɂ���
		mIsCollisionState = false;
		mIsOneCollisionState = true;
	}

	return PlayerState::ePlayerStateThirdAttack;
}


/// <summary>
/// ���͏���
/// </summary>
/// <param name="_owner"> �v���C���[(�e)�̃|�C���^ </param>
/// <param name="_KeyState"> �L�[�{�[�h�A�}�E�X�A�R���g���[���[�̓��͏�� </param>
void PlayerObjectStateThirdAttack::Input(PlayerObject* _owner, const InputState& _KeyState)
{
	if (mMainCameraPtr == nullptr)
	{
		return;
	}

	// �J�����̍��W
	Vector3 cameraPos = mMainCameraPtr->GetPosition();

	// �J�����̑O���x�N�g��
	Vector3 cameraForwardVec = cameraPos - mPosition;
	cameraForwardVec.z = 0.0f;
	cameraForwardVec = Vector3::Normalize(cameraForwardVec);

	// �O���x�N�g��
	mForwardVec = _owner->GetForward();
	mForwardVec = Vector3::Normalize(mForwardVec);
	// �E���x�N�g���Z�o
	mRightVec = Vector3::Cross(Vector3::UnitZ, mForwardVec);

	// �J�����ƃv���C���[�̑O���x�N�g���̊O��
	Vector3 outerProduct = Vector3::Cross(cameraForwardVec, mForwardVec);

	// 180�x�ȉ��̎�
	if (outerProduct.z <= 0.0f)
	{
		// �J�����ƃv���C���[�̑O���x�N�g���̓���
		float innerProduct = Vector3::Dot(cameraForwardVec, mForwardVec);
		// �p�x���Z�o
		mTwoVectorAngle = Math::Acos(innerProduct) * MHalfRotation / Math::Pi;
		mTwoVectorAngle = MHalfRotation - mTwoVectorAngle;
	}
	// 180�x���傫����
	else
	{
		// �J�����̌���x�N�g��
		Vector3 cameraBackwardVec = cameraForwardVec *= -1.0f;
		// �J�����̌���x�N�g���ƃv���C���[�̑O���x�N�g���̓���
		float innerProduct = Vector3::Dot(cameraBackwardVec, mForwardVec);
		// �p�x���Z�o
		mTwoVectorAngle = Math::Acos(innerProduct) * MHalfRotation / Math::Pi;
		mTwoVectorAngle = MAllRotation - mTwoVectorAngle;
	}

	// �R���g���[���[�̏\����������̓L�[�{�[�hW�����͂��ꂽ���]����
	if (VerticalKeyInputOperation(_KeyState, SDL_SCANCODE_W, SDL_CONTROLLER_BUTTON_DPAD_UP,
		faceAngleList[static_cast<int>(FaceAngleType::eDownRight)], faceAngleList[static_cast<int>(FaceAngleType::eUpLeft)],
		faceAngleList[static_cast<int>(FaceAngleType::eUpRight)], faceAngleList[static_cast<int>(FaceAngleType::eDownLeft)],
		MValueShortenVector))
	{
		return;
	}

	// �R���g���[���[�̏\�����������̓L�[�{�[�hS�����͂��ꂽ���]����
	if (VerticalKeyInputOperation(_KeyState, SDL_SCANCODE_S, SDL_CONTROLLER_BUTTON_DPAD_DOWN,
		faceAngleList[static_cast<int>(FaceAngleType::eUpRight)], faceAngleList[static_cast<int>(FaceAngleType::eDownLeft)],
		faceAngleList[static_cast<int>(FaceAngleType::eDownRight)], faceAngleList[static_cast<int>(FaceAngleType::eUpLeft)],
		-MValueShortenVector))
	{
		return;
	}

	// �R���g���[���[�̏\�����������̓L�[�{�[�hA�����͂��ꂽ���]����
	if (LateralKeyInputOperation(_KeyState, SDL_SCANCODE_A, SDL_CONTROLLER_BUTTON_DPAD_LEFT,
		faceAngleList[static_cast<int>(FaceAngleType::eRight)], faceAngleList[static_cast<int>(FaceAngleType::eLeft)],
		MValueShortenVector))
	{
		return;
	}

	// �R���g���[���[�̏\�����������̓L�[�{�[�hD�����͂��ꂽ���]����
	if (LateralKeyInputOperation(_KeyState, SDL_SCANCODE_D, SDL_CONTROLLER_BUTTON_DPAD_RIGHT,
		faceAngleList[static_cast<int>(FaceAngleType::eRight)], faceAngleList[static_cast<int>(FaceAngleType::eLeft)],
		-MValueShortenVector))
	{
		return;
	}

	// ���X�e�B�b�N�̓��͒l���擾
	mLeftAxis = _KeyState.m_controller.GetLAxisVec();

	if (mLeftAxis.y <= MLeftAxisThreshold && mLeftAxis.y >= -MLeftAxisThreshold &&
		mLeftAxis.x <= MLeftAxisThreshold && mLeftAxis.x >= -MLeftAxisThreshold ||
		mLeftAxis.y == 0.0f && mLeftAxis.x == 0.0f)
	{
		return;
	}

	// ���X�e�B�b�N����ɓ|������O�Ɍ������ĉ�]����
	if (mLeftAxis.y < 0.0f)
	{
		// ���X�e�B�b�N�����ɓ|�����獶�O�Ɍ������ĉ�]����
		if (LeftStickDefeatLeftInputOperation(faceAngleList[static_cast<int>(FaceAngleType::eDownRight)],
			faceAngleList[static_cast<int>(FaceAngleType::eUpLeft)], MValueShortenVector))
		{
			return;
		}

		// ���X�e�B�b�N���E�ɓ|������E�O�Ɍ������ĉ�]����
		if (LeftStickDefeatRightInputOperation(faceAngleList[static_cast<int>(FaceAngleType::eUpRight)],
			faceAngleList[static_cast<int>(FaceAngleType::eDownLeft)], -MValueShortenVector))
		{
			return;
		}

		// �O�Ɍ������ĉ�]����
		RotateInRangeAngle(faceAngleList[static_cast<int>(FaceAngleType::eUp)],
			faceAngleList[static_cast<int>(FaceAngleType::eDown)], -MValueShortenVector);

		return;
	}

	// ���X�e�B�b�N�����ɓ|��������Ɍ������ĉ�]����
	if (mLeftAxis.y > 0.0f)
	{
		// ���X�e�B�b�N�����ɓ|�����獶���Ɍ������ĉ�]����
		if (LeftStickDefeatLeftInputOperation(faceAngleList[static_cast<int>(FaceAngleType::eUpRight)],
			faceAngleList[static_cast<int>(FaceAngleType::eDownLeft)], MValueShortenVector))
		{
			return;
		}

		// ���X�e�B�b�N���E�ɓ|������E���Ɍ������ĉ�]����
		if (LeftStickDefeatRightInputOperation(faceAngleList[static_cast<int>(FaceAngleType::eDownRight)],
			faceAngleList[static_cast<int>(FaceAngleType::eUpLeft)], -MValueShortenVector))
		{
			return;
		}

		// ���Ɍ������ĉ�]����
		RotateInRangeAngle(faceAngleList[static_cast<int>(FaceAngleType::eUp)],
			faceAngleList[static_cast<int>(FaceAngleType::eDown)], MValueShortenVector);

		return;
	}

	// ���X�e�B�b�N�����ɓ|�����獶�Ɍ������ĉ�]����
	if (LeftStickDefeatLeftInputOperation(faceAngleList[static_cast<int>(FaceAngleType::eRight)],
		faceAngleList[static_cast<int>(FaceAngleType::eLeft)], MValueShortenVector))
	{
		return;
	}

	// ���X�e�B�b�N���E�ɓ|������E�Ɍ������ĉ�]����
	if (LeftStickDefeatRightInputOperation(faceAngleList[static_cast<int>(FaceAngleType::eRight)],
		faceAngleList[static_cast<int>(FaceAngleType::eLeft)], -MValueShortenVector))
	{
		return;
	}
}


/// <summary>
/// �v���C���[�̏�Ԃ��ύX���āA�ŏ���1�񂾂��Ăяo�����֐�
/// </summary>
/// <param name="_owner"> �v���C���[(�e)�̃|�C���^ </param>
/// <param name="_DeltaTime"> �Ō�̃t���[������������̂ɗv�������� </param>
void PlayerObjectStateThirdAttack::Enter(PlayerObject* _owner, const float _DeltaTime)
{
	// 3�i�K�ڂ̒ʏ�U����Ԃ̃A�j���[�V�����Đ�
	skeletalMeshCompPtr = _owner->GetSkeletalMeshComponentPtr();
	skeletalMeshCompPtr->PlayAnimation(_owner->GetAnimPtr(PlayerState::ePlayerStateThirdAttack), MPlayRate);
	mIsDamage = false;

	// �A�j���[�V�����Đ����Ԏ擾
	mTotalAnimTime = _owner->GetAnimPtr(PlayerState::ePlayerStateThirdAttack)->GetDuration() - 0.6f;
	mElapseTime = 0.0f;
	mBoxDisableTiming = MBoxEnableTiming + _DeltaTime;
	mIsOneCollisionState = false;

	// �q�b�g�X�g�b�v�֌W������
	mIsHitStop = false;
	mHitStopCount = 0;

	mDirVec = Vector3::Zero;
	// ���W
	mPosition = _owner->GetPosition();
}

/// <summary>
/// �q�b�g�������̏���
/// </summary>
/// <param name="_owner"> �v���C���[(�e)�̃|�C���^ </param>
/// <param name="_HitObject"> �q�b�g�����Q�[���I�u�W�F�N�g </param>
void PlayerObjectStateThirdAttack::OnCollision(PlayerObject* _owner, const GameObject& _HitObject)
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
bool PlayerObjectStateThirdAttack::ReceivedAttack(const Tag& _hitTag, const int& _DamageValuePlayerAttack)
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

/// <summary>
/// �c�L�[���͑���
/// </summary>
/// <param name="_KeyState"> �L�[�{�[�h�A�}�E�X�A�R���g���[���[�̓��͏�� </param>
/// <param name="_KeyScancode"> ���L�[���������� </param>
/// <param name="_ButtonScancode"> ���{�^������������ </param>
/// <returns> true : ����������, false : ���������Ȃ����� </returns>
bool PlayerObjectStateThirdAttack::VerticalKeyInputOperation(const InputState& _KeyState, const SDL_Scancode& _KeyScancode, const SDL_GameControllerButton& _ButtonScancode,
	const float& _AngleBorderMinAKey, const float& _AngleBorderMaxAKey, const float& _AngleBorderMinDKey, const float& _AngleBorderMaxDKey, const float& _ValueShortenVector)
{
	if (_KeyState.m_controller.GetButtonState(_ButtonScancode) == Held ||
		_KeyState.m_keyboard.GetKeyState(_KeyScancode) == Held)
	{
		// �R���g���[���[�̏\�����������̓L�[�{�[�hA�����͂��ꂽ���]����
		if (LateralKeyInputOperation(_KeyState, SDL_SCANCODE_A,
			SDL_CONTROLLER_BUTTON_DPAD_LEFT, _AngleBorderMinAKey, _AngleBorderMaxAKey, MValueShortenVector))
		{
			return true;
		}

		// �R���g���[���[�̏\�����������̓L�[�{�[�hD�����͂��ꂽ���]����
		if (LateralKeyInputOperation(_KeyState, SDL_SCANCODE_D,
			SDL_CONTROLLER_BUTTON_DPAD_RIGHT, _AngleBorderMinDKey, _AngleBorderMaxDKey, -MValueShortenVector))
		{
			return true;
		}

		RotateInRangeAngle(faceAngleList[static_cast<int>(FaceAngleType::eUp)],
			faceAngleList[static_cast<int>(FaceAngleType::eDown)], -_ValueShortenVector);

		return true;
	}

	return false;
}

/// <summary>
/// ���L�[���͑���
/// </summary>
/// <param name="_KeyState"> �L�[�{�[�h�A�}�E�X�A�R���g���[���[�̓��͏�� </param>
/// <param name="_KeyScancode"> ���L�[���������� </param>
/// <param name="_ButtonScancode"> ���{�^������������ </param>
/// <param name="_AngleBorderMin"> ���ڂ̊p�x�̍ŏ��l </param>
/// <param name="_AngleBorderMax"> ���ڂ̊p�x�̍ő�l </param>
/// <returns> true : ����������, false : ���������Ȃ����� </returns>
bool PlayerObjectStateThirdAttack::LateralKeyInputOperation(const InputState& _KeyState, const SDL_Scancode& _KeyScancode,
	const SDL_GameControllerButton& _ButtonScancode, const float& _AngleBorderMin, const float& _AngleBorderMax, const float& _ValueShortenVector)
{
	//�R���g���[���[�̏\�����������́A�L�[�{�[�hA�����͂��ꂽ���]����
	if (_KeyState.m_controller.GetButtonState(_ButtonScancode) == Held ||
		_KeyState.m_keyboard.GetKeyState(_KeyScancode) == Held)
	{
		RotateInRangeAngle(_AngleBorderMin, _AngleBorderMax, _ValueShortenVector);

		return true;
	}

	return false;
}

/// <summary>
/// ���X�e�B�b�N�����ɓ|�����Ƃ��̑���
/// </summary>
/// <param name="_AngleBorderMin"> ���ڂ̊p�x�̍ŏ��l </param>
/// <param name="_AngleBorderMax"> ���ڂ̊p�x�̍ő�l </param>
/// <param name="_ValueShortenVector"></param>
/// <returns> true : �X�e�B�b�N��|����, false : �X�e�B�b�N��|���Ȃ����� </returns>
bool PlayerObjectStateThirdAttack::LeftStickDefeatLeftInputOperation(const float& _AngleBorderMin, const float& _AngleBorderMax, const float& _ValueShortenVector)
{
	if (mLeftAxis.x < 0.0f)
	{
		RotateInRangeAngle(_AngleBorderMin, _AngleBorderMax, _ValueShortenVector);

		return true;
	}

	return false;
}

/// <summary>
/// ���X�e�B�b�N���E�ɓ|�����Ƃ��̑���
/// </summary>
/// <param name="_AngleBorderMin"> ���ڂ̊p�x�̍ŏ��l </param>
/// <param name="_AngleBorderMax"> ���ڂ̊p�x�̍ő�l </param>
/// <param name="_ValueShortenVector"> �x�N�g����Z������l </param>
/// <returns> true : �X�e�B�b�N��|����, false : �X�e�B�b�N��|���Ȃ����� </returns>
bool PlayerObjectStateThirdAttack::LeftStickDefeatRightInputOperation(const float& _AngleBorderMin, const float& _AngleBorderMax, const float& _ValueShortenVector)
{
	if (mLeftAxis.x > 0.0f)
	{
		RotateInRangeAngle(_AngleBorderMin, _AngleBorderMax, _ValueShortenVector);

		return true;
	}

	return false;
}

/// <summary>
/// �͈͊p�x�ŉ�]������
/// </summary>
/// <param name="_AngleBorderMin"> ���ڂ̊p�x�̍ŏ��l </param>
/// <param name="_AngleBorderMax"> ���ڂ̊p�x�̍ő�l </param>
/// <param name="_ValueShortenVector"> �x�N�g����Z������l </param>
void PlayerObjectStateThirdAttack::RotateInRangeAngle(const float& _AngleBorderMin, const float& _AngleBorderMax, const float& _ValueShortenVector)
{
	if (mTwoVectorAngle >= _AngleBorderMin && mTwoVectorAngle < _AngleBorderMax)
	{
		mDirVec = mForwardVec + mRightVec * _ValueShortenVector;
	}
	else
	{
		mDirVec = mForwardVec + mRightVec * -_ValueShortenVector;
	}
}