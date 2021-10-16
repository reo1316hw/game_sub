#include "pch.h"

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="_weaponPtr"> プレイヤーの武器のポインタ </param>
PlayerObjectStateSecondAttack::PlayerObjectStateSecondAttack(PlayerWeaponObject* _weaponPtr)
	: MBoxEnableTiming(20)
	, MAttackSpeed(100.0f)
	, mHitUntilCount(0)
	, mNumFrame(0)
	, MPlayRate(1.5f)
	, MValidComboFrame(2)
	, mPosition(Vector3::Zero)
	, mForwardVec(Vector3::Zero)
	, mOwnerBoxCollider(_weaponPtr->GetBoxCollider())
{
}

/// <summary>
/// 更新処理
/// </summary>
/// <param name="_owner"> プレイヤー(親)のポインタ </param>
/// <param name="_DeltaTime"> 最後のフレームを完了するのに要した時間 </param>
/// <returns> プレイヤーの状態 </returns>
PlayerState PlayerObjectStateSecondAttack::Update(PlayerObject* _owner, const float _DeltaTime)
{
	// 開始速度
	float startSpeed = MAttackSpeed * _DeltaTime;
	// 終了速度
	float endSpeed = -MAttackSpeed * _DeltaTime;

	// 攻撃踏み込み移動のためのアニメーション再生時間の経過割合を計算
	mElapseTime += _DeltaTime;
	// 経過割合をもとに移動処理
	mPosition += Quintic::EaseIn(mElapseTime, startSpeed, endSpeed, mTotalAnimTime) * mForwardVec;

	_owner->SetPosition(mPosition);

	// フレーム数を減らしていく
	if (mNumFrame > 0)
	{
		--mNumFrame;
	}

	++mHitUntilCount;

	if (mHitUntilCount == MBoxEnableTiming)
	{
		// 武器の当たり判定を行うようにする
		mOwnerBoxCollider->SetCollisionState(CollisionState::eEnableCollision);
	}

	// アニメーションが終了したらアイドル状態か、次のコンボへ
	if (!_owner->GetSkeletalMeshComponentPtr()->IsPlaying())
	{
		if (mIsNextCombo)
		{
			return PlayerState::ePlayerStateThirdAttack;
		}
		return PlayerState::ePlayerStateIdle;
	}
	else if (mIsHit)
	{
		return PlayerState::ePlayerStateDamage;
	}

	return PlayerState::ePlayerStateSecondAttack;
}

/// <summary>
/// 入力処理
/// </summary>
/// <param name="_owner"> プレイヤー(親)のポインタ </param>
/// <param name="_KeyState"> キーボード、マウス、コントローラーの入力状態 </param>
void PlayerObjectStateSecondAttack::Input(PlayerObject* _owner, const InputState& _KeyState)
{
	// 攻撃ボタン押されたら次のステートへ移行する準備
	if (mNumFrame <= MValidComboFrame && _KeyState.m_controller.GetButtonState(SDL_CONTROLLER_BUTTON_Y) == Released ||
		mNumFrame <= MValidComboFrame && _KeyState.m_keyboard.GetKeyState(SDL_SCANCODE_SPACE) == Released)
	{
		mIsNextCombo = true;
	}
}

/// <summary>
/// プレイヤーの状態が変更して、最初に1回だけ呼び出される関数
/// </summary>
/// <param name="_owner"> プレイヤー(親)のポインタ </param>
/// <param name="_DeltaTime"> 最後のフレームを完了するのに要した時間 </param>
void PlayerObjectStateSecondAttack::Enter(PlayerObject* _owner, const float _DeltaTime)
{
	// ATTACK1のアニメーション再生
	SkeletalMeshComponent* meshComp = _owner->GetSkeletalMeshComponentPtr();
	meshComp->PlayAnimation(_owner->GetAnimPtr(PlayerState::ePlayerStateSecondAttack), MPlayRate);
	mIsNextCombo = false;
	mIsHit = false;

	// アニメーション再生時間取得
	mTotalAnimTime = _owner->GetAnimPtr(PlayerState::ePlayerStateSecondAttack)->GetDuration();
	mNumFrame = _owner->GetAnimPtr(PlayerState::ePlayerStateDashAttack)->GetNumFrames();
	mElapseTime = 0.0f;
	mHitUntilCount = 0;

	// 座標
	mPosition = _owner->GetPosition();
	// 前方ベクトル
	mForwardVec = _owner->GetForward();
}

/// <summary>
/// プレイヤーの状態が変更して、最後に1回だけ呼び出される関数
/// </summary>
/// <param name="_owner"> プレイヤー(親)のポインタ </param>
/// <param name="_DeltaTime"> 最後のフレームを完了するのに要した時間 </param>
void PlayerObjectStateSecondAttack::Exit(PlayerObject* _owner, const float _DeltaTime)
{
	// 武器の当たり判定を行わないようにする
	mOwnerBoxCollider->SetCollisionState(CollisionState::eDisableCollision);
}

/// <summary>
/// ヒットした時の処理
/// </summary>
/// <param name="_owner"> プレイヤー(親)のポインタ </param>
/// <param name="_HitObject"> ヒットしたゲームオブジェクト </param>
void PlayerObjectStateSecondAttack::OnCollision(PlayerObject* _owner, const GameObject& _HitObject)
{
	// オブジェクトのタグ
	Tag tag = _HitObject.GetTag();

	if (tag == Tag::eEnemyAttackDecision)
	{
		mIsHit = true;
	}
}