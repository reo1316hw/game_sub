#include "pch.h"

/// <summary>
/// コンストラクタ
/// </summary>
PlayerObjectStateSprintLoop::PlayerObjectStateSprintLoop()
	: MDamageValueEnemyAttack(25)
	, MMoveSpeed(500.0f)
	, MLeftAxisThreshold(0.5f)
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
PlayerState PlayerObjectStateSprintLoop::Update(PlayerObject* _owner, const float _DeltaTime)
{
	MoveCalc(_owner, _DeltaTime);

	if (mIsHit)
	{
		return PlayerState::ePlayerStateDamage;
	}

	//ボタンが押されていない時
	if (!mIsSprint)
	{
		return PlayerState::ePlayerStateRunLoop;
	}
	else
	{
		if (!mIsRun)
		{
			return PlayerState::ePlayerStateIdle;
		}
		else if (mIsAttack)
		{
			return PlayerState::ePlayerStateDashAttack;
		}
	}

	return PlayerState::ePlayerStateSprintLoop;
}

/// <summary>
/// 入力処理
/// </summary>
/// <param name="_owner"> プレイヤー(親)のポインタ </param>
/// <param name="_KeyState"> キーボード、マウス、コントローラーの入力状態 </param>
void PlayerObjectStateSprintLoop::Input(PlayerObject* _owner, const InputState& _KeyState)
{
	// 向きベクトルを初期化
	mDirVec = Vector3::Zero;

	//方向キーが入力されたか
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

	if (mleftAxis.LengthSq() >= MLeftAxisThreshold)
	{
		mIsRun = true;
	}

	//左Shiftキーが入力されたか
	mIsSprint = _KeyState.m_controller.GetButtonValue(SDL_CONTROLLER_BUTTON_RIGHTSHOULDER)||
		        _KeyState.m_keyboard.GetKeyValue(SDL_SCANCODE_LSHIFT);
	 
	//Spaceキーが入力されたか
	mIsAttack = _KeyState.m_controller.GetButtonValue(SDL_CONTROLLER_BUTTON_Y) ||
		        _KeyState.m_keyboard.GetKeyValue(SDL_SCANCODE_SPACE);
}

/// <summary>
/// プレイヤーの状態が変更して、最初に1回だけ呼び出される関数
/// </summary>
/// <param name="_owner"> プレイヤー(親)のポインタ </param>
/// <param name="_DeltaTime"> 最後のフレームを完了するのに要した時間 </param>
void PlayerObjectStateSprintLoop::Enter(PlayerObject* _owner, const float _DeltaTime)
{
	// 全力疾走状態のアニメーション再生
	SkeletalMeshComponent* meshcomp = _owner->GetSkeletalMeshComponentPtr();
	meshcomp->PlayAnimation(_owner->GetAnimPtr(PlayerState::ePlayerStateSprintLoop));
	mIsHit = false;

	// 座標
	mPosition = _owner->GetPosition();
}

/// <summary>
/// ヒットした時の処理
/// </summary>
/// <param name="_owner"> プレイヤー(親)のポインタ </param>
/// <param name="_HitObject"> ヒットしたゲームオブジェクト </param>
void PlayerObjectStateSprintLoop::OnCollision(PlayerObject* _owner, const GameObject& _HitObject)
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
void PlayerObjectStateSprintLoop::MoveCalc(PlayerObject* _owner, const float _DeltaTime)
{
	if (mMainCameraPtr == nullptr)
	{
		return;
	}

	// カメラの座標
	Vector3 cameraPos = mMainCameraPtr->GetPosition();

	// カメラ前方ベクトル
	mForwardVec = mPosition - cameraPos;
	// 高さ方向を無視
	mForwardVec.z = 0.0f;

	// カメラ前方ベクトルと右方向ベクトル算出
	mForwardVec = Vector3::Normalize(mForwardVec);
	mRightVec = Vector3::Cross(Vector3::UnitZ, mForwardVec);

	if (mleftAxis.LengthSq() >= MLeftAxisThreshold)
	{
		// カメラの向き基準による移動方向ベクトルを求める
		mDirVec = mForwardVec * -mleftAxis.y + mRightVec * mleftAxis.x;
	}
	
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
