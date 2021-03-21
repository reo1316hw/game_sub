#pragma once
#include "PlayerObjectStateBase.h"

class PlayerObjectStateRun : public PlayerObjectStateBase
{
public:
	PlayerObjectStateRun();
	~PlayerObjectStateRun();
	PlayerState Update(PlayerObject* _owner, float _deltaTime) override;
	void Inipt(class PlayerObject* _owner, const InputState& _keyState);
	void Enter(class PlayerObject* _owner, float _deltaTime)override;
private:
	void MoveCalc(PlayerObject* _owner, float _deltaTime);

	bool mIsIdle;
	bool mIsAttack;

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
};