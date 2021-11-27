#include "pch.h"

/// <summary>
/// コンストラクタ
/// </summary>	
/// <param name="_playerPtr"> プレイヤーのポインタ </param>
/// <param name="_Scale"> 大きさ </param>
/// <param name="_ObjectTag"> オブジェクトのタグ </param>
/// <param name="_firstAttackPtr"> 1段階目の通常攻撃状態のクラスのポインタ </param>
FirstAttackEffect::FirstAttackEffect(PlayerObject* _playerPtr, const Vector3& _Scale, const Tag& _ObjectTag, PlayerObjectStateFirstAttack* _firstAttackPtr)
	: GameObject(_ObjectTag)
	, mHitTagList{ Tag::eEnemy, Tag::eBoss }
	, MOffset(10.0f)
	, mHitEnemyCount(0)
	, mHitTagListSize(sizeof(mHitTagList) / sizeof(int))
	, mFaceInEnemyVec(Vector3::Zero)
	, mFaceInFlockCenterVec(Vector3::Zero)
	, mHitTag(Tag::eOther)
	, mPlayerPtr(_playerPtr)
	, mEffectComponentPtr(nullptr)
	, mFirstAttackPtr(_firstAttackPtr)
{
	// エフェクトの矩形当たり判定
	mBox = AABB(Vector3(0.0f, -20.0f, 50.0f), Vector3(70.0f, 20.0f, 50.0f));
	mBoxColliderPtr = new BoxCollider(this, _ObjectTag, GetOnCollisionFunc());
	mBoxColliderPtr->SetObjectBox(mBox);
	// 最初は当たり判定を行わないようにする
	mBoxColliderPtr->SetCollisionState(CollisionState::eDisableCollision);

	// エフェクト生成
	mEffectComponentPtr = new EffectComponent(this, _Scale, u"Assets/Effect/FirstAttack.efk", true, true);
}

/// <summary>
/// オブジェクトの更新処理
/// </summary>
/// <param name="_deltaTime"> 最後のフレームを完了するのに要した時間 </param>
void FirstAttackEffect::UpdateGameObject(float _deltaTime)
{
	// 前のステート
	PlayerState nowState = mPlayerPtr->GetNowState();

	if (nowState != PlayerState::ePlayerStateFirstAttack)
	{
		mEffectComponentPtr->StopEffect();
		return;
	}

	mFaceInFlockCenterVec = Vector3::Zero;

	// エネミーにヒットしいたら
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

/// <summary>
/// ヒットした時の処理
/// </summary>
/// <param name="_HitObject"> ヒットしたゲームオブジェクト </param>
void FirstAttackEffect::OnCollision(const GameObject& _HitObject)
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
void FirstAttackEffect::HitAttack(const GameObject& _HitObject, const Tag& _HitTag)
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