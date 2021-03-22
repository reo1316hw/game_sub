#include "PlayerObjectStateSword.h"
#include "SkeletalMeshComponent.h"
#include "InputSystem.h"
#include "Animation.h"
#include "GameObject.h"
#include "MainCameraObject.h"
#include "Math.h"

PlayerObjectStateSword::PlayerObjectStateSword(bool _moveFlag, bool _drawnSwordFlag)
{
	mMoveFlag = _moveFlag;
	mDrawnSwordFlag = _drawnSwordFlag;
	printf("Create : [PlayerObjectStateBase] PlayerObjectStateDrawnSword\n");
}

PlayerObjectStateSword::~PlayerObjectStateSword()
{
	printf("Remove : [PlayerObjectStateBase] PlayerObjectStateDrawnSword\n");
}

PlayerState PlayerObjectStateSword::Update(PlayerObject* _owner, float _deltaTime)
{
	mElapseTime += _deltaTime;

	bool transitionFlag = mElapseTime > mTotalAnimTime;

	if (mDrawnSwordFlag)
	{
		_owner->SetSwordRot(Vector3(-Math::PiOver2 * 0.5f, Math::Pi * 0.9f, 0.0f));
		_owner->SetSwordPos(Vector3(-70.0f, -5.0f, 135.0f));

		if (mMoveFlag)
		{
			MoveCalc(_owner, _deltaTime);

			if (transitionFlag)
			{
				return PlayerState::PLAYER_STATE_RUN_LOOP;
			}

			return PlayerState::PLAYER_STATE_DRAWN_SWORD_MOVE;
		}
		else
		{
			if (transitionFlag)
			{
				return PlayerState::PLAYER_STATE_SWORD_IDLE;
			}

			return PlayerState::PLAYER_STATE_DRAWN_SWORD;
		}
	}
	else
	{
		if (mMoveFlag)
		{
			MoveCalc(_owner, _deltaTime);

			if (transitionFlag)
			{
				return PlayerState::PLAYER_STATE_RUN_LOOP;
			}

			return PlayerState::PLAYER_STATE_SWORD_DELIVERY_MOVE;
		}
		else
		{
			if (transitionFlag)
			{
				_owner->SetSwordRot(Vector3(-Math::PiOver2 * 0.6f, Math::Pi * 0.4f, 0.0f));
				_owner->SetSwordPos(Vector3(0.0f, 0.0f, 110.0f));

				return PlayerState::PLAYER_STATE_IDLE;
			}

			return PlayerState::PLAYER_STATE_SWORD_DELIVERY;
		}
	}
}

void PlayerObjectStateSword::Inipt(PlayerObject* _owner, const InputState& _keyState)
{

	//// �R���g���[�����͂��ꂽ��
	//Vector2 stickL = INPUT_INSTANCE.GetLStick();
	//bool isContollerInputOff = !INPUT_INSTANCE.IsLStickMove();

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
void PlayerObjectStateSword::Enter(PlayerObject* _owner, float _deltaTime)
{

	if (mDrawnSwordFlag)
	{
		if (mMoveFlag)
		{
			SkeletalMeshComponent* meshcomp = _owner->GetSkeletalMeshComp();
			meshcomp->PlayAnimation(_owner->GetAnim(PlayerState::PLAYER_STATE_DRAWN_SWORD_MOVE));

			// �A�j���[�V�����Đ����Ԏ擾
			mTotalAnimTime = _owner->GetAnim(PlayerState::PLAYER_STATE_DRAWN_SWORD_MOVE)->GetDuration();
			mElapseTime = 0.0f;
		}
		else
		{
			SkeletalMeshComponent* meshcomp = _owner->GetSkeletalMeshComp();
			meshcomp->PlayAnimation(_owner->GetAnim(PlayerState::PLAYER_STATE_DRAWN_SWORD));

			// �A�j���[�V�����Đ����Ԏ擾
			mTotalAnimTime = _owner->GetAnim(PlayerState::PLAYER_STATE_DRAWN_SWORD)->GetDuration();
			mElapseTime = 0.0f;
		}
	}
	else
	{
		if (mMoveFlag)
		{
			SkeletalMeshComponent* meshcomp = _owner->GetSkeletalMeshComp();
			meshcomp->PlayAnimation(_owner->GetAnim(PlayerState::PLAYER_STATE_SWORD_DELIVERY_MOVE));

			// �A�j���[�V�����Đ����Ԏ擾
			mTotalAnimTime = _owner->GetAnim(PlayerState::PLAYER_STATE_SWORD_DELIVERY_MOVE)->GetDuration();
			mElapseTime = 0.0f;
		}
		else
		{
			SkeletalMeshComponent* meshcomp = _owner->GetSkeletalMeshComp();
			meshcomp->PlayAnimation(_owner->GetAnim(PlayerState::PLAYER_STATE_SWORD_DELIVERY));

			// �A�j���[�V�����Đ����Ԏ擾
			mTotalAnimTime = _owner->GetAnim(PlayerState::PLAYER_STATE_SWORD_DELIVERY)->GetDuration();
			mElapseTime = 0.0f;
		}
	}
}

void PlayerObjectStateSword::MoveCalc(PlayerObject* _owner, float _deltaTime)
{
	/*if (buttonFlag == false)
	{
		mCharaSpeed -= 1.0f;
		if (mCharaSpeed <= 0.0f)
		{
			mCharaSpeed = 0.0f;
		}
	}*/

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
	//jumpVec = Vector3::Cross(Vector3::UnitY, mForwardVec);

	//// �E�����x�N�g������J������]�p���Z�o
	//float forwardAngle = 0.0f;
	//float angleSign;
	//Vector3 tmpVec;
	//forwardAngle = acosf(Vector3::Dot(Vector3::UnitX, mRightVec));

	//// �E��]������]���H
	//tmpVec = Vector3::Cross(Vector3::UnitX, mRightVec);
	//angleSign = (tmpVec.z > 0.0) ? 1.0f : -1.0f;
	//forwardAngle *= angleSign;

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

		/*if (mCharaSpeed >= 10.0f)
		{
			mCharaSpeed = 10.0f;
		}*/
	}

	// �ړ�����
	Vector3 position = _owner->GetPosition();
	position += mCharaSpeed * mCharaForwardVec;

	// �L�����̈ʒu�E�X�s�[�h�E�ϊ��s��̍Čv�Z�̕K�v���Z�b�g
	_owner->SetPosition(position);
}
