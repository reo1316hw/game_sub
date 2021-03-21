#pragma once
#include "GameObject.h"
#include "UIComponent.h"
#include <string>

/*
@file ParticleEffectBase.h
@brief 一定時間で消える、主にエフェクトの基底クラスとして使用されるクラス
*/
class UIBase :
	public GameObject
{
public:
	/*
	@param _pos オブジェクトの生成場所
	@param _velocity オブジェクトの移動量
	@param _lifeCount オブジェクトの生存時間
	@param _spriteFileName 画像へのアドレス
	@param _scale 画像の拡大サイズ
	*/
	UIBase(const Vector2& _pos,const std::string& _spriteFileName, const Tag& _objectTag, SceneBase::Scene _sceneTag, const float& _scale = 10);
	~UIBase() {};

	/*
	@fn 派生クラスの更新関数を呼び座標に移動量を足し続ける
	*/
	void UpdateGameObject(float _deltaTime)override;

private:
	/*
	@fn 派生クラスごとに決定する更新関数
	*/
	/*virtual void UpdateParticleObject(float _deltaTime);*/
protected:
	
	//画像の描画クラス
	UIComponent* ui;
public:
};
