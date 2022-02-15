#include "pch.h"

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="_playerPtr"> プレイヤーのポインタ </param>
/// <param name="_bossPtr"> ボスのポインタ </param>
/// <param name="_gateList"> 門のリスト </param>
/// <param name="_ReUseGameObject"> 再利用するかのフラグ </param>
MainCameraObject::MainCameraObject(PlayerObject* _playerPtr, BossObject* _bossPtr, std::vector<GateObject*> _gateList, const bool& _ReUseGameObject)
	: GameObject(Tag::eCamera, _ReUseGameObject)
	, MMinLookDownAngle(Math::ToRadians(0.0f))
	, MMaxLookDownAngle(Math::ToRadians(80.0f))
	, MRightAxisThreshold(0.3f)
	, MAddRotate(0.04f)
	, MCameraOffset(Vector3(-200.0f, -200.0f, -200.0f))
	, MTargetOffset(Vector3(0.0f, 0.0f, 70.0f))
	, mIsLookGate(false)
	, mIsInitOpenGate(true)
	, mGateListNum(1)
	, mRotateZAngle(Math::Pi)
	, mRotateYAngle(0.5f)
	, mTargetPos(Vector3::Zero)
	//, mNotLookGatePos(Vector3::Zero)
	//, mNotLookGateTargetPos(Vector3::Zero)
	, mInitPosition(Vector3::Zero)
	, mGatePos(Vector3::Zero)
	, mPlayerPtr(_playerPtr)
	, mBossPtr(_bossPtr)
	, mGateList(_gateList)
{
	for (auto gateItr : mGateList)
	{
		mOpenGateComponentList.emplace_back(gateItr->GetGateDoorPtr()->GetOpenGatePtr());
	}

	mTargetPos = mPlayerPtr->GetPosition() + MTargetOffset;
	SetPosition(mTargetPos);
}

/// <summary>
/// デストラクタ
/// </summary>
MainCameraObject::~MainCameraObject()
{
	mGateList.clear();
	mOpenGateComponentList.clear();
}

/// <summary>
/// オブジェクトの更新処理
/// </summary>
/// <param name="_deltaTime"> 最後のフレームを完了するのに要した時間 </param>
void MainCameraObject::UpdateGameObject(float _deltaTime)
{
	// プレイヤーかボスのhpが0以下だったら初期座標に戻す
	if (mPlayerPtr->GetHitPoint() <= 0 || mBossPtr->GetHitPoint() <= 0)
	{
		mPosition = mInitPosition;
		SetPosition(mPosition);

		return;
	}

	// プレイヤーの座標
	Vector3 playerPos = mPlayerPtr->GetPosition();

	// 門注目処理
	if (mOpenGateComponentList[mGateListNum]->GetIsOpen())
	{
		if (mIsInitOpenGate)
		{
			mIsLookGate = true;
			// 門の座標
			mGatePos = mGateList[mGateListNum]->GetPosition();

			mTargetPos = mGatePos + MTargetOffset;

			mIsInitOpenGate = false;
		}
		
		// カメラに向くベクトル
		Vector3 cameraToVec = mGatePos - playerPos;
		cameraToVec.Normalize();
		cameraToVec.z = -0.4f;

		mPosition = cameraToVec * MCameraOffset + playerPos;

		//mTargetPos = Vector3::Lerp(mTargetPos, mNotLookGateTargetPos, 0.05f);

		// 見たい座標を見る処理
		Matrix4 view = Matrix4::CreateLookAt(mPosition, mTargetPos, Vector3::UnitZ);
		RENDERER->SetViewMatrix(view);
		SetPosition(mPosition);

		//// 補間中の座標
		//Vector3 lerpPos = Vector3::Lerp(mPosition, mNotLookGatePos, 0.1f);

		//// 見たい座標を見る処理
		//Matrix4 view = Matrix4::CreateLookAt(lerpPos, mTargetPos, Vector3::UnitZ);
		//RENDERER->SetViewMatrix(view);
		//SetPosition(lerpPos);

		return;
	}

	// 最初の門が完全に開いたら、次の門を対象にするために番号を1ずらす
	if (mIsLookGate && mGateListNum >= 1)
	{
		--mGateListNum;
	}

	// この行まで実行されたら門に注目していないのでフラグを戻す
	mIsLookGate = false;
	mIsInitOpenGate = true;

	mTargetPos = playerPos + MTargetOffset;
	//mNotLookGateTargetPos = mTargetPos;

	// 見降ろし角度の角度制限
	if (mRotateYAngle < MMinLookDownAngle)
	{
		mRotateYAngle = MMinLookDownAngle;
	}
	if (mRotateYAngle > MMaxLookDownAngle)
	{
		mRotateYAngle = MMaxLookDownAngle;
	}

	// 回転後の座標
	Vector3 rotatePos;

	// ヨー回転・ピッチ回転
	rotatePos.x = MCameraOffset.x * cosf(mRotateYAngle) * sinf(mRotateZAngle);
	rotatePos.y = MCameraOffset.y * cosf(mRotateYAngle) * cosf(mRotateZAngle);
	rotatePos.z = MCameraOffset.z * sinf(-mRotateYAngle);

	mPosition = rotatePos + mTargetPos;
	//mNotLookGatePos = mPosition;

	// 見たい座標を見る処理
	Matrix4 view = Matrix4::CreateLookAt(mPosition, mTargetPos, Vector3::UnitZ);
	RENDERER->SetViewMatrix(view);
	SetPosition(mPosition);
}

/// <summary>
/// 入力を引数で受け取る更新関数
/// 基本的にここで入力情報を変数に保存しUpdateGameObjectで更新を行う
/// </summary>
/// <param name="_KeyState"> キーボード、マウス、コントローラーの入力状態 </param>
void MainCameraObject::GameObjectInput(const InputState& _KeyState)
{
	if (mOpenGateComponentList[mGateListNum]->GetIsOpen())
	{
		return;
	}

	//右スティックの入力値の値(-1~1)
	Vector2 rightAxis = _KeyState.m_controller.GetRAxisVec();

	// コントローラーの十字上もしくはキーボード、Wが入力されたらzを足す
	if (_KeyState.m_keyboard.GetKeyState(SDL_SCANCODE_UP) == Held)
	{
		mRotateYAngle -= MAddRotate;
	}
	// コントローラーの十字下もしくは、キーボードSが入力されたら-zを足す
	if (_KeyState.m_keyboard.GetKeyState(SDL_SCANCODE_DOWN) == Held)
	{
		mRotateYAngle += MAddRotate;
	}
	//コントローラーの十字左もしくは、キーボードAが入力されたら-xを足す
	if (_KeyState.m_keyboard.GetKeyState(SDL_SCANCODE_LEFT) == Held)
	{
		mRotateZAngle += MAddRotate;
	}
	// コントローラーの十字右もしくは、キーボードDが入力されたらxを足す
	if (_KeyState.m_keyboard.GetKeyState(SDL_SCANCODE_RIGHT) == Held)
	{
		mRotateZAngle -= MAddRotate;
	}

	//右スティック入力時の前移動
	if (rightAxis.y <= -MRightAxisThreshold)
	{
		mRotateYAngle -= MAddRotate;
	}
	//右スティック入力時の後移動
	if (rightAxis.y >= MRightAxisThreshold)
	{
		mRotateYAngle += MAddRotate;
	}
	//右スティック入力時の左移動
	if (rightAxis.x <= -MRightAxisThreshold)
	{
		mRotateZAngle += MAddRotate;
	}
	//右スティック入力時の右移動
	if (rightAxis.x >= MRightAxisThreshold)
	{
		mRotateZAngle -= MAddRotate;
	}
}