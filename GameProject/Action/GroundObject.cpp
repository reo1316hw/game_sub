#include "GroundObject.h"
#include "MeshComponent.h"
#include "Mesh.h"
#include "Renderer.h"
#include "BoxCollider.h"

GroundObject::GroundObject(const Vector3& _pos, const Vector3& _size, const std::string _gpmeshName, const Tag& _objectTag, const SceneBase::Scene _sceneTag)
	: GameObject(_objectTag,_sceneTag)
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
		mBoxCollider = new BoxCollider(this, ColliderTag::Ground, GetOnCollisionFunc());
		mBoxCollider->SetObjectBox(mMesh->GetBox());

		break;
	}
}

GroundObject::~GroundObject()
{
}

void GroundObject::UpdateGameObject(float _deltaTime)
{
	mAabb = mBoxCollider->GetWorldBox();
}

void GroundObject::OnCollision(const GameObject& _hitObject)
{

}