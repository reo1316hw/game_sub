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
	// アニメーションが終了したらアイドル状態か、次のコンボへ
	if (!_owner->GetSkeletalMeshComp()->IsPlaying())
	{
		//_owner->RemoveAttackHitBox();
		if (mNextComboFlag)
		{
			return PlayerState::ePlayerStateFirstAttack;
		}

		return PlayerState::ePlayerStateIdle;
	}

	// 攻撃踏み込み移動のためのアニメーション再生時間の経過割合を計算
	mElapseTime += _deltaTime;
	const float PLAYER_ATTACK_SPEED = 300.0f;

	// 経過割合をもとに移動処理
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

	// 攻撃ボタン押されたら次のステートへ移行する準備
	if (_keyState.m_keyboard.GetKeyState(SDL_SCANCODE_RETURN) == Pressed)
	{
		mNextComboFlag = true;
	}

}

void PlayerObjectStateDashAttack::Enter(PlayerObject* _owner, float _deltaTime)
{
	// ATTACK1のアニメーション再生
	SkeletalMeshComponent* meshComp = _owner->GetSkeletalMeshComp();
	meshComp->PlayAnimation(_owner->GetAnim(PlayerState::ePlayerStateDashAttack), 1.5f);
	mNextComboFlag = false;

	// アニメーション再生時間取得
	mTotalAnimTime = _owner->GetAnim(PlayerState::ePlayerStateDashAttack)->GetDuration() - 0.4f;
	mElapseTime = 0.0f;

	/*owner->SetAttackHitBox(1.5f);*/

	//// effect発生
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
