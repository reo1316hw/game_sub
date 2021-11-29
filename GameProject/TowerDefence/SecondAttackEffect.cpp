#include "pch.h"

/// <summary>
/// コンストラクタ
/// </summary>	
/// <param name="_playerPtr"> プレイヤーのポインタ </param>
/// <param name="_Scale"> 大きさ </param>
/// <param name="_ObjectTag"> オブジェクトのタグ </param>
/// <param name="_secondAttackPtr"> 2段階目の通常攻撃状態のクラスのポインタ </param>
SecondAttackEffect::SecondAttackEffect(PlayerObject* _playerPtr, const Vector3& _Scale, const Tag& _ObjectTag, PlayerObjectStateSecondAttack* _secondAttackPtr)
	: GameObject(_ObjectTag)
	, mHitTagList{ Tag::eEnemy, Tag::eBoss }
	, MOffset(10.0f)
	, mIsPlayEffect(false)
	, mHitEnemyCount(0)
	, mHitTagListSize(sizeof(mHitTagList) / sizeof(int))
	, mFaceInEnemyVec(Vector3::Zero)
	, mFaceInFlockCenterVec(Vector3::Zero)
	, mHitTag(Tag::eOther)
	, mPlayerPtr(_playerPtr)
	, mEffectComponentPtr(nullptr)
	, mSecondAttackPtr(_secondAttackPtr)
{
	// エフェクトの矩形当たり判定
	mBox = AABB(Vector3(0.0f, -40.0f, 50.0f), Vector3(100.0f, 40.0f, 50.0f));
	mBoxColliderPtr = new BoxCollider(this, _ObjectTag, GetOnCollisionFunc());
	mBoxColliderPtr->SetObjectBox(mBox);
	// 最初は当たり判定を行わないようにする
	mBoxColliderPtr->SetCollisionState(CollisionState::eDisableCollision);

	// エフェクト生成
	mEffectComponentPtr = new EffectComponent(this, _Scale, u"Assets/Effect/SecondAttack.efk", true, true);
}

/// <summary>
/// オブジェクトの更新処理
/// </summary>
/// <param name="_deltaTime"> 最後のフレームを完了するのに要した時間 </param>
void SecondAttackEffect::UpdateGameObject(float _deltaTime)
{
	// 前のステート
	PlayerState nowState = mPlayerPtr->GetNowState();

	if (nowState != PlayerState::ePlayerStateSecondAttack)
	{
		mBoxColliderPtr->SetCollisionState(CollisionState::eDisableCollision);
		mEffectComponentPtr->StopEffect();
		mIsPlayEffect = false;
		return;
	}

	mFaceInFlockCenterVec = Vector3::Zero;

	// エネミーにヒットしていたら
	if (mHitEnemyCount != 0)
	{
		// ヒットしたエネミーの群れの中心に向くベクトル
		mFaceInFlockCenterVec = mFaceInEnemyVec / mHitEnemyCount;

		mFaceInEnemyVec = Vector3::Zero;
		mHitEnemyCount = 0;
	}

	// 前にずらすベクトル
	Vector3 offsetVec = mPlayerPtr->GetForward() * MOffset;
	mPosition = mPlayerPtr->GetPosition() + offsetVec;

	SetPosition(mPosition);
	SetRotation(mPlayerPtr->GetRotation());

	// 当たり判定を無効にする
	if (!mSecondAttackPtr->GetIsCollisionState())
	{
		mBoxColliderPtr->SetCollisionState(CollisionState::eDisableCollision);
		return;
	}

	// 当たり判定を有効にする
	if (mSecondAttackPtr->GetIsCollisionState())
	{
		if (!mIsPlayEffect)
		{
			// エフェクトを再生
			mEffectComponentPtr->PlayEffect();
		}

		mIsPlayEffect = true;

		mBoxColliderPtr->SetCollisionState(CollisionState::eEnableCollision);
	}
}

/// <summary>
/// ヒットした時の処理
/// </summary>
/// <param name="_HitObject"> ヒットしたゲームオブジェクト </param>
void SecondAttackEffect::OnCollision(const GameObject& _HitObject)
{
	// オブジェクトのタグ
	mHitTag = _HitObject.GetTag();

	for (int i = 0; i < mHitTagListSize; i++)
	{
		// 攻撃を受けた時の処理
		HitAttack(_HitObject, mHitTagList[i]);
	}
}

/// <summary>
/// 攻撃が当たった時の処理
/// </summary>
/// <param name="_HitObject"> ヒットしたオブジェクト </param>
/// <param name="_HitTag"> ヒットしたオブジェクトのタグ </param>
void SecondAttackEffect::HitAttack(const GameObject& _HitObject, const Tag& _HitTag)
{
	// ヒットしたオブジェクトに向くベクトルの算出と当たったエネミーのカウントを行う
	if (mHitTag == _HitTag)
	{
		// ヒットしたオブジェクトの座標
		Vector3 hitObjectPosition = _HitObject.GetPosition();
		// プレイヤーの座標
		Vector3 playerPosition = mPlayerPtr->GetPosition();

		mFaceInEnemyVec += hitObjectPosition - playerPosition;
		++mHitEnemyCount;
	}
}