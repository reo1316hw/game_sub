#include "pch.h"

/// <summary>
/// コンストラクタ
/// </summary>	
/// <param name="_bossPtr"> ボスのポインタ </param>
/// <param name="_playerPtr"> プレイヤーのポインタ </param>
/// <param name="_Scale"> 大きさ </param>
/// <param name="_ObjectTag"> オブジェクトのタグ </param>
OverheadMagicEffect::OverheadMagicEffect(BossObject* _bossPtr, PlayerObject* _playerPtr, const Vector3& _Scale, const Tag& _ObjectTag)
	: GameObject(_ObjectTag)
	, MEffectPositionUnUpdateTiming(1.8f)
	, MBoxEnableTiming(2.0f)
	, mIsCollisionState(false)
	, mIsOneCollisionState(false)
	, mIsPlayEffect(false)
	, mElapseTime(0.0f)
	, MBoxDisableTiming(2.5f)
	, mBossPtr(_bossPtr)
	, mPlayerPtr(_playerPtr)
	, mEffectComponentPtr(nullptr)
{
	// エフェクトの矩形当たり判定
	mBox = AABB(Vector3(-38.0f, -38.0f, 0.0f), Vector3(38.0f, 38.0f, 85.0f));
	mBoxColliderPtr = new BoxCollider(this, _ObjectTag, GetOnCollisionFunc());
	mBoxColliderPtr->SetObjectBox(mBox);
	// 最初は当たり判定を行わないようにする
	mBoxColliderPtr->SetCollisionState(CollisionState::eDisableCollision);

	// エフェクト生成
	mEffectComponentPtr = new EffectComponent(this, _Scale, u"Assets/Effect/OverheadMagic.efk", true, true);
}

/// <summary>
/// オブジェクトの更新処理
/// </summary>
/// <param name="_deltaTime"> 最後のフレームを完了するのに要した時間 </param>
void OverheadMagicEffect::UpdateGameObject(float _deltaTime)
{
	// 現在のステート
	BossState nowState = mBossPtr->GetNowState();

	if (nowState != BossState::eBossStateOverheadAttack)
	{
		mEffectComponentPtr->StopEffect();
		mBoxColliderPtr->SetCollisionState(CollisionState::eDisableCollision);
		mIsCollisionState = false;
		mIsOneCollisionState = false;
		mIsPlayEffect = false;
		mElapseTime = 0.0f;
		return;
	}

	mElapseTime += _deltaTime;

	if (mElapseTime < MEffectPositionUnUpdateTiming)
	{
		mPosition = mPlayerPtr->GetPosition();
		SetPosition(mPosition);
		return;
	}

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

	if (mElapseTime >= MBoxEnableTiming)
	{
		mBoxColliderPtr->SetCollisionState(CollisionState::eEnableCollision);
		// 1段階目の通常攻撃の当たり判定を有効にする
		mIsCollisionState = true;
	}

	if (!mIsPlayEffect)
	{
		// エフェクトを再生
		mEffectComponentPtr->PlayEffect();
	}

	mIsPlayEffect = true;
}