#include "pch.h"

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="_Pos"> 座標 </param>
/// <param name="_Scale"> 大きさ </param>
/// <param name="_GpmeshName"> gpmeshのパス </param>
/// <param name="_ObjectTag"> オブジェクトのタグ </param>
GateDoorObject::GateDoorObject(const Vector3& _Pos, const Vector3& _Scale,
	const std::string _GpmeshName, const Tag& _ObjectTag)
	: GameObject(_ObjectTag)
{
	//GameObjectメンバ変数の初期化
	SetScale(_Scale);
	SetPosition(_Pos);

	//生成 TestObjectの生成時と同じくComponent基底クラスは自動で管理クラスに追加され自動で解放される
	mMeshComponentPtr = new MeshComponent(this);
	//Rendererクラス内のMesh読み込み関数を利用してMeshをセット(.gpmesh)
	mMeshComponentPtr->SetMesh(RENDERER->GetMesh(_GpmeshName));

	//// 回転処理
	//SelfRotation(Vector3::UnitZ, _Angle);
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