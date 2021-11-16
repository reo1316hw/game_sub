#include "pch.h"

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="_Pos"> 座標 </param>
/// <param name="_Scale"> 大きさ </param>
/// <param name="_AddAngle"> 回転角を増やすための定数 </param>
/// <param name="_GpmeshName"> gpmeshのパス </param>
/// <param name="_ObjectTag"> オブジェクトのタグ </param>
/// <param name="_enemysControlerPtr"> エネミーを制御するコンポーネントクラスのポインタ </param>
GateDoorObject::GateDoorObject(const Vector3& _Pos, const Vector3& _Scale, const float _AddAngle,
	const std::string _GpmeshName, const Tag& _ObjectTag, EnemysControler* _enemysControlerPtr)
	: GameObject(_ObjectTag)
	, MAddAngle(_AddAngle)
	, mAngle(0.0f)
	, mEnemysControlerPtr(_enemysControlerPtr)
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
}

/// <summary>
/// オブジェクトの更新処理
/// </summary>
/// <param name="_deltaTime"> 最後のフレームを完了するのに要した時間 </param>
void GateDoorObject::UpdateGameObject(float _deltaTime)
{
	mBox = mBoxColliderPtr->GetWorldBox();

	if (Math::Abs(mAngle) > 90.0f)
	{
		return;
	}

	if (mEnemysControlerPtr->GetDeadCount() >= 10)
	{
		mAngle += MAddAngle;

		// 回転処理
		SelfRotation(Vector3::UnitZ, MAddAngle);
	}
}

/// <summary>
/// 回転処理
/// </summary>
/// <param name="_Axis"> 軸 </param>
/// <param name="_Angle"> 角度 </param>
void GateDoorObject::SelfRotation(const Vector3& _Axis, const float& _Angle)
{
	float radian = Math::ToRadians(_Angle);
	Quaternion rot = mRotation;
	Quaternion inc(_Axis, radian);
	Quaternion target = Quaternion::Concatenate(rot, inc);
	SetRotation(target);
}