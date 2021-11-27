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
BossObject::BossObject(const Vector3& _Pos, const Vector3& _Scale, const std::string _GpmeshName, const char* _GpskelName,
	const Tag& _ObjectTag, PlayerObject* _playerPtr)
	: GameObject(_ObjectTag)
	, MMaxHp(500)
	, MPlayRate(1.0f)
	, MHitEffectScale(Vector3(10.0f, -10.0f, 10.0f))
	, MFrontMagicEffectScale(Vector3(15.0f, -15.0f, 15.0f))
	, MAreaMagicEffectScale(Vector3(60.0f, -60.0f, 60.0f))
	, MOverheadEffectScale(Vector3(20.0f, -20.0f, 20.0f))
	, MDangerSignalEffectScale(Vector3(40.0f, -40.0f, 40.0f))
	, MTeleportationEffectScale(Vector3(40.0f, -40.0f, 40.0f))
	, mInitPosition(Vector3::Zero)
	, mNowState(BossState::eBossStateWait)
	, mNextState(BossState::eBossStateTeleportation)
{
	//GameObjectメンバ変数の初期化
	SetScale(_Scale);
	SetPosition(_Pos);
	//SetState(State::eDead);
	mInitPosition = mPosition;
	mMaxHp = MMaxHp;
	mHitPoint = mMaxHp;
	// オブジェクトのスケールサイズを求めるための右辺の値を設定
	SetScaleRightSideValue(mHitPoint);

	///生成 TestObjectの生成時と同じくComponent基底クラスは自動で管理クラスに追加され自動で解放される
	mSkeltalMeshComponentPtr = new SkeletalMeshComponent(this);
	//Rendererクラス内のMesh読み込み関数を利用してMeshをセット(.gpmesh)
	mSkeltalMeshComponentPtr->SetMesh(RENDERER->GetMesh(_GpmeshName));
	//Rendererクラス内のSkeletonデータ読み込み関数を利用してSkeletonをセット(.gpskel)
	mSkeltalMeshComponentPtr->SetSkeleton(RENDERER->GetSkeleton(_GpskelName));

	// アニメーションの取得 & アニメーション配列にセット
	mAnimTypes.resize(static_cast<int>(EnemyState::eEnemyStateNum));
	mAnimTypes[static_cast<int>(BossState::eBossStateWait)] = RENDERER->GetAnimation("Assets/Model/Boss/BossWait.gpanim", true);
	mAnimTypes[static_cast<int>(BossState::eBossStateTrack)] = RENDERER->GetAnimation("Assets/Model/Boss/BossTrack.gpanim", true);
	mAnimTypes[static_cast<int>(BossState::eBossStateFrontAttack)] = RENDERER->GetAnimation("Assets/Model/Boss/BossFrontAttack.gpanim", false);
	mAnimTypes[static_cast<int>(BossState::eBossStateAreaAttack)] = RENDERER->GetAnimation("Assets/Model/Boss/BossAreaAttack.gpanim", false);
	mAnimTypes[static_cast<int>(BossState::eBossStateOverheadAttack)] = RENDERER->GetAnimation("Assets/Model/Boss/BossOverheadAttack.gpanim", false);
	mAnimTypes[static_cast<int>(BossState::eBossStateTeleportation)] = RENDERER->GetAnimation("Assets/Model/Boss/BossWait.gpanim", true);
	mAnimTypes[static_cast<int>(BossState::eBossStateImpactDamage)] = RENDERER->GetAnimation("Assets/Model/Boss/BossImpact.gpanim", false);
	mAnimTypes[static_cast<int>(BossState::eBossStateSweepFallDamage)] = RENDERER->GetAnimation("Assets/Model/Boss/BossSweepFall.gpanim", false);
	mAnimTypes[static_cast<int>(BossState::eBossStateFlyingBackDamage)] = RENDERER->GetAnimation("Assets/Model/Boss/BossFlyingBack.gpanim", false);
	mAnimTypes[static_cast<int>(BossState::eBossStateDeath)] = RENDERER->GetAnimation("Assets/Model/Boss/BossDeath.gpanim", false);

	//Rendererクラス内のSkeletonデータ読み込み関数を利用してAnimationをセット(.gpanim)
	const Animation* anim = mAnimTypes[static_cast<int>(BossState::eBossStateTeleportation)];
	//anim変数を速度1.0fで再生
	mSkeltalMeshComponentPtr->PlayAnimation(anim);

	// アクターステートプールの初期化
	mStatePools.push_back(new BossObjectStateWait(_playerPtr));	             // mStatePool[eBossStateWait]
	mStatePools.push_back(new BossObjectStateTrack(_playerPtr));	         // mStatepool[eBossStateTrack]
	mStatePools.push_back(new BossObjectStateFrontAttack(_playerPtr));       // mStatepool[eBossStateFrontAttack]
	mStatePools.push_back(new BossObjectStateAreaAttack(_playerPtr));        // mStatepool[eBossStateAreaAttack]
	mStatePools.push_back(new BossObjectStateOverheadAttack(_playerPtr));    // mStatepool[eBossObjectStateOverheadAttack]
	mStatePools.push_back(new BossObjectStateTeleportation(_playerPtr));     // mStatepool[eBossStateTeleportation]
	mStatePools.push_back(new BossObjectStateImpactDamage(_playerPtr));      // mStatepool[eBossStateImpactDamage]
	mStatePools.push_back(new BossObjectStateSweepFallDamage(_playerPtr));   // mStatepool[eBossStateSweepFallDamage]
	mStatePools.push_back(new BossObjectStateFlyingBackDamage(_playerPtr));  // mStatepool[eBossStateFlyingBackDamage]
	mStatePools.push_back(new BossObjectStateDeath(_playerPtr));             // mStatepool[eBossStateDeath]

	// ヒットエフェクト生成
	new HitEffect(this, MHitEffectScale, Tag::eHItEffect);

	// 前方攻撃エフェクト(中核の部分)を生成
	new FrontCoreMagicEffect(this, MFrontMagicEffectScale, Tag::eFrontCoreMagicEffect);
	// 前方攻撃エフェクト(レーザーの部分)を生成
	new FrontLaserMagicEffect(this, MFrontMagicEffectScale, Tag::eFrontLaserMagicEffect);
	// 範囲攻撃エフェクト生成
	new AreaMagicEffect(this, MAreaMagicEffectScale, Tag::eAreaMagicEffect);
	// プレイヤーの頭上に攻撃するエフェクトを生成
	new OverheadMagicEffect(this, _playerPtr, MOverheadEffectScale, Tag::eOverheadMagicEffect);
	// プレイヤー頭上攻撃時の危険信号エフェクト
	new DangerSignalEffect(this, _playerPtr, MDangerSignalEffectScale, Tag::eDangerSignalEffect);
	// テレポートエフェクト
	new TeleportationEffect(this, MTeleportationEffectScale, Tag::eTeleportationEffect);

	// 矩形当たり判定
	mBox = AABB(Vector3(-45.0f, -45.0f, 0.0f), Vector3(45.0f, 45.0f, 170.0f));

	mBoxColliderPtr = new BoxCollider(this, _ObjectTag, GetOnCollisionFunc());
	mBoxColliderPtr->SetObjectBox(mBox);
}

/// <summary>
/// ボスとエネミーの引き離し
/// </summary>
/// <param name="_DirTargetEnemyVec"> 対象となるエネミーに向いたベクトル </param>
void BossObject::Separation(const Vector3& _DirTargetEnemyVec)
{
	mStatePools[static_cast<int>(mNowState)]->Separation(this, _DirTargetEnemyVec);
}

/// <summary>
/// オブジェクトの更新処理
/// </summary>
/// <param name="_deltaTime"> 最後のフレームを完了するのに要した時間 </param>
void BossObject::UpdateGameObject(float _deltaTime)
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

	mBox = mBoxColliderPtr->GetWorldBox();
}

/// <summary>
/// ヒットした時の処理
/// </summary>
/// <param name="_HitObject"> ヒットしたゲームオブジェクト </param>
void BossObject::OnCollision(const GameObject& _HitObject)
{
	// オブジェクトのタグ
	Tag tag = _HitObject.GetTag();

	mBox = mBoxColliderPtr->GetWorldBox();

	if (tag == eWall ||
		tag == eGate ||
		tag == eGateDoor ||
		tag == eEnemyGenerator ||
		tag == ePlayer ||
		tag == eBossBootSemitransparentWall)
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