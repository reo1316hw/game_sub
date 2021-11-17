#include "pch.h"

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="_Pos"> 座標 </param>
/// <param name="_Scale"> 大きさ </param>
/// <param name="_ObjectTag"> オブジェクトのタグ </param>
BossBootSemitransparentWall::BossBootSemitransparentWall(const Vector3& _Pos, const Vector3& _Scale, const Tag& _ObjectTag)
	: GameObject(_ObjectTag)
{
	//GameObjectメンバ変数の初期化
	SetScale(_Scale);
	SetPosition(_Pos);

	// 当たり判定
	AABB box = AABB(Vector3(-2000.0f, -1.0f, -2000.0f), Vector3(2000.0f, 1.0f, 2000.0f));
	mBoxColliderPtr = new BoxCollider(this, _ObjectTag, GetOnCollisionFunc());
	mBoxColliderPtr->SetObjectBox(box);
}

/// <summary>
/// オブジェクトの更新処理
/// </summary>
/// <param name="_deltaTime"> 最後のフレームを完了するのに要した時間 </param>
void BossBootSemitransparentWall::UpdateGameObject(float _deltaTime)
{
	mBox = mBoxColliderPtr->GetWorldBox();
}