#include "pch.h"

/// <summary>
/// コンストラクタ
/// </summary>
PlayerObjectStateFirstAttack::PlayerObjectStateFirstAttack()
	: MBoxEnableTiming(15)
	, MBoxDisableTiming(16)
	, MDamageValueEnemyAttack(25)
	, MAttackSpeed(50.0f)
	, MPlayRate(1.8f)
	, MLeftAxisThreshold(0.5f)
	, MValidComboFrame(10)
	, mIsCollisionState(false)
	, mIsRotation(false)
	, mDamageValue(0)
	, mHitUntilCount(0)
    , mNumFrame(0)
	, mPosition(Vector3::Zero)
	, mMainCameraPtr(nullptr)
{
}

/// <summary>
/// 更新処理
/// </summary>
/// <param name="_owner"> プレイヤー(親)のポインタ </param>
/// <param name="_DeltaTime"> 最後のフレームを完了するのに要した時間 </param>
/// <returns> プレイヤーの状態 </returns>
PlayerState PlayerObjectStateFirstAttack::Update(PlayerObject* _owner, const float _DeltaTime)
{
	if (mIsHit)
	{
		return PlayerState::ePlayerStateDamage;
	}

	// アニメーションが終了したらアイドル状態か、次のコンボへ
	if (!_owner->GetSkeletalMeshComponentPtr()->IsPlaying())
	{
		if (mIsNextCombo)
		{
			return PlayerState::ePlayerStateSecondAttack;
		}

		return PlayerState::ePlayerStateIdle;
	}

	// 前方ベクトル
	Vector3 forwardVec = _owner->GetForward();
	if (mDirVec == Vector3::Zero)
	{
		mDirVec = forwardVec;
	}

	// 攻撃がヒットしたエネミーの群れの中心に向くベクトル
	Vector3 faceInFlockCenterVec = mFirstAttackEffect->GetFaceInFlockCenterVec();
	if (faceInFlockCenterVec != Vector3::Zero)
	{
		mDirVec = faceInFlockCenterVec;
	}

	mDirVec.Normalize();

	// 開始速度
	float startSpeed = MAttackSpeed * _DeltaTime;
	// 終了速度
	float endSpeed = -MAttackSpeed * _DeltaTime;

	// 攻撃踏み込み移動のためのアニメーション再生時間の経過割合を計算
	mElapseTime += _DeltaTime;
	// 経過割合をもとに移動処理
	mPosition += Quintic::EaseIn(mElapseTime, startSpeed, endSpeed, mTotalAnimTime) * mDirVec;

	_owner->SetPosition(mPosition);
	_owner->RotateToNewForward(mDirVec);

	// フレーム数を減らしていく
	if (mNumFrame > 0)
	{
		--mNumFrame;
	}

	++mHitUntilCount;

	if (mHitUntilCount == MBoxEnableTiming)
	{
		// 1段階目の通常攻撃の当たり判定を有効にする
		mIsCollisionState = true;
	}

	if (mHitUntilCount == MBoxDisableTiming)
	{
		// 1段階目の通常攻撃の当たり判定を無効にする
		mIsCollisionState = false;
	}

	return PlayerState::ePlayerStateFirstAttack;
}

/// <summary>
/// 入力処理
/// </summary>
/// <param name="_owner"> プレイヤー(親)のポインタ </param>
/// <param name="_KeyState"> キーボード、マウス、コントローラーの入力状態 </param>
void PlayerObjectStateFirstAttack::Input(PlayerObject* _owner, const InputState& _KeyState)
{
	if (mMainCameraPtr == nullptr)
	{
		return;
	}

	// カメラの座標
	Vector3 cameraPos = mMainCameraPtr->GetPosition();

	// カメラの前方ベクトル
	Vector3 cameraForwardVec = cameraPos - mPosition;
	cameraForwardVec.z = 0.0f;
	cameraForwardVec = Vector3::Normalize(cameraForwardVec);

	// 前方ベクトル
	Vector3 forwardVec = _owner->GetForward();
	forwardVec = Vector3::Normalize(forwardVec);

	Vector3 vec = Vector3::Cross(cameraForwardVec, forwardVec);
	float b = 0.0f;
	if (vec.z <= 0.0f)
	{
		float a = Vector3::Dot(cameraForwardVec, forwardVec);
		float angle = Math::Acos(a) * 180 / Math::Pi;
		b = 180.0f - angle;
	}
	else
	{
		b = 180.0f;
		Vector3 f = cameraForwardVec *= -1.0f;
		float a = Vector3::Dot(f, forwardVec);
		float angle = Math::Acos(a) * 180 / Math::Pi;
		float d = 180.0f - angle;
		b += d;
	}

	//方向キーが入力されたか
	mIsRotation = _KeyState.m_keyboard.GetKeyValue(SDL_SCANCODE_W) ||
		_KeyState.m_keyboard.GetKeyValue(SDL_SCANCODE_S) ||
		_KeyState.m_keyboard.GetKeyValue(SDL_SCANCODE_A) ||
		_KeyState.m_keyboard.GetKeyValue(SDL_SCANCODE_D) ||
		_KeyState.m_controller.GetButtonValue(SDL_CONTROLLER_BUTTON_DPAD_UP) ||
		_KeyState.m_controller.GetButtonValue(SDL_CONTROLLER_BUTTON_DPAD_DOWN) ||
		_KeyState.m_controller.GetButtonValue(SDL_CONTROLLER_BUTTON_DPAD_LEFT) ||
		_KeyState.m_controller.GetButtonValue(SDL_CONTROLLER_BUTTON_DPAD_RIGHT);

	// 右方ベクトル算出
	Vector3 rightVec = Vector3::Cross(Vector3::UnitZ, forwardVec);

	// コントローラーの十字上もしくはキーボード、Wが入力されたら回転する
	if (_KeyState.m_controller.GetButtonState(SDL_CONTROLLER_BUTTON_DPAD_UP) == Held ||
		_KeyState.m_keyboard.GetKeyState(SDL_SCANCODE_W) == Held)
	{
		//コントローラーの十字左もしくは、キーボードAが入力されたら回転する
		if (_KeyState.m_controller.GetButtonState(SDL_CONTROLLER_BUTTON_DPAD_LEFT) == Held ||
			_KeyState.m_keyboard.GetKeyState(SDL_SCANCODE_A) == Held)
		{
			if (b >= 135.0f && b < 315.0f)
			{
				mDirVec = forwardVec + rightVec * 0.05f;
			}
			else
			{
				mDirVec = forwardVec - rightVec * 0.05f;
			}

			return;
		}

		//コントローラーの十字左もしくは、キーボードAが入力されたら回転する
		if (_KeyState.m_controller.GetButtonState(SDL_CONTROLLER_BUTTON_DPAD_RIGHT) == Held ||
			_KeyState.m_keyboard.GetKeyState(SDL_SCANCODE_D) == Held)
		{
			if (b >= 45.0f && b < 225.0f)
			{
				mDirVec = forwardVec - rightVec * 0.05f;
			}
			else
			{
				mDirVec = forwardVec + rightVec * 0.05f;
			}

			return;
		}

		if (b >= 0.0f && b < 180.0f)
		{
			mDirVec = forwardVec - rightVec * 0.05f;
		}
		else
		{
			mDirVec = forwardVec + rightVec * 0.05f;
		}

		return;
	}

	// コントローラーの十字下もしくは、キーボードSが入力されたら回転する
	if (_KeyState.m_controller.GetButtonState(SDL_CONTROLLER_BUTTON_DPAD_DOWN) == Held ||
		_KeyState.m_keyboard.GetKeyState(SDL_SCANCODE_S) == Held)
	{
		//コントローラーの十字左もしくは、キーボードAが入力されたら回転する
		if (_KeyState.m_controller.GetButtonState(SDL_CONTROLLER_BUTTON_DPAD_LEFT) == Held ||
			_KeyState.m_keyboard.GetKeyState(SDL_SCANCODE_A) == Held)
		{
			if (b >= 45.0f && b < 225.0f)
			{
				mDirVec = forwardVec + rightVec * 0.05f;
			}
			else
			{
				mDirVec = forwardVec - rightVec * 0.05f;
			}

			return;
		}

		//コントローラーの十字左もしくは、キーボードAが入力されたら回転する
		if (_KeyState.m_controller.GetButtonState(SDL_CONTROLLER_BUTTON_DPAD_RIGHT) == Held ||
			_KeyState.m_keyboard.GetKeyState(SDL_SCANCODE_D) == Held)
		{
			if (b >= 135.0f && b < 315.0f)
			{
				mDirVec = forwardVec - rightVec * 0.05f;
			}
			else
			{
				mDirVec = forwardVec + rightVec * 0.05f;
			}

			return;
		}

		if (b >= 0.0f && b < 180.0f)
		{
			mDirVec = forwardVec + rightVec * 0.05f;
		}
		else
		{
			mDirVec = forwardVec - rightVec * 0.05f;
		}

		return;
	}

	//コントローラーの十字左もしくは、キーボードAが入力されたら回転する
	if (_KeyState.m_controller.GetButtonState(SDL_CONTROLLER_BUTTON_DPAD_LEFT) == Held ||
		_KeyState.m_keyboard.GetKeyState(SDL_SCANCODE_A) == Held)
	{
		if (b >= 90.0f && b < 270.0f)
		{
			mDirVec = forwardVec + rightVec * 0.05f;
		}
		else
		{
			mDirVec = forwardVec - rightVec * 0.05f;
		}

		return;
	}

	// コントローラーの十字右もしくは、キーボードDが入力されたら回転する
	if (_KeyState.m_controller.GetButtonState(SDL_CONTROLLER_BUTTON_DPAD_RIGHT) == Held ||
		_KeyState.m_keyboard.GetKeyState(SDL_SCANCODE_D) == Held)
	{
		if (b >= 90.0f && b < 270.0f)
		{
			mDirVec = forwardVec - rightVec * 0.05f;
		}
		else
		{
			mDirVec = forwardVec + rightVec * 0.05f;
		}

		return;
	}

	// 左スティックの入力値を取得
	Vector2 leftAxis = _KeyState.m_controller.GetLAxisVec();

	if (leftAxis.y <= -MLeftAxisThreshold)
	{
		if (leftAxis.x <= -MLeftAxisThreshold)
		{
			if (b >= 135.0f && b < 315.0f)
			{
				mDirVec = forwardVec + rightVec * 0.05f;
			}
			else
			{
				mDirVec = forwardVec - rightVec * 0.05f;
			}

			return;
		}

		if (leftAxis.x >= MLeftAxisThreshold)
		{
			if (b >= 45.0f && b < 225.0f)
			{
				mDirVec = forwardVec - rightVec * 0.05f;
			}
			else
			{
				mDirVec = forwardVec + rightVec * 0.05f;
			}

			return;
		}

		if (b >= 0.0f && b < 180.0f)
		{
			mDirVec = forwardVec - rightVec * 0.05f;
		}
		else
		{
			mDirVec = forwardVec + rightVec * 0.05f;
		}

		return;
	}

	if (leftAxis.y >= MLeftAxisThreshold)
	{
		if (leftAxis.x <= -MLeftAxisThreshold)
		{
			if (b >= 45.0f && b < 225.0f)
			{
				mDirVec = forwardVec + rightVec * 0.05f;
			}
			else
			{
				mDirVec = forwardVec - rightVec * 0.05f;
			}

			return;
		}

		if (leftAxis.x >= MLeftAxisThreshold)
		{
			if (b >= 135.0f && b < 315.0f)
			{
				mDirVec = forwardVec - rightVec * 0.05f;
			}
			else
			{
				mDirVec = forwardVec + rightVec * 0.05f;
			}

			return;
		}

		if (b >= 0.0f && b < 180.0f)
		{
			mDirVec = forwardVec + rightVec * 0.05f;
		}
		else
		{
			mDirVec = forwardVec - rightVec * 0.05f;
		}

		return;
	}

	//コントローラーの十字左もしくは、キーボードAが入力されたら回転する
	if (leftAxis.x <= -MLeftAxisThreshold)
	{
		if (b >= 90.0f && b < 270.0f)
		{
			mDirVec = forwardVec + rightVec * 0.05f;
		}
		else
		{
			mDirVec = forwardVec - rightVec * 0.05f;
		}

		return;
	}

	// コントローラーの十字右もしくは、キーボードDが入力されたら回転する
	if (leftAxis.x >= MLeftAxisThreshold)
	{
		if (b >= 90.0f && b < 270.0f)
		{
			mDirVec = forwardVec - rightVec * 0.05f;
		}
		else
		{
			mDirVec = forwardVec + rightVec * 0.05f;
		}

		return;
	}

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
void PlayerObjectStateFirstAttack::Enter(PlayerObject* _owner, const float _DeltaTime)
{
	// 1段階目の通常攻撃状態のアニメーション再生
	SkeletalMeshComponent* meshComp = _owner->GetSkeletalMeshComponentPtr();
	meshComp->PlayAnimation(_owner->GetAnimPtr(PlayerState::ePlayerStateFirstAttack), MPlayRate);
	mIsNextCombo = false;
	mIsHit = false;

	// アニメーション再生時間取得
	mTotalAnimTime = _owner->GetAnimPtr(PlayerState::ePlayerStateFirstAttack)->GetDuration();
	mNumFrame = _owner->GetAnimPtr(PlayerState::ePlayerStateDashAttack)->GetNumFrames();
	mElapseTime = 0.0f;
	mHitUntilCount = 0;

	mDirVec = Vector3::Zero;
	// 座標
	mPosition = _owner->GetPosition();
}

/// <summary>
/// ヒットした時の処理
/// </summary>
/// <param name="_owner"> プレイヤー(親)のポインタ </param>
/// <param name="_HitObject"> ヒットしたゲームオブジェクト </param>
void PlayerObjectStateFirstAttack::OnCollision(PlayerObject* _owner, const GameObject& _HitObject)
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