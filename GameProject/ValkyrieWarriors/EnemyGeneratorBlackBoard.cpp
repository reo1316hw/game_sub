#include "pch.h"

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="_Pos"> 座標 </param>
/// <param name="_Scale"> 大きさ </param>
/// <param name="_Angle"> 回転角 </param>
/// <param name="_GpmeshName"> gpmeshのパス </param>
/// <param name="_ObjectTag"> オブジェクトのタグ </param>
EnemyGeneratorBlackBoard::EnemyGeneratorBlackBoard(const Vector3& _Pos, const Vector3& _Scale, const float& _Angle,
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

	// 自身の回転処理
	new SelfRotation(this, Vector3::UnitZ, _Angle);
}