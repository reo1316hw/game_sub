#include "pch.h"

PlayerObjectStateAttack02::PlayerObjectStateAttack02()
{
	printf("Create : [PlayerObjectStateBase] PlayerObjectStateAttack02\n");
}

PlayerObjectStateAttack02::~PlayerObjectStateAttack02()
{
	printf("Remove : [PlayerObjectStateBase] PlayerObjectStateAttack02\n");
}

PlayerState PlayerObjectStateAttack02::Update(PlayerObject* _owner, float _deltaTime)
{
	// �A�j���[�V�������I��������A�C�h����Ԃ��A���̃R���{��
	if (!_owner->GetSkeletalMeshComp()->IsPlaying())
	{
		//_owner->RemoveAttackHitBox();
		if (mNextComboFlag)
		{
			return PlayerState::ePlayerStateThirdAttack;
		}
		return PlayerState::ePlayerStateIdle;
	}

	// �U�����ݍ��݈ړ��̂��߂̃A�j���[�V�����Đ����Ԃ̌o�ߊ������v�Z
	mElapseTime += _deltaTime;
	const float PLAYER_ATTACK_SPEED = 100.0f;

	// �o�ߊ��������ƂɈړ�����
	Vector3 pos, forward;
	pos = _owner->GetPosition();
	forward = _owner->GetForward();
	float differencePos = 0.0f - PLAYER_ATTACK_SPEED * _deltaTime;
	pos += Quintic::EaseIn(mElapseTime, PLAYER_ATTACK_SPEED * _deltaTime, differencePos, mTotalAnimTime) * forward;

	_owner->SetPosition(pos);

	return PlayerState::ePlayerStateSecondAttack;
}

void PlayerObjectStateAttack02::Inipt(PlayerObject* _owner, const InputState& _keyState)
{
	// �U���{�^�������ꂽ�玟�̃X�e�[�g�ֈڍs���鏀��
	if (_keyState.m_keyboard.GetKeyState(SDL_SCANCODE_SPACE) == Pressed)
	{
		mNextComboFlag = true;
	}
}

void PlayerObjectStateAttack02::Enter(PlayerObject* _owner, float _deltaTime)
{
	// ATTACK1�̃A�j���[�V�����Đ�
	SkeletalMeshComponent* meshComp = _owner->GetSkeletalMeshComp();
	meshComp->PlayAnimation(_owner->GetAnim(PlayerState::ePlayerStateSecondAttack),1.5f);
	mNextComboFlag = false;

	// �A�j���[�V�����Đ����Ԏ擾
	mTotalAnimTime = _owner->GetAnim(PlayerState::ePlayerStateSecondAttack)->GetDuration();
	mElapseTime = 0.0f;

	//_owner->SetAttackHitBox(1.5f);

	//// ���G�t�F�N�g����
	//SwordEffectActor* effect = new SwordEffectActor(_owner);
	//Vector3 localPos, localAngle;
	//localPos = Vector3(50, 0, 100);
	//localAngle = Vector3(Math::ToRadians(-180.0f), 0, 0);
	//effect->SetLocalPos(localPos);
	//effect->SetLocalRotation(localAngle);
	//effect->SetEffectTime(mTotalAnimTime);
}

void PlayerObjectStateAttack02::Exit(PlayerObject* _owner, float _deltaTime)
{
	//_owner->RemoveAttackHitBox();
}
