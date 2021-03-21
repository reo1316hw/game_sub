#include "Game.h"
#include "Math.h"
#include "GameObject.h"
#include "Component.h"
#include "InputSystem.h"
#include "GameObjectManager.h"
#include "PhysicsWorld.h"
#include "MainCameraObject.h"

int GameObject::gameObjectId = 0;
MainCameraObject* GameObject::mainCamera = nullptr;
PauzingEvent GameObject::pauzingEvent = PauzingEvent::NoneEvent;

/*
@param	ゲームクラスのポインタ
*/
GameObject::GameObject(const Tag& _objectTag, SceneBase::Scene _sceneTag, bool _reUseGameObject)
	: state(Active)
	, worldTransform()
	, position(Vector3::Zero)
	, velocity(Vector3::Zero)
	, scale(Vector3(1.0f, 1.0f, 1.0f))
	, rotation(Quaternion::Identity)
	, recomputeWorldTransform(true)
	, myObjectId(gameObjectId)
	, reUseObject(_reUseGameObject)
	, aabb(Vector3::Zero, Vector3::Zero)
	, moveSpeed(0)
	, gravity(0)
	, tag(_objectTag)
	, sceneTag(_sceneTag)
	, hitFlag(false)
{
	gameObjectId++;
	//GameObjectManagerにポインタを渡す
	GAME_OBJECT_MANAGER->AddGameObject(this);
}

GameObject::~GameObject()
{
	//GameObjectManagerからポインタを削除する
	GAME_OBJECT_MANAGER->RemoveGameObject(this);
	while (!components.empty())
	{
		delete components.back();
	}
}

/*
@brief	フレーム毎の処理
@param	最後のフレームを完了するのに要した時間
*/
void GameObject::Update(float _deltaTime)
{
	//更新停止のイベント中でないか(ポーズ画面など)
	if (pauzingEvent == PauzingEvent::NoneEvent)
	{
		if (state == Active)
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
	else if(pauzingEvent == PauzingEvent::PausingEvent)
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
	if (state != Dead)
	{	
		for (auto itr : components)
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
	if (state == Active)
	{
		//コンポーネントの入力関数にコントローラーの入力状態を
		for (auto comp : components)
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
	auto itr = components.begin();
	for (;
		itr != components.end();
		++itr)
	{
		if (order < (*itr)->GetUpdateOder())
		{
			break;
		}
	}
	components.insert(itr, _component);
}

/*
@brief	コンポーネントを削除する
@param	削除するコンポーネントのポインタ
*/
void GameObject::RemoveComponent(Component * _component)
{
	auto itr = std::find(components.begin(), components.end(), _component);
	if (itr != components.end())
	{
		components.erase(itr);
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
	if (recomputeWorldTransform)
	{
		//objectの
		//変換が必要フラグを降ろす
		recomputeWorldTransform = false;
		//スケールのワールド変換
		worldTransform = Matrix4::CreateScale(scale);
		//回転のワールド変換（クウォータニオン）
		worldTransform *= Matrix4::CreateFromQuaternion(rotation);
		//平行移動の更新
		worldTransform *= Matrix4::CreateTranslation(position);

		//object（owner）が持っているcomponentによる座標変換系
		for (auto itr : components)
		{
			itr->OnUpdateWorldTransform();
		}
	}
}

void GameObject::FixCollision(const AABB & myAABB, const AABB & pairAABB, const Tag& _pairTag)
{
	Vector3 ment = Vector3(0, 0, 0);
	calcCollisionFixVec(myAABB, pairAABB, ment);
	SetPosition(GetPosition() + (ment));
}

void GameObject::CreateMainCamera()
{
	mainCamera = new MainCameraObject();
}

// forwardベクトルの向きに回転する
// in forward : 向かせたい前方方向ベクトル
void GameObject::RotateToNewForward(const Vector3& forward)
{
	// X軸ベクトル(1,0,0)とforwardの間の角度を求める
	float dot = Vector3::Dot(Vector3::UnitX, forward);
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
		Vector3 axis = Vector3::Cross(Vector3::UnitX, forward);
		axis.Normalize();
		SetRotation(Quaternion(axis, angle));
	}
}
