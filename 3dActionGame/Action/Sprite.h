#pragma once
#include "GameObject.h"
#include <string>

class Texture;
class SpriteComponent;

class Sprite :
	public GameObject
{
public:
	Sprite(const std::string _fileName);
	~Sprite() {};
private:
	Texture* spriteTexture;
	SpriteComponent* spriteComponent;
};

