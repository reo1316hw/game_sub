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
	, MOffset(10.0f)
	, mIsHit(false)
	, mDisableIsHit(false)
	, mIsPlayEffect(false)
	, mPlayerPtr(_playerPtr)
	, mEffectComponentPtr(nullptr)
	, mThirdAttackPtr(_thirdAttackPtr)
{
	// エフェクトの矩形当たり判定
	mBox = AABB(Vector3(0.0f, -80.0f, 50.0f), Vector3(130.0f, 80.0f, 50.0f));
	mBoxColliderPtr = new BoxCollider(this, _ObjectTag, GetOnCollisionFunc());
	mBoxColliderPtr->SetObjectBox(mBox);
	// 最初は当たり判定を行わないようにする
	mBoxColliderPtr->SetCollisionState(CollisionState::eDisableCollision);

	// エフェクト生成
	mEffectComponentPtr = new EffectComponent(this, _Scale, u"Assets/Effect/ThirdAttack.efk", true, true);
}

/// <summary>
/// オブジェクトの更新処理
/// </summary>
/// <param name="_deltaTime"> 最後のフレームを完了するのに要した時間 </param>
void ThirdAttackEffect::UpdateGameObject(float _deltaTime)
{
	// 前のステート
	PlayerState nowState = mPlayerPtr->GetNowState();

	if (nowState != PlayerState::ePlayerStateThirdAttack)
	{
		mBoxColliderPtr->SetCollisionState(CollisionState::eDisableCollision);
		mEffectComponentPtr->StopEffect();
		mIsPlayEffect = false;
		return;
	}

	// 前にずらすベクトル
	Vector3 offsetVec = mPlayerPtr->GetForward() * MOffset;
	mPosition = mPlayerPtr->GetPosition() + offsetVec;

	SetPosition(mPosition);
	SetRotation(mPlayerPtr->GetRotation());

	// 当たり判定を無効にする
	if (!mThirdAttackPtr->GetIsCollisionState())
	{
		mBoxColliderPtr->SetCollisionState(CollisionState::eDisableCollision);
		// ヒットストップができるようにする
		mDisableIsHit = false;
		return;
	}

	// 当たり判定を有効にする
	if (mThirdAttackPtr->GetIsCollisionState())
	{
		if (!mIsPlayEffect)
		{
			// エフェクトを再生
			mEffectComponentPtr->PlayEffect();
		}

		mIsPlayEffect = true;

		mBoxColliderPtr->SetCollisionState(CollisionState::eEnableCollision);
	}

	// ヒットストップ時にオブジェクトと常に当たってしまうので、ヒットフラグを一定時間無効にする
	if (mDisableIsHit)
	{
		mIsHit = false;
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

	if (tag == Tag::eEnemy && !mDisableIsHit && mPlayerPtr->GetNowState() == PlayerState::ePlayerStateThirdAttack ||
		tag == Tag::eBoss && !mDisableIsHit && mPlayerPtr->GetNowState() == PlayerState::ePlayerStateThirdAttack)
	{
		mIsHit = true;
		mDisableIsHit = true;
	}
}