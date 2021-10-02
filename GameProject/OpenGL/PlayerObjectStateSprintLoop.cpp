#include "pch.h"

PlayerObjectStateSprintLoop::PlayerObjectStateSprintLoop()
{
	printf("Create : [PlayerObjectStateBase] PlayerObjectStateSprintLoop\n");
	mCharaSpeed = 0.0f;
}

PlayerObjectStateSprintLoop::~PlayerObjectStateSprintLoop()
{
	printf("Remove : [PlayerObjectStateBase] PlayerObjectStateSprintLoop\n");
}

PlayerState PlayerObjectStateSprintLoop::Update(PlayerObject* _owner, float _deltaTime)
{
	MoveCalc(_owner, _deltaTime);

	//�{�^����������Ă��Ȃ���
	if (!mRunFlag)
	{
		return PlayerState::ePlayerStateRunLoop;
	}
	else
	{
		if (!mIdleFlag)
		{
			return PlayerState::ePlayerStateIdle;
		}
		if (mAttackFlag)
		{
			return PlayerState::ePlayerStateDashAttack;
		}
	}

	return PlayerState::ePlayerStateSprintLoop;
}

void PlayerObjectStateSprintLoop::Input(PlayerObject* _owner, const InputState& _keyState)
{
	//�����L�[�����͂��ꂽ��
	mIdleFlag = _keyState.m_keyboard.GetKeyValue(SDL_SCANCODE_W) ||
		_keyState.m_keyboard.GetKeyValue(SDL_SCANCODE_S) ||
		_keyState.m_keyboard.GetKeyValue(SDL_SCANCODE_A) ||
		_keyState.m_keyboard.GetKeyValue(SDL_SCANCODE_D);

	//��Shift�L�[�����͂��ꂽ��
	mRunFlag = _keyState.m_keyboard.GetKeyValue(SDL_SCANCODE_LSHIFT);
	 
	//Enter�L�[�����͂��ꂽ��
	mAttackFlag = _keyState.m_keyboard.GetKeyValue(SDL_SCANCODE_SPACE);

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
void PlayerObjectStateSprintLoop::Enter(PlayerObject* _owner, float _deltaTime)
{
	SkeletalMeshComponent* meshcomp = _owner->GetSkeletalMeshComp();
	meshcomp->PlayAnimation(_owner->GetAnim(PlayerState::ePlayerStateSprintLoop));
}

void PlayerObjectStateSprintLoop::MoveCalc(PlayerObject* _owner, float _deltaTime)
{
	// ���x������
	mCharaSpeed = 0.0f;
	// �ړ����x
	const float PLAYER_SPEED = 750.0f;

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
