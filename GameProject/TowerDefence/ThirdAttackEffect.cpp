#include "pch.h"

/// <summary>
/// コンストラクタ
/// </summary>	
/// <param name="_playerPtr"> プレイヤーのポインタ </param>
/// <param name="_Scale"> 大きさ </param>
/// <param name="_ObjectTag"> オブジェクトのタグ </param>
/// <param name="_thirdAttackPtr"> 3段階目の通常攻撃状態のクラスのポインタ </param>
ThirdAttackEffect::ThirdAttackEffect(PlayerObject* _playerPtr, const Vector3& _Scale, const Tag& _ObjectTag, PlayerObjectStateThirdAttack* _thirdAttackPtr)
	: GameObject(_ObjectTag)
	, MEnableIsHitTiming(120)
	, MOffset(10.0f)
	, MHeightCorrection(Vector3(0.0f, 0.0f, 25.0f))
	, mIsHit(false)
	, mDisableIsHit(false)
	, mIsHitDisableCount(0)
	, mPlayerPtr(_playerPtr)
	, mEffectComponentPtr(nullptr)
	, mThirdAttackPtr(_thirdAttackPtr)
{
	SetScale(mPlayerPtr->GetScale());

	// 武器の矩形当たり判定
	mBox = AABB(Vector3(-30.0f, -160.0f, 100.0f), Vector3(200.0f, 160.0f, 100.0f));
	mBoxColliderPtr = new BoxCollider(this, _ObjectTag, GetOnCollisionFunc());
	mBoxColliderPtr->SetObjectBox(mBox);
	// 最初は当たり判定を行わないようにする
	mBoxColliderPtr->SetCollisionState(CollisionState::eDisableCollision);

	// 衝撃エフェクト生成
	mEffectComponentPtr = new EffectComponent(this, _Scale, u"Assets/Effect/ThirdAttack.efk", true, true);
}

/// <summary>
/// オブジェクトの更新処理
/// </summary>
/// <param name="_deltaTime"> 最後のフレームを完了するのに要した時間 </param>
void ThirdAttackEffect::UpdateGameObject(float _deltaTime)
{
	// 高さ補正後の座標
	Vector3 postionHeightCorrection = mPlayerPtr->GetPosition() + MHeightCorrection;
	// 高さ補正後の座標から前にずらした座標
	Vector3 offsetPos = mPlayerPtr->GetForward() * MOffset;

	mPosition = postionHeightCorrection + offsetPos;
	SetPosition(mPosition);
	SetRotation(mPlayerPtr->GetRotation());

	// 当たり判定を無効にする
	if (!mThirdAttackPtr->GetIsCollisionState())
	{
		mBoxColliderPtr->SetCollisionState(CollisionState::eDisableCollision);
		return;
	}

	// 当たり判定を有効にする
	if (mThirdAttackPtr->GetIsCollisionState())
	{
		// 再生済みじゃなかったらエフェクトを再生する
		if (mEffectComponentPtr->IsPlayedEffect())
		{
			// エフェクトを再生
			mEffectComponentPtr->PlayEffect();
		}

		mBoxColliderPtr->SetCollisionState(CollisionState::eEnableCollision);
	}

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
void ThirdAttackEffect::OnCollision(const GameObject& _HitObject)
{
	// オブジェクトのタグ
	Tag tag = _HitObject.GetTag();

	if (tag == Tag::eEnemy && !mDisableIsHit && mPlayerPtr->GetPlayerState() == PlayerState::ePlayerStateThirdAttack)
	{
		mIsHit = true;
		mDisableIsHit = true;
	}
}