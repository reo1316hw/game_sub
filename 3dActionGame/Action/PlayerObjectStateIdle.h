#pragma once
#include "PlayerObjectStateBase.h"

class PlayerObjectStateIdle : public PlayerObjectStateBase
{
public:
	PlayerObjectStateIdle();
	~PlayerObjectStateIdle();
	PlayerState Update(PlayerObject* _owner, float _deltaTime) override;
	void Inipt(class PlayerObject* _owner, const InputState& _keyState);
	void Enter(class PlayerObject* _owner, float _deltaTime)override;
private:
	//プレイヤーの状態遷移に使うフラグ
	bool mIsSprint;				//走り出すか
	bool mIsRun;				//走るか
	bool mIsAttack;				//攻撃するか
	bool mIsSwordDelivery;		//抜刀するか
};