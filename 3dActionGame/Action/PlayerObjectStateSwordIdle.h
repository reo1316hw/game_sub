#pragma once
#include "PlayerObjectStateBase.h"

class PlayerObjectStateSwordIdle : public PlayerObjectStateBase
{
public:
	PlayerObjectStateSwordIdle();
	~PlayerObjectStateSwordIdle();
	PlayerState Update(PlayerObject* _owner, float _deltaTime) override;
	void Inipt(class PlayerObject* _owner, const InputState& _keyState);
	void Enter(class PlayerObject* _owner, float _deltaTime)override;
private:
	//プレイヤーの状態遷移に使うフラグ
	bool mIsSprint;		//走り出すか
	bool mIsRun;		//走るか
	bool mIsAttack;		//攻撃するか
	bool swordDelivery; //納刀したかどうか
};