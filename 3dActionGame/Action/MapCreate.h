#pragma once
#include <vector>

#include"GameObject.h"
#include "RapidJsonHelper.h"

class MapCreate : public GameObject
{
public:
	MapCreate();
	~MapCreate();

	//json����ǂݍ���ŉϒ��R���e�i�Ɋi�[����֐�
	bool OpenFile();

	//�S�Ă�"��"�𐶐����z�u����֐�
	void CreateGround();
	//�S�Ă�"�v���C���["�𐶐����z�u����֐�
	void CreatePlayer();
	//�S�Ă�"��"�𐶐����z�u����֐�
	void CreateWall();
	//�S�Ă�"�G"�𐶐����z�u����֐�
	void CreateEnemy();

private:
	bool readTiledJson(std::vector<std::vector<int>>& mapData, const char* fileName, const char* layerName);
	int  findLayerIndex(rapidjson::GenericArray<false,rapidjson::Value>& layer,std::string& layerName);

	//json����ǂݍ���"�v���C���["�f�[�^���i�[���邽�߂̉ϒ��R���e�i
	std::vector<std::vector<int>> playerMapData;
	//json����ǂݍ���"��"�f�[�^���i�[���邽�߂̉ϒ��R���e�i
	std::vector<std::vector<int>> groundMapData;
	//json����ǂݍ���"��"�f�[�^���i�[���邽�߂̉ϒ��R���e�i
	std::vector<std::vector<int>> wallMapData;
	//json����ǂݍ���"�G�l�~�["�f�[�^���i�[���邽�߂̉ϒ��R���e�i
	std::vector<std::vector<int>> enemyMapData;

	int scene;

	int sizeX;
	int sizeY;
	int sizeZ;
	float offset;
};

