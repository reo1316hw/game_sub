#include "pch.h"

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="_Pos"> 座標 </param>
/// <param name="_Scale"> 大きさ </param>
/// <param name="_GpmeshName"> gpmeshのパス </param>
/// <param name="_GpskelName"> gpskelのパス </param>
/// <param name="_ObjectTag"> オブジェクトのタグ </param>
/// <param name="_playerPtr"> プレイヤーのポインタ </param>
EnemyObject::EnemyObject(const Vector3& _Pos, const Vector3& _Scale, const std::string _GpmeshName, const char* _GpskelName,
	const Tag& _ObjectTag, PlayerObject* _playerPtr)
	: GameObject(_ObjectTag)
	, MShouldTutorialUse(false)
	, MMaxHp(50)
	, MPlayRate(1.0f)
	, MHpGaugeScale(Vector3(0.05f, 1.0f, 4.0f))
	, MHitEffectScale(Vector3(10.0f, -10.0f, 10.0f))
	, mInitPosition(Vector3::Zero)
	, mNowState(EnemyState::eEnemyStateWait)
	, mNextState(EnemyState::eEnemyStateTrack)
	, mEnemyHitPointGaugePtr(nullptr)
	, mEnemyHitPointFramePtr(nullptr)
{
	//GameObjectメンバ変数の初期化
	SetScale(_Scale);
	SetPosition(_Pos);
	SetState(State::eDead);
	mInitPosition = mPosition;
	mMaxHp = MMaxHp;
	mHitPoint = mMaxHp;

	///生成 TestObjectの生成時と同じくComponent基底クラスは自動で管理クラスに追加され自動で解放される
	mSkeltalMeshComponentPtr = new SkeletalMeshComponent(this);
	//Rendererクラス内のMesh読み込み関数を利用してMeshをセット(.gpmesh)
	mSkeltalMeshComponentPtr->SetMesh(RENDERER->GetMesh(_GpmeshName));
	//Rendererクラス内のSkeletonデータ読み込み関数を利用してSkeletonをセット(.gpskel)
	mSkeltalMeshComponentPtr->SetSkeleton(RENDERER->GetSkeleton(_GpskelName));

	// アニメーションの取得 & アニメーション配列にセット
	mAnimTypes.resize(static_cast<int>(EnemyState::eEnemyStateNum));
	mAnimTypes[static_cast<int>(EnemyState::eEnemyStateTrack)] = RENDERER->GetAnimation("Assets/Model/Enemy/EnemyTrack.gpanim", true);
	mAnimTypes[static_cast<int>(EnemyState::eEnemyStateWait)] = RENDERER->GetAnimation("Assets/Model/Enemy/EnemyWait.gpanim", true);
	mAnimTypes[static_cast<int>(EnemyState::eEnemyStateAttack)] = RENDERER->GetAnimation("Assets/Model/Enemy/EnemyAttack.gpanim", false);
	mAnimTypes[static_cast<int>(EnemyState::eEnemyStateAttackReady)] = RENDERER->GetAnimation("Assets/Model/Enemy/EnemyAttackReady.gpanim", false);
	mAnimTypes[static_cast<int>(EnemyState::eEnemyStateLeftMove)] = RENDERER->GetAnimation("Assets/Model/Enemy/EnemyLeftMove.gpanim", true);
	mAnimTypes[static_cast<int>(EnemyState::eEnemyStateRightMove)] = RENDERER->GetAnimation("Assets/Model/Enemy/EnemyRightMove.gpanim", true);
	mAnimTypes[static_cast<int>(EnemyState::eEnemyStateImpactDamage)] = RENDERER->GetAnimation("Assets/Model/Enemy/EnemyImpact.gpanim", false);
	mAnimTypes[static_cast<int>(EnemyState::eEnemyStateSweepFallDamage)] = RENDERER->GetAnimation("Assets/Model/Enemy/EnemySweepFall.gpanim", false);
	mAnimTypes[static_cast<int>(EnemyState::eEnemyStateFlyingBackDamage)] = RENDERER->GetAnimation("Assets/Model/Enemy/EnemyFlyingBack.gpanim", false);
	mAnimTypes[static_cast<int>(EnemyState::eEnemyStateStandUp)] = RENDERER->GetAnimation("Assets/Model/Enemy/EnemyStandUp.gpanim", false);
	mAnimTypes[static_cast<int>(EnemyState::eEnemyStateFallingBackDeath)] = RENDERER->GetAnimation("Assets/Model/Enemy/EnemyFallingBack.gpanim", false);
	mAnimTypes[static_cast<int>(EnemyState::eEnemyStateSweepFallDeath)] = RENDERER->GetAnimation("Assets/Model/Enemy/EnemySweepFall.gpanim", false);
	mAnimTypes[static_cast<int>(EnemyState::eEnemyStateFlyingBackDeath)] = RENDERER->GetAnimation("Assets/Model/Enemy/EnemyFlyingBack.gpanim", false);

	//Rendererクラス内のSkeletonデータ読み込み関数を利用してAnimationをセット(.gpanim)
	const Animation* anim = mAnimTypes[static_cast<int>(EnemyState::eEnemyStateTrack)];
	//anim変数を速度1.0fで再生
	mSkeltalMeshComponentPtr->PlayAnimation(anim);

	// エネミーの攻撃判定生成
	mEnemyAttackPtr = new EnemyAttackDecisionObject(this, Tag::eEnemyAttackDecision);

	// ヒットエフェクト生成
	new HitEffect(this, MHitEffectScale, Tag::eHItEffect);

	// アクターステートプールの初期化
	mStatePools.push_back(new EnemyObjectStateTrack(_playerPtr));	                                // mStatePool[eEnemyStateTrack]
	mStatePools.push_back(new EnemyObjectStateWait(_playerPtr));	                                // mStatepool[eEnemyStateWait]
	mStatePools.push_back(new EnemyObjectStateAttack(mEnemyAttackPtr));                             // mStatepool[eEnemyStateAttack]
	mStatePools.push_back(new EnemyObjectStateAttackReady);                                         // mStatepool[eEnemyStateAttackReady]
	mStatePools.push_back(new EnemyObjectStateMove(EnemyState::eEnemyStateLeftMove, _playerPtr));	// mStatepool[eEnemyStateLeftMove]
	mStatePools.push_back(new EnemyObjectStateMove(EnemyState::eEnemyStateRightMove, _playerPtr));	// mStatepool[eEnemyStateRightMove]
	mStatePools.push_back(new EnemyObjectStateImpactDamage(_playerPtr));                            // mStatepool[eEnemyStateImpactDamage];
	mStatePools.push_back(new EnemyObjectStateSweepFallDamage(_playerPtr));                            // mStatepool[eEnemyStateImpactDamage];
	mStatePools.push_back(new EnemyObjectStateFlyingBackDamage(_playerPtr));                            // mStatepool[eEnemyStateImpactDamage];
	mStatePools.push_back(new EnemyObjectStateStandUp(_playerPtr));                            // mStatepool[eEnemyStateImpactDamage];
	mStatePools.push_back(new EnemyObjectStateFallingBackDeath(_playerPtr));                            // mStatepool[eEnemyStateImpactDamage];
	mStatePools.push_back(new EnemyObjectStateSweepFallDeath(_playerPtr));                            // mStatepool[eEnemyStateImpactDamage];
	mStatePools.push_back(new EnemyObjectStateFlyingBackDeath(_playerPtr));                         // mStatepool[eEnemyStateFlyingBackDeath];

	// 矩形当たり判定
	mBox = AABB(Vector3(-45.0f, -45.0f, 0.0f), Vector3(45.0f, 45.0f, 170.0f));

	mBoxColliderPtr = new BoxCollider(this, _ObjectTag, GetOnCollisionFunc());
	mBoxColliderPtr->SetObjectBox(mBox);

	// エネミーのhpゲージを生成
	mEnemyHitPointGaugePtr = new EnemyHitPointGauge(MHpGaugeScale, "Assets/Texture/EnemyHpGauge.png", Tag::eOther, this);
	// エネミーのhpの枠を生成
	mEnemyHitPointFramePtr = new EnemyHitPointFrame(MHpGaugeScale, "Assets/Texture/EnemyHpFrame.png", Tag::eOther, this);
}

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="_ShouldTutorialUse"> チュートリアルで使用するか </param>
/// <param name="_Pos"> 座標 </param>
/// <param name="_Scale"> 大きさ </param>
/// <param name="_GpmeshName"> gpmeshのパス </param>
/// <param name="_GpskelName"> gpskelのパス </param>
/// <param name="_ObjectTag"> オブジェクトのタグ </param>
/// <param name="_playerPtr"> プレイヤーのポインタ </param>
EnemyObject::EnemyObject(const bool& _ShouldTutorialUse, const Vector3& _Pos, const Vector3& _Scale, const std::string _GpmeshName, const char* _GpskelName,
	const Tag& _ObjectTag, PlayerObject* _playerPtr)
	: GameObject(_ObjectTag)
	, MShouldTutorialUse(_ShouldTutorialUse)
	, MMaxHp(50)
	, MPlayRate(1.0f)
	, MHpGaugeScale(Vector3(0.05f, 1.0f, 4.0f))
	, MHitEffectScale(Vector3(10.0f, -10.0f, 10.0f))
	, mInitPosition(Vector3::Zero)
	, mNowState(EnemyState::eEnemyStateWait)
	, mNextState(EnemyState::eEnemyStateTrack)
	, mEnemyHitPointGaugePtr(nullptr)
	, mEnemyHitPointFramePtr(nullptr)
{
	//GameObjectメンバ変数の初期化
	SetScale(_Scale);
	SetPosition(_Pos);
	mInitPosition = mPosition;
	mMaxHp = MMaxHp;
	mHitPoint = mMaxHp;

	///生成 TestObjectの生成時と同じくComponent基底クラスは自動で管理クラスに追加され自動で解放される
	mSkeltalMeshComponentPtr = new SkeletalMeshComponent(this);
	//Rendererクラス内のMesh読み込み関数を利用してMeshをセット(.gpmesh)
	mSkeltalMeshComponentPtr->SetMesh(RENDERER->GetMesh(_GpmeshName));
	//Rendererクラス内のSkeletonデータ読み込み関数を利用してSkeletonをセット(.gpskel)
	mSkeltalMeshComponentPtr->SetSkeleton(RENDERER->GetSkeleton(_GpskelName));

	// アニメーションの取得 & アニメーション配列にセット
	mAnimTypes.resize(static_cast<int>(EnemyState::eEnemyStateNum));
	mAnimTypes[static_cast<int>(EnemyState::eEnemyStateTrack)] = RENDERER->GetAnimation("Assets/Model/Enemy/EnemyTrack.gpanim", true);
	mAnimTypes[static_cast<int>(EnemyState::eEnemyStateWait)] = RENDERER->GetAnimation("Assets/Model/Enemy/EnemyWait.gpanim", true);
	mAnimTypes[static_cast<int>(EnemyState::eEnemyStateAttack)] = RENDERER->GetAnimation("Assets/Model/Enemy/EnemyAttack.gpanim", false);
	mAnimTypes[static_cast<int>(EnemyState::eEnemyStateAttackReady)] = RENDERER->GetAnimation("Assets/Model/Enemy/EnemyAttackReady.gpanim", false);
	mAnimTypes[static_cast<int>(EnemyState::eEnemyStateLeftMove)] = RENDERER->GetAnimation("Assets/Model/Enemy/EnemyLeftMove.gpanim", true);
	mAnimTypes[static_cast<int>(EnemyState::eEnemyStateRightMove)] = RENDERER->GetAnimation("Assets/Model/Enemy/EnemyRightMove.gpanim", true);
	mAnimTypes[static_cast<int>(EnemyState::eEnemyStateImpactDamage)] = RENDERER->GetAnimation("Assets/Model/Enemy/EnemyImpact.gpanim", false);
	mAnimTypes[static_cast<int>(EnemyState::eEnemyStateSweepFallDamage)] = RENDERER->GetAnimation("Assets/Model/Enemy/EnemySweepFall.gpanim", false);
	mAnimTypes[static_cast<int>(EnemyState::eEnemyStateFlyingBackDamage)] = RENDERER->GetAnimation("Assets/Model/Enemy/EnemyFlyingBack.gpanim", false);
	mAnimTypes[static_cast<int>(EnemyState::eEnemyStateStandUp)] = RENDERER->GetAnimation("Assets/Model/Enemy/EnemyStandUp.gpanim", false);
	mAnimTypes[static_cast<int>(EnemyState::eEnemyStateFallingBackDeath)] = RENDERER->GetAnimation("Assets/Model/Enemy/EnemyFallingBack.gpanim", false);
	mAnimTypes[static_cast<int>(EnemyState::eEnemyStateSweepFallDeath)] = RENDERER->GetAnimation("Assets/Model/Enemy/EnemySweepFall.gpanim", false);
	mAnimTypes[static_cast<int>(EnemyState::eEnemyStateFlyingBackDeath)] = RENDERER->GetAnimation("Assets/Model/Enemy/EnemyFlyingBack.gpanim", false);

	//Rendererクラス内のSkeletonデータ読み込み関数を利用してAnimationをセット(.gpanim)
	const Animation* anim = mAnimTypes[static_cast<int>(EnemyState::eEnemyStateTrack)];
	//anim変数を速度1.0fで再生
	mSkeltalMeshComponentPtr->PlayAnimation(anim);

	// エネミーの攻撃判定生成
	mEnemyAttackPtr = new EnemyAttackDecisionObject(this, Tag::eEnemyAttackDecision);

	// ヒットエフェクト生成
	new HitEffect(this, MHitEffectScale, Tag::eHItEffect);

	// アクターステートプールの初期化
	mStatePools.push_back(new EnemyObjectStateTrack(_playerPtr));	                                // mStatePool[eEnemyStateTrack]
	mStatePools.push_back(new EnemyObjectStateWait(_playerPtr));	                                // mStatepool[eEnemyStateWait]
	mStatePools.push_back(new EnemyObjectStateAttack(mEnemyAttackPtr));                             // mStatepool[eEnemyStateAttack]
	mStatePools.push_back(new EnemyObjectStateAttackReady);                                         // mStatepool[eEnemyStateAttackReady]
	mStatePools.push_back(new EnemyObjectStateMove(EnemyState::eEnemyStateLeftMove, _playerPtr));	// mStatepool[eEnemyStateLeftMove]
	mStatePools.push_back(new EnemyObjectStateMove(EnemyState::eEnemyStateRightMove, _playerPtr));	// mStatepool[eEnemyStateRightMove]
	mStatePools.push_back(new EnemyObjectStateImpactDamage(_playerPtr));                            // mStatepool[eEnemyStateImpactDamage];
	mStatePools.push_back(new EnemyObjectStateSweepFallDamage(_playerPtr));                            // mStatepool[eEnemyStateImpactDamage];
	mStatePools.push_back(new EnemyObjectStateFlyingBackDamage(_playerPtr));                            // mStatepool[eEnemyStateImpactDamage];
	mStatePools.push_back(new EnemyObjectStateStandUp(_playerPtr));                            // mStatepool[eEnemyStateImpactDamage];
	mStatePools.push_back(new EnemyObjectStateFallingBackDeath(_playerPtr));                            // mStatepool[eEnemyStateImpactDamage];
	mStatePools.push_back(new EnemyObjectStateSweepFallDeath(_playerPtr));                            // mStatepool[eEnemyStateImpactDamage];
	mStatePools.push_back(new EnemyObjectStateFlyingBackDeath(_playerPtr));                         // mStatepool[eEnemyStateFlyingBackDeath];

	// 矩形当たり判定
	mBox = AABB(Vector3(-45.0f, -45.0f, 0.0f), Vector3(45.0f, 45.0f, 170.0f));

	mBoxColliderPtr = new BoxCollider(this, _ObjectTag, GetOnCollisionFunc());
	mBoxColliderPtr->SetObjectBox(mBox);

	// エネミーのhpゲージを生成
	mEnemyHitPointGaugePtr = new EnemyHitPointGauge(MHpGaugeScale, "Assets/Texture/EnemyHpGauge.png", Tag::eOther, this);
	mEnemyHitPointGaugePtr->SetState(eActive);
	// エネミーのhpの枠を生成
	mEnemyHitPointFramePtr = new EnemyHitPointFrame(MHpGaugeScale, "Assets/Texture/EnemyHpFrame.png", Tag::eOther, this);
	mEnemyHitPointFramePtr->SetState(eActive);

}

/// <summary>
/// エネミー同士の引き離し
/// </summary>
/// <param name="_DirTargetEnemyVec"> 対象となるエネミーに向いたベクトル </param>
void EnemyObject::Separation(const Vector3& _DirTargetEnemyVec)
{
	mStatePools[static_cast<int>(mNowState)]->Separation(this, _DirTargetEnemyVec);
}

/// <summary>
/// オブジェクトの更新処理
/// </summary>
/// <param name="_deltaTime"> 最後のフレームを完了するのに要した時間 </param>
void EnemyObject::UpdateGameObject(float _deltaTime)
{
	// ステート外部からステート変更があったか？
	if (mNowState != mNextState)
	{
		mStatePools[static_cast<int>(mNowState)]->Exit(this, _deltaTime);
		mStatePools[static_cast<int>(mNextState)]->Enter(this, _deltaTime);
		mNowState = mNextState;
		return;
	}

	// ステート実行
	mNextState = mStatePools[static_cast<int>(mNowState)]->Update(this, _deltaTime);

	// ステート内部からステート変更あったか？
	if (mNowState != mNextState)
	{
		mStatePools[static_cast<int>(mNowState)]->Exit(this, _deltaTime);
		mStatePools[static_cast<int>(mNextState)]->Enter(this, _deltaTime);
		mNowState = mNextState;
	}
}

/// <summary>
/// ヒットした時の処理
/// </summary>
/// <param name="_HitObject"> ヒットしたゲームオブジェクト </param>
void EnemyObject::OnCollision(const GameObject& _HitObject)
{
	// オブジェクトのタグ
	Tag tag = _HitObject.GetTag();

	mBox = mBoxColliderPtr->GetWorldBox();

	if (tag == eWall ||
		tag == eGate ||
		tag == eGateDoor ||
		tag == eEnemyGenerator ||
		tag == ePlayer)
	{
		//押し戻し処理
		float dx1 = _HitObject.GetObjectAABB().m_min.x - mBox.m_max.x;
		float dx2 = _HitObject.GetObjectAABB().m_max.x - mBox.m_min.x;
		float dy1 = _HitObject.GetObjectAABB().m_min.y - mBox.m_max.y;
		float dy2 = _HitObject.GetObjectAABB().m_max.y - mBox.m_min.y;

		float dx = Math::Abs(dx1) < Math::Abs(dx2) ? dx1 : dx2;
		float dy = Math::Abs(dy1) < Math::Abs(dy2) ? dy1 : dy2;

		if (Math::Abs(dx) <= Math::Abs(dy))
		{
			mPosition.x += dx;
		}
		else if (Math::Abs(dy) <= Math::Abs(dx))
		{
			mPosition.y += dy;
		}

		SetPosition(mPosition);
	}

	mStatePools[static_cast<int>(mNowState)]->OnCollision(this, _HitObject);
}