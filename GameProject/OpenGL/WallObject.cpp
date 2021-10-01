#include "pch.h"

WallObject::WallObject(const Vector3& _pos, const Vector3& _size, const std::string _gpmeshName, const Tag& _objectTag, const SceneBase::Scene _sceneTag) :
	GameObject(_objectTag,_sceneTag)
{
	//GameObjectメンバ変数の初期化
	mTag = _objectTag;
	SetScale(_size);
	SetPosition(_pos);

	switch (_sceneTag)
	{
	case SceneBase::Scene::tutorial:

		//生成 TestObjectの生成時と同じくComponent基底クラスは自動で管理クラスに追加され自動で解放される
		mMeshComponent = new MeshComponent(this);
		//Rendererクラス内のMesh読み込み関数を利用してMeshをセット(.gpmesh)
		mMeshComponent->SetMesh(RENDERER->GetMesh(_gpmeshName));

		// 当たり判定
		mMesh = new Mesh;
		mMesh = RENDERER->GetMesh(_gpmeshName);
		mBoxCollider = new BoxCollider(this, ColliderTag::Wall, GetOnCollisionFunc());
		mBoxCollider->SetObjectBox(mMesh->GetBox());

		break;
	}
}

WallObject::~WallObject()
{
}

void WallObject::UpdateGameObject(float _deltaTime)
{
	mAabb = mBoxCollider->GetWorldBox();
}