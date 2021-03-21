#include "WallObject.h"
#include "MeshComponent.h"
#include "Mesh.h"
#include "Renderer.h"
#include "BoxCollider.h"

WallObject::WallObject(const Vector3& _pos, const Vector3& _size, const std::string _gpmeshName, const Tag& _objectTag, const SceneBase::Scene _sceneTag) :
	GameObject(_objectTag,_sceneTag)
{
	//GameObjectメンバ変数の初期化
	tag = _objectTag;
	SetScale(_size);
	SetPosition(_pos);

	switch (_sceneTag)
	{
	case SceneBase::Scene::tutorial:

		//生成 TestObjectの生成時と同じくComponent基底クラスは自動で管理クラスに追加され自動で解放される
		meshComponent = new MeshComponent(this);
		//Rendererクラス内のMesh読み込み関数を利用してMeshをセット(.gpmesh)
		meshComponent->SetMesh(RENDERER->GetMesh(_gpmeshName));

		// 当たり判定
		mesh = new Mesh;
		mesh = RENDERER->GetMesh(_gpmeshName);
		boxCollider = new BoxCollider(this, ColliderTag::Wall, GetOnCollisionFunc());
		boxCollider->SetObjectBox(mesh->GetBox());

		break;
	}
}

WallObject::~WallObject()
{
}

void WallObject::UpdateGameObject(float _deltaTime)
{
	aabb = boxCollider->GetWorldBox();
}