#pragma once

// 前方宣言
class Texture;
class SpriteComponent;

class Sprite : public GameObject
{
public:
	Sprite(const std::string _fileName);
	~Sprite() {};
private:
	//テクスチャを生成
	Texture* mSpriteTexture;
	//SpriteComponentを生成
	SpriteComponent* mSpriteComponent;
};

