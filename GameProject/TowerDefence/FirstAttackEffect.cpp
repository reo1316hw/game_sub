#include "pch.h"

/// <summary>
/// コンストラクタ
/// </summary>	
/// <param name="_playerPtr"> プレイヤーのポインタ </param>
/// <param name="_ObjectTag"> オブジェクトのタグ </param>
FirstAttackEffect::FirstAttackEffect(PlayerObject* _playerPtr, const Tag& _ObjectTag)
	: GameObject(_ObjectTag)
	, MEnableIsHitTiming(120)
	, mIsHitDisableCount(0)
	, mIsHit(false)
	, mDisableIsHit(false)
	, mPlayerPtr(_playerPtr)
{
	// 武器の矩形当たり判定
	mBox = AABB(Vector3(-100.0f, -100.0f, -100.0f), Vector3(100.0f, 100.0f, 100.0f));
	mBoxColliderPtr = new BoxCollider(this, _ObjectTag, GetOnCollisionFunc());
	mBoxColliderPtr->SetObjectBox(mBox);
	// 最初は当たり判定を行わないようにする
	mBoxColliderPtr->SetCollisionState(CollisionState::eDisableCollision);

	// 衝撃エフェクト生成
	EffectComponent* ec = new EffectComponent(_playerPtr, u"Assets/Effect/SecondAttack.efk", true, true);
	ec->PlayEffect();
}

/// <summary>
/// オブジェクトの更新処理
/// </summary>
/// <param name="_deltaTime"> 最後のフレームを完了するのに要した時間 </param>
void FirstAttackEffect::UpdateGameObject(float _deltaTime)
{
	// ヒットストップ時にオブジェクトと常に当たってしまうので、ヒットフラグを一定時間無効にする
	if (mDisableIsHit)
	{
		mIsHit = false;
		++mIsHitDisableCount;

		if (mIsHitDisableCount >= MEnableIsHitTiming)
		{
			mIsHitDisableCount = 0;
			mDisableIsHit = false;
		}
	}
}

/// <summary>
/// ヒットした時の処理
/// </summary>
/// <param name="_HitObject"> ヒットしたゲームオブジェクト </param>
void FirstAttackEffect::OnCollision(const GameObject& _HitObject)
{
	// オブジェクトのタグ
	Tag tag = _HitObject.GetTag();

	if (tag == Tag::eEnemy && !mDisableIsHit && mPlayerPtr->GetPlayerState() == PlayerState::ePlayerStateThirdAttack)
	{
		mIsHit = true;
		mDisableIsHit = true;
	}
}