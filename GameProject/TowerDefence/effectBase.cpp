#include "effectBase.h"
#include "Renderer.h"

EffectBase::EffectBase(const Vector3& _pos, const Vector3& _velocity, const int _lifeCount, const Tag& _objectTag, const SceneBase::Scene _sceneTag, const float& _scale)
	: GameObject(_sceneTag, _objectTag)
	,lifeCount(_lifeCount)
{
	velocity = _velocity;
	SetPosition(_pos);
	particle = new ParticleComponent(this);
	particleTexture = new Texture();
	particleTexture = RENDERER->GetTexture("Assets/title.png");
	int texID = particleTexture->GetTextureID();
	particle->SetTextureID(texID);
	particle->SetColor(Vector3(1.0f, 1.0f, 1.0f));
	particle->SetScale(_scale);
}

void EffectBase::UpdateGameObject(float _deltaTime)
{
	UpdateParticleObject(_deltaTime);
	SetPosition(position + velocity);
}

void EffectBase::UpdateParticleObject(float _deltaTime)
{
	LifeCountDown();
}

void EffectBase::LifeCountDown()
{
	//生存時間がゼロになるとこのオブジェクトを更新終了する
	if (lifeCount <= 0)
	{
		particle->SetVisible(false);
		SetState(State::Dead);
	}
	else
	{
		particle->SetVisible(true);
		/*lifeCount--;*/
	}
}