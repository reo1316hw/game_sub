#include "ParticleEffectBase.h"
#include "Renderer.h"
#include "Texture.h"
#include "SceneBase.h"

ParticleEffectBase::ParticleEffectBase(const Vector3& _pos, const Vector3& _velocity, const int& _lifeCount, const std::string& _spriteFileName, const Tag& _objectTag, SceneBase::Scene _sceneTag, const float& _scale)
	: GameObject(_objectTag, _sceneTag)
	 ,lifeCount(_lifeCount)
{
	velocity = _velocity;
	SetPosition(_pos);
	particle = new ParticleComponent(this);
	particle->SetTextureID(RENDERER->GetTexture(_spriteFileName)->GetTextureID());
	particle->SetColor(Vector3(1.0f, 1.0f, 1.0f));
	particle->SetScale(_scale);
}

ParticleEffectBase::~ParticleEffectBase()
{
}

void ParticleEffectBase::UpdateGameObject(float _deltaTime)
{
	UpdateParticleObject(_deltaTime);
	SetPosition(position + velocity);
}

void ParticleEffectBase::UpdateParticleObject(float _deltaTime)
{
	LifeCountDown();
}

void ParticleEffectBase::LifeCountDown()
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
		lifeCount--;
	}

}

void ParticleEffectBase::SetReverve(float _flag)
{
	particle->SetReverce(_flag);

}