#pragma once

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
	bool readTiledJson(std::vector<std::vector<int>>& _mapData, const char* _fileName, const char* _layerName);
	int  findLayerIndex(rapidjson::GenericArray<false,rapidjson::Value>& _layer,std::string& _layerName);

	//json����ǂݍ���"�v���C���["�f�[�^���i�[���邽�߂̉ϒ��R���e�i
	std::vector<std::vector<int>> mPlayerMapData;
	//json����ǂݍ���"��"�f�[�^���i�[���邽�߂̉ϒ��R���e�i
	std::vector<std::vector<int>> mGroundMapData;
	//json����ǂݍ���"��"�f�[�^���i�[���邽�߂̉ϒ��R���e�i
	std::vector<std::vector<int>> mWallMapData;
	//json����ǂݍ���"�G�l�~�["�f�[�^���i�[���邽�߂̉ϒ��R���e�i
	std::vector<std::vector<int>> mEnemyMapData;

	int		mScene;
	int		mSizeX;
	int		mSizeY;
	int		mSizeZ;
	float	mOffset;

	PlayerObject* mPlayerPtr;
};

