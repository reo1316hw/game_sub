#include "pch.h"

/// <summary>
/// コンストラクタ
/// </summary>	
/// <param name="_playerPtr"> プレイヤーのポインタ </param>
/// <param name="_ObjectTag"> オブジェクトのタグ </param>
/// <param name="_firstAttackPtr"> 1段階目の通常攻撃状態のクラスのポインタ </param>
FirstAttackEffect::FirstAttackEffect(PlayerObject* _playerPtr, const Tag& _ObjectTag, PlayerObjectStateFirstAttack* _firstAttackPtr)
	: GameObject(_ObjectTag)
	, mPlayerPtr(_playerPtr)
	, mEffectComponentPtr(nullptr)
	, mFirstAttackPtr(_firstAttackPtr)
{
	SetPosition(mPlayerPtr->GetPosition());
	SetScale(mPlayerPtr->GetScale());
	SetRotation(mPlayerPtr->GetRotation());

	// 武器の矩形当たり判定
	mBox = AABB(Vector3(-100.0f, -100.0f, -100.0f), Vector3(100.0f, 100.0f, 100.0f));
	mBoxColliderPtr = new BoxCollider(this, _ObjectTag, GetOnCollisionFunc(), false);
	mBoxColliderPtr->SetObjectBox(mBox);
	// 最初は当たり判定を行わないようにする
	mBoxColliderPtr->SetCollisionState(CollisionState::eDisableCollision);

	// 衝撃エフェクト生成
	mEffectComponentPtr = new EffectComponent(this, u"Assets/Effect/FirstAttack.efk", true, true);
}

/// <summary>
/// オブジェクトの更新処理
/// </summary>
/// <param name="_deltaTime"> 最後のフレームを完了するのに要した時間 </param>
void FirstAttackEffect::UpdateGameObject(float _deltaTime)
{
	SetPosition(mPlayerPtr->GetPosition());
	SetRotation(mPlayerPtr->GetRotation());

	// 当たり判定を無効にする
	if (!mFirstAttackPtr->GetIsCollisionState())
	{
		mBoxColliderPtr->SetCollisionState(CollisionState::eDisableCollision);
		return;
	}

	// 当たり判定を有効にする
	if (mFirstAttackPtr->GetIsCollisionState())
	{
		// 再生済みじゃなかったらエフェクトを再生する
		if (mEffectComponentPtr->IsPlayedEffect())
		{
			// エフェクトを再生
			mEffectComponentPtr->PlayEffect();
		}
		
		mBoxColliderPtr->SetCollisionState(CollisionState::eEnableCollision);
	}
}