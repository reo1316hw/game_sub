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

/// <summary>
/// ゲームオブジェクトの状態
/// </summary>
enum State
{
	//アクティブ
	eActive,
	//更新が停止している
	ePaused,
	//オブジェクトの更新が終了(外部からのみActiveに変更可能)
	eDead
};

/// <summary>
/// GameObjectタグ
/// 衝突相手を判別するために使用
/// </summary>
enum Tag
{
	eOther = 0,
	eCamera,
	ePlayer,
	eWeapon,
	eGround,
	eEnemyManager,
	eEnemyGenerator,
	eEnemy,
	eEnemyAttackDecision,
	eBoss,
	eTranslucentWall
};

/// <summary>
/// ゲームオブジェクトの更新を停止するイベント名
/// </summary>
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

/// <summary>
/// オブジェクトの基底クラス
/// </summary>
class GameObject
{
public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="_ObjectTag"> オブジェクトのタグ </param>
	/// <param name="_reUseGameObject"> 再利用するか </param>
	GameObject(const Tag& _ObjectTag, bool _reUseGameObject = false);

	/// <summary>
	/// デストラクタ
	/// </summary>
	virtual ~GameObject();

	/// <summary>
	/// フレーム毎の処理
	/// </summary>
	/// <param name="_deltaTime"> 最後のフレームを完了するのに要した時間 </param>
	void Update(float _deltaTime);

	/// <summary>
	/// アタッチされてるコンポーネントのアップデート
	/// </summary>
	/// <param name="_deltaTime"> 最後のフレームを完了するのに要した時間 </param>
	void UpdateComponents(float _deltaTime);

	/// <summary>
	/// ゲームオブジェクトのアップデート
	/// </summary>
	/// <param name="_deltaTime"> 最後のフレームを完了するのに要した時間 </param>
	virtual void UpdateGameObject(float _deltaTime) {};

	/// <summary>
	/// ゲームオブジェクトが静止中に更新されるアップデート関数
	/// pauzingUpdateがtrueのときだけ呼ばれる更新関数
	/// </summary>
	virtual void PausingUpdateGameObject() {};

	/// <summary>
	/// 入力状態を受け取りGameObjectとComponentの入力更新関数を呼び出す
	/// </summary>
	/// <param name="_KeyState"> キーボード、マウス、コントローラーの入力状態 </param>
	void ProcessInput(const InputState& _KeyState);

	/// <summary>
	/// 入力を引数で受け取る更新関数
	/// 基本的にここで入力情報を変数に保存しUpdateGameObjectで更新を行う
	/// </summary>
	/// <param name="_KeyState"> キーボード、マウス、コントローラーの入力状態 </param>
	virtual void GameObjectInput(const InputState& _KeyState) {};

	/// <summary>
	/// コンポーネントを追加する
	/// </summary>
	/// <param name="_component"> 追加するコンポーネントのポインタ </param>
	void AddComponent(Component* _component);

	/// <summary>
	/// コンポーネントを削除する
	/// </summary>
	/// <param name="_component"> 削除するコンポーネントのポインタ </param>
	void RemoveComponent(Component* _component);

	///// <summary>
	///// 現在の仕様上行うことができない処理を外部から強引に行うための関数
	///// ゲームオブジェクト全体の更新が停止中に対象のゲームオブジェクトを更新する
	///// </summary>
	//void ExceptionUpdate();

	/// <summary>
	/// Transformのワールド変換
	/// </summary>
	void ComputeWorldTransform();

	/// <summary>
	/// 押し戻し
	/// </summary>
	/// <param name="_MyAABB"> 自身のAABB </param>
	/// <param name="_PairAABB"> 当たった相手のAABB </param>
	/// <param name="_PairTag"> 当たった相手のタグ </param>
	virtual void FixCollision(const AABB& _MyAABB, const AABB& _PairAABB, const Tag& _PairTag);

	/// <summary>
	/// 前方ベクトルの向きに回転する
	/// </summary>
	/// <param name="_Forward"> 向かせたい前方ベクトル </param>
	void RotateToNewForward(const Vector3& _Forward);

	/// <summary>
	/// 静的なmainCameraを生成する
	/// </summary>
	static void CreateMainCamera();

	/// <summary>
	/// オブジェクトの引き離し
	/// </summary>
	/// <param name="_DirTargetEnemyVec"> 対象となるオブジェクトに向いたベクトル </param>
	virtual void Separation(const Vector3& _DirTargetEnemyVec) {};

protected:

	std::function<void(GameObject&)> GetOnCollisionFunc() { return std::bind(&GameObject::OnCollision, this, std::placeholders::_1); }
	virtual void OnCollision(const GameObject& _hitObject) {};

	// メインカメラ　
	// 生成はGameObjectManager生成時に行われる
	static class MainCameraObject* mMainCamera;
	// ゲームオブジェクトの更新を止めるイベント状態
	static PauzingEvent mPauzingEvent;
	// 衝突時のリアクション関数(ColliderComponentにこの関数のアドレスを渡す) Enter...衝突した Stay...衝突している
	virtual void OnTriggerEnter(ColliderComponent* _colliderPair) {};
	// 衝突時のリアクション関数(ColliderComponentにこの関数のアドレスを渡す) Enter...衝突した Stay...衝突している
	virtual void OnTriggerStay(ColliderComponent* _colliderPair) {};

	// オブジェクトのAABB
	AABB mBox;
	// ゲームオブジェクトの状態
	State mState;
	// ゲームオブジェクトのタグ
	Tag mTag;
	// ゲームオブジェクトのID、カウント用
	static int mGameObjectId;
	// このゲームオブジェクトのID
	int mMyObjectId;
	// 体力
	int mHitPoint;

	// ゲームオブジェクトのメッシュ
	MeshComponent* mMeshComponentPtr;
	// 矩形の当たり判定を行うクラスのポインタ
	BoxCollider* mBoxColliderPtr;
	// 当たり判定をmeshにするためのインスタンス
	Mesh* mMeshPtr;

	// Transform
	Vector3 mPosition;
	Vector3 mScale;
	Quaternion  mRotation;
	// 速度
	Vector3 mVelocity;
	// ワールド行列
	Matrix4		mWorldTransform;
	// 移動速度
	float mMoveSpeed;
	// ワールド変換の処理を行う必要性があるか
	bool mRecomputeWorldTransform;
	
	// アタッチされているコンポーネント
	std::vector<class Component*>mComponents;

private:

	// シーンを跨ぐ際に解放されるオブジェクトかどうか、カメラなどが対象になる
	bool mReUseObject;

public:// ゲッターセッター

	/// <summary>
	/// オブジェクトの座標を取得する
	/// </summary>
	/// <returns> オブジェクトの座標 </returns>
	const Vector3& GetPosition() const { return mPosition; }

	/// <summary>
	/// オブジェクトの座標を設定
	/// </summary>
	/// <param name="_Pos"> オブジェクトの座標 </param>
	virtual void SetPosition(const Vector3& _Pos) { mPosition = _Pos; mRecomputeWorldTransform = true; }

	/// <summary>
	/// ワールド行列変換を行うかのフラグを取得
	/// </summary>
	/// <returns> ワールド行列変換を行うか </returns>
	bool GetRecomputeWorldTransform() { return mRecomputeWorldTransform; }

	/// <summary>
	/// オブジェクトの大きさをVector3型で取得する
	/// </summary>
	/// <returns> オブジェクトの大きさ(Vector3型) </returns>
	Vector3 GetScale() const { return mScale; }

	/// <summary>
	/// オブジェクトの大きさをfloat型で取得する
	/// </summary>
	/// <returns> オブジェクトの大きさ(float型) </returns>
	float GetScaleFloat() { return mScale.x; }

	/// <summary>
	/// オブジェクトの大きさ(Vector3型)を設定する
	/// </summary>
	/// <param name="_scale"> オブジェクトの大きさ(Vector3型) </param>
	void SetScale(Vector3 _scale) { mScale.x = _scale.x; mScale.y = _scale.y; mScale.z = _scale.z; mRecomputeWorldTransform = true; }

	/// <summary>
	/// オブジェクトの大きさ(float型)を設定する
	/// </summary>
	/// <param name="_scale"> オブジェクトの大きさ(float型) </param>
	void SetScale(float _scale) { mScale.x = _scale; mScale.y = _scale; mScale.z = _scale; mRecomputeWorldTransform = true; }

	/// <summary>
	/// オブジェクトの回転値を取得する
	/// </summary>
	/// <returns> オブジェクトの回転値 </returns>
	const Quaternion& GetRotation() const { return mRotation; }

	/// <summary>
	/// オブジェクトの回転値を設定する
	/// </summary>
	/// <param name="_Rotation"> オブジェクトの回転値 </param>
	virtual void SetRotation(const Quaternion& _Rotation) { mRotation = _Rotation;  mRecomputeWorldTransform = true; }

	/// <summary>
	/// オブジェクトの状態を取得する
	/// </summary>
	/// <returns> オブジェクトの状態 </returns>
	State GetState() const { return mState; }

	/// <summary>
	/// オブジェクトの状態を設定する
	/// </summary>
	/// <param name="_state"> オブジェクトの状態 </param>
	virtual void SetState(State _state) { mState = _state; }

	/// <summary>
	/// オブジェクトのワールド行列を取得する
	/// </summary>
	/// <returns> オブジェクトのワールド行列 </returns>
	const Matrix4& GetWorldTransform() const { return mWorldTransform; }

	/// <summary>
	/// オブジェクトの前方ベクトルを取得する
	/// </summary>
	/// <returns> オブジェクトの前方ベクトル </returns>
	Vector3 GetForward() const { return Vector3::Transform(Vector3::UnitX, mRotation); }

	/// <summary>
	/// オブジェクトの右方ベクトルを取得する
	/// </summary>
	/// <returns> オブジェクトの右方ベクトル </returns>
	Vector3 GetRight() const { return Vector3::Transform(Vector3::UnitY, mRotation); }

	/// <summary>
	/// オブジェクトの上方ベクトルを取得する
	/// </summary>
	/// <returns> オブジェクトの上方ベクトル </returns>
	Vector3 GetUp() const { return Vector3::Transform(Vector3::UnitZ, mRotation); }

	/// <summary>
	/// オブジェクトのタグを取得する
	/// </summary>
	/// <returns> オブジェクトのタグ </returns>
	Tag GetTag() const { return mTag; }

	/// <summary>
	/// オブジェクトのidを取得する
	/// </summary>
	/// <returns> オブジェクトのid </returns>
	int GetObjectId() { return mMyObjectId; }

	/// <summary>
	/// オブジェクトの体力を取得する
	/// </summary>
	/// <returns> オブジェクトの体力 </returns>
	int GetHitPoint() { return mHitPoint; }

	/// <summary>
	/// オブジェクトの体力を設定する
	/// </summary>
	/// <param name="_hitPoint"> オブジェクトの体力 </param>
	void SetScale(int _hitPoint) { mHitPoint = _hitPoint; }

	/// <summary>
	/// 解放されるオブジェクトを取得する
	/// </summary>
	/// <returns> 解放されるオブジェクト </returns>
	bool GetReUseGameObject() { return mReUseObject; }

	/// <summary>
	/// オブジェクトのAABBを取得する
	/// </summary>
	/// <returns> オブジェクトのAABB </returns>
	AABB GetObjectAABB() const { return mBox; }

	/// <summary>
	/// 矩形の当たり判定を行うクラスのポインタを取得
	/// </summary>
	/// <returns> 矩形の当たり判定を行うクラスのポインタ </returns>
	BoxCollider* GetBoxCollider() { return mBoxColliderPtr; }
};

