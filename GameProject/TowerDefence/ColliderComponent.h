#pragma once

// 前方宣言
class GameObject;

/// <summary>
/// 当たり判定を行うコンポーネントの基底クラス
/// </summary>
class ColliderComponent : public Component
{
public:

    /**
	@brief	コンストラクタ
	@param	アタッチするゲームオブジェクトのポインタ
    @param	コンポーネントの更新順番（数値が小さいほど早く更新される）
    @param  当たり判定時に、めり込みから動かす処理の優先度を決める数値
    */
	ColliderComponent(GameObject* _owner, const Tag& _ObjectTag, int _updateOrder = 200,int _collisionOrder = 100);

	/**
	@brief	めり込み動かす際の優先度を示す数値を取得する
	@return 優先度を示す数値(int)
	*/
	int GetCollisionOrder() const { return mCollisionOrder; }

private:

	bool mTriggerFlag;		//実体を伴う当たり判定をするかどうか
	int	 mCollisionOrder;	//数値が大きい方を優先してめり込みから動かす処理をする（0以下は動かさない）
};

