#include "pch.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
PlayerObjectStateFirstAttack::PlayerObjectStateFirstAttack()
	: faceAngleList{ 0.0f, 45.0f, 90.0f, 135.0f, 180.0f, 225.0f, 270.0f, 315.0f }
	, MDamageValueEnemyAttack(25)
	, MHalfRotation(180)
	, MAllRotation(360)
	, MValidComboFrame(0.4f)
	, MBoxEnableTiming(0.25f)
	, MAttackSpeed(50.0f)
	, MPlayRate(1.8f)
	, MLeftAxisThreshold(0.5f)
	, MValueShortenVector(0.05f)
	, mIsCollisionState(false)
	, mIsOneCollisionState(false)
	, mDamageValue(0)
	, mTwoVectorAngle(0.0f)
	, mBoxDisableTiming(0.0f)
	, mLeftAxis(Vector2::Zero)
	, mPosition(Vector3::Zero)
	, mForwardVec(Vector3::Zero)
	, mRightVec(Vector3::Zero)
	, mMainCameraPtr(nullptr)
	, mFirstAttackEffectPtr(nullptr)
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

	// ���̃R���{��
	if (mIsNextCombo)
	{
		return PlayerState::ePlayerStateSecondAttack;
	}

	// �A�j���[�V�������I��������A�C�h����Ԃ��A���̃R���{��
	if (!_owner->GetSkeletalMeshComponentPtr()->IsPlaying())
	{
		return PlayerState::ePlayerStateIdle;
	}

	// �����̏�񂪂Ȃ�������O���x�N�g���ɂ���
	if (mDirVec == Vector3::Zero)
	{
		mDirVec = mForwardVec;
	}

	// �U�����q�b�g�����G�l�~�[�̌Q��̒��S�Ɍ����x�N�g��
	Vector3 faceInFlockCenterVec = mFirstAttackEffectPtr->GetFaceInFlockCenterVec();
	if (faceInFlockCenterVec != Vector3::Zero)
	{
		mDirVec = faceInFlockCenterVec;
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
		return PlayerState::ePlayerStateFirstAttack;
	}

	if (mElapseTime >= MBoxEnableTiming)
	{
		// 1�i�K�ڂ̒ʏ�U���̓����蔻���L���ɂ���
		mIsCollisionState = true;
	}

	if (!mIsCollisionState)
	{
		return PlayerState::ePlayerStateFirstAttack;
	}


	if (mElapseTime >= mBoxDisableTiming)
	{
		// 1�i�K�ڂ̒ʏ�U���̓����蔻��𖳌��ɂ���
		mIsCollisionState = false;
		mIsOneCollisionState = true;
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

	// �U���{�^�������ꂽ�玟�̃X�e�[�g�ֈڍs���鏀��
	if (mElapseTime >= MValidComboFrame && _KeyState.m_controller.GetButtonState(SDL_CONTROLLER_BUTTON_Y) == Released ||
		mElapseTime >= MValidComboFrame && _KeyState.m_keyboard.GetKeyState(SDL_SCANCODE_SPACE) == Released)
	{
		mIsNextCombo = true;
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
		if(LeftStickDefeatLeftInputOperation(faceAngleList[static_cast<int>(FaceAngleType::eDownRight)],
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
void PlayerObjectStateFirstAttack::Enter(PlayerObject* _owner, const float _DeltaTime)
{
	// 1�i�K�ڂ̒ʏ�U����Ԃ̃A�j���[�V�����Đ�
	SkeletalMeshComponent* meshComp = _owner->GetSkeletalMeshComponentPtr();
	meshComp->PlayAnimation(_owner->GetAnimPtr(PlayerState::ePlayerStateFirstAttack), MPlayRate);
	mIsNextCombo = false;
	mIsHit = false;

	// �A�j���[�V�����Đ����Ԏ擾
	mTotalAnimTime = _owner->GetAnimPtr(PlayerState::ePlayerStateFirstAttack)->GetDuration();
	mElapseTime = 0.0f;
	mBoxDisableTiming = MBoxEnableTiming + _DeltaTime;
	mIsOneCollisionState = false;

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
	// ���W
	mPosition = _owner->GetPosition();

	// �I�u�W�F�N�g�̃^�O
	Tag tag = _HitObject.GetTag();

	if (tag == Tag::eEnemyAttackDecision)
	{
		mDamageValue = MDamageValueEnemyAttack;
		mIsHit = true;
	}

	_owner->SetDamageValue(mDamageValue);
}

/// <summary>
/// �c�L�[���͑���
/// </summary>
/// <param name="_KeyState"> �L�[�{�[�h�A�}�E�X�A�R���g���[���[�̓��͏�� </param>
/// <param name="_KeyScancode"> ���L�[���������� </param>
/// <param name="_ButtonScancode"> ���{�^������������ </param>
/// <returns> true : ����������, false : ���������Ȃ����� </returns>
bool PlayerObjectStateFirstAttack::VerticalKeyInputOperation(const InputState& _KeyState, const SDL_Scancode& _KeyScancode, const SDL_GameControllerButton& _ButtonScancode,
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
bool PlayerObjectStateFirstAttack::LateralKeyInputOperation(const InputState& _KeyState, const SDL_Scancode& _KeyScancode,
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
bool PlayerObjectStateFirstAttack::LeftStickDefeatLeftInputOperation(const float& _AngleBorderMin, const float& _AngleBorderMax, const float& _ValueShortenVector)
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
bool PlayerObjectStateFirstAttack::LeftStickDefeatRightInputOperation(const float& _AngleBorderMin, const float& _AngleBorderMax, const float& _ValueShortenVector)
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
void PlayerObjectStateFirstAttack::RotateInRangeAngle(const float& _AngleBorderMin, const float& _AngleBorderMax, const float& _ValueShortenVector)
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