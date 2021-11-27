#include "pch.h"

/// <summary>
/// コンストラクタ
/// </summary>	
/// <param name="_bossPtr"> ボスのポインタ </param>
/// <param name="_Scale"> 大きさ </param>
/// <param name="_ObjectTag"> オブジェクトのタグ </param>
FrontCoreMagicEffect::FrontCoreMagicEffect(BossObject* _bossPtr, const Vector3& _Scale, const Tag& _ObjectTag)
	: GameObject(_ObjectTag)
	, MBoxEnableTiming(0.5f)
	, MMoveSpeed(10.0f)
	, MHeightCorrection(Vector3(0.0f, 0.0f, 50.0f))
	, mElapseTime(0.0f)
	, mBossPtr(_bossPtr)
	, mEffectComponentPtr(nullptr)
{
	// エフェクトの矩形当たり判定
	mBox = AABB(Vector3(-20.0f, -20.0f, -20.0f), Vector3(20.0f, 20.0f, 20.0f));
	mBoxColliderPtr = new BoxCollider(this, _ObjectTag, GetOnCollisionFunc());
	mBoxColliderPtr->SetObjectBox(mBox);
	// 最初は当たり判定を行わないようにする
	mBoxColliderPtr->SetCollisionState(CollisionState::eDisableCollision);

	// エフェクト生成
	mEffectComponentPtr = new EffectComponent(this, _Scale, u"Assets/Effect/FrontCoreMagic.efk", true, true);
}

/// <summary>
/// オブジェクトの更新処理
/// </summary>
/// <param name="_deltaTime"> 最後のフレームを完了するのに要した時間 </param>
void FrontCoreMagicEffect::UpdateGameObject(float _deltaTime)
{
	// 現在のステート
	BossState nowState = mBossPtr->GetNowState();

	if (nowState != BossState::eBossStateFrontAttack)
	{
		mEffectComponentPtr->StopEffect();
		mBoxColliderPtr->SetCollisionState(CollisionState::eDisableCollision);
		mElapseTime = 0.0f;
		return;
	}

	mElapseTime += _deltaTime;

	if (mElapseTime <= MBoxEnableTiming)
	{
		mPosition = mBossPtr->GetPosition() + MHeightCorrection;
		return;
	}

	// 前方ベクトル
	Vector3 forwardVec = mBossPtr->GetForward();
 	forwardVec.Normalize();
	// 速度
	Vector3 volocity = forwardVec * MMoveSpeed;

	mPosition += volocity;
	SetPosition(mPosition);
	SetRotation(mBossPtr->GetRotation());

	mBoxColliderPtr->SetCollisionState(CollisionState::eEnableCollision);

	// 再生済みじゃなかったらエフェクトを再生する
	if (mEffectComponentPtr->IsPlayedEffect())
	{
		// エフェクトを再生
		mEffectComponentPtr->PlayEffect();
	}
}