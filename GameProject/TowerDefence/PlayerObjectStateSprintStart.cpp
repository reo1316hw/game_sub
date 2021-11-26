#include "pch.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
PlayerObjectStateSprintStart::PlayerObjectStateSprintStart()
	: mHitTagList{ Tag::eEnemyAttackDecision, Tag::eFrontCoreMagicEffect, Tag::eAreaMagicEffect, Tag::eOverheadMagicEffect }
	, MDamageValueEnemyAttack(25)
	, MMoveSpeed(100.0f)
	, MMaxSpeed(12.0f)
	, MPlayRate(1.2f)
	, MLeftAxisThreshold(0.5f)
	, mIsDamage(false)
	, mDamageValue(0)
	, mHitTagListSize(sizeof(mHitTagList) / sizeof(int))
	, mPosition(Vector3::Zero)
	, mHitTag(Tag::eOther)
	, mPlayerPtr(nullptr)
	, mMainCameraPtr(nullptr)
{
}

/// <summary>
/// �X�V����
/// </summary>
/// <param name="_owner"> �v���C���[(�e)�̃|�C���^ </param>
/// <param name="_DeltaTime"> �Ō�̃t���[������������̂ɗv�������� </param>
/// <returns> �v���C���[�̏�� </returns>
PlayerState PlayerObjectStateSprintStart::Update(PlayerObject* _owner, const float _DeltaTime)
{
	if (mIsDamage)
	{
		return PlayerState::ePlayerStateDamage;
	}

	if (!mIsSprint || mIsSprint && !mIsRun)
	{
		return PlayerState::ePlayerStateIdle;
	}

	// �A�j���[�V�������I��������RUN��Ԃ�
	if (!_owner->GetSkeletalMeshComponentPtr()->IsPlaying())
	{
		return PlayerState::ePlayerStateSprintLoop;
	}

	MoveCalc(_owner, _DeltaTime);

	return PlayerState::ePlayerStateSprintStart;
}

/// <summary>
/// ���͏���
/// </summary>
/// <param name="_owner"> �v���C���[(�e)�̃|�C���^ </param>
/// <param name="_KeyState"> �L�[�{�[�h�A�}�E�X�A�R���g���[���[�̓��͏�� </param>
void PlayerObjectStateSprintStart::Input(PlayerObject* _owner, const InputState& _KeyState)
{
	if (mMainCameraPtr == nullptr)
	{
		return;
	}

	// �����x�N�g����������
	mDirVec = Vector3::Zero;

	// �J�����̍��W
	Vector3 cameraPos = mMainCameraPtr->GetPosition();

	// �J�����̑O���x�N�g��
	Vector3 cameraForwardVec = mPosition - cameraPos;
	// ���������𖳎�
	cameraForwardVec.z = 0.0f;
	cameraForwardVec = Vector3::Normalize(cameraForwardVec);

	// �J�����̉E���x�N�g���Z�o
	Vector3 cameraRightVec = Vector3::Cross(Vector3::UnitZ, cameraForwardVec);

	// �����L�[�����͂��ꂽ��
	mIsRun = _KeyState.m_keyboard.GetKeyValue(SDL_SCANCODE_W) ||
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
		mDirVec += cameraForwardVec;
	}
	// �R���g���[���[�̏\�����������́A�L�[�{�[�hS�����͂��ꂽ��-z�𑫂�
	else if (_KeyState.m_controller.GetButtonState(SDL_CONTROLLER_BUTTON_DPAD_DOWN) == Held ||
		_KeyState.m_keyboard.GetKeyState(SDL_SCANCODE_S) == Held)
	{
		mDirVec -= cameraForwardVec;
	}

	// �R���g���[���[�̏\�����������́A�L�[�{�[�hA�����͂��ꂽ��-x�𑫂�
	if (_KeyState.m_controller.GetButtonState(SDL_CONTROLLER_BUTTON_DPAD_LEFT) == Held ||
		_KeyState.m_keyboard.GetKeyState(SDL_SCANCODE_A) == Held)
	{
		mDirVec -= cameraRightVec;
	}
	// �R���g���[���[�̏\���E�������́A�L�[�{�[�hD�����͂��ꂽ��x�𑫂�
	else if (_KeyState.m_controller.GetButtonState(SDL_CONTROLLER_BUTTON_DPAD_RIGHT) == Held ||
		_KeyState.m_keyboard.GetKeyState(SDL_SCANCODE_D) == Held)
	{
		mDirVec += cameraRightVec;
	}

	// ���X�e�B�b�N�̓��͒l���擾
	Vector2 leftAxis = _KeyState.m_controller.GetLAxisVec();

	if (leftAxis.LengthSq() >= MLeftAxisThreshold)
	{
		mIsRun = true;

		// �J�����̌�����ɂ��ړ������x�N�g�������߂�
		mDirVec = cameraForwardVec * -leftAxis.y + cameraRightVec * leftAxis.x;
	}

	//��Shift�L�[�����͂��ꂽ��
	mIsSprint = _KeyState.m_controller.GetButtonValue(SDL_CONTROLLER_BUTTON_RIGHTSHOULDER) ||
		        _KeyState.m_keyboard.GetKeyValue(SDL_SCANCODE_LSHIFT);
}

/// <summary>
/// �v���C���[�̏�Ԃ��ύX���āA�ŏ���1�񂾂��Ăяo�����֐�
/// </summary>
/// <param name="_owner"> �v���C���[(�e)�̃|�C���^ </param>
/// <param name="_DeltaTime"> �Ō�̃t���[������������̂ɗv�������� </param>
void PlayerObjectStateSprintStart::Enter(PlayerObject* _owner, const float _DeltaTime)
{
	// �S�͎����n�ߏ�Ԃ̃A�j���[�V�����Đ�
	SkeletalMeshComponent* meshComp = _owner->GetSkeletalMeshComponentPtr();
	meshComp->PlayAnimation(_owner->GetAnimPtr(PlayerState::ePlayerStateSprintStart), MPlayRate);
	mIsDamage = false;
	mCharaSpeed = 0.0f;

	// ���W
	mPosition = _owner->GetPosition();
}

/// <summary>
/// �q�b�g�������̏���
/// </summary>
/// <param name="_owner"> �v���C���[(�e)�̃|�C���^ </param>
/// <param name="_HitObject"> �q�b�g�����Q�[���I�u�W�F�N�g </param>
void PlayerObjectStateSprintStart::OnCollision(PlayerObject* _owner, const GameObject& _HitObject)
{
	mPlayerPtr = _owner;

	// �I�u�W�F�N�g�̃^�O
	mHitTag = _HitObject.GetTag();

	for (int i = 0; i < mHitTagListSize; i++)
	{
		// �U�����󂯂����̏���
		if (ReceivedAttack(mHitTagList[i], MDamageValueEnemyAttack))
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
bool PlayerObjectStateSprintStart::ReceivedAttack(const Tag& _hitTag, const int& _DamageValuePlayerAttack)
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
/// �ړ�����
/// </summary>
/// <param name="_owner"> �v���C���[(�e)�̃|�C���^ </param>
/// <param name="_DeltaTime"> �Ō�̃t���[������������̂ɗv�������� </param>
void PlayerObjectStateSprintStart::MoveCalc(PlayerObject* _owner, const float _DeltaTime)
{
	if (mDirVec == Vector3::Zero)
	{
		return;
	}

	// �����L�[����
	mCharaForwardVec = mDirVec;

	// �i�s�����Ɍ����ĉ�]
	mCharaForwardVec.Normalize();
	_owner->RotateToNewForward(mCharaForwardVec);

	// ���x�����X�ɏグ�Ă���
	mCharaSpeed += MMoveSpeed * _DeltaTime;

	if (mCharaSpeed >= MMaxSpeed)
	{
		mCharaSpeed = MMaxSpeed;
	}

	mPosition += mCharaSpeed * mCharaForwardVec;

	// �L�����̈ʒu�E�X�s�[�h�E�ϊ��s��̍Čv�Z�̕K�v���Z�b�g
	_owner->SetPosition(mPosition);
}
