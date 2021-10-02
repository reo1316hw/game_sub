#pragma once

// 前方宣言
class SkeletalMeshComponent;
class MeshComponent;
class Mesh;
class BoxCollider;
class Animation;
class PlayerObjectStateBase;
class AttackMeshComponent;

enum class PlayerState
{
	ePlayerStateIdle = 0,		// 待機
	ePlayerStateRunLoop,		// 走っている状態
	ePlayerStateSprintStart,	// 全力疾走始め
	ePlayerStateSprintLoop,		// 全力疾走している状態
	ePlayerStateFirstAttack,	// 攻撃1
	ePlayerStateSecondAttack,	// 攻撃2
	ePlayerStateThirdAttack,	// 攻撃3
	ePlayerStateDashAttack,     // ダッシュ攻撃

	ePlayerStateNum,   // 総アニメーション数
};

class PlayerObject : public GameObject
{
public:

	PlayerObject(const Vector3& _pos, const Vector3& _size, const std::string _gpmeshName, const char* _gpskelName, const Tag& _objectTag, const SceneBase::Scene _sceneTag);

	~PlayerObject() {};

	SkeletalMeshComponent* GetSkeletalMeshComp() { return mSkeltalMeshComponent; };
	const Animation* GetAnim(PlayerState _state) { return mAnimTypes[static_cast<unsigned int>(_state)]; };

	void UpdateGameObject(float _deltaTime)override;
	void GameObjectInput(const InputState& _keyState)override;
	void SelfRotation(Vector3 _axis, float _angle);
	void PausingUpdateGameObject()override;

	Vector3 GetTargetPos() { return mTargetPos; };
	Vector3 GetViewPos() { return mViewPos; };

	void SetAttackBoneIndex(int _attackBoneIndex) { mAttackBoneIndex = _attackBoneIndex; };

private:

	//剣の初期回転値
	const Vector3 MSwordRot;
	//剣の初期座標
	const Vector3 MSwordPos;

	// 重力
	const float GRAVITY = 100.0f;

	std::vector<const class Animation*>      mAnimTypes;
	// ステートクラスプール
	std::vector<class PlayerObjectStateBase*> mStatePools;

	// 現在のステート
	PlayerState mNowState;
	// 次のステート
	PlayerState mNextState;

	AABB mPlayerBox;

	// 武器メッシュ
	AttackMeshComponent* mWeaponMesh;

	//見たい座標との差
	Vector3 mOffsetPos;
	//見る対象のポジション
	Vector3 mTargetPos;
	//カメラのポジション
	Vector3 mViewPos;

	int mAttackBoneIndex;
	
	void OnCollision(const GameObject& _hitObject)override;
};

