#include "pch.h"

PlayerObjectStateDashAttack::PlayerObjectStateDashAttack()
	: mNumFrame(0)
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

	// フレーム数を減らしていく
	if (mNumFrame > 0)
	{
		--mNumFrame;
	}

	// 攻撃踏み込み移動のためのアニメーション再生時間の経過割合を計算
	mElapseTime += _deltaTime;
	const float PLAYER_ATTACK_SPEED = 300.0f;

	// 経過割合をもとに移動処理
	Vector3 pos, forward;
	pos = _owner->GetPosition();
	forward = _owner->GetForward();
	float differencePos = 0.0f - PLAYER_ATTACK_SPEED * _deltaTime;
	pos += Quintic::EaseIn(mElapseTime, PLAYER_ATTACK_SPEED * _deltaTime, differencePos, mTotalAnimTime) * forward;

	_owner->SetPosition(pos);

	return PlayerState::ePlayerStateDashAttack;
}

void PlayerObjectStateDashAttack::Input(PlayerObject* _owner, const InputState& _keyState)
{
	// 攻撃ボタン押されたら次のステートへ移行する準備
	if (mNumFrame <= 5 && _keyState.m_keyboard.GetKeyState(SDL_SCANCODE_SPACE) == Released)
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
	mNumFrame = _owner->GetAnim(PlayerState::ePlayerStateDashAttack)->GetNumFrames();
	mElapseTime = 0.0f;
}