#include "pch.h"

/// <summary>
/// コンストラクタ
/// </summary>
PlayerObjectStateFirstAttack::PlayerObjectStateFirstAttack()
	: faceAngleList{0.0f, 45.0f, 90.0f, 135.0f, 180.0f, 225.0f, 270.0f, 315.0f}
	, MBoxEnableTiming(15)
	, MBoxDisableTiming(16)
	, MDamageValueEnemyAttack(25)
	, MHalfRotation(180)
	, MValidComboFrame(10)
	, MAttackSpeed(50.0f)
	, MPlayRate(1.8f)
	, MLeftAxisThreshold(0.5f)
	, MValueShortenVector(0.05f)
	, mIsCollisionState(false)
	, mIsRotation(false)
	, mDamageValue(0)
	, mHitUntilCount(0)
	, mTwoVectorAngle(0.0f)
    , mNumFrame(0)
	, mLeftAxis(Vector2::Zero)
	, mPosition(Vector3::Zero)
	, mForwardVec(Vector3::Zero)
	, mRightVec(Vector3::Zero)
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

	// 向きの情報がなかったら前方ベクトルにする
	if (mDirVec == Vector3::Zero)
	{
		mDirVec = mForwardVec;
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
	mForwardVec = _owner->GetForward();
	mForwardVec = Vector3::Normalize(mForwardVec);
	// 右方ベクトル算出
	mRightVec = Vector3::Cross(Vector3::UnitZ, mForwardVec);

	// カメラとプレイヤーの前方ベクトルの外積
	Vector3 outerProduct = Vector3::Cross(cameraForwardVec, mForwardVec);

	if (outerProduct.z <= 0.0f)
	{
		float a = Vector3::Dot(cameraForwardVec, mForwardVec);
		mTwoVectorAngle = Math::Acos(a) * MHalfRotation / Math::Pi;
		mTwoVectorAngle = MHalfRotation - mTwoVectorAngle;
	}
	else
	{
		float b = 180.0f;
		Vector3 f = cameraForwardVec *= -1.0f;
		float a = Vector3::Dot(f, mForwardVec);
		mTwoVectorAngle = Math::Acos(a) * MHalfRotation / Math::Pi;
		mTwoVectorAngle = MHalfRotation - mTwoVectorAngle;
		mTwoVectorAngle += b;
	}

	// 攻撃ボタン押されたら次のステートへ移行する準備
	if (mNumFrame <= MValidComboFrame && _KeyState.m_controller.GetButtonState(SDL_CONTROLLER_BUTTON_Y) == Released ||
		mNumFrame <= MValidComboFrame && _KeyState.m_keyboard.GetKeyState(SDL_SCANCODE_SPACE) == Released)
	{
		mIsNextCombo = true;
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

	// コントローラーの十字上もしくはキーボードWが入力されたら回転する
	if (VerticalKeyInputOperation(_KeyState, SDL_SCANCODE_W, SDL_CONTROLLER_BUTTON_DPAD_UP,
		faceAngleList[static_cast<int>(FaceAngleType::eDownRight)], faceAngleList[static_cast<int>(FaceAngleType::eUpLeft)],
		faceAngleList[static_cast<int>(FaceAngleType::eUpRight)], faceAngleList[static_cast<int>(FaceAngleType::eDownLeft)],
		MValueShortenVector))
	{
		return;
	}

	// コントローラーの十字下もしくはキーボードSが入力されたら回転する
	if (VerticalKeyInputOperation(_KeyState, SDL_SCANCODE_S, SDL_CONTROLLER_BUTTON_DPAD_DOWN,
		faceAngleList[static_cast<int>(FaceAngleType::eUpRight)], faceAngleList[static_cast<int>(FaceAngleType::eDownLeft)],
		faceAngleList[static_cast<int>(FaceAngleType::eDownRight)], faceAngleList[static_cast<int>(FaceAngleType::eUpLeft)],
		-MValueShortenVector))
	{
		return;
	}

	// コントローラーの十字左もしくはキーボードAが入力されたら回転する
	if (LateralKeyInputOperation(_KeyState, SDL_SCANCODE_A, SDL_CONTROLLER_BUTTON_DPAD_LEFT,
		faceAngleList[static_cast<int>(FaceAngleType::eRight)], faceAngleList[static_cast<int>(FaceAngleType::eLeft)],
		MValueShortenVector))
	{
		return;
	}

	// コントローラーの十字左もしくはキーボードDが入力されたら回転する
	if (LateralKeyInputOperation(_KeyState, SDL_SCANCODE_D, SDL_CONTROLLER_BUTTON_DPAD_RIGHT,
		faceAngleList[static_cast<int>(FaceAngleType::eRight)], faceAngleList[static_cast<int>(FaceAngleType::eLeft)],
		-MValueShortenVector))
	{
		return;
	}
	
	// 左スティックの入力値を取得
	mLeftAxis = _KeyState.m_controller.GetLAxisVec();

	if (mLeftAxis.y <= MLeftAxisThreshold && mLeftAxis.y >= -MLeftAxisThreshold &&
		mLeftAxis.x <= MLeftAxisThreshold && mLeftAxis.x >= -MLeftAxisThreshold ||
		mLeftAxis.y == 0.0f && mLeftAxis.x == 0.0f)
	{
		return;
	}

	// 左スティックを上に倒したら前に向かって回転する
	if (mLeftAxis.y < 0.0f)
	{
		// 左スティックを左に倒したら左前に向かって回転する
		if(LeftStickDefeatLeftInputOperation(faceAngleList[static_cast<int>(FaceAngleType::eDownRight)],
			faceAngleList[static_cast<int>(FaceAngleType::eUpLeft)], MValueShortenVector))
		{
			return;
		}

		// 左スティックを右に倒したら右前に向かって回転する
		if (LeftStickDefeatRightInputOperation(faceAngleList[static_cast<int>(FaceAngleType::eUpRight)],
			faceAngleList[static_cast<int>(FaceAngleType::eDownLeft)], -MValueShortenVector))
		{
			return;
		}

		// 前に向かって回転する
		RotateInRangeAngle(faceAngleList[static_cast<int>(FaceAngleType::eUp)],
			faceAngleList[static_cast<int>(FaceAngleType::eDown)], -MValueShortenVector);

		return;
	}

	// 左スティックを下に倒したら後ろに向かって回転する
	if (mLeftAxis.y > 0.0f)
	{
		// 左スティックを左に倒したら左後ろに向かって回転する
		if (LeftStickDefeatLeftInputOperation(faceAngleList[static_cast<int>(FaceAngleType::eUpRight)],
			faceAngleList[static_cast<int>(FaceAngleType::eDownLeft)], MValueShortenVector))
		{
			return;
		}

		// 左スティックを右に倒したら右後ろに向かって回転する
		if (LeftStickDefeatRightInputOperation(faceAngleList[static_cast<int>(FaceAngleType::eDownRight)],
			faceAngleList[static_cast<int>(FaceAngleType::eUpLeft)], -MValueShortenVector))
		{
			return;
		}

		// 後ろに向かって回転する
		RotateInRangeAngle(faceAngleList[static_cast<int>(FaceAngleType::eUp)],
			faceAngleList[static_cast<int>(FaceAngleType::eDown)], MValueShortenVector);

		return;
	}

	// 左スティックを左に倒したら左に向かって回転する
	if (LeftStickDefeatLeftInputOperation(faceAngleList[static_cast<int>(FaceAngleType::eRight)],
		faceAngleList[static_cast<int>(FaceAngleType::eLeft)], MValueShortenVector))
	{
		return;
	}

	// 左スティックを右に倒したら右に向かって回転する
	if (LeftStickDefeatRightInputOperation(faceAngleList[static_cast<int>(FaceAngleType::eRight)],
		faceAngleList[static_cast<int>(FaceAngleType::eLeft)], -MValueShortenVector))
	{
		return;
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

/// <summary>
/// 縦キー入力操作
/// </summary>
/// <param name="_KeyState"> キーボード、マウス、コントローラーの入力状態 </param>
/// <param name="_KeyScancode"> 何キーを押したか </param>
/// <param name="_ButtonScancode"> 何ボタンを押したか </param>
/// <returns> true : 何か押した, false : 何も押さなかった </returns>
bool PlayerObjectStateFirstAttack::VerticalKeyInputOperation(const InputState& _KeyState, const SDL_Scancode& _KeyScancode, const SDL_GameControllerButton& _ButtonScancode,
	const float& _AngleBorderMinAKey, const float& _AngleBorderMaxAKey, const float& _AngleBorderMinDKey, const float& _AngleBorderMaxDKey, const float& _ValueShortenVector)
{
	if (_KeyState.m_controller.GetButtonState(_ButtonScancode) == Held ||
		_KeyState.m_keyboard.GetKeyState(_KeyScancode) == Held)
	{
		// コントローラーの十字左もしくはキーボードAが入力されたら回転する
		if (LateralKeyInputOperation(_KeyState, SDL_SCANCODE_A,
			SDL_CONTROLLER_BUTTON_DPAD_LEFT, _AngleBorderMinAKey, _AngleBorderMaxAKey, MValueShortenVector))
		{
			return true;
		}

		// コントローラーの十字左もしくはキーボードDが入力されたら回転する
		if (LateralKeyInputOperation(_KeyState, SDL_SCANCODE_D,
			SDL_CONTROLLER_BUTTON_DPAD_RIGHT, _AngleBorderMinDKey, _AngleBorderMaxDKey, -MValueShortenVector))
		{
			return true;
		}

		RotateInRangeAngle(faceAngleList[static_cast<int>(FaceAngleType::eUp)],
			faceAngleList[static_cast<int>(FaceAngleType::eDown)], -_ValueShortenVector);

		return true;
	}

	return false;
}

/// <summary>
/// 横キー入力操作
/// </summary>
/// <param name="_KeyState"> キーボード、マウス、コントローラーの入力状態 </param>
/// <param name="_KeyScancode"> 何キーを押したか </param>
/// <param name="_ButtonScancode"> 何ボタンを押したか </param>
/// <param name="_AngleBorderMin"> 境目の角度の最小値 </param>
/// <param name="_AngleBorderMax"> 境目の角度の最大値 </param>
/// <returns> true : 何か押した, false : 何も押さなかった </returns>
bool PlayerObjectStateFirstAttack::LateralKeyInputOperation(const InputState& _KeyState, const SDL_Scancode& _KeyScancode,
	const SDL_GameControllerButton& _ButtonScancode, const float& _AngleBorderMin, const float& _AngleBorderMax, const float& _ValueShortenVector)
{
	//コントローラーの十字左もしくは、キーボードAが入力されたら回転する
	if (_KeyState.m_controller.GetButtonState(_ButtonScancode) == Held ||
		_KeyState.m_keyboard.GetKeyState(_KeyScancode) == Held)
	{
		RotateInRangeAngle(_AngleBorderMin, _AngleBorderMax, _ValueShortenVector);

		return true;
	}

	return false;
}

/// <summary>
/// 左スティックを左に倒したときの操作
/// </summary>
/// <param name="_AngleBorderMin"> 境目の角度の最小値 </param>
/// <param name="_AngleBorderMax"> 境目の角度の最大値 </param>
/// <param name="_ValueShortenVector"></param>
/// <returns> true : スティックを倒した, false : スティックを倒さなかった </returns>
bool PlayerObjectStateFirstAttack::LeftStickDefeatLeftInputOperation(const float& _AngleBorderMin, const float& _AngleBorderMax, const float& _ValueShortenVector)
{
	if (mLeftAxis.x < 0.0f)
	{
		RotateInRangeAngle(_AngleBorderMin, _AngleBorderMax, _ValueShortenVector);

		return true;
	}

	return false;
}

/// <summary>
/// 左スティックを右に倒したときの操作
/// </summary>
/// <param name="_AngleBorderMin"> 境目の角度の最小値 </param>
/// <param name="_AngleBorderMax"> 境目の角度の最大値 </param>
/// <param name="_ValueShortenVector"> ベクトルを短くする値 </param>
/// <returns> true : スティックを倒した, false : スティックを倒さなかった </returns>
bool PlayerObjectStateFirstAttack::LeftStickDefeatRightInputOperation(const float& _AngleBorderMin, const float& _AngleBorderMax, const float& _ValueShortenVector)
{
	if (mLeftAxis.x > 0.0f)
	{
		RotateInRangeAngle(_AngleBorderMin, _AngleBorderMax, _ValueShortenVector);

		return true;
	}

	return false;
}

/// <summary>
/// 範囲角度で回転させる
/// </summary>
/// <param name="_AngleBorderMin"> 境目の角度の最小値 </param>
/// <param name="_AngleBorderMax"> 境目の角度の最大値 </param>
/// <param name="_ValueShortenVector"> ベクトルを短くする値 </param>
void PlayerObjectStateFirstAttack::RotateInRangeAngle(const float& _AngleBorderMin, const float& _AngleBorderMax, const float& _ValueShortenVector)
{
	if (mTwoVectorAngle >= _AngleBorderMin && mTwoVectorAngle < _AngleBorderMax)
	{
		mDirVec = mForwardVec + mRightVec * _ValueShortenVector;
	}
	else
	{
		mDirVec = mForwardVec + mRightVec * -_ValueShortenVector;
	}
}