#include "pch.h"

PlayerObjectStateRunLoop::PlayerObjectStateRunLoop()
{
	printf("Create : [PlayerObjectStateBase] PlayerObjectStateRunLoop\n");
}

PlayerObjectStateRunLoop::~PlayerObjectStateRunLoop()
{
	printf("Remove : [PlayerObjectStateBase] PlayerObjectStateRunLoop\n");
}

PlayerState PlayerObjectStateRunLoop::Update(PlayerObject* _owner, float _deltaTime)
{
	MoveCalc(_owner, _deltaTime);
	
	// ������̃{�^����������Ă��Ȃ�
	if (!mIdleFlag && !mAttackFlag)
	{
		return PlayerState::ePlayerStateIdle;
	}

	if (mSprintStartFlag)
	{
		return PlayerState::ePlayerStateSprintStart;
	}

	// �U���{�^���������ꂽ���H
	if (mAttackFlag)
	{
		return PlayerState::ePlayerStateFirstAttack;
	}

	return PlayerState::ePlayerStateRunLoop;
}

void PlayerObjectStateRunLoop::Input(PlayerObject* _owner, const InputState& _keyState)
{
	//��Shift�L�[�����͂��ꂽ��
	mSprintFlag = _keyState.m_keyboard.GetKeyState(SDL_SCANCODE_LSHIFT) == Held;

	//�����L�[�����͂��ꂽ��
	mRunFlag = _keyState.m_keyboard.GetKeyState(SDL_SCANCODE_W) == Held ||
		_keyState.m_keyboard.GetKeyValue(SDL_SCANCODE_S) == Held ||
		_keyState.m_keyboard.GetKeyValue(SDL_SCANCODE_A) == Held ||
		_keyState.m_keyboard.GetKeyValue(SDL_SCANCODE_D) == Held;

	//Space�L�[�����͂��ꂽ��
	mAttackFlag = _keyState.m_keyboard.GetKeyState(SDL_SCANCODE_SPACE) == Released;

	//�l���X�V���ꑱ����̂�h�����߂ɏ�����
	mDirVec = Vector3::Zero;

	// �R���g���[���[�̏\����������̓L�[�{�[�h�AW�����͂��ꂽ��z�𑫂�
	if (_keyState.m_controller.GetButtonValue(SDL_CONTROLLER_BUTTON_DPAD_UP) == 1 ||
		_keyState.m_keyboard.GetKeyValue(SDL_SCANCODE_W) == 1)
	{
		mDirVec += mForwardVec;
	}
	// �R���g���[���[�̏\�����������́A�L�[�{�[�hS�����͂��ꂽ��-z�𑫂�
	else if (_keyState.m_controller.GetButtonValue(SDL_CONTROLLER_BUTTON_DPAD_DOWN) == 1 ||
		_keyState.m_keyboard.GetKeyValue(SDL_SCANCODE_S) == 1)
	{
		mDirVec -= mForwardVec;
	}

	//�R���g���[���[�̏\�����������́A�L�[�{�[�hA�����͂��ꂽ��-x�𑫂�
	if (_keyState.m_controller.GetButtonValue(SDL_CONTROLLER_BUTTON_DPAD_LEFT) == 1 ||
		_keyState.m_keyboard.GetKeyValue(SDL_SCANCODE_A) == 1)
	{
		mDirVec -= mRightVec;
	}
	// �R���g���[���[�̏\���E�������́A�L�[�{�[�hD�����͂��ꂽ��x�𑫂�
	else if (_keyState.m_controller.GetButtonValue(SDL_CONTROLLER_BUTTON_DPAD_RIGHT) == 1 ||
		_keyState.m_keyboard.GetKeyValue(SDL_SCANCODE_D) == 1)
	{
		mDirVec += mRightVec;
	}
}

// RUN��Ԃւ̐؂�ւ�����
void PlayerObjectStateRunLoop::Enter(PlayerObject* _owner, float _deltaTime)
{
    SkeletalMeshComponent* meshcomp = _owner->GetSkeletalMeshComp();
	meshcomp->PlayAnimation(_owner->GetAnim(PlayerState::ePlayerStateRunLoop));
}

void PlayerObjectStateRunLoop::MoveCalc(PlayerObject* _owner, float _deltaTime)
{
	// �ړ����x
	const float PLAYER_SPEED = 300.0f;

	// �J��������݂��O�i�������擾
	Vector3 targetPos = _owner->GetTargetPos();
	Vector3 viewPos = _owner->GetViewPos();
	mForwardVec = targetPos - viewPos;
	mForwardVec.z = 0.0f; // ���������𖳎�

	// �J�����O���x�N�g���ƉE�����x�N�g���Z�o
	mForwardVec = Vector3::Normalize(mForwardVec);
	mRightVec = Vector3::Cross(Vector3::UnitZ, mForwardVec);

	// ���̓L�[�̑��a
	if (mDirVec.LengthSq() > 0.5f)
	{
		// �����L�[����
		mCharaForwardVec = mDirVec;

		// �i�s�����Ɍ����ĉ�]
		mCharaForwardVec.Normalize();
		_owner->RotateToNewForward(mCharaForwardVec);

		// ���݂̃X�s�[�h��ۑ�
		mCharaSpeed = PLAYER_SPEED * _deltaTime;
	}

	// �ړ�����
	Vector3 position = _owner->GetPosition();
	position += mCharaSpeed * mCharaForwardVec;

	// �L�����̈ʒu�E�X�s�[�h�E�ϊ��s��̍Čv�Z�̕K�v���Z�b�g
	_owner->SetPosition(position);
}
