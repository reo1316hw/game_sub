#pragma once
#include <vector>

#include"GameObject.h"
#include "RapidJsonHelper.h"

class MapCreate : public GameObject
{
public:
	MapCreate();
	~MapCreate();

	//jsonから読み込んで可変長コンテナに格納する関数
	bool OpenFile();

	//全ての"床"を生成し配置する関数
	void CreateGround();
	//全ての"プレイヤー"を生成し配置する関数
	void CreatePlayer();
	//全ての"壁"を生成し配置する関数
	void CreateWall();
	//全ての"敵"を生成し配置する関数
	void CreateEnemy();

private:
	bool readTiledJson(std::vector<std::vector<int>>& mapData, const char* fileName, const char* layerName);
	int  findLayerIndex(rapidjson::GenericArray<false,rapidjson::Value>& layer,std::string& layerName);

	//jsonから読み込んだ"プレイヤー"データを格納するための可変長コンテナ
	std::vector<std::vector<int>> playerMapData;
	//jsonから読み込んだ"床"データを格納するための可変長コンテナ
	std::vector<std::vector<int>> groundMapData;
	//jsonから読み込んだ"壁"データを格納するための可変長コンテナ
	std::vector<std::vector<int>> wallMapData;
	//jsonから読み込んだ"エネミー"データを格納するための可変長コンテナ
	std::vector<std::vector<int>> enemyMapData;

	int scene;

	int sizeX;
	int sizeY;
	int sizeZ;
	float offset;
};

