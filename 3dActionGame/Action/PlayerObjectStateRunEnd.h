#pragma once
#include "PlayerObjectStateBase.h"

class PlayerObjectStateRunEnd : public PlayerObjectStateBase
{
public:
	PlayerObjectStateRunEnd();
	~PlayerObjectStateRunEnd();
	PlayerState Update(PlayerObject* _owner, float _deltaTime)override;
	void Inipt(class PlayerObject* _owner, const InputState& _keyState)override;
	void Enter(class PlayerObject* _owner, float _deltaTime)override;
	void Exit(class PlayerObject* _owner, float _deltaTime)override;
private:
	void MoveCalc(PlayerObject* _owner, float _deltaTime);

	bool mIsIdle;
	bool mIsAttack;
	float mElapseTime;    // このステートに入ってからの経過時刻
	float mTotalAnimTime; // アニメーション総時間

	//  キャラの現在のスピード
	float charaSpeed;

	//向き
	Vector3 dirVec;
	//前進方向
	Vector3 forwardVec;
	//右方向
	Vector3 rightVec;
	// キャラの前進ベクトル
	Vector3 charaForwardVec;

	const float cStopTime = 1.0f;
};