#include "Component.h"
#include "GameObject.h"

/*
@param	アタッチするゲームオブジェクトのポインタ
@param	コンポーネントの更新順番（数値が小さいほど早く更新される）
*/
Component::Component(GameObject* _owner, int _updateOrder)
	: mOwner(_owner)
	, mUpdateOrder(_updateOrder)
{
	mOwner->AddComponent(this);
}

Component::~Component()
{
	mOwner->RemoveComponent(this);
}

/*
@param	最後のフレームを完了するのに要した時間
*/
void Component::Update(float _deltaTime)
{
}
