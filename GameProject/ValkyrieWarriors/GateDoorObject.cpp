#include "pch.h"

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="_Pos"> 座標 </param>
/// <param name="_Scale"> 大きさ </param>
/// <param name="_AddAngle"> 回転角を増やすための定数 </param>
/// <param name="_OpenToEnemyDefeatNum"> 門を開くために倒すエネミーの数 </param>
/// <param name="_GpmeshName"> gpmeshのパス </param>
/// <param name="_ObjectTag"> オブジェクトのタグ </param>
/// <param name="_enemysControlerPtr"> エネミーを制御するコンポーネントクラスのポインタ </param>
GateDoorObject::GateDoorObject(const Vector3& _Pos, const Vector3& _Scale, const float _AddAngle, const int& _OpenToDefeatEnemyNum,
	const std::string _GpmeshName, const Tag& _ObjectTag, EnemysControler* _enemysControlerPtr)
	: GameObject(_ObjectTag)
	, MAddAngle(_AddAngle)
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

	// 自身を回転する処理
	SelfRotation* selfRotationPtr = new SelfRotation(this, Vector3::UnitZ, 0.0f);
	// 門を開く処理
	mOpenGatePtr = new OpenGate(this, Vector3::UnitZ, MAddAngle, _OpenToDefeatEnemyNum, _enemysControlerPtr, selfRotationPtr);
}

/// <summary>
/// オブジェクトの更新処理
/// </summary>
/// <param name="_deltaTime"> 最後のフレームを完了するのに要した時間 </param>
void GateDoorObject::UpdateGameObject(float _deltaTime)
{
	mBox = mBoxColliderPtr->GetWorldBox();
}