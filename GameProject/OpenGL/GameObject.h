#pragma once
#include <vector>
#include <functional>
#include "Math.h"
#include "Collision.h"
#include "SceneBase.h"

// 前方宣言
class Game;
class Vector3;
class Matrix4;
class Component;
class ColliderComponent;
class SkeletalMeshComponent;
class MeshComponent;
class Mesh;
class BoxCollider;
struct InputState;

/*
@brief	ゲームオブジェクトの状態
*/
enum State
{
	//アクティブ
	Active,
	//更新が停止している
	Paused,
	//オブジェクトの更新が終了(外部からのみActiveに変更可能)
	Dead,
};

/*
	@enum　GameObjectタグ
	衝突相手を判別するために使用
	*/
enum Tag
{
	Other = 0,
	Camera = 1,
	Player = 2,
	EightTimesSeventeenGround = 3,
	SixTimesThreeGround = 4,
	FourTimesFiveGround = 5,
	ThreeTimesFourGround = 6,
	TwentyFiveTimesTwoGround = 7,
	TwelveTimesThirteenGround = 8,
	ThreeTimesNineGround01 = 9,
	NineTimesTwoGround = 10,
	ThreeTimesNineGround02 = 11,
	SevenTimesSevenGround = 12,
	ThirteenTimesThreeGround = 13,
	ThreeTimesThreeGround = 14,
	ElevenTimesOneGround = 15,
	NineteenTimesNineteenGround = 16,
	SideSuperShortWall = 17,
	VerticalSuperShortWall = 18,
	SideShortWall = 19,
	VerticalShortWall = 20,
	UsuallyWall = 21,
	SideLongWall = 22,
	VerticalLongWall = 23,
	SideSuperLongWall = 24,
	VerticalSuperLongWall = 25,
	Enemy = 26,
	Swith = 27
};

/*
@enum ゲームオブジェクトの更新を停止するイベント名
*/
enum PauzingEvent
{
	//ボスの特殊演出
	SummonMageEvent,
	//ポーズ画面中
	PausingEvent,
	//プレイヤーが撃破されてしまった際の演出
	DeadPlayerEvent,
	//ゲームオーバー時の演出 DeadPlayerEventと関連
	GameOverEvent,
	//ゲームオブジェクトの更新が行われている。
	NoneEvent
};

class GameObject
{
public:

	/*
	@param	ゲームクラスのポインタ
	*/
	GameObject(const Tag& _objectTag ,SceneBase::Scene _sceneTag, bool _reUseGameObject = false);
	virtual ~GameObject();

	/*
	@brief	フレーム毎の処理
	@param	最後のフレームを完了するのに要した時間
	*/
	void Update(float _deltaTime);

	/*
	@brief	アタッチされてるコンポーネントのアップデート
	@param	最後のフレームを完了するのに要した時間
	*/
	void UpdateComponents(float _deltaTime);

	/*
	@brief	ゲームオブジェクトのアップデート
	@param	最後のフレームを完了するのに要した時間
	*/
	virtual void UpdateGameObject(float _deltaTime);

	/*
	@fn ゲームオブジェクトが静止中に更新されるアップデート関数
	@brief pauzingUpdateがtrueのときだけ呼ばれる更新関数
	*/
	virtual void PausingUpdateGameObject();

	/*
	@fn 入力状態を受け取りGameObjectとComponentの入力更新関数を呼び出す
	*/
	void ProcessInput(const InputState& _keyState);

	/*
	@fn 入力を引数で受け取る更新関数
	@brief 基本的にここで入力情報を変数に保存しUpdateGameObjectで更新を行う
	*/
	virtual void GameObjectInput(const InputState& _keyState);

	/*
	@brief	コンポーネントを追加する
	@param	追加するコンポーネントのポインタ
	*/
	void AddComponent(Component* _component);

	/*
	@brief	コンポーネントを削除する
	@param	削除するコンポーネントのポインタ
	*/
	void RemoveComponent(Component* _component);

	/*
	@fn 現在の仕様上行うことができない処理を外部から強引に行うための関数
	@exsample ゲームオブジェクト全体の更新が停止中に対象のゲームオブジェクトを更新する
	*/
	void ExceptionUpdate();
	/*
	@brief	Transformのワールド変換
	*/
	void ComputeWorldTransform();

	/*
	@brief　オブジェクトのポジションを取得する
	@return	position
	*/
	const Vector3& GetPosition() const { return mPosition; }

	/*
	@brief　オブジェクトのポジションを設定する
	@param	position
	*/
	virtual void SetPosition(const Vector3& _pos) { mPosition = _pos; mRecomputeWorldTransform = true; }
	bool GetRecomputeWorldTransform() { return mRecomputeWorldTransform; }

	/*
	@brief　オブジェクトのスケールを取得する
	@return	scale
	*/
	Vector3 GetScaleFloat() const { return mScale; }

	/*
	@brief　オブジェクトのスケールを設定する
	@param	scale
	*/
	void SetScale(float _scale) { mScale.x = _scale; mScale.y = _scale; mScale.z = _scale; mRecomputeWorldTransform = true; }
	void SetScale(Vector3 _scale) { mScale.x = _scale.x; mScale.y = _scale.y; mScale.z = _scale.z; mRecomputeWorldTransform = true; }

	float GetScale() { return mScale.x; }
	/*
	@brief　オブジェクトのクォータニオンを取得する
	@return	rotation（Quaternion型）
	*/
	const Quaternion& GetRotation() const { return mRotation; }

	/*
	@brief　オブジェクトのクォータニオンを設定する
	@param	rotation（Quaternion型）
	*/
	virtual void SetRotation(const Quaternion& _qotation) { mRotation = _qotation;  mRecomputeWorldTransform = true; }

	/*
	@brief　オブジェクトの状態を取得する
	@return	state
	*/
	State GetState() const { return mState; }

	/*
	@brief　オブジェクトの状態を設定する
	@param	state
	*/
	virtual void SetState(State _state) { mState = _state; }

	/*
	@brief　オブジェクトのワールド行列を取得する
	@return	worldTransform
	*/
	const Matrix4& GetWorldTransform() const { return mWorldTransform; }

	/*
	@brief　オブジェクトの前方を表すベクトルを取得する
	@param	forward(Vector3型)
	*/
	Vector3 GetForward() const { return Vector3::Transform(Vector3::UnitX, mRotation); }

	/*
	@brief　オブジェクトの右を表すベクトルを取得する
	@param	right(Vector3型)
	*/
	Vector3 GetRight() const { return Vector3::Transform(Vector3::UnitY, mRotation); }

	/*
	@brief　オブジェクトの上を表すベクトルを取得する
	@param	up(Vector3型)
	*/
	Vector3 GetUp() const { return Vector3::Transform(Vector3::UnitZ, mRotation); };
	
	/*
	@brief　オブジェクトのタグを取得する
	@return	tag
	*/
	Tag GetTag() const { return mTag; };

	/*
	@brief　オブジェクトのidを取得する
	@return	myObjectId(int型)
	*/
	int GetObjectId() { return mMyObjectId; };

	/*
	@brief　解放されるオブジェクトを取得する
	@return	reUseObject(bool型)
	*/
	bool GetReUseGameObject() { return mReUseObject; };

	virtual void FixCollision(const AABB& _myAABB, const AABB& _pairAABB, const Tag& _pairTag);

	void RotateToNewForward(const Vector3& _forward);

	/*
	@fn 静的なmainCameraを生成する
	*/
	static void CreateMainCamera();

	/*
	@brief　シーンのタグを取得する
	@return	sceneTag
	*/
	SceneBase::Scene GetScene() const { return mSceneTag; };

	/*
	@brief　オブジェクトのAABBを取得する
	@return	mAabb
	*/
	AABB GetObjectAABB() const { return mAabb; };

protected:
	std::function<void(GameObject&)> GetOnCollisionFunc() { return std::bind(&GameObject::OnCollision, this, std::placeholders::_1); }
	virtual void OnCollision(const GameObject& _hitObject) {}

	//メインカメラ　生成はGameObjectManager生成時に行われる
	static class MainCameraObject* mMainCamera;
	//ゲームオブジェクトの更新を止めるイベント状態
	static PauzingEvent mPauzingEvent;
	//衝突時のリアクション関数(ColliderComponentにこの関数のアドレスを渡す) Enter...衝突した Stay...衝突している
	virtual void OnTriggerEnter(ColliderComponent* _colliderPair) {};
	//衝突時のリアクション関数(ColliderComponentにこの関数のアドレスを渡す) Enter...衝突した Stay...衝突している
	virtual void OnTriggerStay(ColliderComponent* _colliderPair) {};

	//オブジェクトのAABB
	AABB mAabb;
	//ゲームオブジェクトの状態
	State mState;
	//ゲームオブジェクトのタグ
	Tag mTag;
	//ゲームオブジェクトのID、カウント用
	static int mGameObjectId;
	//このゲームオブジェクトのID
	int mMyObjectId;

	//ゲームオブジェクトのスケルトンメッシュ
	SkeletalMeshComponent* mSkeltalMeshComponent;
	//ゲームオブジェクトのメッシュ
	MeshComponent* mMeshComponent;
	//ゲームオブジェクトの当たり判定
	BoxCollider* mBoxCollider;
	//当たり判定をmeshにするためのインスタンス
	Mesh* mMesh;

	//Transform
	Vector3 mPosition;
	Vector3 mVelocity;
	Vector3 mScale;
	//　移動先
	Vector3 mEndPos;
	//　初期座標
	Vector3		mInitPos;
	Quaternion  mRotation;
	Matrix4		mWorldTransform;
	// 移動速度
	float mMoveSpeed;
	//重力
	float mGravity;
	//ワールド変換の処理を行う必要性があるか
	bool mRecomputeWorldTransform;
	// 当たったかどうか
	bool mHitFlag;
	// 初期位置に戻すか
	bool mOriginalPosFlag;
	
	//シーンのタグ
	SceneBase::Scene mSceneTag;
	//アタッチされているコンポーネント
	std::vector<class Component*>mComponents;
private:
	//シーンを跨ぐ際に解放されるオブジェクトかどうか、カメラなどが対象になる
	bool mReUseObject;
};

