#include "pch.h"

/// <summary>
/// コンストラクタ
/// </summary>	
/// <param name="_playerPtr"> プレイヤーのポインタ </param>
/// <param name="_Scale"> 大きさ </param>
/// <param name="_ObjectTag"> オブジェクトのタグ </param>
/// <param name="_dashAttackPtr"> ダッシュ攻撃状態のクラスのポインタ </param>
DashAttackEffect::DashAttackEffect(PlayerObject* _playerPtr, const Vector3& _Scale, const Tag& _ObjectTag, PlayerObjectStateDashAttack* _dashAttackPtr)
	: GameObject(_ObjectTag)
	, MOffset(10.0f)
	, mIsHit(false)
	, mDisableIsHit(false)
	, mPlayerPtr(_playerPtr)
	, mEffectComponentPtr(nullptr)
	, mDashAttackPtr(_dashAttackPtr)
{
	// 武器の矩形当たり判定
	mBox = AABB(Vector3(-15.0f, -100.0f, 50.0f), Vector3(75.0f, 100.0f, 50.0f));
	mBoxColliderPtr = new BoxCollider(this, _ObjectTag, GetOnCollisionFunc());
	mBoxColliderPtr->SetObjectBox(mBox);
	// 最初は当たり判定を行わないようにする
	mBoxColliderPtr->SetCollisionState(CollisionState::eDisableCollision);

	// エフェクト生成
	mEffectComponentPtr = new EffectComponent(this, _Scale, u"Assets/Effect/DashAttack.efk", true, true);
}

/// <summary>
/// オブジェクトの更新処理
/// </summary>
/// <param name="_deltaTime"> 最後のフレームを完了するのに要した時間 </param>
void DashAttackEffect::UpdateGameObject(float _deltaTime)
{
	// 前にずらすベクトル
	Vector3 offsetVec = mPlayerPtr->GetForward() * MOffset;
	mPosition = mPlayerPtr->GetPosition() + offsetVec;

	SetPosition(mPosition);
	SetRotation(mPlayerPtr->GetRotation());

	// 当たり判定を無効にする
	if (!mDashAttackPtr->GetIsCollisionState())
	{
		mBoxColliderPtr->SetCollisionState(CollisionState::eDisableCollision);
		// ヒットストップができるようにする
		mDisableIsHit = false;
		return;
	}

	// 当たり判定を有効にする
	if (mDashAttackPtr->GetIsCollisionState())
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
	}
}

/// <summary>
/// ヒットした時の処理
/// </summary>
/// <param name="_HitObject"> ヒットしたゲームオブジェクト </param>
void DashAttackEffect::OnCollision(const GameObject& _HitObject)
{
	// オブジェクトのタグ
	Tag tag = _HitObject.GetTag();

	if (tag == Tag::eEnemy && !mDisableIsHit && mPlayerPtr->GetPlayerState() == PlayerState::ePlayerStateDashAttack ||
		tag == Tag::eBoss && !mDisableIsHit && mPlayerPtr->GetPlayerState() == PlayerState::ePlayerStateDashAttack)
	{
		mIsHit = true;
		mDisableIsHit = true;
	}
}