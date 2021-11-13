#include "pch.h"

/// <summary>
/// コンストラクタ
/// </summary>
PlayerObjectStateDashAttack::PlayerObjectStateDashAttack()
	: MDamageValueEnemyAttack(25)
	, MHitStopEndTiming(5)
	, MValidComboFrame(0.4f)
	, MBoxEnableTiming(0.15f)
	, MPlayRate(1.5f)
	, MAttackSpeed(300.0f)
	, mIsCollisionState(false)
	, mIsHitStop(false)
	, mDamageValue(0)
	, mHitStopCount(0)
	, mBoxDisableTiming(0.0f)
	, mPosition(Vector3::Zero)
	, mForwardVec(Vector3::Zero)
	, skeletalMeshCompPtr(nullptr)
	, mDashAttackEffectPtr(nullptr)
{
}

/// <summary>
/// 更新処理
/// </summary>
/// <param name="_owner"> プレイヤー(親)のポインタ </param>
/// <param name="_DeltaTime"> 最後のフレームを完了するのに要した時間 </param>
/// <returns> プレイヤーの状態 </returns>
PlayerState PlayerObjectStateDashAttack::Update(PlayerObject* _owner, const float _DeltaTime)
{
	if (mIsHit)
	{
		return PlayerState::ePlayerStateDamage;
	}

	// 次のコンボへ
	if (mIsNextCombo)
	{
		return PlayerState::ePlayerStateFirstAttack;
	}

	// アニメーションが終了したらアイドル状態か、次のコンボへ
	if (!_owner->GetSkeletalMeshComponentPtr()->IsPlaying())
	{
		return PlayerState::ePlayerStateIdle;
	}

	// 攻撃時に武器が当たったらヒットストップを行う
	if (mDashAttackEffectPtr->IsHitCheck())
	{
		mIsHitStop = true;
		skeletalMeshCompPtr->SetIsHitStop(mIsHitStop);
	}

	// ヒットストップ時に移動処理を無効化
	if (mIsHitStop)
	{
		++mHitStopCount;

		if (mHitStopCount <= MHitStopEndTiming)
		{
			return PlayerState::ePlayerStateDashAttack;
		}

		mIsHitStop = false;
		mHitStopCount = 0;
	}

	// 開始速度
	float startSpeed = MAttackSpeed * _DeltaTime;
	// 終了速度
	float endSpeed = -MAttackSpeed * _DeltaTime;

	// 攻撃踏み込み移動のためのアニメーション再生時間の経過割合を計算
	mElapseTime += _DeltaTime;
	// 経過割合をもとに移動処理
	mPosition += Quintic::EaseIn(mElapseTime, startSpeed, endSpeed, mTotalAnimTime) * mForwardVec;

	_owner->SetPosition(mPosition);

	if (mIsOneCollisionState)
	{
		return PlayerState::ePlayerStateDashAttack;
	}

	if (mElapseTime >= MBoxEnableTiming)
	{
		// ダッシュ攻撃の当たり判定を有効にする
		mIsCollisionState = true;
	}

	if (!mIsCollisionState)
	{
		return PlayerState::ePlayerStateDashAttack;
	}

	if (mElapseTime >= mBoxDisableTiming)
	{
		// ダッシュ攻撃の当たり判定を無効にする
		mIsCollisionState = false;
		mIsOneCollisionState = true;
	}

	return PlayerState::ePlayerStateDashAttack;
}

/// <summary>
/// 入力処理
/// </summary>
/// <param name="_owner"> プレイヤー(親)のポインタ </param>
/// <param name="_KeyState"> キーボード、マウス、コントローラーの入力状態 </param>
void PlayerObjectStateDashAttack::Input(PlayerObject* _owner, const InputState& _KeyState)
{
	// 攻撃ボタン押されたら次のステートへ移行する準備
	if (mElapseTime >= MValidComboFrame && _KeyState.m_controller.GetButtonState(SDL_CONTROLLER_BUTTON_Y) == Released ||
		mElapseTime >= MValidComboFrame && _KeyState.m_keyboard.GetKeyState(SDL_SCANCODE_SPACE) == Released)
	{
		mIsNextCombo = true;
	}
}

/// <summary>
/// プレイヤーの状態が変更して、最初に1回だけ呼び出される関数
/// </summary>
/// <param name="_owner"> プレイヤー(親)のポインタ </param>
/// <param name="_DeltaTime"> 最後のフレームを完了するのに要した時間 </param>
void PlayerObjectStateDashAttack::Enter(PlayerObject* _owner, const float _DeltaTime)
{
	// ダッシュ攻撃状態のアニメーション再生
	skeletalMeshCompPtr = _owner->GetSkeletalMeshComponentPtr();
	skeletalMeshCompPtr->PlayAnimation(_owner->GetAnimPtr(PlayerState::ePlayerStateDashAttack), MPlayRate);
	mIsNextCombo = false;
	mIsHit = false;
	mIsOneCollisionState = false;

	// アニメーション再生時間取得
	mTotalAnimTime = _owner->GetAnimPtr(PlayerState::ePlayerStateDashAttack)->GetDuration() - 0.4f;
	mElapseTime = 0.0f;
	mBoxDisableTiming = MBoxEnableTiming + _DeltaTime;

	// ヒットストップ関係初期化
	mIsHitStop = false;
	mHitStopCount = 0;

	// 座標
	mPosition = _owner->GetPosition();
	// 前方ベクトル
	mForwardVec = _owner->GetForward();
}

/// <summary>
/// ヒットした時の処理
/// </summary>
/// <param name="_owner"> プレイヤー(親)のポインタ </param>
/// <param name="_HitObject"> ヒットしたゲームオブジェクト </param>
void PlayerObjectStateDashAttack::OnCollision(PlayerObject* _owner, const GameObject& _HitObject)
{
	// オブジェクトのタグ
	Tag tag = _HitObject.GetTag();

	if (tag == Tag::eEnemyAttackDecision)
	{
		mDamageValue = MDamageValueEnemyAttack;
		mIsHit = true;
	}

	_owner->SetDamageValue(mDamageValue);
}