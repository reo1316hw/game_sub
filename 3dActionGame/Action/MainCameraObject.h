#pragma once
#include "GameObject.h"

/*
@file MainCameraObject.h
@brief メインカメラ。GameObjectの静的オブジェクト カメラと衝突していないオブジェクトは更新を一時的に停止する
*/
class MainCameraObject :
	public GameObject
{
public:
	MainCameraObject();
	~MainCameraObject();

	//このクラスはポーズ中に別クラスから更新関数を呼ばれることがある
	void UpdateGameObject(float _deltaTime = 1.0f)override;
	void GameObjectInput(const InputState& _keyState)override;

	/*
	@param _offset　見たい座標との差
	@param _parentPos　見る座標
	*/
	void SetViewMatrixLerpObject(const Vector3& _offset, const Vector3& _parentPos);
private:
	//親オブジェクトとの差
	Vector3 offsetPos;
	//追従先のオブジェクト座標
	Vector3 lerpObject;
	//追従先のオブジェクトを所持しているか
	bool hasParentObject;

	float angle;
      
	// カメラ周囲回転方向回転角
	float mRotateYAngle;
	// カメラ見降ろし方向回転角
	float mLookDownAngle;


	// 最大仰角
	const float maxLookDownAngle = Math::ToRadians(80.0f);
	// 最小仰角
	const float minLookDownAngle = Math::ToRadians(0.0f);
};

