#pragma once
#include "UI.h"

class HeartUI
{
public:
	HeartUI(GameObject* _owner );
	~HeartUI();
private:
	UI* ui;
	Texture* uiTexture;
};