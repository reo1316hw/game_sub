#include "pch.h"

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="_owner"> 親クラスのポインタ </param>
/// <param name="_Scale"> 大きさ </param>
/// <param name="_GpmeshName"> gpmeshのパス </param>
/// <param name="_ObjectTag"> オブジェクトのタグ </param>
CircleShadowObject::CircleShadowObject(GameObject* _owner, const Vector3& _Scale, const std::string _GpmeshName, const Tag& _ObjectTag)
	: GameObject(_ObjectTag)
	, MDistance(Vector3(0.0f, 0.0f, 2.0f))
	, mOwner(_owner)
{
	//GameObjectメンバ変数の初期化
	SetScale(_Scale);

	//生成 TestObjectの生成時と同じくComponent基底クラスは自動で管理クラスに追加され自動で解放される
	mMeshComponentPtr = new MeshComponent(this);
	//Rendererクラス内のMesh読み込み関数を利用してMeshをセット(.gpmesh)
	mMeshComponentPtr->SetMesh(RENDERER->GetMesh(_GpmeshName));
}

/// <summary>
/// オブジェクトの更新処理
/// </summary>
/// <param name="_deltaTime"> 最後のフレームを完了するのに要した時間 </param>
void CircleShadowObject::UpdateGameObject(float _deltaTime)
{
	if (mOwner->GetState())
	{

	}

	mPosition = mOwner->GetPosition() + MDistance;
	SetPosition(mPosition);
}