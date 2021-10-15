#include "pch.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
PlayerObjectStateRunLoop::PlayerObjectStateRunLoop()
	: MMoveSpeed(300.0f)
	, MDirThreshold(0.5f)
	, MLeftAxisThreshold(0.3f)
{
}

/// <summary>
/// �X�V����
/// </summary>
/// <param name="_owner"> �v���C���[(�e)�̃|�C���^ </param>
/// <param name="_DeltaTime"> �Ō�̃t���[������������̂ɗv�������� </param>
/// <returns> �v���C���[�̏�� </returns>
PlayerState PlayerObjectStateRunLoop::Update(PlayerObject* _owner, const float _DeltaTime)
{
	MoveCalc(_owner, _DeltaTime);
	
	// ������̃{�^����������Ă��Ȃ�
	if (!mIsRun && !mIsAttack)
	{
		return PlayerState::ePlayerStateIdle;
	}
	else if (mIsSprint)
	{
		return PlayerState::ePlayerStateSprintStart;
	}
	// �U���{�^���������ꂽ���H
	else if (mIsAttack)
	{
		return PlayerState::ePlayerStateFirstAttack;
	}
	else if (mIsHit)
	{
		return PlayerState::ePlayerStateDamage;
	}

	return PlayerState::ePlayerStateRunLoop;
}

/// <summary>
/// ���͏���
/// </summary>
/// <param name="_owner"> �v���C���[(�e)�̃|�C���^ </param>
/// <param name="_KeyState"> �L�[�{�[�h�A�}�E�X�A�R���g���[���[�̓��͏�� </param>
void PlayerObjectStateRunLoop::Input(PlayerObject* _owner, const InputState& _KeyState)
{
	//���X�e�B�b�N�̓��͒l�̒l(-1~1)
	Vector2 leftAxis = _KeyState.m_controller.GetLAxisVec();

	//�����L�[�����͂��ꂽ��
	mIsRun = _KeyState.m_keyboard.GetKeyValue(SDL_SCANCODE_W) ||
		     _KeyState.m_keyboard.GetKeyValue(SDL_SCANCODE_S) ||
		     _KeyState.m_keyboard.GetKeyValue(SDL_SCANCODE_A) ||
		     _KeyState.m_keyboard.GetKeyValue(SDL_SCANCODE_D) ||
		     _KeyState.m_controller.GetButtonValue(SDL_CONTROLLER_BUTTON_DPAD_UP)   ||
		     _KeyState.m_controller.GetButtonValue(SDL_CONTROLLER_BUTTON_DPAD_DOWN) ||
		     _KeyState.m_controller.GetButtonValue(SDL_CONTROLLER_BUTTON_DPAD_LEFT) ||
	         _KeyState.m_controller.GetButtonValue(SDL_CONTROLLER_BUTTON_DPAD_RIGHT);

	if (leftAxis.x != 0.0f || leftAxis.y != 0.0f)
	{
		mIsRun = true;
	}

	//��Shift�L�[�����͂��ꂽ��
	mIsSprint = _KeyState.m_controller.GetButtonValue(SDL_CONTROLLER_BUTTON_RIGHTSHOULDER) ||
		        _KeyState.m_keyboard.GetKeyValue(SDL_SCANCODE_LSHIFT);

	//Space�L�[�����͂��ꂽ��
	mIsAttack = _KeyState.m_controller.GetButtonValue(SDL_CONTROLLER_BUTTON_A) ||
		        _KeyState.m_keyboard.GetKeyValue(SDL_SCANCODE_SPACE);

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
void PlayerObjectStateRunLoop::Enter(PlayerObject* _owner, const float _DeltaTime)
{
    SkeletalMeshComponent* meshcomp = _owner->GetSkeletalMeshComponentPtr();
	meshcomp->PlayAnimation(_owner->GetAnimPtr(PlayerState::ePlayerStateRunLoop));
	mIsHit = false;
}

/// <summary>
/// �q�b�g�������̏���
/// </summary>
/// <param name="_owner"> �v���C���[(�e)�̃|�C���^ </param>
/// <param name="_HitObject"> �q�b�g�����Q�[���I�u�W�F�N�g </param>
void PlayerObjectStateRunLoop::OnCollision(PlayerObject* _owner, const GameObject& _HitObject)
{
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
void PlayerObjectStateRunLoop::MoveCalc(PlayerObject* _owner, const float _DeltaTime)
{
	// �J��������݂��O�i�������擾
	Vector3 targetPos = _owner->GetTargetPos();
	Vector3 cameraPos = _owner->GetCameraPos();

	mForwardVec = targetPos - cameraPos;
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

		// ���݂̃X�s�[�h��ۑ�
		mCharaSpeed = MMoveSpeed * _DeltaTime;
	}

	// ���W
	Vector3 position = _owner->GetPosition();
	position += mCharaSpeed * mCharaForwardVec;

	// �L�����̈ʒu�E�X�s�[�h�E�ϊ��s��̍Čv�Z�̕K�v���Z�b�g
	_owner->SetPosition(position);
}