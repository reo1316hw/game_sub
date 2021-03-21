#pragma once
#include "PlayerObjectStateBase.h"

class PlayerObjectStateSword : public PlayerObjectStateBase
{
public:
	PlayerObjectStateSword(bool _moveFlag, bool _drawnSwordFlag);
	~PlayerObjectStateSword();
	PlayerState Update(PlayerObject* _owner, float _deltaTime) override;
	void Inipt(class PlayerObject* _owner, const InputState& _keyState) override;
	void Enter(class PlayerObject* _owner, float _deltaTime) override;
private:
	void MoveCalc(PlayerObject* _owner, float _deltaTime);

	bool mIsIdle;
	bool mIsRunStart;
	bool mIsAttack;
	//動くかどうか
	bool moveFlag;
	//抜刀したかどうか
	bool drawnSwordFlag;

	//  キャラの現在のスピード
	float charaSpeed;
	float mElapseTime;    // このステートに入ってからの経過時刻
	float mTotalAnimTime; // アニメーション総時間

	//向き
	Vector3 dirVec;
	//前進方向
	Vector3 forwardVec;
	//右方向
	Vector3 rightVec;
	// キャラの前進ベクトル
	Vector3 charaForwardVec;
};