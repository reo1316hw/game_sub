#pragma once
#include "GameObject.h"
#include "Texture.h"
#include "ParticleComponent.h"

// ��莞�Ԃŏ�����A��ɃG�t�F�N�g�̊��N���X�Ƃ��Ďg�p�����N���X
class TutorialEffectBase : public GameObject
{
public:
	/*
	_pos �I�u�W�F�N�g�̐����ꏊ
	_velocity �I�u�W�F�N�g�̈ړ���
	_lifeCount �I�u�W�F�N�g�̐�������
	_size �摜�̊g��T�C�Y
	*/

	TutorialEffectBase(const Vector3& _pos, const Vector3& _velocity, const int _lifeCount, const Tag& _objectTag, const SceneBase::Scene _sceneTag, const float& _scale = 10);
	~TutorialEffectBase() {}

	enum ParticleState
	{
		ACTIVE,
		DISABLE,
	};

	// �h���N���X�̍X�V�֐����Ăэ��W�Ɉړ��ʑ���������
	void UpdateGameObject(float _deltaTime)override;
protected:

	void LifeCountDown();

	ParticleComponent* particle;
	Texture* particleTexture;

	// �p�[�e�B�N�������݂��Ă��鎞��
	int lifeCount;

	ParticleState particleState;
private:
	virtual void UpdateParticleObject(float _deltaTime);
};