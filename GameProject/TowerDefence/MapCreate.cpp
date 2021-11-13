#include "pch.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
MapCreate::MapCreate()
	:GameObject(Tag::eOther)
	, MPlayerHitPointGaugePosition(Vector3(-800.0f, -400.0f, 0.0f))
	, MBossHitPointGaugePosition(Vector3(400.0f, 400.0f, 0.0f))
	, MStaticObjectSize(Vector3(1.0f, 1.0f, 1.0f))
	, MPersonSize(Vector3(0.5f, 0.5f, 0.5f))
	, MGroundShiftVec(Vector3(0.0f, 0.0f, 50.0f))
	, MWallShiftVec(Vector3(0.0f, 0.0f, 300.0f))
    , mPlayerPtr(nullptr)
	, mEnemyObjectManagerPtr(nullptr)
{
	mSizeX = 0;
	mSizeY = 0;
	mOffset = 700;
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
MapCreate::~MapCreate()
{
	mPlayerMapData.clear();
	mUpperObjectMapData.clear();
	mUnderObjectMapData.clear();
	mBottomObjectMapData.clear();
}

/// <summary>
/// json�t�@�C����RapidJson�œǂݍ���ŁA�}�b�v�f�[�^���ϒ��z��Ɋi�[����
/// </summary>
void MapCreate::OpenFile()
{
	// �v���C���[�̃f�[�^�̓ǂݍ���
	if (!readTiledJson(mPlayerMapData, "Assets/Config/ValkyrieWarriorsMap.json", "Player"))
	{
		printf("don't have Layer/Player\n");
		return;
	}

	// ��w�}�b�v�f�[�^�̓ǂݍ���
	if (!readTiledJson(mUpperObjectMapData, "Assets/Config/ValkyrieWarriorsMap.json", "Upper"))
	{
		printf("don't have Layer/UpperObject\n");
		return;
	}

	// ���w�}�b�v�f�[�^�̓ǂݍ���
	if (!readTiledJson(mUnderObjectMapData, "Assets/Config/ValkyrieWarriorsMap.json", "Under"))
	{
		printf("don't have Layer/UnderObject\n");
		return;
	}

	// �ŉ��w�}�b�v�f�[�^�̓ǂݍ���
	if (!readTiledJson(mBottomObjectMapData, "Assets/Config/ValkyrieWarriorsMap.json", "Bottom"))
	{
		printf("don't have Layer/BottomObject\n");
		return;
	}

	mSizeX = mBottomObjectMapData[0].size();
	mSizeY = mBottomObjectMapData.size();
	
	// �G�l�~�[�}�l�[�W���[����
	mEnemyObjectManagerPtr = new EnemyObjectManager(Tag::eOther);
	mCreateEnemysPtr = mEnemyObjectManagerPtr->GetCreateEnemysPtr();

	// �v���C���[�̃}�b�v�f�[�^�ɃA�N�Z�X����
	AccessMapData(mPlayerMapData);
	// ��w�I�u�W�F�N�g�̃}�b�v�f�[�^�ɃA�N�Z�X����
	AccessMapData(mUpperObjectMapData);
	// ���w�I�u�W�F�N�g�̃}�b�v�f�[�^�ɃA�N�Z�X����
	AccessMapData(mUnderObjectMapData);
	// ���w�I�u�W�F�N�g�̃}�b�v�f�[�^�ɃA�N�Z�X����
	AccessMapData(mBottomObjectMapData);

	// �G�l�~�[�𐶐�
	mCreateEnemysPtr->CreateEnemyObject(MPersonSize, "Assets/Model/Enemy/Enemy.gpmesh", "Assets/Model/Enemy/Enemy.gpskel",
		                                Tag::eEnemy, mPlayerPtr);
	
	//// UI�𐶐�����
	//CreateUI();
}

/// <summary>
/// �}�b�v�f�[�^�ɃA�N�Z�X����
/// </summary>
/// <param name="_mapData"> �}�b�v�f�[�^ </param>
void MapCreate::AccessMapData(std::vector<std::vector<int>> _mapData)
{
	for (int iy = 0; iy < mSizeY; iy++)
	{
		for (int ix = 0; ix < mSizeX; ix++)
		{
			unsigned int Name = _mapData[iy][ix];
			Vector3 ObjectPos = Vector3(mOffset * ix, mOffset * iy, 0.0f);

			CreateGameObject(Name, ObjectPos);
		}
	}
}

/// <summary>
/// �I�u�W�F�N�g�𐶐�����
/// </summary>
/// <param name="_Name"> �}�b�v�f�[�^�̗v�f </param>
/// <param name="_ObjectPos"> �I�u�W�F�N�g�̍��W </param>
void MapCreate::CreateGameObject(const unsigned int _Name, const Vector3 _ObjectPos)
{
	switch (_Name)
	{
	case(MapDataNum::ePlayerNum):

		mPlayerPtr = new PlayerObject(_ObjectPos, MPersonSize, "Assets/Model/Player/Player.gpmesh",
			                          "Assets/Model/Player/Player.gpskel", Tag::ePlayer);
		break;

	case(MapDataNum::eGroundNum):
	{
		// ���̍��W
		Vector3 groundPos = _ObjectPos - MGroundShiftVec;

		new GroundObject(groundPos, MStaticObjectSize,
			             "Assets/Model/Ground/Ground.gpmesh", Tag::eGround);
		break;
	}	
	case(MapDataNum::eLateralWallNum):
	{
		// ���ǂ̍��W
		Vector3 lateralWallPos = _ObjectPos + MWallShiftVec;

		new WallObject(lateralWallPos, MStaticObjectSize, "Assets/Model/Wall/LateralWall.gpmesh", Tag::eTranslucentWall);
		break;
	}
	case(MapDataNum::eVerticalWallNum):
	{
		// �c�ǂ̍��W
		Vector3 VerticalWallPos = _ObjectPos + MWallShiftVec;

		new WallObject(VerticalWallPos, MStaticObjectSize, "Assets/Model/Wall/VerticalWall.gpmesh", Tag::eTranslucentWall);
		break;
	}
	case(MapDataNum::eEnemyGeneratorNum):

		// �G�l�~�[�̐�����𐶐�
		mCreateEnemysPtr->CreateEnemyGenerator(_ObjectPos, MStaticObjectSize, mPlayerPtr);

		break;
	case(MapDataNum::eBossNum):

		// �G�l�~�[�{�X�𐶐�
		mBossPtr = mCreateEnemysPtr->CreateBossObject(_ObjectPos, MPersonSize, "Assets/Model/Boss/Boss.gpmesh",
			"Assets/Model/Boss/Boss.gpskel", Tag::eBoss, mPlayerPtr);

		break;
	}
}

/// <summary>
/// UI�𐶐�����
/// </summary>
void MapCreate::CreateUI()
{
	// �v���C���[��hp�Q�[�W�𐶐�
	new PlayerHitPointGauge(MPlayerHitPointGaugePosition, "Assets/Texture/hp.png", Tag::eOther, mPlayerPtr);
	// �v���C���[��hp�̘g�𐶐�
	new PlayerHitPointFrame(MPlayerHitPointGaugePosition + Vector3(0.0f, 200.0f, 0.0f), "Assets/Texture/hp.png", Tag::eOther);
	// �{�X��hp�Q�[�W�𐶐�
	new BossHitPointGauge(MBossHitPointGaugePosition, "Assets/Texture/hp.png", Tag::eOther, mBossPtr);
	// �{�X��hp�̘g�𐶐�
	new BossHitPointFrame(MBossHitPointGaugePosition + Vector3(0.0f, -200.0f, 0.0f), "Assets/Texture/hp.png", Tag::eOther);
}

bool MapCreate::readTiledJson(std::vector<std::vector<int>>& _mapData, const char* _fileName, const char* _layerName)
{
	//RapidJson�h�L�������g�Ƃ��ĊJ���邩�H
	rapidjson::Document doc;
	if (!openJsonFile(doc,_fileName))
	{
		return false;
	}

	//�J����document��type��map���H
	if (!IsExistMemberAndValue(doc,"type","map"))
	{
		return false;
	}
	//�J����document��layer�͂��邩�H
	if (!IsExistArrayName(doc,"layers"))
	{
		return false;
	}
	//layer�����擾
	auto layer = doc["layers"].GetArray();
	int layerSize = layer.Size();

	//layer������Y��layer�̓Y�����𒲂ׂ�
	std::string layerNameString(_layerName);
	int layerIndex = findLayerIndex(layer, layerNameString);
	if (layerIndex<0)
	{
		return false;
	}

	//layer���Ƀf�[�^�͂��邩�H
	rapidjson::Value::ConstMemberIterator itr = layer[layerIndex].FindMember("data");
	if (itr==layer[layerIndex].MemberEnd())
	{
		printf("���C���[��:%s�Ƀ}�b�v�f�[�^������܂���\n", _layerName);
		return false;
	}

	//���C���[���rapidjson�z��쐬
	const rapidjson::Value& rapidArrayData = layer[layerIndex]["data"].GetArray();
	int width, height;
	width = layer[layerIndex]["width"].GetInt();
	height = layer[layerIndex]["height"].GetInt();

	//���[�U�[�z��m�ہ@�s�����A������̏��ԂɃT�C�Y�m��
	_mapData.resize(height);
	for (auto&mapIter:_mapData)
	{
		mapIter.resize(width);
	}

	//���[�U�[�z��i2�����j�Ƀf�[�^���R�s�[
	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			//�Ȃ���ID��+1����Ă���̂ŕ␳����
			_mapData[y][x] = rapidArrayData[y * width + x].GetInt();
		}
	}
	return true;
}

int MapCreate::findLayerIndex(rapidjson::GenericArray<false, rapidjson::Value>& layer, std::string& layerName)
{
	int layerSize = layer.Size();
	int i;
	std::string layerNameString(layerName);
	for ( i = 0; i < layerSize; i++)
	{
		std::string currentLayerName = layer[i]["name"].GetString();
		printf("%s\n", currentLayerName.c_str());
		if (layerNameString == currentLayerName)
		{
			break;
		}
	}
	if (i == layerSize)
	{
		return -1;
	}
	return i;
}
