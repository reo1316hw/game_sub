#pragma once
#include "PlayerObject.h"

class InputSystem;
class AttackMeshComponent;

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
	bool  mDrawnSwordFlag;			//抜刀するか
	bool  mSwordDeliveryFlag;		//納刀するか

	int	mAttackBoneIndex;  //gpSkelファイルの何番目のボーンか

	float mElapseTime;    // このステートに入ってからの経過時刻
	float mTotalAnimTime; // アニメーション総時間
	float mCharaSpeed;	  // キャラの現在のスピード

	AttackMeshComponent* mAttackMeshComponent;	//武器メッシュのポインタ

	//向き
	Vector3 mDirVec;
	//前進方向
	Vector3 mForwardVec;
	//右方向
	Vector3 mRightVec;
	// キャラの前進ベクトル
	Vector3 mCharaForwardVec;

	Vector3 mDrawnSwordRot; //抜刀時の剣の円周率
	Vector3 mDrawnSwordPos; //抜刀時の剣の座標
	Vector3 mSwordDeliveryRot; //納刀時の剣の円周率
	Vector3 mSwordDeliveryPos; //納刀時の剣の座標
private:
};