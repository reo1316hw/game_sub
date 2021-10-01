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
	PLAYER_STATE_IDLE = 0,				// 納刀時の待機
	PLAYER_STATE_SWORD_IDLE,			// 抜刀時の待機
	PLAYER_STATE_DRAWN_SWORD,			// 抜刀(移動しない)
	PLAYER_STATE_DRAWN_SWORD_MOVE,		// 抜刀(移動する)
	PLAYER_STATE_SWORD_DELIVERY,		// 納刀(移動しない)
	PLAYER_STATE_SWORD_DELIVERY_MOVE,	// 納刀(移動する)
	PLAYER_STATE_RUN_START,				// 納刀時の走り始め
	PLAYER_STATE_RUN_LOOP,				// 納刀時の走っている状態
	PLAYER_STATE_SWORD_RUN_LOOP,		// 抜刀時の走っている状態
	PLAYER_STATE_SPRINT_LOOP,			// 納刀時の全力疾走している状態
	PLAYER_STATE_RUN_END,				// 納刀時の走り終わり
	PLAYER_STATE_ATTACK1,				// 攻撃1
	PLAYER_STATE_ATTACK2,				// 攻撃2
	PLAYER_STATE_ATTACK3,				// 攻撃3
	//PLAYER_STATE_JUMPSTART,			// ジャンプスタート
	//PLAYER_STATE_JUMPLOOP,			// ジャンプループ
	//PLAYER_STATE_JUMPEND,				// ジャンプ終了
	//PLAYER_STATE_HIT,

	PLAYER_STATE_NUM,   // 総アニメーション数
};

class PlayerObject : public GameObject
{
public:
	PlayerObject(const Vector3& _pos, const Vector3& _size, const std::string _gpmeshName, const char* _gpskelName, const char* _gpanimName, const Tag& _objectTag, const SceneBase::Scene _sceneTag);
	//PlayerObject(const Vector3& _pos, const Vector3& _size, const std::string _gpmeshName, const char* _gpskelName, const char* _gpanimName);
	~PlayerObject();

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

	// 重力
	const float GRAVITY = 100.0f;
	
	void OnCollision(const GameObject& _hitObject)override;
};

