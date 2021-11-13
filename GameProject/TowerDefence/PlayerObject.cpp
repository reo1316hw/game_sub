#include "pch.h"

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="_Pos"> 座標 </param>
/// <param name="_Scale"> 大きさ </param>
/// <param name="_GpmeshName"> gpmeshのパス </param>
/// <param name="_GpskelName"> gpskelのパス </param>
/// <param name="_ObjectTag"> オブジェクトのタグ </param>
PlayerObject::PlayerObject(const Vector3& _Pos, const Vector3& _Scale, const char* _GpmeshName, const char* _GpskelName, const Tag& _ObjectTag)
	: GameObject(_ObjectTag)
	, MMaxHp(100)
	, MPlayRate(1.0f)
	, MAngle(270.0f)
	, MAttackEffectScale(Vector3(50.0f, -50.0f, 50.0f))
	, MHitEffectScale(Vector3(25.0f, -25.0f, 25.0f))
	, mNowState(PlayerState::ePlayerStateIdle)
	, mNextState(PlayerState::ePlayerStateIdle)
	, mSkeltalMeshComponentPtr(nullptr)
	, mMainCameraPtr(nullptr)
	, mRunLoopPtr(nullptr)
	, mSprintStartPtr(nullptr)
	, mSprintLoopPtr(nullptr)
	, mFirstAttackPtr(nullptr)
	, mSecondAttackPtr(nullptr)
	, mThirdAttackPtr(nullptr)
{
	// GameObjectメンバ変数の初期化
	SetScale(_Scale);
	SetPosition(_Pos);
	mMaxHp = MMaxHp;
	mHitPoint = mMaxHp;

	// 生成 TestObjectの生成時と同じくComponent基底クラスは自動で管理クラスに追加され自動で解放される
	mSkeltalMeshComponentPtr = new SkeletalMeshComponent(this);
	// Rendererクラス内のMesh読み込み関数を利用してMeshをセット(.gpmesh)
	mSkeltalMeshComponentPtr->SetMesh(RENDERER->GetMesh(_GpmeshName));
	// Rendererクラス内のSkeletonデータ読み込み関数を利用してSkeletonをセット(.gpskel)
	mSkeltalMeshComponentPtr->SetSkeleton(RENDERER->GetSkeleton(_GpskelName));

	// アニメーションの取得 & アニメーション配列にセット
	mAnimTypes.resize(static_cast<int>(PlayerState::ePlayerStateNum));
	mAnimTypes[static_cast<int>(PlayerState::ePlayerStateIdle)] = RENDERER->GetAnimation("Assets/Model/Player/PlayerIdle.gpanim", true);
	mAnimTypes[static_cast<int>(PlayerState::ePlayerStateRunLoop)] = RENDERER->GetAnimation("Assets/Model/Player/PlayerRun.gpanim", true);
	mAnimTypes[static_cast<int>(PlayerState::ePlayerStateSprintStart)] = RENDERER->GetAnimation("Assets/Model/Player/PlayerSprintStart.gpanim", false);
	mAnimTypes[static_cast<int>(PlayerState::ePlayerStateSprintLoop)] = RENDERER->GetAnimation("Assets/Model/Player/PlayerSprint.gpanim", true);
	mAnimTypes[static_cast<int>(PlayerState::ePlayerStateFirstAttack)] = RENDERER->GetAnimation("Assets/Model/Player/PlayerFirstAttack.gpanim", false);
	mAnimTypes[static_cast<int>(PlayerState::ePlayerStateSecondAttack)] = RENDERER->GetAnimation("Assets/Model/Player/PlayerSecondAttack.gpanim", false);
	mAnimTypes[static_cast<int>(PlayerState::ePlayerStateThirdAttack)] = RENDERER->GetAnimation("Assets/Model/Player/PlayerThirdAttack.gpanim", false);
	mAnimTypes[static_cast<int>(PlayerState::ePlayerStateDashAttack)] = RENDERER->GetAnimation("Assets/Model/Player/PlayerDashAttack.gpanim", false);
	mAnimTypes[static_cast<int>(PlayerState::ePlayerStateDamage)] = RENDERER->GetAnimation("Assets/Model/Player/PlayerDamage.gpanim", false);
	mAnimTypes[static_cast<int>(PlayerState::ePlayerStateDeath)] = RENDERER->GetAnimation("Assets/Model/Player/PlayerDeath.gpanim", false);

	// Rendererクラス内のSkeletonデータ読み込み関数を利用してAnimationをセット(.gpanim)
	const Animation* anim = mAnimTypes[static_cast<int>(PlayerState::ePlayerStateIdle)];
	// anim変数を速度1.0fで再生
	mSkeltalMeshComponentPtr->PlayAnimation(anim, MPlayRate);

	// 死亡状態のクラスのポインタ
	PlayerObjectStateDeath* deathPtr = nullptr;
	// ダッシュ攻撃状態のクラスのポインタ
	PlayerObjectStateDashAttack* dashAttackPtr = nullptr;

	// アクターステートプールの初期化
	mStatePools.push_back(new PlayerObjectStateIdle());	                  // mStatePool[ePlayerStateIdle]
	mStatePools.push_back(mRunLoopPtr = new PlayerObjectStateRunLoop);	              // mStatepool[ePlayerStateRunLoop]
	mStatePools.push_back(mSprintStartPtr = new PlayerObjectStateSprintStart);              // mStatepool[ePlayerStateSprintStart]
	mStatePools.push_back(mSprintLoopPtr = new PlayerObjectStateSprintLoop);	              // mStatepool[ePlayerStateSprintLoop]
	mStatePools.push_back(mFirstAttackPtr = new PlayerObjectStateFirstAttack);  // mStatepool[ePlayerStateFirstAttack];
	mStatePools.push_back(mSecondAttackPtr = new PlayerObjectStateSecondAttack); // mStatepool[ePlayerStateSecondAttack];
	mStatePools.push_back(mThirdAttackPtr = new PlayerObjectStateThirdAttack);  // mStatepool[ePlayerStateThirdAttack];
	mStatePools.push_back(dashAttackPtr = new PlayerObjectStateDashAttack);   // mStatepool[ePlayerStateDashAttack];
	mStatePools.push_back(new PlayerObjectStateDamage);	                  // mStatepool[ePlayerStateDamage]
	mStatePools.push_back(deathPtr = new PlayerObjectStateDeath);	      // mStatepool[ePlayerStateDeath]

	// 武器
	new PlayerWeaponObject(mSkeltalMeshComponentPtr, "Assets/Model/Sword/Sword.gpmesh", Tag::eWeapon, deathPtr);

	// 1段階目の通常攻撃エフェクトを生成
	FirstAttackEffect* firstAttackEffectPtr = new FirstAttackEffect(this, MAttackEffectScale, Tag::eFirstAttackEffect, mFirstAttackPtr);
	// 2段階目の通常攻撃エフェクトを生成
	SecondAttackEffect* secondAttackEffectPtr = new SecondAttackEffect(this, MAttackEffectScale, Tag::eSecondAttackEffect, mSecondAttackPtr);
	// 3段階目の通常攻撃エフェクトを生成
	ThirdAttackEffect* thirdAttackEffectPtr = new ThirdAttackEffect(this, MAttackEffectScale, Tag::eThirdAttackEffect, mThirdAttackPtr);
	// ダッシュ攻撃エフェクトを生成
	DashAttackEffect* dashEffectPtr = new DashAttackEffect(this, MAttackEffectScale, Tag::eDashAttackEffect, dashAttackPtr);

	// 1段階目の通常攻撃状態クラスに1段階目の通常攻撃エフェクトクラスのポインタを渡す
	mFirstAttackPtr->SetFirstAttackEffectPtr(firstAttackEffectPtr);
	// 2段階目の通常攻撃状態クラスに2段階目の通常攻撃エフェクトクラスのポインタを渡す
	mSecondAttackPtr->SetSecondAttackEffectPtr(secondAttackEffectPtr);
	// 3段階目の通常攻撃状態クラスに3段階目の通常攻撃エフェクトクラスのポインタを渡す
	mThirdAttackPtr->SetThirdAttackEffectPtr(thirdAttackEffectPtr);
	// ダッシュ攻撃状態クラスにダッシュ攻撃エフェクトクラスのポインタを渡す
	dashAttackPtr->SetDashAttackEffectPtr(dashEffectPtr);

	// ヒットエフェクト生成
	new HitEffect(this, MHitEffectScale, Tag::eHItEffect);

	// 矩形当たり判定
	mBox = AABB(Vector3(-30.0f, -30.0f, 0.0f), Vector3(30.0f, 30.0f, 170.0f));

	mBoxColliderPtr = new BoxCollider(this, _ObjectTag, GetOnCollisionFunc());
	mBoxColliderPtr->SetObjectBox(mBox);

	// 回転処理
	SelfRotation(Vector3::UnitZ, MAngle);
}

/// <summary>
/// オブジェクトの更新処理
/// </summary>
/// <param name="_deltaTime"> 最後のフレームを完了するのに要した時間 </param>
void PlayerObject::UpdateGameObject(float _deltaTime)
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
/// 入力を引数で受け取る更新関数
/// 基本的にここで入力情報を変数に保存しUpdateGameObjectで更新を行う
/// </summary>
/// <param name="_KeyState"> キーボード、マウス、コントローラーの入力状態 </param>
void PlayerObject::GameObjectInput(const InputState& _KeyState)
{
	mStatePools[static_cast<int>(mNowState)]->Input(this, _KeyState);
}

/// <summary>
/// 回転処理
/// </summary>
/// <param name="_Axis"> 軸 </param>
/// <param name="_Angle"> 角度 </param>
void PlayerObject::SelfRotation(Vector3 _axis, float _angle)
{
	float radian = Math::ToRadians(_angle);
	Quaternion rot = mRotation;
	Quaternion inc(_axis, radian);
	Quaternion target = Quaternion::Concatenate(rot, inc);
	SetRotation(target);
}

/// <summary>
/// ヒットした時の処理
/// </summary>
/// <param name="_HitObject"> ヒットしたゲームオブジェクト </param>
void PlayerObject::OnCollision(const GameObject& _HitObject)
{
	//// オブジェクトのタグ
	//Tag tag = _HitObject.GetTag();

	//if (tag == eWall)
	//{
	//	//押し戻し処理
	//	float dx1 = _HitObject.GetObjectAABB().m_min.x - mBox.m_max.x;
	//	float dx2 = _HitObject.GetObjectAABB().m_max.x - mBox.m_min.x;
	//	float dy1 = _HitObject.GetObjectAABB().m_min.y - mBox.m_max.y;
	//	float dy2 = _HitObject.GetObjectAABB().m_max.y - mBox.m_min.y;
	//	float dz1 = _HitObject.GetObjectAABB().m_min.z - mBox.m_max.z;
	//	float dz2 = _HitObject.GetObjectAABB().m_max.z - mBox.m_min.z;

	//	float dx = Math::Abs(dx1) < Math::Abs(dx2) ? dx1 : dx2;
	//	float dy = Math::Abs(dy1) < Math::Abs(dy2) ? dy1 : dy2;
	//	float dz = Math::Abs(dz1) < Math::Abs(dz2) ? dz1 : dz2;

	//	if (Math::Abs(dx) <= Math::Abs(dy))
	//	{
	//		mPosition.x += dx;
	//	}
	//	else if (Math::Abs(dy) <= Math::Abs(dx))
	//	{
	//		mPosition.y += dy;
	//	}

	//	SetPosition(mPosition);
	//}

	mStatePools[static_cast<int>(mNowState)]->OnCollision(this, _HitObject);
}

/// <summary>
/// カメラのポインタを設定
/// </summary>
/// <param name="_mainCameraPtr"> カメラのポインタ </param>
void PlayerObject::SetMainCameraPtr(MainCameraObject* _mainCameraPtr)
{
	mRunLoopPtr->SetMainCameraPtr(_mainCameraPtr);
	mSprintStartPtr->SetMainCameraPtr(_mainCameraPtr);
	mSprintLoopPtr->SetMainCameraPtr(_mainCameraPtr);
	mFirstAttackPtr->SetMainCameraPtr(_mainCameraPtr);
	mSecondAttackPtr->SetMainCameraPtr(_mainCameraPtr);
	mThirdAttackPtr->SetMainCameraPtr(_mainCameraPtr);
}