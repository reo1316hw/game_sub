#include "pch.h"

int GameObject::mGameObjectId = 0;
PauzingEvent GameObject::mPauzingEvent = PauzingEvent::NoneEvent;

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="_ObjectTag"> オブジェクトのタグ </param>
/// <param name="_reUseGameObject"> 再利用するか </param>
GameObject::GameObject(const Tag& _objectTag, bool _reUseGameObject)
	: mState(eActive)
	, mWorldTransform()
	, mPosition(Vector3::Zero)
	, mVelocity(Vector3::Zero)
	, mBox(Vector3::Zero, Vector3::Zero)
	, mScale(Vector3(1.0f, 1.0f, 1.0f))
	, mRotation(Quaternion::Identity)
	, mHitPoint(0)
	, mMyObjectId(mGameObjectId)
	, mMaxHp(0)
	, mTag(_objectTag)
	, mMoveSpeed(0.0f)
	, mReUseObject(_reUseGameObject)
	, mRecomputeWorldTransform(true)
{
	mGameObjectId++;
	//GameObjectManagerにポインタを渡す
	GAME_OBJECT_MANAGER->AddGameObject(this);
}

/// <summary>
/// デストラクタ
/// </summary>
GameObject::~GameObject()
{
	//GameObjectManagerからポインタを削除する
	GAME_OBJECT_MANAGER->RemoveGameObject(this);
	while (!mComponents.empty())
	{
		delete mComponents.back();
	}
}

/// <summary>
/// フレーム毎の処理
/// </summary>
/// <param name="_deltaTime"> 最後のフレームを完了するのに要した時間 </param>
void GameObject::Update(float _deltaTime)
{
	//更新停止のイベント中でないか(ポーズ画面など)
	if (mPauzingEvent == PauzingEvent::NoneEvent)
	{
		if (mState == eActive)
		{
			//Transformのワールド変換
			ComputeWorldTransform();
			//ゲームオブジェクトの更新
			UpdateGameObject(_deltaTime);
			//このゲームオブジェクトに付属するコンポーネントの更新
			UpdateComponents(_deltaTime);
			//Transformのワールド変換
			ComputeWorldTransform();
		}
	}
	//ポーズ画面のときコンポーネントを更新させない(アニメーションなども止めるため)
	else if(mPauzingEvent == PauzingEvent::PausingEvent)
	{
		PausingUpdateGameObject();
	}
	else
	{
		PausingUpdateGameObject();
		UpdateComponents(_deltaTime);
	}
}

/// <summary>
/// アタッチされてるコンポーネントのアップデート
/// </summary>
/// <param name="_deltaTime"> 最後のフレームを完了するのに要した時間 </param>
void GameObject::UpdateComponents(float _deltaTime)
{
	if (mState != eDead)
	{	
		for (auto itr : mComponents)
		{
			itr->Update(_deltaTime);
		}
	}
}

/// <summary>
/// 入力状態を受け取りGameObjectとComponentの入力更新関数を呼び出す
/// </summary>
/// <param name="_KeyState"> キーボード、マウス、コントローラーの入力状態 </param>
void GameObject::ProcessInput(const InputState& _keyState)
{
	if (mState == eActive)
	{
		//コンポーネントの入力関数にコントローラーの入力状態を
		for (auto comp : mComponents)
		{
			comp->ProcessInput(_keyState);
		}
		//ゲームオブジェクトの入力関数にコントローラーの入力状態を
		GameObjectInput(_keyState);
	}
}

/// <summary>
/// コンポーネントを追加する
/// </summary>
/// <param name="_component"> 追加するコンポーネントのポインタ </param>
void GameObject::AddComponent(Component * _component)
{
	int order = _component->GetUpdateOder();
	auto itr = mComponents.begin();
	for (;
		itr != mComponents.end();
		++itr)
	{
		if (order < (*itr)->GetUpdateOder())
		{
			break;
		}
	}
	mComponents.insert(itr, _component);
}

/// <summary>
/// コンポーネントを削除する
/// </summary>
/// <param name="_component"> 削除するコンポーネントのポインタ </param>
void GameObject::RemoveComponent(Component * _component)
{
	auto itr = std::find(mComponents.begin(), mComponents.end(), _component);
	if (itr != mComponents.end())
	{
		mComponents.erase(itr);
	}
}

/// <summary>
/// Transformのワールド変換
/// </summary>
void GameObject::ComputeWorldTransform()
{
	//ワールド変換が必要かどうか？
	//もし必要だったらワールド変換を行う
	if (mRecomputeWorldTransform)
	{
		//objectの
		//変換が必要フラグを降ろす
		mRecomputeWorldTransform = false;
		//スケールのワールド変換
		mWorldTransform = Matrix4::CreateScale(mScale);
		//回転のワールド変換（クウォータニオン）
		mWorldTransform *= Matrix4::CreateFromQuaternion(mRotation);
		//平行移動の更新
		mWorldTransform *= Matrix4::CreateTranslation(mPosition);

		//object（owner）が持っているcomponentによる座標変換系
		for (auto itr : mComponents)
		{
			itr->OnUpdateWorldTransform();
		}
	}
}

/// <summary>
/// 押し戻し
/// </summary>
/// <param name="_MyAABB"> 自身のAABB </param>
/// <param name="_PairAABB"> 当たった相手のAABB </param>
/// <param name="_PairTag"> 当たった相手のタグ </param>
void GameObject::FixCollision(const AABB & _myAABB, const AABB & _pairAABB, const Tag& _pairTag)
{
	Vector3 ment = Vector3(0, 0, 0);
	CalcCollisionFixVec(_myAABB, _pairAABB, ment);
	SetPosition(GetPosition() + (ment));
}

/// <summary>
/// 前方ベクトルの向きに回転する
/// </summary>
/// <param name="_Forward"> 向かせたい前方ベクトル </param>
void GameObject::RotateToNewForward(const Vector3& _forward)
{
	// X軸ベクトル(1,0,0)とforwardの間の角度を求める
	float dot = Vector3::Dot(Vector3::UnitX, _forward);
	float angle = Math::Acos(dot);
	//printf("%f\n", angle);
	// 下向きだった場合
	if (dot > 0.9999f)
	{
		SetRotation(Quaternion::Identity);
	}
	// 上向きだった場合
	else if (dot < -0.9999f)
	{
		SetRotation(Quaternion(Vector3::UnitZ, Math::Pi));
	}
	else
	{
		// 軸ベクトルとforwardとの外積から回転軸をもとめ、回転させる
		Vector3 axis = Vector3::Cross(Vector3::UnitX, _forward);
		axis.Normalize();
		SetRotation(Quaternion(axis, angle));
	}
}