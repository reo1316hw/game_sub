#include "PlayerObjectStateRunLoop.h"
#include "SkeletalMeshComponent.h"
#include "InputSystem.h"
#include "GameObject.h"
#include "MainCameraObject.h"

PlayerObjectStateRunLoop::PlayerObjectStateRunLoop(bool _isDrawnSword)
	: mIsIdle(false)
	, mIsRunStart(false)
	, mIsAttack(false)
	, mIsDrawnSword(false)
	, charaSpeed(0.0f)
	, dirVec(Vector3::Zero)
	, forwardVec(Vector3::Zero)
	, rightVec(Vector3::Zero)
{
	mIsDrawnSword = _isDrawnSword;
	printf("Create : [PlayerObjectStateBase] PlayerObjectStateRunLoop\n");
}

PlayerObjectStateRunLoop::~PlayerObjectStateRunLoop()
{
	printf("Remove : [PlayerObjectStateBase] PlayerObjectStateRunLoop\n");
}

PlayerState PlayerObjectStateRunLoop::Update(PlayerObject* _owner, float _deltaTime)
{

	MoveCalc(_owner, _deltaTime);

	if (mIsDrawnSword)
	{
		// ������̃{�^����������Ă��Ȃ�
		if (!mIsIdle /*&& !IsJump */ && !mIsAttack)
		{
			return PlayerState::PLAYER_STATE_SWORD_IDLE;
		}

		// �U���{�^���������ꂽ���H
		if (mIsAttack)
		{
			return PlayerState::PLAYER_STATE_ATTACK1;
		}

		return PlayerState::PLAYER_STATE_SWORD_RUN_LOOP;
	}
	else
	{
		// ������̃{�^����������Ă��Ȃ�
		if (!mIsIdle /*&& !IsJump */ && !mIsAttack)
		{
			return PlayerState::PLAYER_STATE_RUN_END;
		}

		if (mIsRunStart)
		{
			return PlayerState::PLAYER_STATE_RUN_START;
		}

		return PlayerState::PLAYER_STATE_RUN_LOOP;
	}

	//// �W�����v�{�^���������ꂽ���H
	//if (IsJump)
	//{
	//	return PlayerState::PLAYER_STATE_JUMPSTART;
	//}
}

void PlayerObjectStateRunLoop::Inipt(PlayerObject* _owner, const InputState& _keyState)
{

	//// �R���g���[�����͂��ꂽ��
	//Vector2 stickL = INPUT_INSTANCE.GetLStick();
	//bool isContollerInputOff = !INPUT_INSTANCE.IsLStickMove();

	//�����L�[�����͂��ꂽ��
	mIsIdle = _keyState.Keyboard.GetKeyValue(SDL_SCANCODE_W) ||
				_keyState.Keyboard.GetKeyValue(SDL_SCANCODE_S) ||
				_keyState.Keyboard.GetKeyValue(SDL_SCANCODE_A) ||
				_keyState.Keyboard.GetKeyValue(SDL_SCANCODE_D); //||
			  // isContollerInputOff;

	//��Shift�L�[�����͂��ꂽ��
	mIsRunStart = _keyState.Keyboard.GetKeyValue(SDL_SCANCODE_LSHIFT);

	//Enter�L�[�����͂��ꂽ��
	mIsAttack = _keyState.Keyboard.GetKeyValue(SDL_SCANCODE_RETURN);
	//bool IsJump = INPUT_INSTANCE.IsKeyPushdown(KEY_B);

	//�l���X�V���ꑱ����̂�h�����߂ɏ�����
	dirVec = Vector3::Zero;

	// �R���g���[���[�̏\����������̓L�[�{�[�h�AW�����͂��ꂽ��z�𑫂�
	if (_keyState.Controller.GetButtonValue(SDL_CONTROLLER_BUTTON_DPAD_UP) == 1 ||
		_keyState.Keyboard.GetKeyValue(SDL_SCANCODE_W) == 1)
	{
		dirVec += forwardVec;
	}
	// �R���g���[���[�̏\�����������́A�L�[�{�[�hS�����͂��ꂽ��-z�𑫂�
	else if (_keyState.Controller.GetButtonValue(SDL_CONTROLLER_BUTTON_DPAD_DOWN) == 1 ||
		_keyState.Keyboard.GetKeyValue(SDL_SCANCODE_S) == 1)
	{
		dirVec -= forwardVec;
	}

	//�R���g���[���[�̏\�����������́A�L�[�{�[�hA�����͂��ꂽ��-x�𑫂�
	if (_keyState.Controller.GetButtonValue(SDL_CONTROLLER_BUTTON_DPAD_LEFT) == 1 ||
		_keyState.Keyboard.GetKeyValue(SDL_SCANCODE_A) == 1)
	{
		dirVec -= rightVec;
	}
	// �R���g���[���[�̏\���E�������́A�L�[�{�[�hD�����͂��ꂽ��x�𑫂�
	else if (_keyState.Controller.GetButtonValue(SDL_CONTROLLER_BUTTON_DPAD_RIGHT) == 1 ||
		_keyState.Keyboard.GetKeyValue(SDL_SCANCODE_D) == 1)
	{
		dirVec += rightVec;
	}
}

// RUN��Ԃւ̐؂�ւ�����
void PlayerObjectStateRunLoop::Enter(PlayerObject* _owner, float _deltaTime)
{
	if (mIsDrawnSword)
	{
		SkeletalMeshComponent* meshcomp = _owner->GetSkeletalMeshComp();
		meshcomp->PlayAnimation(_owner->GetAnim(PlayerState::PLAYER_STATE_SWORD_RUN_LOOP));
	}
	else
	{
		SkeletalMeshComponent* meshcomp = _owner->GetSkeletalMeshComp();
		meshcomp->PlayAnimation(_owner->GetAnim(PlayerState::PLAYER_STATE_RUN_LOOP));
	}
	
}

void PlayerObjectStateRunLoop::MoveCalc(PlayerObject* _owner, float _deltaTime)
{
	/*if (buttonFlag == false)
	{
		charaSpeed -= 1.0f;
		if (charaSpeed <= 0.0f)
		{
			charaSpeed = 0.0f;
		}
	}*/

	// �ړ����x
	const float PLAYER_SPEED = 300.0f;

	// �J��������݂��O�i�������擾
	Vector3 targetPos = _owner->GetTargetPos();
	Vector3 viewPos = _owner->GetViewPos();
	forwardVec = targetPos - viewPos;
	forwardVec.z = 0.0f; // ���������𖳎�

	// �J�����O���x�N�g���ƉE�����x�N�g���Z�o
	forwardVec = Vector3::Normalize(forwardVec);
	rightVec = Vector3::Cross(Vector3::UnitZ, forwardVec);
	//jumpVec = Vector3::Cross(Vector3::UnitY, forwardVec);

	//// �E�����x�N�g������J������]�p���Z�o
	//float forwardAngle = 0.0f;
	//float angleSign;
	//Vector3 tmpVec;
	//forwardAngle = acosf(Vector3::Dot(Vector3::UnitX, rightVec));

	//// �E��]������]���H
	//tmpVec = Vector3::Cross(Vector3::UnitX, rightVec);
	//angleSign = (tmpVec.z > 0.0) ? 1.0f : -1.0f;
	//forwardAngle *= angleSign;

	// ���̓L�[�̑��a
	if (dirVec.LengthSq() > 0.5f)
	{
		// �����L�[����
		charaForwardVec = dirVec;

		// �i�s�����Ɍ����ĉ�]
		charaForwardVec.Normalize();
		_owner->RotateToNewForward(charaForwardVec);

		// ���݂̃X�s�[�h��ۑ�
		charaSpeed = PLAYER_SPEED * _deltaTime;

		/*if (charaSpeed >= 10.0f)
		{
			charaSpeed = 10.0f;
		}*/
	}

	// �ړ�����
	Vector3 position = _owner->GetPosition();
	position += charaSpeed * charaForwardVec;

	// �L�����̈ʒu�E�X�s�[�h�E�ϊ��s��̍Čv�Z�̕K�v���Z�b�g
	_owner->SetPosition(position);
}
