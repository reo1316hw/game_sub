#include "pch.h"

MainCameraObject::MainCameraObject() 
	: GameObject(Tag::Camera,SceneBase::Scene::other,true)
	, mRotateYAngle(Math::Pi)
	, mLookDownAngle(maxLookDownAngle)
{
	SetPosition(Vector3(0,0,0));
	mTag = Tag::Camera;
}

MainCameraObject::~MainCameraObject()
{
}

void MainCameraObject::UpdateGameObject(float _deltaTime)
{
	/*Vector3 pos = offsetPos + mPosition;
	pos.x = mLerpObject.x + offsetPos.x;
	pos.y = mLerpObject.y + offsetPos.y;
	pos.z = mLerpObject.z + offsetPos.z;
	mPosition = pos;*/
	//mPosition = Vector3::Lerp(mPosition, pos, _deltaTime * 3.0f);
	//Vector3 aa = mPosition;
	//aa.z = 0;

	// 見降ろし角度の角度制限
	if (mLookDownAngle < minLookDownAngle)
	{
		mLookDownAngle = minLookDownAngle;
	}
	if (mLookDownAngle > maxLookDownAngle)
	{
		mLookDownAngle = maxLookDownAngle;
	}

	// ヨー回転・ピッチ回転
	Vector3 rotatePos;
	float distance = -150.0f;
	rotatePos.x = distance * cosf(mLookDownAngle) * sinf(mRotateYAngle);
	rotatePos.y = distance * cosf(mLookDownAngle) * cosf(mRotateYAngle);
	rotatePos.z = distance * sinf(-mLookDownAngle);

	mPosition = rotatePos + mLerpObject;

	Matrix4 view = Matrix4::CreateLookAt(mPosition, mLerpObject, Vector3::UnitZ);
	RENDERER->SetViewMatrix(view);
	SetPosition(mPosition);

	/*float radian = Math::ToRadians(angle);
	Quaternion rot = this->GetRotation();
	Quaternion inc(Vector3::UnitZ, radian);
	Quaternion target = Quaternion::Concatenate(rot, inc);
	SetRotation(target);*/
}

void MainCameraObject::GameObjectInput(const InputState& _keyState)
{
	const float rotate = 0.03f;
	// コントローラーの十字上もしくはキーボード、Wが入力されたらzを足す
	if (_keyState.m_keyboard.GetKeyValue(SDL_SCANCODE_UP) == 1)
	{
		mLookDownAngle += rotate;
	}
	// コントローラーの十字下もしくは、キーボードSが入力されたら-zを足す
	if (_keyState.m_keyboard.GetKeyValue(SDL_SCANCODE_DOWN) == 1)
	{
		mLookDownAngle -= rotate;
	}
	//コントローラーの十字左もしくは、キーボードAが入力されたら-xを足す
	if (_keyState.m_keyboard.GetKeyValue(SDL_SCANCODE_LEFT) == 1)
	{
		mRotateYAngle += rotate;
	}
	// コントローラーの十字右もしくは、キーボードDが入力されたらxを足す
	if (_keyState.m_keyboard.GetKeyValue(SDL_SCANCODE_RIGHT) == 1)
	{
		mRotateYAngle -= rotate;
	}
}

/*
@param _offset　見たい座標との差
@param _parentPos　見る座標
*/
void MainCameraObject::SetViewMatrixLerpObject(const Vector3 & _offset, const Vector3 & _parentPos)
{
	mHasParentObject = true;
	mOffsetPos = _offset;
	mLerpObject = _parentPos;
}
