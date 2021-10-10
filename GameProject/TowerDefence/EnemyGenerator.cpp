#include "pch.h"

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="_Pos"> 座標 </param>
/// <param name="_Scale"> 大きさ </param>
/// <param name="_ObjectTag"> タグ </param>
/// <param name="_SceneTag"> シーンタグ </param>
/// <param name="_playerPtr"> プレイヤーのポインタ </param>
EnemyGenerator::EnemyGenerator(const Vector3& _Pos, const Vector3& _Scale, const Tag& _ObjectTag, const SceneBase::Scene _SceneTag, PlayerObject* _playerPtr)
	: GameObject(_ObjectTag, _SceneTag)
	, mPlayerPtr(_playerPtr)
{
	//GameObjectメンバ変数の初期化
	mTag = _ObjectTag;
	SetScale(_Scale);
	SetPosition(_Pos);
}

EnemyObject* EnemyGenerator::CreateEnemyObject()
{
	return new EnemyObject(mPosition, mScale, "Assets/Model/Enemy/Enemy.gpmesh"
		, "Assets/Model/Enemy/Enemy.gpskel"
		, Tag::eEnemy
		, SceneBase::tutorial
		, mPlayerPtr);
}