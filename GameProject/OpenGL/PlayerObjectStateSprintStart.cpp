#include "pch.h"

PlayerObjectStateSprintStart::PlayerObjectStateSprintStart()
{
	printf("Create : [PlayerObjectStateBase] PlayerObjectStateSprintStart\n");
}

PlayerObjectStateSprintStart::~PlayerObjectStateSprintStart()
{
	printf("Remove : [PlayerObjectStateBase] PlayerObjectStateSprintStart\n");
}

PlayerState PlayerObjectStateSprintStart::Update(PlayerObject* _owner, float _deltaTime)
{
	mElapseTime += _deltaTime;

	// �A�j���[�V�������I��������cStopTime�d����ARUN��Ԃ�
	if (!_owner->GetSkeletalMeshComp()->IsPlaying())
	{
		if (mElapseTime > mTotalAnimTime)
		{
			return PlayerState::ePlayerStateSprintLoop;
		}
	}

	MoveCalc(_owner, _deltaTime);

	return PlayerState::ePlayerStateSprintStart;
}

void PlayerObjectStateSprintStart::Input(PlayerObject* _owner, const InputState& _keyState)
{
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

void PlayerObjectStateSprintStart::Enter(PlayerObject* _owner, float _deltaTime)
{
	// RUN_START�̃A�j���[�V�����Đ�
	SkeletalMeshComponent* meshComp = _owner->GetSkeletalMeshComp();
	meshComp->PlayAnimation(_owner->GetAnim(PlayerState::ePlayerStateSprintStart),1.2f);

	// �A�j���[�V�����Đ����Ԏ擾(�A�j���[�V�����̑����ԋ���)
	mTotalAnimTime = _owner->GetAnim(PlayerState::ePlayerStateSprintStart)->GetDuration() - 0.3f;
	mElapseTime = 0.0f;
	mCharaSpeed = 0.0f;
}

void PlayerObjectStateSprintStart::MoveCalc(PlayerObject* _owner, float _deltaTime)
{
	// �ړ����x
	const float PLAYER_SPEED = 100.0f;

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
		mCharaSpeed += PLAYER_SPEED * _deltaTime;
	}

	if (mCharaSpeed >= 12.0f)
	{
		mCharaSpeed = 12.0f;
	}

	// �ړ�����
	Vector3 position = _owner->GetPosition();
	position += mCharaSpeed * mCharaForwardVec;

	// �L�����̈ʒu�E�X�s�[�h�E�ϊ��s��̍Čv�Z�̕K�v���Z�b�g
	_owner->SetPosition(position);
}
