#include "pch.h"

/// <summary>
/// コンストラクタ
/// </summary>	
/// <param name="_bossPtr"> ボスのポインタ </param>
/// <param name="_Scale"> 大きさ </param>
/// <param name="_ObjectTag"> オブジェクトのタグ </param>
AreaMagicEffect::AreaMagicEffect(BossObject* _bossPtr, const Vector3& _Scale, const Tag& _ObjectTag)
	: GameObject(_ObjectTag)
	, MBoxEnableTiming(2.2f)
	, MBoxDisableTiming(2.5f)
	, MHeightCorrection(Vector3(0.0f, 0.0f, 50.0f))
	, mIsCollisionState(false)
	, mIsOneCollisionState(false)
	, mElapseTime(0.0f)
	, mNowState(_bossPtr->GetNowState())
	, mBossPtr(_bossPtr)
	, mEffectComponentPtr(nullptr)
{
	// エフェクトの矩形当たり判定
	mBox = AABB(Vector3(-250.0f, -250.0f, -100.0f), Vector3(250.0f, 250.0f, 100.0f));
	mBoxColliderPtr = new BoxCollider(this, _ObjectTag, GetOnCollisionFunc());
	mBoxColliderPtr->SetObjectBox(mBox);
	// 最初は当たり判定を行わないようにする
	mBoxColliderPtr->SetCollisionState(CollisionState::eDisableCollision);

	// エフェクト生成
	mEffectComponentPtr = new EffectComponent(this, _Scale, u"Assets/Effect/AreaMagic.efk", true, true);
}

/// <summary>
/// オブジェクトの更新処理
/// </summary>
/// <param name="_deltaTime"> 最後のフレームを完了するのに要した時間 </param>
void AreaMagicEffect::UpdateGameObject(float _deltaTime)
{
	// 前のステート
	BossState preState = mNowState;

	mNowState = mBossPtr->GetNowState();

	if (mNowState != BossState::eBossStateAreaAttack)
	{
		mEffectComponentPtr->StopEffect();
		mIsOneCollisionState = false;
		mElapseTime = 0.0f;
		return;
	}

	mElapseTime += _deltaTime;

	if (mIsCollisionState)
	{
		if (mElapseTime >= MBoxDisableTiming)
		{
			mBoxColliderPtr->SetCollisionState(CollisionState::eDisableCollision);

			// 1段階目の通常攻撃の当たり判定を無効にする
			mIsCollisionState = false;
			mIsOneCollisionState = true;
		}
	}

	if (mIsOneCollisionState)
	{
		return;
	}

	mPosition = mBossPtr->GetPosition() + MHeightCorrection;
	SetPosition(mPosition);
	SetRotation(mBossPtr->GetRotation());

	if (mElapseTime >= MBoxEnableTiming)
	{
		mBoxColliderPtr->SetCollisionState(CollisionState::eEnableCollision);
		// 1段階目の通常攻撃の当たり判定を有効にする
		mIsCollisionState = true;
	}

	if (mNowState == preState)
	{
		return;
	}

	// 再生済みじゃなかったらエフェクトを再生する
	if (mEffectComponentPtr->IsPlayedEffect())
	{
		// エフェクトを再生
		mEffectComponentPtr->PlayEffect();
	}
}