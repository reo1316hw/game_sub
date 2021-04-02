#pragma once
#include "PlayerObjectStateBase.h"

class PlayerObjectStateIdle : public PlayerObjectStateBase
{
public:
	PlayerObjectStateIdle(class AttackMeshComponent* _attackMesh, class SkeletalMeshComponent* _skMesh, const char* _AttachBoneName);
	~PlayerObjectStateIdle();
	PlayerState Update(PlayerObject* _owner, float _deltaTime) override;
	void Inipt(class PlayerObject* _owner, const InputState& _keyState) override;
	void Enter(class PlayerObject* _owner, float _deltaTime)override;
private:
};