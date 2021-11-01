#include "pch.h"

/// <summary>
/// コンストラクタ
/// </summary>
PlayerObjectStateSprintStart::PlayerObjectStateSprintStart()
	: MDamageValueEnemyAttack(25)
	, MMoveSpeed(100.0f)
	, MMaxSpeed(12.0f)
	, MPlayRate(1.2f)
	, MDirThreshold(0.5f)
	, MLeftAxisThreshold(0.3f)
	, mDamageValue(0)
	, mleftAxis(Vector2::Zero)
	, mPosition(Vector3::Zero)
	, mForwardVec(Vector3::Zero)
	, mMainCameraPtr(nullptr)
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

	if (mIsHit)
	{
		return PlayerState::ePlayerStateDamage;
	}

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

	// 左スティックの入力値を取得
	mleftAxis = _KeyState.m_controller.GetLAxisVec();

	if (mleftAxis.x != 0.0f || mleftAxis.y != 0.0f)
	{
		mIsRun = true;
	}
}

/// <summary>
/// プレイヤーの状態が変更して、最初に1回だけ呼び出される関数
/// </summary>
/// <param name="_owner"> プレイヤー(親)のポインタ </param>
/// <param name="_DeltaTime"> 最後のフレームを完了するのに要した時間 </param>
void PlayerObjectStateSprintStart::Enter(PlayerObject* _owner, const float _DeltaTime)
{
	// 全力疾走始め状態のアニメーション再生
	SkeletalMeshComponent* meshComp = _owner->GetSkeletalMeshComponentPtr();
	meshComp->PlayAnimation(_owner->GetAnimPtr(PlayerState::ePlayerStateSprintStart), MPlayRate);
	mIsHit = false;

	// アニメーション再生時間取得(アニメーションの総時間矯正)
	mTotalAnimTime = _owner->GetAnimPtr(PlayerState::ePlayerStateSprintStart)->GetDuration() - 0.3f;
	mElapseTime = 0.0f;
	mCharaSpeed = 0.0f;

	// 座標
	mPosition = _owner->GetPosition();
}

/// <summary>
/// ヒットした時の処理
/// </summary>
/// <param name="_owner"> プレイヤー(親)のポインタ </param>
/// <param name="_HitObject"> ヒットしたゲームオブジェクト </param>
void PlayerObjectStateSprintStart::OnCollision(PlayerObject* _owner, const GameObject& _HitObject)
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

/// <summary>
/// 移動処理
/// </summary>
/// <param name="_owner"> プレイヤー(親)のポインタ </param>
/// <param name="_DeltaTime"> 最後のフレームを完了するのに要した時間 </param>
void PlayerObjectStateSprintStart::MoveCalc(PlayerObject* _owner, const float _DeltaTime)
{
	if (mMainCameraPtr != nullptr)
	{
		// カメラの座標
		Vector3 cameraPos = mMainCameraPtr->GetPosition();

		// カメラ前方ベクトル
		mForwardVec = mPosition - cameraPos;
		// 高さ方向を無視
		mForwardVec.z = 0.0f;

		// カメラ前方ベクトルと右方向ベクトル算出
		mForwardVec = Vector3::Normalize(mForwardVec);
		mRightVec = Vector3::Cross(Vector3::UnitZ, mForwardVec);

		// カメラの向き基準による移動方向ベクトルを求める
		mDirVec = mForwardVec * -mleftAxis.y + mRightVec * mleftAxis.x;
	}
	
	// 速度を初期化
	mCharaSpeed = 0.0f;

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

	mPosition += mCharaSpeed * mCharaForwardVec;

	// キャラの位置・スピード・変換行列の再計算の必要をセット
	_owner->SetPosition(mPosition);
}
