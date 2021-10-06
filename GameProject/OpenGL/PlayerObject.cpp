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
PlayerObject::PlayerObject(const Vector3& _Pos, const Vector3& _Scale, const char* _GpmeshName, const char* _GpskelName, const Tag& _ObjectTag, const SceneBase::Scene _SceneTag)
    : GameObject(_ObjectTag, _SceneTag)
    , MCameraOffset(Vector3(-150.0f,-150.0f,-150.0f))
	, MTargetOffset(Vector3(0.0f, 0.0f, 40.0f))
	, MPlayRate(1.0f)
	, MAngle(270.0f)
    , mTargetPos(Vector3::Zero)
    , mCameraPos(Vector3::Zero)
    , mNowState(PlayerState::ePlayerStateIdle)
    , mNextState(PlayerState::ePlayerStateIdle)
	, mSkeltalMeshComponentPtr(nullptr)
{
	// GameObjectメンバ変数の初期化
	mTag = _ObjectTag;
	SetScale(_Scale);
	SetPosition(_Pos);

	// 生成 TestObjectの生成時と同じくComponent基底クラスは自動で管理クラスに追加され自動で解放される
	mSkeltalMeshComponentPtr = new SkeletalMeshComponent(this);
	// Rendererクラス内のMesh読み込み関数を利用してMeshをセット(.gpmesh)
	mSkeltalMeshComponentPtr->SetMesh(RENDERER->GetMesh(_GpmeshName));
	// Rendererクラス内のSkeletonデータ読み込み関数を利用してSkeletonをセット(.gpskel)
	mSkeltalMeshComponentPtr->SetSkeleton(RENDERER->GetSkeleton(_GpskelName));

	// アニメーションの取得 & アニメーション配列にセット
	mAnimTypes.resize(static_cast<int>(PlayerState::ePlayerStateNum));
	mAnimTypes[static_cast<int>(PlayerState::ePlayerStateIdle)] = RENDERER->GetAnimation("Assets/Model/Player/PlayerSwordIdle.gpanim", true);
	mAnimTypes[static_cast<int>(PlayerState::ePlayerStateRunLoop)] = RENDERER->GetAnimation("Assets/Model/Player/PlayerSwordRun.gpanim", true);
	mAnimTypes[static_cast<int>(PlayerState::ePlayerStateSprintStart)] = RENDERER->GetAnimation("Assets/Model/Player/PlayerIdleToRun.gpanim", false);
	mAnimTypes[static_cast<int>(PlayerState::ePlayerStateSprintLoop)] = RENDERER->GetAnimation("Assets/Model/Player/PlayerFastRun.gpanim", true);
	mAnimTypes[static_cast<int>(PlayerState::ePlayerStateFirstAttack)] = RENDERER->GetAnimation("Assets/Model/Player/PlayerAttack01.gpanim", false);
	mAnimTypes[static_cast<int>(PlayerState::ePlayerStateSecondAttack)] = RENDERER->GetAnimation("Assets/Model/Player/PlayerAttack02.gpanim", false);
	mAnimTypes[static_cast<int>(PlayerState::ePlayerStateThirdAttack)] = RENDERER->GetAnimation("Assets/Model/Player/PlayerAttack03.gpanim", false);
	mAnimTypes[static_cast<int>(PlayerState::ePlayerStateDashAttack)] = RENDERER->GetAnimation("Assets/Model/Player/PlayerDashAttack.gpanim", false);

	// Rendererクラス内のSkeletonデータ読み込み関数を利用してAnimationをセット(.gpanim)
	const Animation* anim = mAnimTypes[static_cast<int>(PlayerState::ePlayerStateIdle)];
	// anim変数を速度1.0fで再生
	mSkeltalMeshComponentPtr->PlayAnimation(anim, MPlayRate);

	// 武器
	new PlayerWeaponObject(this, mSkeltalMeshComponentPtr, "Assets/Model/Sword/Sword.gpmesh", Tag::Weapon, _SceneTag);

	// アクターステートプールの初期化
	mStatePools.push_back(new PlayerObjectStateIdle());	      // mStatePool[ePlayerStateIdle]
	mStatePools.push_back(new PlayerObjectStateRunLoop);	  // mStatepool[ePlayerStateRunLoop]
	mStatePools.push_back(new PlayerObjectStateSprintStart);  // mStatepool[ePlayerStateSprintStart]
	mStatePools.push_back(new PlayerObjectStateSprintLoop);	  // mStatepool[ePlayerStateSprintLoop]
	mStatePools.push_back(new PlayerObjectStateFirstAttack);  // mStatepool[ePlayerStateFirstAttack];
	mStatePools.push_back(new PlayerObjectStateSecondAttack); // mStatepool[ePlayerStateSecondAttack];
	mStatePools.push_back(new PlayerObjectStateThirdAttack);  // mStatepool[ePlayerStateThirdAttack];
	mStatePools.push_back(new PlayerObjectStateDashAttack);   // mStatepool[ePlayerStateDashAttack];
	
	//// メッシュ当たり判定
	//mMeshPtr = RENDERER->GetMesh(_GpmeshName);
	//mBoxColliderPtr = new BoxCollider(this, ColliderTag::Player, GetOnCollisionFunc());
	//mBoxColliderPtr->SetObjectBox(mMeshPtr->GetBox());

	// 矩形当たり判定
	mBox = AABB(Vector3(-30.0f, -30.0f, 0.0f), Vector3(30.0f, 30.0f, 180.0f));

	mBoxColliderPtr = new BoxCollider(this, ColliderTag::Player, GetOnCollisionFunc());
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
	mTargetPos = mPosition + MTargetOffset;
	mCameraPos = mMainCamera->GetPosition();
	// 見たい座標の設定
	mMainCamera->SetViewObject(MCameraOffset, mTargetPos);

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
	Quaternion rot = this->GetRotation();
	Quaternion inc(_axis, radian);
	Quaternion target = Quaternion::Concatenate(rot, inc);
	SetRotation(target);
}

/// <summary>
/// ヒットされた時の処理
/// </summary>
/// <param name="_HitObject"> ヒットしたゲームオブジェクト </param>
void PlayerObject::OnCollision(const GameObject& _HitObject)
{
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

	if (Math::Abs(dx) <= Math::Abs(dy)/* && Math::Abs(dx) <= Math::Abs(dz)*/)
	{
		mPosition.x += dx;
	}
	else if (Math::Abs(dy) <= Math::Abs(dx) /*&& Math::Abs(dy) <= Math::Abs(dz)*/)
	{
		mPosition.y += dy;
	}
	//else
	//	//if (Math::Abs(dz) <= Math::Abs(dx) && Math::Abs(dz) <= Math::Abs(dy))
	//{
	//	mPosition.z += dz;
	//}

	SetPosition(mPosition);
}