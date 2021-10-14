#pragma once

// �O���錾
class Texture;
class SpriteComponent;

class Sprite : public GameObject
{
public:
	Sprite(const std::string _fileName);
	~Sprite() {};
private:
	//�e�N�X�`���𐶐�
	Texture* mSpriteTexture;
	//SpriteComponent�𐶐�
	SpriteComponent* mSpriteComponent;
};

