#pragma once
#include "GameObject.h"
#include "Texture.h"
#include "ParticleComponent.h"

// 一定時間で消える、主にエフェクトの基底クラスとして使用されるクラス
class TutorialEffectBase : public GameObject
{
public:
	/*
	_pos オブジェクトの生成場所
	_velocity オブジェクトの移動量
	_lifeCount オブジェクトの生存時間
	_size 画像の拡大サイズ
	*/

	TutorialEffectBase(const Vector3& _pos, const Vector3& _velocity, const int _lifeCount, const Tag& _objectTag, const SceneBase::Scene _sceneTag, const float& _scale = 10);
	~TutorialEffectBase() {}

	enum ParticleState
	{
		ACTIVE,
		DISABLE,
	};

	// 派生クラスの更新関数を呼び座標に移動量足し続ける
	void UpdateGameObject(float _deltaTime)override;
protected:

	void LifeCountDown();

	ParticleComponent* particle;
	Texture* particleTexture;

	// パーティクルが存在している時間
	int lifeCount;

	ParticleState particleState;
private:
	virtual void UpdateParticleObject(float _deltaTime);
};