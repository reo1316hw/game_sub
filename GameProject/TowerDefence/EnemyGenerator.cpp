#include "pch.h"

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="_Pos"> 座標 </param>
/// <param name="_Scale"> 大きさ </param>
/// <param name="_ObjectTag"> オブジェクトのタグ </param>
/// <param name="_playerPtr"> プレイヤーのポインタ </param>
EnemyGenerator::EnemyGenerator(const Vector3& _Pos, const Vector3& _Scale, const Tag& _ObjectTag, PlayerObject* _playerPtr)
	: GameObject(_ObjectTag)
	, mPlayerPtr(_playerPtr)
{
	//GameObjectメンバ変数の初期化
	SetScale(_Scale);
	SetPosition(_Pos);
}

/// <summary>
/// エネミーの生成
/// </summary>
/// <returns> エネミーのポインタ</returns>
EnemyObject* EnemyGenerator::CreateEnemyObject()
{
	return new EnemyObject(mPosition, mScale, "Assets/Model/Enemy/Enemy.gpmesh"
		, "Assets/Model/Enemy/Enemy.gpskel"
		, Tag::eEnemy
		, mPlayerPtr);
}