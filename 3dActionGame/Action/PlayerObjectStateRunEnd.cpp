#include "PlayerObjectStateRunEnd.h"
#include "SkeletalMeshComponent.h"
#include "game.h"
#include "Animation.h"
#include "InputSystem.h"
//#include "AudioManager.h"
//#include "SwordEffectActor.h"

PlayerObjectStateRunEnd::PlayerObjectStateRunEnd()
	: mIsIdle(false)
	, mIsAttack(false)
{
	printf("Create : [PlayerObjectStateBase] PlayerObjectStateRunEnd\n");
}

PlayerObjectStateRunEnd::~PlayerObjectStateRunEnd()
{
	printf("Remove : [PlayerObjectStateBase] PlayerObjectStateRunEnd\n");
}

PlayerState PlayerObjectStateRunEnd::Update(PlayerObject* _owner, float _deltaTime)
{
	mElapseTime += _deltaTime;

	// �A�j���[�V�������I��������cStopTime�d����ARUN��Ԃ�
	if (!_owner->GetSkeletalMeshComp()->IsPlaying())
	{
		if (mElapseTime > mTotalAnimTime)
		{
			return PlayerState::PLAYER_STATE_IDLE;
		}
		else
		{
			return PlayerState::PLAYER_STATE_RUN_END;
		}
	}


	//// �W�����v�J�n�E�W�����v���[�v/�I���A�j��
	//const Animation* runStart = _owner->GetAnim(PlayerState::PLAYER_STATE_RUN_START);
	//const Animation* runLoop = _owner->GetAnim(PlayerState::PLAYER_STATE_RUN_LOOP);

	//// ���ݍĐ����̃A�j�����擾
	//SkeletalMeshComponent* skeltalMesh = _owner->GetSkeletalMeshComp();
	//const Animation* nowAnim = skeltalMesh->GetNowPlayingAnimation();

	MoveCalc(_owner, _deltaTime);

	//// �J�n�A�j���I���Ȃ�W�����v���[�v�A�j���Ɉڍs
	//if (nowAnim == runStart && skeltalMesh->IsPlaying())
	//{
	//	//skeltalMesh->PlayAnimation(runLoop);
	//	return PlayerState::PLAYER_STATE_RUN_LOOP;
	//}

	return PlayerState::PLAYER_STATE_RUN_END;
}

void PlayerObjectStateRunEnd::Inipt(PlayerObject* _owner, const InputState& _keyState)
{
	////�l���X�V���ꑱ����̂�h�����߂ɏ�����
	//dirVec = Vector3::Zero;

	//// �R���g���[���[�̏\����������̓L�[�{�[�h�AW�����͂��ꂽ��z�𑫂�
	//if (_keyState.Controller.GetButtonValue(SDL_CONTROLLER_BUTTON_DPAD_UP) == 1 ||
	//	_keyState.Keyboard.GetKeyValue(SDL_SCANCODE_W) == 1)
	//{
	//	dirVec += forwardVec;
	//}
	//// �R���g���[���[�̏\�����������́A�L�[�{�[�hS�����͂��ꂽ��-z�𑫂�
	//else if (_keyState.Controller.GetButtonValue(SDL_CONTROLLER_BUTTON_DPAD_DOWN) == 1 ||
	//	_keyState.Keyboard.GetKeyValue(SDL_SCANCODE_S) == 1)
	//{
	//	dirVec -= forwardVec;
	//}

	////�R���g���[���[�̏\�����������́A�L�[�{�[�hA�����͂��ꂽ��-x�𑫂�
	//if (_keyState.Controller.GetButtonValue(SDL_CONTROLLER_BUTTON_DPAD_LEFT) == 1 ||
	//	_keyState.Keyboard.GetKeyValue(SDL_SCANCODE_A) == 1)
	//{
	//	dirVec -= rightVec;
	//}
	//// �R���g���[���[�̏\���E�������́A�L�[�{�[�hD�����͂��ꂽ��x�𑫂�
	//else if (_keyState.Controller.GetButtonValue(SDL_CONTROLLER_BUTTON_DPAD_RIGHT) == 1 ||
	//	_keyState.Keyboard.GetKeyValue(SDL_SCANCODE_D) == 1)
	//{
	//	dirVec += rightVec;
	//}
}

void PlayerObjectStateRunEnd::Enter(PlayerObject* _owner, float _deltaTime)
{
	// RUN_START�̃A�j���[�V�����Đ�
	SkeletalMeshComponent* meshComp = _owner->GetSkeletalMeshComp();
	meshComp->PlayAnimation(_owner->GetAnim(PlayerState::PLAYER_STATE_RUN_END), 1.5f);

	// �A�j���[�V�����Đ����Ԏ擾(�A�j���[�V�����̑����ԋ���)
	mTotalAnimTime = _owner->GetAnim(PlayerState::PLAYER_STATE_RUN_END)->GetDuration() - 0.6f;
	mElapseTime = 0.0f;
	mCharaSpeed = 12.0f;
}

void PlayerObjectStateRunEnd::Exit(PlayerObject* _owner, float _deltaTime)
{

}

void PlayerObjectStateRunEnd::MoveCalc(PlayerObject* _owner, float _deltaTime)
{
	//// �J��������݂��O�i�������擾
	//Vector3 targetPos = _owner->GetTargetPos();
	//Vector3 viewPos = _owner->GetViewPos();
	//forwardVec = targetPos - viewPos;
	//forwardVec.z = 0.0f; // ���������𖳎�

	//// �J�����O���x�N�g���ƉE�����x�N�g���Z�o
	//forwardVec = Vector3::Normalize(forwardVec);
	//rightVec = Vector3::Cross(Vector3::UnitZ, forwardVec);
	////jumpVec = Vector3::Cross(Vector3::UnitY, forwardVec);

	////// �E�����x�N�g������J������]�p���Z�o
	////float forwardAngle = 0.0f;
	////float angleSign;
	////Vector3 tmpVec;
	////forwardAngle = acosf(Vector3::Dot(Vector3::UnitX, rightVec));

	////// �E��]������]���H
	////tmpVec = Vector3::Cross(Vector3::UnitX, rightVec);
	////angleSign = (tmpVec.z > 0.0) ? 1.0f : -1.0f;
	////forwardAngle *= angleSign

	//// ���̓L�[�̑��a
	//if (dirVec.LengthSq() > 0.5f)
	//{
	//	// �����L�[����
	//	charaForwardVec = dirVec;

	//	// �i�s�����Ɍ����ĉ�]
	//	charaForwardVec.Normalize();
	//	_owner->RotateToNewForward(charaForwardVec);

	//	// ���݂̃X�s�[�h��ۑ�
	//	charaSpeed -= PLAYER_SPEED * _deltaTime;
	//}

	// �ړ����x
	const float PLAYER_SPEED = 100.0f;

	mCharaForwardVec = _owner->GetForward();

	// ���݂̃X�s�[�h��ۑ�
	mCharaSpeed -= PLAYER_SPEED * _deltaTime;

	if (mCharaSpeed <= 0.0f)
	{
		mCharaSpeed = 0.0f;
	}

	// �ړ�����
	Vector3 position = _owner->GetPosition();
	position += mCharaSpeed * mCharaForwardVec;

	// �L�����̈ʒu�E�X�s�[�h�E�ϊ��s��̍Čv�Z�̕K�v���Z�b�g
	_owner->SetPosition(position);
}
