#include "pch.h"

WallObject::WallObject(const Vector3& _pos, const Vector3& _size, const std::string _gpmeshName, const Tag& _objectTag) :
	GameObject(_objectTag)
{
	//GameObjectメンバ変数の初期化
	SetScale(_size);
	SetPosition(_pos);

	//生成 TestObjectの生成時と同じくComponent基底クラスは自動で管理クラスに追加され自動で解放される
	mMeshComponentPtr = new MeshComponent(this);
	//Rendererクラス内のMesh読み込み関数を利用してMeshをセット(.gpmesh)
	mMeshComponentPtr->SetMesh(RENDERER->GetMesh(_gpmeshName));

	// 当たり判定
	mMeshPtr = new Mesh;
	mMeshPtr = RENDERER->GetMesh(_gpmeshName);
	mBoxColliderPtr = new BoxCollider(this, _objectTag, GetOnCollisionFunc());
	mBoxColliderPtr->SetObjectBox(mMeshPtr->GetBox());
}

WallObject::~WallObject()
{
}

void WallObject::UpdateGameObject(float _deltaTime)
{
	mBox = mBoxColliderPtr->GetWorldBox();
}