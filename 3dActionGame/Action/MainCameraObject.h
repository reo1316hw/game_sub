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

	/*
	@param _offset　見たい座標との差
	@param _parentPos　見る座標
	*/
	void SetViewMatrixLerpObject(const Vector3& _offset, const Vector3& _parentPos);
private:
	//親オブジェクトとの差
	Vector3 mOffsetPos;
	//追従先のオブジェクト座標
	Vector3 mLerpObject;               
	//追従先のオブジェクトを所持しているか
	bool mHasParentObject;
};

