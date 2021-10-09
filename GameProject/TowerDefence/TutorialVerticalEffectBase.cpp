#include "TutorialVerticalEffectBase.h"
#include "Renderer.h"

TutorialVerticalEffectBase::TutorialVerticalEffectBase(const Vector3& _pos, const Vector3& _velocity, const int _lifeCount, const Tag& _objectTag, const SceneBase::Scene _sceneTag, const float& _scale)
	: GameObject(_sceneTag, _objectTag)
	,lifeCount(_lifeCount)
{
	velocity = _velocity;
	SetPosition(_pos);
	particle = new ParticleComponent(this);
	particleTexture = new Texture();
	particleTexture = RENDERER->GetTexture("Assets/tutorial01.png");
	int texID = particleTexture->GetTextureID();
	particle->SetTextureID(texID);
	particle->SetColor(Vector3(1.0f, 1.0f, 1.0f));
	particle->SetScale(_scale);
}

void TutorialVerticalEffectBase::UpdateGameObject(float _deltaTime)
{
	UpdateParticleObject(_deltaTime);
	SetPosition(position + velocity);
}

void TutorialVerticalEffectBase::UpdateParticleObject(float _deltaTime)
{
	LifeCountDown();
}

void TutorialVerticalEffectBase::LifeCountDown()
{
	//�������Ԃ��[���ɂȂ�Ƃ��̃I�u�W�F�N�g���X�V�I������
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