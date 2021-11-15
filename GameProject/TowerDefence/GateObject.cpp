#include "pch.h"

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="_Pos"> 座標 </param>
/// <param name="_Scale"> 大きさ </param>
/// <param name="_GpmeshName"> gpmeshのパス </param>
/// <param name="_ObjectTag"> オブジェクトのタグ </param>
GateObject::GateObject(const Vector3& _Pos, const Vector3& _Scale, const std::string _GpmeshName, const Tag& _ObjectTag)
	: GameObject(_ObjectTag)
	, MRightGateDoorShiftVec(Vector3(-200.0f, 25.0f, 0.0f))
	, MLeftGateDoorShiftVec(Vector3(200.0f, 25.0f, 0.0f))
{
	//GameObjectメンバ変数の初期化
	SetScale(_Scale);
	SetPosition(_Pos);

	//生成 TestObjectの生成時と同じくComponent基底クラスは自動で管理クラスに追加され自動で解放される
	mMeshComponentPtr = new MeshComponent(this);
	//Rendererクラス内のMesh読み込み関数を利用してMeshをセット(.gpmesh)
	mMeshComponentPtr->SetMesh(RENDERER->GetMesh(_GpmeshName));

	// 当たり判定
	mMeshPtr = new Mesh;
	mMeshPtr = RENDERER->GetMesh(_GpmeshName);
	mBoxColliderPtr = new BoxCollider(this, _ObjectTag, GetOnCollisionFunc());
	mBoxColliderPtr->SetObjectBox(mMeshPtr->GetBox());

	// 門の右扉の座標
	Vector3 rightGateDoorPos = _Pos + MLeftGateDoorShiftVec;
	// 門の右扉の大きさ
	Vector3 rightGateDoorScale = _Scale * Vector3(-1.0f, 1.0f, 1.0f);
	// 門の右扉を生成
	new GateDoorObject(rightGateDoorPos, rightGateDoorScale, "Assets/Model/Gate/GateDoor.gpmesh", Tag::eGateDoor);
	// 門の左扉の座標
	Vector3 leftGateDoorPos = _Pos + MRightGateDoorShiftVec;
	// 門の左扉を生成
	new GateDoorObject(leftGateDoorPos, _Scale, "Assets/Model/Gate/GateDoor.gpmesh", Tag::eGateDoor);
}

/// <summary>
/// オブジェクトの更新処理
/// </summary>
/// <param name="_deltaTime"> 最後のフレームを完了するのに要した時間 </param>
void GateObject::UpdateGameObject(float _deltaTime)
{
	mBox = mBoxColliderPtr->GetWorldBox();
}