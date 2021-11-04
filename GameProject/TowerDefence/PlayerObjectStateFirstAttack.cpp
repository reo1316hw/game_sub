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
	, mMainCameraPtr(nullptr)
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

	// �O���x�N�g��
	Vector3 forwardVec = _owner->GetForward();
	if (mDirVec == Vector3::Zero)
	{
		mDirVec = forwardVec;
	}

	// �U�����q�b�g�����G�l�~�[�̌Q��̒��S�Ɍ����x�N�g��
	Vector3 faceInFlockCenterVec = mFirstAttackEffect->GetFaceInFlockCenterVec();
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
	Vector3 forwardVec = _owner->GetForward();
	forwardVec = Vector3::Normalize(forwardVec);

	Vector3 vec = Vector3::Cross(cameraForwardVec, forwardVec);
	float b = 0.0f;
	if (vec.z <= 0.0f)
	{
		float a = Vector3::Dot(cameraForwardVec, forwardVec);
		float angle = Math::Acos(a) * 180 / Math::Pi;
		b = 180.0f - angle;
	}
	else
	{
		b = 180.0f;
		Vector3 f = cameraForwardVec *= -1.0f;
		float a = Vector3::Dot(f, forwardVec);
		float angle = Math::Acos(a) * 180 / Math::Pi;
		float d = 180.0f - angle;
		b += d;
	}

	//�����L�[�����͂��ꂽ��
	mIsRotation = _KeyState.m_keyboard.GetKeyValue(SDL_SCANCODE_W) ||
		_KeyState.m_keyboard.GetKeyValue(SDL_SCANCODE_S) ||
		_KeyState.m_keyboard.GetKeyValue(SDL_SCANCODE_A) ||
		_KeyState.m_keyboard.GetKeyValue(SDL_SCANCODE_D) ||
		_KeyState.m_controller.GetButtonValue(SDL_CONTROLLER_BUTTON_DPAD_UP) ||
		_KeyState.m_controller.GetButtonValue(SDL_CONTROLLER_BUTTON_DPAD_DOWN) ||
		_KeyState.m_controller.GetButtonValue(SDL_CONTROLLER_BUTTON_DPAD_LEFT) ||
		_KeyState.m_controller.GetButtonValue(SDL_CONTROLLER_BUTTON_DPAD_RIGHT);

	// �E���x�N�g���Z�o
	Vector3 rightVec = Vector3::Cross(Vector3::UnitZ, forwardVec);

	// �R���g���[���[�̏\����������̓L�[�{�[�h�AW�����͂��ꂽ���]����
	if (_KeyState.m_controller.GetButtonState(SDL_CONTROLLER_BUTTON_DPAD_UP) == Held ||
		_KeyState.m_keyboard.GetKeyState(SDL_SCANCODE_W) == Held)
	{
		//�R���g���[���[�̏\�����������́A�L�[�{�[�hA�����͂��ꂽ���]����
		if (_KeyState.m_controller.GetButtonState(SDL_CONTROLLER_BUTTON_DPAD_LEFT) == Held ||
			_KeyState.m_keyboard.GetKeyState(SDL_SCANCODE_A) == Held)
		{
			if (b >= 135.0f && b < 315.0f)
			{
				mDirVec = forwardVec + rightVec * 0.05f;
			}
			else
			{
				mDirVec = forwardVec - rightVec * 0.05f;
			}

			return;
		}

		//�R���g���[���[�̏\�����������́A�L�[�{�[�hA�����͂��ꂽ���]����
		if (_KeyState.m_controller.GetButtonState(SDL_CONTROLLER_BUTTON_DPAD_RIGHT) == Held ||
			_KeyState.m_keyboard.GetKeyState(SDL_SCANCODE_D) == Held)
		{
			if (b >= 45.0f && b < 225.0f)
			{
				mDirVec = forwardVec - rightVec * 0.05f;
			}
			else
			{
				mDirVec = forwardVec + rightVec * 0.05f;
			}

			return;
		}

		if (b >= 0.0f && b < 180.0f)
		{
			mDirVec = forwardVec - rightVec * 0.05f;
		}
		else
		{
			mDirVec = forwardVec + rightVec * 0.05f;
		}

		return;
	}

	// �R���g���[���[�̏\�����������́A�L�[�{�[�hS�����͂��ꂽ���]����
	if (_KeyState.m_controller.GetButtonState(SDL_CONTROLLER_BUTTON_DPAD_DOWN) == Held ||
		_KeyState.m_keyboard.GetKeyState(SDL_SCANCODE_S) == Held)
	{
		//�R���g���[���[�̏\�����������́A�L�[�{�[�hA�����͂��ꂽ���]����
		if (_KeyState.m_controller.GetButtonState(SDL_CONTROLLER_BUTTON_DPAD_LEFT) == Held ||
			_KeyState.m_keyboard.GetKeyState(SDL_SCANCODE_A) == Held)
		{
			if (b >= 45.0f && b < 225.0f)
			{
				mDirVec = forwardVec + rightVec * 0.05f;
			}
			else
			{
				mDirVec = forwardVec - rightVec * 0.05f;
			}

			return;
		}

		//�R���g���[���[�̏\�����������́A�L�[�{�[�hA�����͂��ꂽ���]����
		if (_KeyState.m_controller.GetButtonState(SDL_CONTROLLER_BUTTON_DPAD_RIGHT) == Held ||
			_KeyState.m_keyboard.GetKeyState(SDL_SCANCODE_D) == Held)
		{
			if (b >= 135.0f && b < 315.0f)
			{
				mDirVec = forwardVec - rightVec * 0.05f;
			}
			else
			{
				mDirVec = forwardVec + rightVec * 0.05f;
			}

			return;
		}

		if (b >= 0.0f && b < 180.0f)
		{
			mDirVec = forwardVec + rightVec * 0.05f;
		}
		else
		{
			mDirVec = forwardVec - rightVec * 0.05f;
		}

		return;
	}

	//�R���g���[���[�̏\�����������́A�L�[�{�[�hA�����͂��ꂽ���]����
	if (_KeyState.m_controller.GetButtonState(SDL_CONTROLLER_BUTTON_DPAD_LEFT) == Held ||
		_KeyState.m_keyboard.GetKeyState(SDL_SCANCODE_A) == Held)
	{
		if (b >= 90.0f && b < 270.0f)
		{
			mDirVec = forwardVec + rightVec * 0.05f;
		}
		else
		{
			mDirVec = forwardVec - rightVec * 0.05f;
		}

		return;
	}

	// �R���g���[���[�̏\���E�������́A�L�[�{�[�hD�����͂��ꂽ���]����
	if (_KeyState.m_controller.GetButtonState(SDL_CONTROLLER_BUTTON_DPAD_RIGHT) == Held ||
		_KeyState.m_keyboard.GetKeyState(SDL_SCANCODE_D) == Held)
	{
		if (b >= 90.0f && b < 270.0f)
		{
			mDirVec = forwardVec - rightVec * 0.05f;
		}
		else
		{
			mDirVec = forwardVec + rightVec * 0.05f;
		}

		return;
	}

	// ���X�e�B�b�N�̓��͒l���擾
	Vector2 leftAxis = _KeyState.m_controller.GetLAxisVec();

	if (leftAxis.y <= -MLeftAxisThreshold)
	{
		if (leftAxis.x <= -MLeftAxisThreshold)
		{
			if (b >= 135.0f && b < 315.0f)
			{
				mDirVec = forwardVec + rightVec * 0.05f;
			}
			else
			{
				mDirVec = forwardVec - rightVec * 0.05f;
			}

			return;
		}

		if (leftAxis.x >= MLeftAxisThreshold)
		{
			if (b >= 45.0f && b < 225.0f)
			{
				mDirVec = forwardVec - rightVec * 0.05f;
			}
			else
			{
				mDirVec = forwardVec + rightVec * 0.05f;
			}

			return;
		}

		if (b >= 0.0f && b < 180.0f)
		{
			mDirVec = forwardVec - rightVec * 0.05f;
		}
		else
		{
			mDirVec = forwardVec + rightVec * 0.05f;
		}

		return;
	}

	if (leftAxis.y >= MLeftAxisThreshold)
	{
		if (leftAxis.x <= -MLeftAxisThreshold)
		{
			if (b >= 45.0f && b < 225.0f)
			{
				mDirVec = forwardVec + rightVec * 0.05f;
			}
			else
			{
				mDirVec = forwardVec - rightVec * 0.05f;
			}

			return;
		}

		if (leftAxis.x >= MLeftAxisThreshold)
		{
			if (b >= 135.0f && b < 315.0f)
			{
				mDirVec = forwardVec - rightVec * 0.05f;
			}
			else
			{
				mDirVec = forwardVec + rightVec * 0.05f;
			}

			return;
		}

		if (b >= 0.0f && b < 180.0f)
		{
			mDirVec = forwardVec + rightVec * 0.05f;
		}
		else
		{
			mDirVec = forwardVec - rightVec * 0.05f;
		}

		return;
	}

	//�R���g���[���[�̏\�����������́A�L�[�{�[�hA�����͂��ꂽ���]����
	if (leftAxis.x <= -MLeftAxisThreshold)
	{
		if (b >= 90.0f && b < 270.0f)
		{
			mDirVec = forwardVec + rightVec * 0.05f;
		}
		else
		{
			mDirVec = forwardVec - rightVec * 0.05f;
		}

		return;
	}

	// �R���g���[���[�̏\���E�������́A�L�[�{�[�hD�����͂��ꂽ���]����
	if (leftAxis.x >= MLeftAxisThreshold)
	{
		if (b >= 90.0f && b < 270.0f)
		{
			mDirVec = forwardVec - rightVec * 0.05f;
		}
		else
		{
			mDirVec = forwardVec + rightVec * 0.05f;
		}

		return;
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