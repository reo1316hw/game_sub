#pragma once
#include "SceneBase.h"

class TitleScene : public SceneBase
{
public:
	TitleScene(const Scene& _scene);
	~TitleScene();

	SceneBase* update() override;
private:
};

