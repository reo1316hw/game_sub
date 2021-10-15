#include "pch.h"

/// <summary>
/// コンストラクタ
/// </summary>
PlayerObjectStateRunLoop::PlayerObjectStateRunLoop()
	: MMoveSpeed(300.0f)
	, MDirThreshold(0.5f)
	, MLeftAxisThreshold(0.3f)
{
}

/// <summary>
/// 更新処理
/// </summary>
/// <param name="_owner"> プレイヤー(親)のポインタ </param>
/// <param name="_DeltaTime"> 最後のフレームを完了するのに要した時間 </param>
/// <returns> プレイヤーの状態 </returns>
PlayerState PlayerObjectStateRunLoop::Update(PlayerObject* _owner, const float _DeltaTime)
{
	MoveCalc(_owner, _DeltaTime);
	
	// いずれのボタンも押されていない
	if (!mIsRun && !mIsAttack)
	{
		return PlayerState::ePlayerStateIdle;
	}
	else if (mIsSprint)
	{
		return PlayerState::ePlayerStateSprintStart;
	}
	// 攻撃ボタンが押されたか？
	else if (mIsAttack)
	{
		return PlayerState::ePlayerStateFirstAttack;
	}
	else if (mIsHit)
	{
		return PlayerState::ePlayerStateDamage;
	}

	return PlayerState::ePlayerStateRunLoop;
}

/// <summary>
/// 入力処理
/// </summary>
/// <param name="_owner"> プレイヤー(親)のポインタ </param>
/// <param name="_KeyState"> キーボード、マウス、コントローラーの入力状態 </param>
void PlayerObjectStateRunLoop::Input(PlayerObject* _owner, const InputState& _KeyState)
{
	//左スティックの入力値の値(-1~1)
	Vector2 leftAxis = _KeyState.m_controller.GetLAxisVec();

	//方向キーが入力されたか
	mIsRun = _KeyState.m_keyboard.GetKeyValue(SDL_SCANCODE_W) ||
		     _KeyState.m_keyboard.GetKeyValue(SDL_SCANCODE_S) ||
		     _KeyState.m_keyboard.GetKeyValue(SDL_SCANCODE_A) ||
		     _KeyState.m_keyboard.GetKeyValue(SDL_SCANCODE_D) ||
		     _KeyState.m_controller.GetButtonValue(SDL_CONTROLLER_BUTTON_DPAD_UP)   ||
		     _KeyState.m_controller.GetButtonValue(SDL_CONTROLLER_BUTTON_DPAD_DOWN) ||
		     _KeyState.m_controller.GetButtonValue(SDL_CONTROLLER_BUTTON_DPAD_LEFT) ||
	         _KeyState.m_controller.GetButtonValue(SDL_CONTROLLER_BUTTON_DPAD_RIGHT);

	if (leftAxis.x != 0.0f || leftAxis.y != 0.0f)
	{
		mIsRun = true;
	}

	//左Shiftキーが入力されたか
	mIsSprint = _KeyState.m_controller.GetButtonValue(SDL_CONTROLLER_BUTTON_RIGHTSHOULDER) ||
		        _KeyState.m_keyboard.GetKeyValue(SDL_SCANCODE_LSHIFT);

	//Spaceキーが入力されたか
	mIsAttack = _KeyState.m_controller.GetButtonValue(SDL_CONTROLLER_BUTTON_A) ||
		        _KeyState.m_keyboard.GetKeyValue(SDL_SCANCODE_SPACE);

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

	//左スティック入力時の前移動
	if (leftAxis.y <= -MLeftAxisThreshold)
	{
		mDirVec += mForwardVec;
	}
	//左スティック入力時の後移動
	if (leftAxis.y >= MLeftAxisThreshold)
	{
		mDirVec -= mForwardVec;
	}
	//左スティック入力時の左移動
	if (leftAxis.x <= -MLeftAxisThreshold)
	{
		mDirVec -= mRightVec;
	}
	//左スティック入力時の右移動
	if (leftAxis.x >= MLeftAxisThreshold)
	{
		mDirVec += mRightVec;
	}
}

/// <summary>
/// プレイヤーの状態が変更して、最初に1回だけ呼び出される関数
/// </summary>
/// <param name="_owner"> プレイヤー(親)のポインタ </param>
/// <param name="_DeltaTime"> 最後のフレームを完了するのに要した時間 </param>
void PlayerObjectStateRunLoop::Enter(PlayerObject* _owner, const float _DeltaTime)
{
    SkeletalMeshComponent* meshcomp = _owner->GetSkeletalMeshComponentPtr();
	meshcomp->PlayAnimation(_owner->GetAnimPtr(PlayerState::ePlayerStateRunLoop));
	mIsHit = false;
}

/// <summary>
/// ヒットした時の処理
/// </summary>
/// <param name="_owner"> プレイヤー(親)のポインタ </param>
/// <param name="_HitObject"> ヒットしたゲームオブジェクト </param>
void PlayerObjectStateRunLoop::OnCollision(PlayerObject* _owner, const GameObject& _HitObject)
{
	Tag tag = _HitObject.GetTag();

	if (tag == Tag::eEnemyAttackDecision)
	{
		mIsHit = true;
	}
}

/// <summary>
/// 移動処理
/// </summary>
/// <param name="_owner"> プレイヤー(親)のポインタ </param>
/// <param name="_DeltaTime"> 最後のフレームを完了するのに要した時間 </param>
void PlayerObjectStateRunLoop::MoveCalc(PlayerObject* _owner, const float _DeltaTime)
{
	// カメラからみた前進方向を取得
	Vector3 targetPos = _owner->GetTargetPos();
	Vector3 cameraPos = _owner->GetCameraPos();

	mForwardVec = targetPos - cameraPos;
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

		// 現在のスピードを保存
		mCharaSpeed = MMoveSpeed * _DeltaTime;
	}

	// 座標
	Vector3 position = _owner->GetPosition();
	position += mCharaSpeed * mCharaForwardVec;

	// キャラの位置・スピード・変換行列の再計算の必要をセット
	_owner->SetPosition(position);
}