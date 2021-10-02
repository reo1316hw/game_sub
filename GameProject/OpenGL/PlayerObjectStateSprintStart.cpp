#include "pch.h"

/// <summary>
/// コンストラクタ
/// </summary>
PlayerObjectStateSprintStart::PlayerObjectStateSprintStart()
	: MMoveSpeed(100.0f)
	, MMaxSpeed(12.0f)
	, MPlayRate(1.2f)
	, MDirThreshold(0.5f)
{
}

/// <summary>
/// 更新処理
/// </summary>
/// <param name="_owner"> プレイヤー(親)のポインタ </param>
/// <param name="_DeltaTime"> 最後のフレームを完了するのに要した時間 </param>
/// <returns> プレイヤーの状態 </returns>
PlayerState PlayerObjectStateSprintStart::Update(PlayerObject* _owner, const float _DeltaTime)
{
	MoveCalc(_owner, _DeltaTime);

	mElapseTime += _DeltaTime;

	// アニメーションが終了したらcStopTime硬直後、RUN状態へ
	if (!_owner->GetSkeletalMeshComponentPtr()->IsPlaying())
	{
		if (mElapseTime > mTotalAnimTime)
		{
			return PlayerState::ePlayerStateSprintLoop;
		}
	}

	return PlayerState::ePlayerStateSprintStart;
}

/// <summary>
/// 入力処理
/// </summary>
/// <param name="_owner"> プレイヤー(親)のポインタ </param>
/// <param name="_KeyState"> キーボード、マウス、コントローラーの入力状態 </param>
void PlayerObjectStateSprintStart::Input(PlayerObject* _owner, const InputState& _KeyState)
{
	//値が更新され続けるのを防ぐために初期化
	mDirVec = Vector3::Zero;

	// コントローラーの十字上もしくはキーボード、Wが入力されたらzを足す
	if (_KeyState.m_controller.GetButtonState(SDL_CONTROLLER_BUTTON_DPAD_UP) == Held ||
		_KeyState.m_keyboard.GetKeyState(SDL_SCANCODE_W) == Held)
	{
		mDirVec += mForwardVec;
	}
	// コントローラーの十字下もしくは、キーボードSが入力されたら-zを足す
	else if (_KeyState.m_controller.GetButtonState(SDL_CONTROLLER_BUTTON_DPAD_DOWN) == Held ||
		_KeyState.m_keyboard.GetKeyState(SDL_SCANCODE_S) == Held)
	{
		mDirVec -= mForwardVec;
	}

	//コントローラーの十字左もしくは、キーボードAが入力されたら-xを足す
	if (_KeyState.m_controller.GetButtonState(SDL_CONTROLLER_BUTTON_DPAD_LEFT) == Held ||
		_KeyState.m_keyboard.GetKeyState(SDL_SCANCODE_A) == Held)
	{
		mDirVec -= mRightVec;
	}
	// コントローラーの十字右もしくは、キーボードDが入力されたらxを足す
	else if (_KeyState.m_controller.GetButtonState(SDL_CONTROLLER_BUTTON_DPAD_RIGHT) == Held ||
		_KeyState.m_keyboard.GetKeyState(SDL_SCANCODE_D) == Held)
	{
		mDirVec += mRightVec;
	}
}

/// <summary>
/// プレイヤーの状態が変更して、最初に1回だけ呼び出される関数
/// </summary>
/// <param name="_owner"> プレイヤー(親)のポインタ </param>
/// <param name="_DeltaTime"> 最後のフレームを完了するのに要した時間 </param>
void PlayerObjectStateSprintStart::Enter(PlayerObject* _owner, const float _DeltaTime)
{
	// RUN_STARTのアニメーション再生
	SkeletalMeshComponent* meshComp = _owner->GetSkeletalMeshComponentPtr();
	meshComp->PlayAnimation(_owner->GetAnimPtr(PlayerState::ePlayerStateSprintStart), MPlayRate);

	// アニメーション再生時間取得(アニメーションの総時間矯正)
	mTotalAnimTime = _owner->GetAnimPtr(PlayerState::ePlayerStateSprintStart)->GetDuration() - 0.3f;
	mElapseTime = 0.0f;
	mCharaSpeed = 0.0f;
}

/// <summary>
/// 移動処理
/// </summary>
/// <param name="_owner"> プレイヤー(親)のポインタ </param>
/// <param name="_DeltaTime"> 最後のフレームを完了するのに要した時間 </param>
void PlayerObjectStateSprintStart::MoveCalc(PlayerObject* _owner, const float _DeltaTime)
{
	// カメラからみた前進方向を取得
	const Vector3 TargetPos = _owner->GetTargetPos();
	const Vector3 CameraPos = _owner->GetCameraPos();

	mForwardVec = TargetPos - CameraPos;
	// 高さ方向を無視
	mForwardVec.z = 0.0f;

	// カメラ前方ベクトルと右方向ベクトル算出
	mForwardVec = Vector3::Normalize(mForwardVec);
	mRightVec = Vector3::Cross(Vector3::UnitZ, mForwardVec);

	// 入力キーの総和
	if (mDirVec.LengthSq() > MDirThreshold)
	{
		// 方向キー入力
		mCharaForwardVec = mDirVec;

		// 進行方向に向けて回転
		mCharaForwardVec.Normalize();
		_owner->RotateToNewForward(mCharaForwardVec);

		// 速度を徐々に上げていく
		mCharaSpeed += MMoveSpeed * _DeltaTime;
	}

	if (mCharaSpeed >= MMaxSpeed)
	{
		mCharaSpeed = MMaxSpeed;
	}

	// 座標
	Vector3 position = _owner->GetPosition();
	position += mCharaSpeed * mCharaForwardVec;

	// キャラの位置・スピード・変換行列の再計算の必要をセット
	_owner->SetPosition(position);
}
