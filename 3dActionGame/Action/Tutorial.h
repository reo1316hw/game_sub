#pragma once
#include "SceneBase.h"
#include "MapCreate.h"
#include "SpriteComponent.h"
#include "Texture.h"
#include "Shader.h"
#include "PlayerObject.h"
#include "ParticleComponent.h"
#include <SDL.h>

class Tutorial : public SceneBase
{
public:
	Tutorial(const Scene& _scene);
	~Tutorial();

	SceneBase* update() override;
	void       draw() override;

	static bool GetContinueTutorialFlag() { return sendContinueTutorialFlag; };
	static void SetContinueTutorialFlag(bool _continue) { sendContinueTutorialFlag = _continue; };

private:
	MapCreate* mapCreate;
	PlayerObject* player;
	Sprite* sprite;

	static bool sendContinueTutorialFlag;

	bool continueTutorialFlag;
	int count;
};

