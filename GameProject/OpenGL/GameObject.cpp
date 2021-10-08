#include "pch.h"

int GameObject::mGameObjectId = 0;
MainCameraObject* GameObject::mMainCamera = nullptr;
PauzingEvent GameObject::mPauzingEvent = PauzingEvent::NoneEvent;

/*
@param	ゲームクラスのポインタ
*/
GameObject::GameObject(const Tag& _objectTag, SceneBase::Scene _sceneTag, bool _reUseGameObject)
	: mState(Active)
	, mWorldTransform()
	, mPosition(Vector3::Zero)
	, mVelocity(Vector3::Zero)
	, mBox(Vector3::Zero, Vector3::Zero)
	, mScale(Vector3(1.0f, 1.0f, 1.0f))
	, mRotation(Quaternion::Identity)
	, mMyObjectId(mGameObjectId)
	, mTag(_objectTag)
	, mSceneTag(_sceneTag)
	, mMoveSpeed(0.0f)
	, mGravity(0.0f)
	, mReUseObject(_reUseGameObject)
	, mRecomputeWorldTransform(true)
	, mHitFlag(false)
{
	mGameObjectId++;
	//GameObjectManagerにポインタを渡す
	GAME_OBJECT_MANAGER->AddGameObject(this);
}

GameObject::~GameObject()
{
	//GameObjectManagerからポインタを削除する
	GAME_OBJECT_MANAGER->RemoveGameObject(this);
	while (!mComponents.empty())
	{
		delete mComponents.back();
	}
}

/*
@brief	フレーム毎の処理
@param	最後のフレームを完了するのに要した時間
*/
void GameObject::Update(float _deltaTime)
{
	//更新停止のイベント中でないか(ポーズ画面など)
	if (mPauzingEvent == PauzingEvent::NoneEvent)
	{
		if (mState == Active)
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

/*
@brief	アタッチされてるコンポーネントのアップデート
@param	最後のフレームを完了するのに要した時間
*/
void GameObject::UpdateComponents(float _deltaTime)
{
	if (mState != Dead)
	{	
		for (auto itr : mComponents)
		{
			itr->Update(_deltaTime);
		}
	}
}
/*
@brief	ゲームオブジェクトのアップデート
@param	最後のフレームを完了するのに要した時間
*/
void GameObject::UpdateGameObject(float _deltaTime)
{
}
/*
@fn ゲームオブジェクトが静止中に更新されるアップデート関数
@brief pauzingUpdateがtrueのときだけ呼ばれる更新関数
*/
void GameObject::PausingUpdateGameObject()
{
}

/*
@fn 入力状態を受け取りGameObjectとComponentの入力更新関数を呼び出す
*/
void GameObject::ProcessInput(const InputState& _keyState)
{
	if (mState == Active)
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

/*
@fn 入力を引数で受け取る更新関数
@brief 基本的にここで入力情報を変数に保存しUpdateGameObjectで更新を行う
*/
void GameObject::GameObjectInput(const InputState & _keyState)
{
}

/*
@brief	コンポーネントを追加する
@param	追加するコンポーネントのポインタ
*/
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

/*
@brief	コンポーネントを削除する
@param	削除するコンポーネントのポインタ
*/
void GameObject::RemoveComponent(Component * _component)
{
	auto itr = std::find(mComponents.begin(), mComponents.end(), _component);
	if (itr != mComponents.end())
	{
		mComponents.erase(itr);
	}
}
/*
@fn 現在の仕様上行うことができない処理を外部から強引に行うための関数
@exsample ゲームオブジェクト全体の更新が停止中に対象のゲームオブジェクトを更新する
*/
void GameObject::ExceptionUpdate()
{
	ComputeWorldTransform();

	UpdateGameObject(0.016f);
	UpdateComponents(0.016f);

	ComputeWorldTransform();
}


/*
@brief	Transformのワールド変換
*/
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

void GameObject::FixCollision(const AABB & _myAABB, const AABB & _pairAABB, const Tag& _pairTag)
{
	Vector3 ment = Vector3(0, 0, 0);
	CalcCollisionFixVec(_myAABB, _pairAABB, ment);
	SetPosition(GetPosition() + (ment));
}

void GameObject::CreateMainCamera()
{
	mMainCamera = new MainCameraObject();
}

// forwardベクトルの向きに回転する
// in forward : 向かせたい前方方向ベクトル
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
