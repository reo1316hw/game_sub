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
	, MEffectPlayTiming(2.0f)
	, mElapseTime(0.0f)
	, mBossPtr(_bossPtr)
	, mPlayerPtr(_playerPtr)
	, mEffectComponentPtr(nullptr)
{
	// エフェクトの矩形当たり判定
	mBox = AABB(Vector3(-25.0f, -25.0f, 0.0f), Vector3(25.0f, 25.0f, 85.0f));
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
		mElapseTime = 0.0f;
		return;
	}

	mElapseTime += _deltaTime;

	if (mElapseTime < MEffectPositionUnUpdateTiming)
	{
		mPosition = mPlayerPtr->GetPosition();
		SetPosition(mPosition);
	}

	if (mElapseTime < MEffectPlayTiming)
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