#include "pch.h"

PlayerObjectStateDashAttack::PlayerObjectStateDashAttack()
{
	printf("Create : [PlayerObjectStateBase] PlayerObjectStateDashAttack\n");
}

PlayerObjectStateDashAttack::~PlayerObjectStateDashAttack()
{
	printf("Remove : [PlayerObjectStateBase] PlayerObjectStateDashAttack\n");
}

PlayerState PlayerObjectStateDashAttack::Update(PlayerObject* _owner, float _deltaTime)
{
	// �A�j���[�V�������I��������A�C�h����Ԃ��A���̃R���{��
	if (!_owner->GetSkeletalMeshComp()->IsPlaying())
	{
		//_owner->RemoveAttackHitBox();
		if (mNextComboFlag)
		{
			return PlayerState::ePlayerStateFirstAttack;
		}

		return PlayerState::ePlayerStateIdle;
	}

	// �U�����ݍ��݈ړ��̂��߂̃A�j���[�V�����Đ����Ԃ̌o�ߊ������v�Z
	mElapseTime += _deltaTime;
	const float PLAYER_ATTACK_SPEED = 300.0f;

	// �o�ߊ��������ƂɈړ�����
	Vector3 pos, forward;
	pos = _owner->GetPosition();
	forward = _owner->GetForward();
	float differencePos = /*-5.0f*/ 0.0f - PLAYER_ATTACK_SPEED * _deltaTime;
	pos += Quintic::EaseIn(mElapseTime, PLAYER_ATTACK_SPEED * _deltaTime, differencePos, mTotalAnimTime) * forward;

	_owner->SetPosition(pos);

	return PlayerState::ePlayerStateDashAttack;
}

void PlayerObjectStateDashAttack::Inipt(PlayerObject* _owner, const InputState& _keyState)
{

	// �U���{�^�������ꂽ�玟�̃X�e�[�g�ֈڍs���鏀��
	if (_keyState.m_keyboard.GetKeyState(SDL_SCANCODE_RETURN) == Pressed)
	{
		mNextComboFlag = true;
	}

}

void PlayerObjectStateDashAttack::Enter(PlayerObject* _owner, float _deltaTime)
{
	// ATTACK1�̃A�j���[�V�����Đ�
	SkeletalMeshComponent* meshComp = _owner->GetSkeletalMeshComp();
	meshComp->PlayAnimation(_owner->GetAnim(PlayerState::ePlayerStateDashAttack), 1.5f);
	mNextComboFlag = false;

	// �A�j���[�V�����Đ����Ԏ擾
	mTotalAnimTime = _owner->GetAnim(PlayerState::ePlayerStateDashAttack)->GetDuration() - 0.4f;
	mElapseTime = 0.0f;

	/*owner->SetAttackHitBox(1.5f);*/

	//// effect����
	//SwordEffectActor* effect = new SwordEffectActor(owner);
	//Vector3 localPos, localAngle;
	//localPos = Vector3(50, 0, 100);
	//localAngle = Vector3(Math::ToRadians(30.0f), 0, Math::ToRadians(-30.0f));
	//effect->SetLocalPos(localPos);
	//effect->SetLocalRotation(localAngle);
	//effect->SetEffectTime(mTotalAnimTime);
}

void PlayerObjectStateDashAttack::Exit(PlayerObject* _owner, float _deltaTime)
{
	//_owner->RemoveAttackHitBox();
}
