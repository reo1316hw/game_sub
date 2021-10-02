#include "pch.h"

/// <summary>
/// コンストラクタ
/// </summary>
PlayerObjectStateSecondAttack::PlayerObjectStateSecondAttack()
	: MPlayerAttackSpeed(100.0f)
	, mNumFrame(0)
	, MPlayRate(1.5f)
	, MValidComboFrame(2)
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
	// フレーム数を減らしていく
	if (mNumFrame > 0)
	{
	    --mNumFrame;
	}

	// 座標
	Vector3 pos = _owner->GetPosition();
	// 前方ベクトル
	Vector3 forward = _owner->GetForward();
	// 開始速度
	float startSpeed = MPlayerAttackSpeed * _DeltaTime;
	// 終了速度
	float endSpeed = -MPlayerAttackSpeed * _DeltaTime;

	// 攻撃踏み込み移動のためのアニメーション再生時間の経過割合を計算
	mElapseTime += _DeltaTime;
	// 経過割合をもとに移動処理
	pos += Quintic::EaseIn(mElapseTime, startSpeed, endSpeed, mTotalAnimTime) * forward;

	_owner->SetPosition(pos);

	// アニメーションが終了したらアイドル状態か、次のコンボへ
	if (!_owner->GetSkeletalMeshComponentPtr()->IsPlaying())
	{
		if (mIsNextCombo)
		{
			return PlayerState::ePlayerStateThirdAttack;
		}
		return PlayerState::ePlayerStateIdle;
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
	if (mNumFrame <= MValidComboFrame && _KeyState.m_keyboard.GetKeyState(SDL_SCANCODE_SPACE) == Released)
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

	// アニメーション再生時間取得
	mTotalAnimTime = _owner->GetAnimPtr(PlayerState::ePlayerStateSecondAttack)->GetDuration();
	mNumFrame = _owner->GetAnimPtr(PlayerState::ePlayerStateDashAttack)->GetNumFrames();
	mElapseTime = 0.0f;
}