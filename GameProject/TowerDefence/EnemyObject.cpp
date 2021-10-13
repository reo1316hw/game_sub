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
	mAnimTypes[static_cast<int>(EnemyState::eEnemyStateTrack)] = RENDERER->GetAnimation("Assets/Model/Enemy/EnemyTrack.gpanim", true);
	mAnimTypes[static_cast<int>(EnemyState::eEnemyStateWait)] = RENDERER->GetAnimation("Assets/Model/Enemy/EnemyWait.gpanim", true);
	mAnimTypes[static_cast<int>(EnemyState::eEnemyStateAttack)] = RENDERER->GetAnimation("Assets/Model/Enemy/EnemyAttack.gpanim", false);
	mAnimTypes[static_cast<int>(EnemyState::eEnemyStateLeftMove)] = RENDERER->GetAnimation("Assets/Model/Enemy/EnemyMove.gpanim", true);
	mAnimTypes[static_cast<int>(EnemyState::eEnemyStateRightMove)] = RENDERER->GetAnimation("Assets/Model/Enemy/EnemyMove.gpanim", true);
	mAnimTypes[static_cast<int>(EnemyState::eEnemyStateDamage)] = RENDERER->GetAnimation("Assets/Model/Enemy/EnemyDamage.gpanim", false);
	mAnimTypes[static_cast<int>(EnemyState::eEnemyStateDeath)] = RENDERER->GetAnimation("Assets/Model/Enemy/EnemyDeath.gpanim", false);

	//Rendererクラス内のSkeletonデータ読み込み関数を利用してAnimationをセット(.gpanim)
	const Animation* anim = mAnimTypes[static_cast<int>(EnemyState::eEnemyStateTrack)];
	//anim変数を速度1.0fで再生
	mSkeltalMeshComponentPtr->PlayAnimation(anim, 1.0f);

	// アクターステートプールの初期化
	mStatePools.push_back(new EnemyObjectStateTrack(_playerPtr));	// mStatePool[eEnemyStateTrack]
	mStatePools.push_back(new EnemyObjectStateWait(_playerPtr));	// mStatepool[eEnemyStateWait]
	mStatePools.push_back(new EnemyObjectStateAttack);              // mStatepool[eEnemyStateAttack]
	mStatePools.push_back(new EnemyObjectStateMove(EnemyState::eEnemyStateLeftMove, _playerPtr));	// mStatepool[eEnemyStateLeftMove]
	mStatePools.push_back(new EnemyObjectStateMove(EnemyState::eEnemyStateRightMove, _playerPtr));	// mStatepool[eEnemyStateRightMove]
	mStatePools.push_back(new EnemyObjectStateDamage);              // mStatepool[eEnemyStateDamage];
	mStatePools.push_back(new EnemyObjectStateDeath);               // mStatepool[eEnemyStateDeath];

	// 矩形当たり判定
	mBox = AABB(Vector3(-15.0f, -15.0f, 0.0f), Vector3(15.0f, 15.0f, 170.0f));

	mBoxColliderPtr = new BoxCollider(this, Tag::eEnemy, GetOnCollisionFunc());
	mBoxColliderPtr->SetObjectBox(mBox);
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

	mBox = mBoxColliderPtr->GetWorldBox();
}

/// <summary>
/// ヒットした時の処理
/// </summary>
/// <param name="_HitObject"> ヒットしたゲームオブジェクト </param>
void EnemyObject::OnCollision(const GameObject& _HitObject)
{
	mStatePools[static_cast<int>(mNowState)]->OnColision(this, _HitObject);
}