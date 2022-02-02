#include "pch.h"

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="_owner"> アタッチするゲームオブジェクトのポインタ </param>
/// <param name="_UpdateOrder"> コンポーネントの更新順番（数値が小さいほど早く更新される） </param>
Component::Component(GameObject* _owner, int _updateOrder)
	: mOwner(_owner)
	, mUpdateOrder(_updateOrder)
{
	mOwner->AddComponent(this);
}

/// <summary>
/// デストラクタ
/// </summary>
Component::~Component()
{
	mOwner->RemoveComponent(this);
}