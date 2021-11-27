#include "pch.h"

/// <summary>
/// コンストラクタ
/// </summary>
PlayerObjectStateRunLoop::PlayerObjectStateRunLoop()
	: mHitTagList{ Tag::eEnemyAttackDecision, Tag::eFrontCoreMagicEffect, Tag::eAreaMagicEffect, Tag::eOverheadMagicEffect }
	, mDamageValueList{ 5, 10, 20, 15 }
	, MMoveSpeed(300.0f)
	, MLeftAxisThreshold(0.5f)
	, mIsDamage(false)
	, mDamageValue(0)
	, mHitTagListSize(sizeof(mHitTagList) / sizeof(int))
	, mHitTag(Tag::eOther)
	, mPlayerPtr(nullptr)
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
	if (mIsDamage)
	{
	    return PlayerState::ePlayerStateDamage;
	}

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

	MoveCalc(_owner, _DeltaTime);

	return PlayerState::ePlayerStateRunLoop;
}

/// <summary>
/// 入力処理
/// </summary>
/// <param name="_owner"> プレイヤー(親)のポインタ </param>
/// <param name="_KeyState"> キーボード、マウス、コントローラーの入力状態 </param>
void PlayerObjectStateRunLoop::Input(PlayerObject* _owner, const InputState& _KeyState)
{
	if (mMainCameraPtr == nullptr)
	{
		return;
	}

	// 向きベクトルを初期化
	mDirVec = Vector3::Zero;

	// カメラの座標
	Vector3 cameraPos = mMainCameraPtr->GetPosition();

	// カメラの前方ベクトル
	Vector3 cameraForwardVec = mPosition - cameraPos;
	// 高さ方向を無視
	cameraForwardVec.z = 0.0f;
	cameraForwardVec = Vector3::Normalize(cameraForwardVec);

	// カメラの右方ベクトル算出
	Vector3 cameraRightVec = Vector3::Cross(Vector3::UnitZ, cameraForwardVec);

	// 方向キーが入力されたか
	mIsRun = _KeyState.m_keyboard.GetKeyValue(SDL_SCANCODE_W) ||
		     _KeyState.m_keyboard.GetKeyValue(SDL_SCANCODE_S) ||
		     _KeyState.m_keyboard.GetKeyValue(SDL_SCANCODE_A) ||
		     _KeyState.m_keyboard.GetKeyValue(SDL_SCANCODE_D) ||
		     _KeyState.m_controller.GetButtonValue(SDL_CONTROLLER_BUTTON_DPAD_UP)   ||
		     _KeyState.m_controller.GetButtonValue(SDL_CONTROLLER_BUTTON_DPAD_DOWN) ||
		     _KeyState.m_controller.GetButtonValue(SDL_CONTROLLER_BUTTON_DPAD_LEFT) ||
	         _KeyState.m_controller.GetButtonValue(SDL_CONTROLLER_BUTTON_DPAD_RIGHT);

	// コントローラーの十字上もしくはキーボード、Wが入力されたらzを足す
	if (_KeyState.m_controller.GetButtonState(SDL_CONTROLLER_BUTTON_DPAD_UP) == Held ||
		_KeyState.m_keyboard.GetKeyState(SDL_SCANCODE_W) == Held)
	{
		mDirVec += cameraForwardVec;
	}
	// コントローラーの十字下もしくは、キーボードSが入力されたら-zを足す
	else if (_KeyState.m_controller.GetButtonState(SDL_CONTROLLER_BUTTON_DPAD_DOWN) == Held ||
		_KeyState.m_keyboard.GetKeyState(SDL_SCANCODE_S) == Held)
	{
		mDirVec -= cameraForwardVec;
	}

	// コントローラーの十字左もしくは、キーボードAが入力されたら-xを足す
	if (_KeyState.m_controller.GetButtonState(SDL_CONTROLLER_BUTTON_DPAD_LEFT) == Held ||
		_KeyState.m_keyboard.GetKeyState(SDL_SCANCODE_A) == Held)
	{
		mDirVec -= cameraRightVec;
	}
	// コントローラーの十字右もしくは、キーボードDが入力されたらxを足す
	else if (_KeyState.m_controller.GetButtonState(SDL_CONTROLLER_BUTTON_DPAD_RIGHT) == Held ||
		_KeyState.m_keyboard.GetKeyState(SDL_SCANCODE_D) == Held)
	{
		mDirVec += cameraRightVec;
	}

	// 左スティックの入力値を取得
	Vector2 leftAxis = _KeyState.m_controller.GetLAxisVec();

	if (leftAxis.LengthSq() >= MLeftAxisThreshold)
	{
		mIsRun = true;

		// カメラの向き基準による移動方向ベクトルを求める
		mDirVec = cameraForwardVec * -leftAxis.y + cameraRightVec * leftAxis.x;
	}

	// 左Shiftキーが入力されたか
	mIsSprint = _KeyState.m_controller.GetButtonValue(SDL_CONTROLLER_BUTTON_RIGHTSHOULDER) ||
		        _KeyState.m_keyboard.GetKeyValue(SDL_SCANCODE_LSHIFT);

	// Spaceキーが入力されたか
	mIsAttack = _KeyState.m_controller.GetButtonValue(SDL_CONTROLLER_BUTTON_Y) ||
		        _KeyState.m_keyboard.GetKeyValue(SDL_SCANCODE_SPACE);
}

/// <summary>
/// プレイヤーの状態が変更して、最初に1回だけ呼び出される関数
/// </summary>
/// <param name="_owner"> プレイヤー(親)のポインタ </param>
/// <param name="_DeltaTime"> 最後のフレームを完了するのに要した時間 </param>
void PlayerObjectStateRunLoop::Enter(PlayerObject* _owner, const float _DeltaTime)
{
	// 走り状態のアニメーション再生
    SkeletalMeshComponent* meshcomp = _owner->GetSkeletalMeshComponentPtr();
	meshcomp->PlayAnimation(_owner->GetAnimPtr(PlayerState::ePlayerStateRunLoop));
	mIsDamage = false;

	// 座標
	mPosition = _owner->GetPosition();
}

/// <summary>
/// ヒットした時の処理
/// </summary>
/// <param name="_owner"> プレイヤー(親)のポインタ </param>
/// <param name="_HitObject"> ヒットしたゲームオブジェクト </param>
void PlayerObjectStateRunLoop::OnCollision(PlayerObject* _owner, const GameObject& _HitObject)
{
	mPlayerPtr = _owner;

	// オブジェクトのタグ
	mHitTag = _HitObject.GetTag();

	for (int i = 0; i < mHitTagListSize; i++)
	{
		// 攻撃を受けた時の処理
		if (ReceivedAttack(mHitTagList[i], mDamageValueList[i]))
		{
			return;
		}
	}
}

/// <summary>
/// 攻撃を受けた時の処理
/// </summary>
/// <param name="_HitTag"> ヒットしたオブジェクトのタグ </param>
/// <param name="_DamageValuePlayerAttack"> ダメージ量 </param>
/// <returns> ヒットしたか </returns>
bool PlayerObjectStateRunLoop::ReceivedAttack(const Tag& _hitTag, const int& _DamageValuePlayerAttack)
{
	if (mHitTag == _hitTag)
	{
		mDamageValue = _DamageValuePlayerAttack;
		mIsDamage = true;

		mPlayerPtr->SetDamageValue(mDamageValue);
		return true;
	}

	return false;
}

/// <summary>
/// 移動処理
/// </summary>
/// <param name="_owner"> プレイヤー(親)のポインタ </param>
/// <param name="_DeltaTime"> 最後のフレームを完了するのに要した時間 </param>
void PlayerObjectStateRunLoop::MoveCalc(PlayerObject* _owner, const float _DeltaTime)
{	
	if (mDirVec == Vector3::Zero)
	{
		return;
	}

	// 速度を初期化
	mCharaSpeed = 0.0f;

	// 方向キー入力
	mCharaForwardVec = mDirVec;

	// 進行方向に向けて回転
	mCharaForwardVec.Normalize();
	_owner->RotateToNewForward(mCharaForwardVec);

	// 現在のスピードを保存
	mCharaSpeed = MMoveSpeed * _DeltaTime;

	mPosition += mCharaSpeed * mCharaForwardVec;

	// キャラの位置・スピード・変換行列の再計算の必要をセット
	_owner->SetPosition(mPosition);
}