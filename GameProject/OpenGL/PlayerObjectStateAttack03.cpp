#include "pch.h"

//const Vector3 swordLocalPos(0, 0, 100);
//const Vector3 swordLocalAngle(Math::ToRadians(80.0f), Math::ToRadians(40.0f), 0);

PlayerObjectStateAttack03::PlayerObjectStateAttack03()
{
	printf("Create : [PlayerObjectStateBase] PlayerObjectStateAttack03\n");
}

PlayerObjectStateAttack03::~PlayerObjectStateAttack03()
{
	printf("Remove : [PlayerObjectStateBase] PlayerObjectStateAttack03\n");
}

PlayerState PlayerObjectStateAttack03::Update(PlayerObject* _owner, float _deltaTime)
{
	mElapseTime += _deltaTime;
	// アニメーションが終了したらcStopTime硬直後、IDLE状態へ
	if (!_owner->GetSkeletalMeshComp()->IsPlaying())
	{
		if (mElapseTime > mTotalAnimTime /*> cStopTime*/)
		{
			//_owner->RemoveAttackHitBox();
			return PlayerState::ePlayerStateIdle;
		}
		else
		{
			return PlayerState::ePlayerStateThirdAttack;
		}
	}

	// 攻撃踏み込み移動のためのアニメーション再生時間の経過割合を計算
	/*mElapseTime += __deltaTime;*/
	const float PLAYER_ATTACK_SPEED = 150.0f;

	// 経過割合をもとに移動処理
	Vector3 pos, forward;
	pos = _owner->GetPosition();
	forward = _owner->GetForward();
	float differencePos = 0.0f - PLAYER_ATTACK_SPEED * _deltaTime;
	pos += Quintic::EaseIn(mElapseTime, PLAYER_ATTACK_SPEED * _deltaTime, differencePos, mTotalAnimTime) * forward;

	_owner->SetPosition(pos);

	return PlayerState::ePlayerStateThirdAttack;
}

void PlayerObjectStateAttack03::Enter(PlayerObject* _owner, float _deltaTime)
{
	// ATTACK3のアニメーション再生
	SkeletalMeshComponent* meshComp = _owner->GetSkeletalMeshComp();
	meshComp->PlayAnimation(_owner->GetAnim(PlayerState::ePlayerStateThirdAttack),1.5f);

	// アニメーション再生時間取得
	mTotalAnimTime = _owner->GetAnim(PlayerState::ePlayerStateThirdAttack)->GetDuration() - 0.6f;
	mElapseTime = 0.0f;
}