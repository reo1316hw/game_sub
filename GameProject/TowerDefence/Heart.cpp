#include "Heart.h"
#include "Renderer.h"

HeartUI::HeartUI(GameObject* _owner )
{
	ui = new UI(_owner);

	uiTexture = RENDERER->GetTexture("Assets/heart.png");
	ui->SetTexture(uiTexture);
}

HeartUI::~HeartUI()
{
	delete ui;
}
