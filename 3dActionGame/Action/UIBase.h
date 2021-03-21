#pragma once
#include "GameObject.h"
#include "UIComponent.h"
#include <string>

/*
@file ParticleEffectBase.h
@brief ��莞�Ԃŏ�����A��ɃG�t�F�N�g�̊��N���X�Ƃ��Ďg�p�����N���X
*/
class UIBase :
	public GameObject
{
public:
	/*
	@param _pos �I�u�W�F�N�g�̐����ꏊ
	@param _velocity �I�u�W�F�N�g�̈ړ���
	@param _lifeCount �I�u�W�F�N�g�̐�������
	@param _spriteFileName �摜�ւ̃A�h���X
	@param _scale �摜�̊g��T�C�Y
	*/
	UIBase(const Vector2& _pos,const std::string& _spriteFileName, const Tag& _objectTag, SceneBase::Scene _sceneTag, const float& _scale = 10);
	~UIBase() {};

	/*
	@fn �h���N���X�̍X�V�֐����Ăэ��W�Ɉړ��ʂ𑫂�������
	*/
	void UpdateGameObject(float _deltaTime)override;

private:
	/*
	@fn �h���N���X���ƂɌ��肷��X�V�֐�
	*/
	/*virtual void UpdateParticleObject(float _deltaTime);*/
protected:
	
	//�摜�̕`��N���X
	UIComponent* ui;
public:
};
