#include "pch.h"

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="_Pos"> 座標 </param>
/// <param name="_Scale"> 大きさ </param>
/// <param name="_OpenToEnemyDefeatNum"> 門を開くために倒すエネミーの数 </param>
/// <param name="_GpmeshName"> gpmeshのパス </param>
/// <param name="_ObjectTag"> オブジェクトのタグ </param>
/// <param name="_enemysControlerPtr"> エネミーを制御するコンポーネントクラスのポインタ </param>
GateObject::GateObject(const Vector3& _Pos, const Vector3& _Scale, const int& _OpenToDefeatEnemyNum,
	const std::string _GpmeshName, const Tag& _ObjectTag, EnemysControler* _enemysControlerPtr)
	: GameObject(_ObjectTag)
	, BoxColliderNum(2)
	, MRightGateDoorAddAngle(0.5f)
	, MLeftGateDoorAddAngle(-0.5f)
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

	for (int i = 0; i < BoxColliderNum; i++)
	{
		// 矩形当たり判定を丁度よい位置にずらすためのベクトル
		Vector3 BoxColliderShiftVec = Vector3(550.0f, 0.0f, 0.0f) * i;
		// 矩形当たり判定の最小のポジション
		Vector3 BoxColliderMin = Vector3(-350.0f, 0.0f, 0.0f) + BoxColliderShiftVec;
		// 矩形当たり判定の最大のポジション
		Vector3 BoxColliderMax = Vector3(-200.0f, 60.0f, 800.0f) + BoxColliderShiftVec;

		// 当たり判定
		AABB box = AABB(BoxColliderMin, BoxColliderMax);
		mBoxColliderPtr = new BoxCollider(this, _ObjectTag, GetOnCollisionFunc());
		mBoxColliderPtr->SetObjectBox(box);
	}
	
	// 門の右扉の座標
	Vector3 rightGateDoorPos = _Pos + MLeftGateDoorShiftVec;
	// 門の右扉の大きさ
	Vector3 rightGateDoorScale = _Scale * Vector3(-1.0f, 1.0f, 1.0f);
	// 門の右扉を生成
	new GateDoorObject(rightGateDoorPos, rightGateDoorScale, MRightGateDoorAddAngle, _OpenToDefeatEnemyNum,
		               "Assets/Model/Gate/GateDoor.gpmesh", Tag::eGateDoor, _enemysControlerPtr);
	// 門の左扉の座標
	Vector3 leftGateDoorPos = _Pos + MRightGateDoorShiftVec;
	// 門の左扉を生成
	new GateDoorObject(leftGateDoorPos, _Scale, MLeftGateDoorAddAngle, _OpenToDefeatEnemyNum,
		               "Assets/Model/Gate/GateDoor.gpmesh", Tag::eGateDoor, _enemysControlerPtr);
}

/// <summary>
/// オブジェクトの更新処理
/// </summary>
/// <param name="_deltaTime"> 最後のフレームを完了するのに要した時間 </param>
void GateObject::UpdateGameObject(float _deltaTime)
{
	mBox = mBoxColliderPtr->GetWorldBox();
}