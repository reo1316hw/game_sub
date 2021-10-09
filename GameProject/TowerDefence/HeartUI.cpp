#include "HeartUI.h"
#include "Renderer.h"
#include "Player.h"

HeartUI::HeartUI(const Vector2& _pos, SceneBase::Scene _sceneTag, const Tag& _objectTag)
	:UIBase(_pos, "Assets/heart02.png", _sceneTag, _objectTag)
{
	mUI = new UIComponent(this);
	mUI->SetTexture(RENDERER->GetTexture("Assets/heart.png"));

	mPosition = Vector3(_pos.x, _pos.y, 0.0f);

}

void HeartUI::UpdateGameObject(float _deltaTime)
{
	if (player->GetLife() == 2)
	{
		if (mUI->GetUIid() == 2 || mUI->GetUIid() == 5 || mUI->GetUIid() == 8)
		{
			mUI->SetVisible(false);

		}
	}

	if (player->GetLife() == 1)
	{
		if (mUI->GetUIid() == 1 || mUI->GetUIid() == 4 || mUI->GetUIid() == 7)
		{
			mUI->SetVisible(false);

		}
	}

	if (player->GetLife() == 0)
	{
		if (mUI->GetUIid() == 0 || mUI->GetUIid() == 3 || mUI->GetUIid() == 6)
		{
			mUI->SetVisible(false);
		}
	}
}
