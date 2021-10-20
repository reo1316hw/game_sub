#include "pch.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
PlayerObjectStateSprintStart::PlayerObjectStateSprintStart()
	: MMoveSpeed(100.0f)
	, MMaxSpeed(12.0f)
	, MPlayRate(1.2f)
	, MDirThreshold(0.5f)
	, MLeftAxisThreshold(0.3f)
	, mPosition(Vector3::Zero)
	, mForwardVec(Vector3::Zero)
	, mCameraPos(Vector3::Zero)
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
	MoveCalc(_owner, _DeltaTime);

	mElapseTime += _DeltaTime;

	if (mIsHit)
	{
		return PlayerState::ePlayerStateDamage;
	}

	// �A�j���[�V�������I��������cStopTime�d����ARUN��Ԃ�
	if (!_owner->GetSkeletalMeshComponentPtr()->IsPlaying())
	{
		if (mElapseTime > mTotalAnimTime)
		{
			return PlayerState::ePlayerStateSprintLoop;
		}
	}

	return PlayerState::ePlayerStateSprintStart;
}

/// <summary>
/// ���͏���
/// </summary>
/// <param name="_owner"> �v���C���[(�e)�̃|�C���^ </param>
/// <param name="_KeyState"> �L�[�{�[�h�A�}�E�X�A�R���g���[���[�̓��͏�� </param>
void PlayerObjectStateSprintStart::Input(PlayerObject* _owner, const InputState& _KeyState)
{
	//���X�e�B�b�N�̓��͒l�̒l(-1~1)
	Vector2 leftAxis = _KeyState.m_controller.GetLAxisVec();
	
	//�l���X�V���ꑱ����̂�h�����߂ɏ�����
	mDirVec = Vector3::Zero;

	// �R���g���[���[�̏\����������̓L�[�{�[�h�AW�����͂��ꂽ��z�𑫂�
	if (_KeyState.m_controller.GetButtonState(SDL_CONTROLLER_BUTTON_DPAD_UP) == Held ||
		_KeyState.m_keyboard.GetKeyState(SDL_SCANCODE_W) == Held)
	{
		mDirVec += mForwardVec;
	}
	// �R���g���[���[�̏\�����������́A�L�[�{�[�hS�����͂��ꂽ��-z�𑫂�
	else if (_KeyState.m_controller.GetButtonState(SDL_CONTROLLER_BUTTON_DPAD_DOWN) == Held ||
		_KeyState.m_keyboard.GetKeyState(SDL_SCANCODE_S) == Held)
	{
		mDirVec -= mForwardVec;
	}

	//�R���g���[���[�̏\�����������́A�L�[�{�[�hA�����͂��ꂽ��-x�𑫂�
	if (_KeyState.m_controller.GetButtonState(SDL_CONTROLLER_BUTTON_DPAD_LEFT) == Held ||
		_KeyState.m_keyboard.GetKeyState(SDL_SCANCODE_A) == Held)
	{
		mDirVec -= mRightVec;
	}
	// �R���g���[���[�̏\���E�������́A�L�[�{�[�hD�����͂��ꂽ��x�𑫂�
	else if (_KeyState.m_controller.GetButtonState(SDL_CONTROLLER_BUTTON_DPAD_RIGHT) == Held ||
		_KeyState.m_keyboard.GetKeyState(SDL_SCANCODE_D) == Held)
	{
		mDirVec += mRightVec;
	}

	//���X�e�B�b�N���͎��̑O�ړ�
	if (leftAxis.y <= -MLeftAxisThreshold)
	{
		mDirVec += mForwardVec;
	}
	//���X�e�B�b�N���͎��̌�ړ�
	if (leftAxis.y >= MLeftAxisThreshold)
	{
		mDirVec -= mForwardVec;
	}
	//���X�e�B�b�N���͎��̍��ړ�
	if (leftAxis.x <= -MLeftAxisThreshold)
	{
		mDirVec -= mRightVec;
	}
	//���X�e�B�b�N���͎��̉E�ړ�
	if (leftAxis.x >= MLeftAxisThreshold)
	{
		mDirVec += mRightVec;
	}
}

/// <summary>
/// �v���C���[�̏�Ԃ��ύX���āA�ŏ���1�񂾂��Ăяo�����֐�
/// </summary>
/// <param name="_owner"> �v���C���[(�e)�̃|�C���^ </param>
/// <param name="_DeltaTime"> �Ō�̃t���[������������̂ɗv�������� </param>
void PlayerObjectStateSprintStart::Enter(PlayerObject* _owner, const float _DeltaTime)
{
	// RUN_START�̃A�j���[�V�����Đ�
	SkeletalMeshComponent* meshComp = _owner->GetSkeletalMeshComponentPtr();
	meshComp->PlayAnimation(_owner->GetAnimPtr(PlayerState::ePlayerStateSprintStart), MPlayRate);
	mIsHit = false;

	// �A�j���[�V�����Đ����Ԏ擾(�A�j���[�V�����̑����ԋ���)
	mTotalAnimTime = _owner->GetAnimPtr(PlayerState::ePlayerStateSprintStart)->GetDuration() - 0.3f;
	mElapseTime = 0.0f;
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
	// �I�u�W�F�N�g�̃^�O
	Tag tag = _HitObject.GetTag();

	if (tag == Tag::eEnemyAttackDecision)
	{
		mIsHit = true;
	}
}

/// <summary>
/// �ړ�����
/// </summary>
/// <param name="_owner"> �v���C���[(�e)�̃|�C���^ </param>
/// <param name="_DeltaTime"> �Ō�̃t���[������������̂ɗv�������� </param>
void PlayerObjectStateSprintStart::MoveCalc(PlayerObject* _owner, const float _DeltaTime)
{
	// �J�����̍��W
	mCameraPos = _owner->GetCameraPos();

	mForwardVec = mPosition - mCameraPos;
	// ���������𖳎�
	mForwardVec.z = 0.0f;

	// �J�����O���x�N�g���ƉE�����x�N�g���Z�o
	mForwardVec = Vector3::Normalize(mForwardVec);
	mRightVec = Vector3::Cross(Vector3::UnitZ, mForwardVec);

	// ���̓L�[�̑��a
	if (mDirVec.LengthSq() > MDirThreshold)
	{
		// �����L�[����
		mCharaForwardVec = mDirVec;

		// �i�s�����Ɍ����ĉ�]
		mCharaForwardVec.Normalize();
		_owner->RotateToNewForward(mCharaForwardVec);

		// ���x�����X�ɏグ�Ă���
		mCharaSpeed += MMoveSpeed * _DeltaTime;
	}

	if (mCharaSpeed >= MMaxSpeed)
	{
		mCharaSpeed = MMaxSpeed;
	}

	mPosition += mCharaSpeed * mCharaForwardVec;

	// �L�����̈ʒu�E�X�s�[�h�E�ϊ��s��̍Čv�Z�̕K�v���Z�b�g
	_owner->SetPosition(mPosition);
}
