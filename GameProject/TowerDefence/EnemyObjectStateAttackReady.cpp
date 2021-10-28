#include "pch.h"

/// <summary>
/// コンストラクタ
/// </summary>
EnemyObjectStateAttackReady::EnemyObjectStateAttackReady()
    : MVecShortenVelue(0.1f)
    , MSeparationVecLength(8.0f)
	, mIsDamage(false)
	, mDamageValue(0)
	, MDamageValuePlayerFirstAttack(25)
	, mPosition(Vector3::Zero)
	, mVelocity(Vector3::Zero)
{
}

/// <summary>
/// 更新処理
/// </summary>
/// <param name="_owner"> エネミー(親)のポインタ </param>
/// <param name="_DeltaTime"> 最後のフレームを完了するのに要した時間 </param>
/// <returns> エネミーの状態 </returns>
EnemyState EnemyObjectStateAttackReady::Update(EnemyObject* _owner, const float _DeltaTime)
{
	_owner->SetPosition(mPosition);
	
	if (mIsDamage)
	{
		return EnemyState::eEnemyStateDamage;
	}

	// アニメーションが終了したら攻撃状態へ遷移
	if (!_owner->GetSkeletalMeshComponentPtr()->IsPlaying())
	{
		return EnemyState::eEnemyStateAttack;
	}

	return EnemyState::eEnemyStateAttackReady;
}

/// <summary>
/// エネミーの状態が変更して、最初に1回だけ呼び出される関数
/// </summary>
/// <param name="_owner"> エネミー(親)のポインタ </param>
/// <param name="_DeltaTime"> 最後のフレームを完了するのに要した時間 </param>
void EnemyObjectStateAttackReady::Enter(EnemyObject* _owner, const float _DeltaTime)
{
	SkeletalMeshComponent* meshcomp = _owner->GetSkeletalMeshComponentPtr();
	meshcomp->PlayAnimation(_owner->GetAnimPtr(EnemyState::eEnemyStateAttackReady));
	mIsDamage = false;

	// 座標
	mPosition = _owner->GetPosition();
}

/// <summary>
/// エネミー同士の引き離し
/// </summary>
/// <param name="_owner"> エネミー(親)のポインタ </param>
/// <param name="_DirTargetEnemyVec"> 対象となるエネミーに向いたベクトル </param>
void EnemyObjectStateAttackReady::Separation(EnemyObject* _owner, const Vector3& _DirTargetEnemyVec)
{
	// 座標
	mPosition = _owner->GetPosition();
	// 引き離しベクトル
	Vector3 separationVec = MSeparationVecLength * _DirTargetEnemyVec;

	mVelocity -= separationVec;
	mVelocity *= MVecShortenVelue;
	mPosition += mVelocity;

	_owner->SetPosition(mPosition);
}

/// <summary>
/// ヒットした時の処理
/// </summary>
/// <param name="_owner"> エネミー(親)のポインタ </param>
/// <param name="_HitObject"> ヒットしたゲームオブジェクト </param>
void EnemyObjectStateAttackReady::OnCollision(EnemyObject* _owner, const GameObject& _HitObject)
{
	// 座標
	mPosition = _owner->GetPosition();

	// オブジェクトのタグ
	Tag tag = _HitObject.GetTag();

	if (tag == Tag::eFirstAttackEffect)
	{
		mDamageValue = MDamageValuePlayerFirstAttack;
		mIsDamage = true;
	}

	_owner->SetDamageValue(mDamageValue);
}