#include "pch.h"

/// <summary>
/// コンストラクタ
/// </summary>
MainCameraObject::MainCameraObject() 
	: GameObject(Tag::eCamera,SceneBase::Scene::other,true)
	, MMinLookDownAngle(Math::ToRadians(0.0f))
	, MMaxLookDownAngle(Math::ToRadians(80.0f))
	, MRightAxisThreshold(0.3f)
	, MAddRotate(0.04f)
	, mHasTarget(false)
	, mRotateZAngle(Math::Pi)
	, mRotateYAngle(0.0f)
	, mOwnerOffset(Vector3::Zero)
	, mTargetPos(Vector3::Zero)
{
	SetPosition(Vector3(0,0,0));
	mTag = Tag::eCamera;
}

/// <summary>
/// オブジェクトの更新処理
/// </summary>
/// <param name="_deltaTime"> 最後のフレームを完了するのに要した時間 </param>
void MainCameraObject::UpdateGameObject(float _deltaTime)
{
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
	rotatePos.x = mOwnerOffset.x * cosf(mRotateYAngle) * sinf(mRotateZAngle);
	rotatePos.y = mOwnerOffset.y * cosf(mRotateYAngle) * cosf(mRotateZAngle);
	rotatePos.z = mOwnerOffset.z * sinf(-mRotateYAngle);

	mPosition = rotatePos + mTargetPos;

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

/// <summary>
/// 見たい座標を設定
/// </summary>
/// <param name="_Offset"> 見たい座標との差 </param>
/// <param name="_TargetPos"> 見る座標 </param>
void MainCameraObject::SetViewObject(const Vector3 & _Offset, const Vector3 & _TargetPos)
{
	mHasTarget = true;
	mOwnerOffset = _Offset;
	mTargetPos = _TargetPos;
}
