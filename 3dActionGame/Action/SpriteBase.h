#pragma once
#include "GameObject.h"
#include <string>

class SpriteBase :
	public GameObject
{
public:
	SpriteBase(const std::string _fileName);
	~SpriteBase() {};
private:
	

};

