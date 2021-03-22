#pragma once
#include "PlayerObject.h"

class InputSystem;

class PlayerObjectStateBase
{
public:
	PlayerObjectStateBase();
	virtual ~PlayerObjectStateBase() {};
	virtual PlayerState Update(class PlayerObject* _owner, float _deltaTime) = 0;
	virtual void Inipt(class PlayerObject* _owner, const InputState& _keyState) = 0;
	virtual void Enter(class PlayerObject* _owner, float _deltaTime) {};
	virtual void Exit(class PlayerObject* _owner, float _deltaTime) {};
protected:
	////上方向(ジャンプ用)
	//Vector3 jumpVec;
	//// ジャンプスピード
	//const float JUMP_SPEED = 1000.0f;
	bool  mNextComboFlag;			//次のコンボにつなげるか  
	bool  mIdleFlag;				//待機するか
	bool  mRunStartFlag;			//走り始めか
	bool  mRunFlag;					//走っているか
	bool  mSprintFlag;				//全力疾走するか
	bool  mAttackFlag;				//攻撃するか
	bool  mSwordDeliveryFlag;		//抜刀するか
	bool  mDrawnSwordFlag;			//納刀するか

	float mElapseTime;    // このステートに入ってからの経過時刻
	float mTotalAnimTime; // アニメーション総時間

	//  キャラの現在のスピード
	float mCharaSpeed;

	//向き
	Vector3 mDirVec;
	//前進方向
	Vector3 mForwardVec;
	//右方向
	Vector3 mRightVec;
	// キャラの前進ベクトル
	Vector3 mCharaForwardVec;
private:
};