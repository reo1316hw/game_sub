#pragma once

// 前方宣言
class AttackMeshComponent;

class PlayerObjectStateBase
{
public:

	PlayerObjectStateBase();

	virtual ~PlayerObjectStateBase() {};

	virtual PlayerState Update(class PlayerObject* _owner, float _deltaTime) = 0;

	virtual void Input(class PlayerObject* _owner, const InputState& _keyState) {};

	virtual void Enter(class PlayerObject* _owner, float _deltaTime) = 0;

	virtual void Exit(class PlayerObject* _owner, float _deltaTime) {};

protected:

	// 次のコンボにつなげるか
	bool  mNextComboFlag;
	// 待機するか
	bool  mIdleFlag;
	// 走っているか
	bool  mRunFlag;
	// 全力疾走始めか
	bool  mSprintStartFlag;
	// 全力疾走するか
	bool  mSprintFlag;
	// 攻撃するか
	bool  mAttackFlag;

	// gpSkelファイルの何番目のボーンか
	int	mAttackBoneIndex;

	// このステートに入ってからの経過時刻
	float mElapseTime;
	// アニメーション総時間
	float mTotalAnimTime;
	// キャラの現在のスピード
	float mCharaSpeed;

	//向き
	Vector3 mDirVec;
	//前進方向
	Vector3 mForwardVec;
	//右方向
	Vector3 mRightVec;
	// キャラの前進ベクトル
	Vector3 mCharaForwardVec;

	//武器メッシュのポインタ
	AttackMeshComponent* mAttackMeshComponent;

private:
};