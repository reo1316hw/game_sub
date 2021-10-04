#include "pch.h"

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="_Pos"> 座標 </param>
/// <param name="_Scale"> 大きさ </param>
/// <param name="_GpmeshName"> gpmeshのパス </param>
/// <param name="_GpskelName"> gpskelのパス </param>
/// <param name="_ObjectTag"> タグ </param>
/// <param name="_SceneTag"> シーンタグ </param>
/// <param name="_playerPtr"> プレイヤーのポインタ </param>
EnemyObject::EnemyObject(const Vector3& _Pos, const Vector3& _Scale, const std::string _GpmeshName, const char* _GpskelName,
	                     const Tag& _ObjectTag, const SceneBase::Scene _SceneTag, PlayerObject* _playerPtr)
	: GameObject(_ObjectTag, _SceneTag)
	, MPlayRate(1.0f)
	, mBox(Vector3::Zero, Vector3::Zero)
	, mNowState(EnemyState::eEnemyStateTrack)
	, mNextState(EnemyState::eEnemyStateTrack)
{
	//GameObjectメンバ変数の初期化
	mTag = _ObjectTag;
	SetScale(_Scale);
	SetPosition(_Pos);

	///生成 TestObjectの生成時と同じくComponent基底クラスは自動で管理クラスに追加され自動で解放される
	mSkeltalMeshComponentPtr = new SkeletalMeshComponent(this);
	//Rendererクラス内のMesh読み込み関数を利用してMeshをセット(.gpmesh)
	mSkeltalMeshComponentPtr->SetMesh(RENDERER->GetMesh(_GpmeshName));
	//Rendererクラス内のSkeletonデータ読み込み関数を利用してSkeletonをセット(.gpskel)
	mSkeltalMeshComponentPtr->SetSkeleton(RENDERER->GetSkeleton(_GpskelName));

	// アニメーションの取得 & アニメーション配列にセット
	mAnimTypes.resize(static_cast<int>(EnemyState::eEnemyStateNum));
	mAnimTypes[static_cast<int>(EnemyState::eEnemyStateTrack)] = RENDERER->GetAnimation("Assets/Model/Enemy/EnemyIdle.gpanim", true);
	//mAnimTypes[static_cast<int>(EnemyState::eEnemyStateWait)] = RENDERER->GetAnimation("Assets/Model/Player/PlayerSwordRun.gpanim", true);
	//mAnimTypes[static_cast<int>(EnemyState::eEnemyStateAttack)] = RENDERER->GetAnimation("Assets/Model/Player/PlayerIdleToRun.gpanim", false);
	//mAnimTypes[static_cast<int>(EnemyState::eEnemyStateMove)] = RENDERER->GetAnimation("Assets/Model/Player/PlayerFastRun.gpanim", true);

	//Rendererクラス内のSkeletonデータ読み込み関数を利用してAnimationをセット(.gpanim)
	const Animation* anim = mAnimTypes[static_cast<int>(EnemyState::eEnemyStateTrack)];
	//anim変数を速度1.0fで再生
	mSkeltalMeshComponentPtr->PlayAnimation(anim, 1.0f);

	//// アクターステートプールの初期化
	mStatePools.push_back(new EnemyObjectStateTrack(_playerPtr));	      // mStatePool[eEnemyStateTrack]
	//mStatePools.push_back(new PlayerObjectStateRunLoop);	  // mStatepool[ePlayerStateRunLoop]
	//mStatePools.push_back(new PlayerObjectStateSprintStart);  // mStatepool[ePlayerStateSprintStart]
	//mStatePools.push_back(new PlayerObjectStateSprintLoop);	  // mStatepool[ePlayerStateSprintLoop]
	//mStatePools.push_back(new PlayerObjectStateFirstAttack);  // mStatepool[ePlayerStateFirstAttack];
	//mStatePools.push_back(new PlayerObjectStateSecondAttack); // mStatepool[ePlayerStateSecondAttack];
	//mStatePools.push_back(new PlayerObjectStateThirdAttack);  // mStatepool[ePlayerStateThirdAttack];
	//mStatePools.push_back(new PlayerObjectStateDashAttack);   // mStatepool[ePlayerStateDashAttack];

	// 当たり判定
	mMeshPtr = new Mesh;
	mMeshPtr = RENDERER->GetMesh(_GpmeshName);
	mBoxColliderPtr = new BoxCollider(this, ColliderTag::Enemy, GetOnCollisionFunc());
	mBoxColliderPtr->SetObjectBox(mMeshPtr->GetBox());
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
/// ヒットされた時の処理
/// </summary>
/// <param name="_HitObject"> ヒットしたゲームオブジェクト </param>
void EnemyObject::OnCollision(const GameObject& _HitObject)
{
	mBox = mBoxColliderPtr->GetWorldBox();

	//押し戻し処理
	float dx1 = _HitObject.GetObjectAABB().m_min.x - mBox.m_max.x;
	float dx2 = _HitObject.GetObjectAABB().m_max.x - mBox.m_min.x;
	float dy1 = _HitObject.GetObjectAABB().m_min.y - mBox.m_max.y;
	float dy2 = _HitObject.GetObjectAABB().m_max.y - mBox.m_min.y;
	float dz1 = _HitObject.GetObjectAABB().m_min.z - mBox.m_max.z;
	float dz2 = _HitObject.GetObjectAABB().m_max.z - mBox.m_min.z;

	float dx = Math::Abs(dx1) < Math::Abs(dx2) ? dx1 : dx2;
	float dy = Math::Abs(dy1) < Math::Abs(dy2) ? dy1 : dy2;
	float dz = Math::Abs(dz1) < Math::Abs(dz2) ? dz1 : dz2;

	if (Math::Abs(dx) <= Math::Abs(dy) && Math::Abs(dx) <= Math::Abs(dz))
	{
		mPosition.x += dx;
	}

	if (Math::Abs(dy) <= Math::Abs(dx) && Math::Abs(dy) <= Math::Abs(dz))
	{
		mPosition.y += dy;
	}

	if (Math::Abs(dz) <= Math::Abs(dx) && Math::Abs(dz) <= Math::Abs(dy))
	{
		mPosition.z += dz;
	}
}