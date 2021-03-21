#include "UIBase.h"
#include "Renderer.h"
#include "Texture.h"
#include "SceneBase.h"

UIBase::UIBase(const Vector2& _pos, const std::string& _spriteFileName, const Tag& _objectTag, SceneBase::Scene _sceneTag, const float& _scale)
	: GameObject(_objectTag, _sceneTag)
{
	//ui = new UIComponent(this);
}

void UIBase::UpdateGameObject(float _deltaTime)
{
	/*UpdateParticleObject(_deltaTime);*/
}

//void UIBase::UpdateParticleObject(float _deltaTime)
//{
//
//}