#include "pch.h"

/// <summary>
/// コンストラクタ
/// </summary>
MapCreate::MapCreate() 
	:GameObject(Tag::eOther,SceneBase::Scene::other)
	, MStaticObjectSize(Vector3(1.0f, 1.0f, 1.0f))
	, MPersonSize(Vector3(0.5f, 0.5f, 0.5f))
    , mPlayerPtr(nullptr)
{
	mSizeX = 0;
	mSizeY = 0;
	mOffset = 200;
}

/// <summary>
/// デストラクタ
/// </summary>
MapCreate::~MapCreate()
{
	mPlayerMapData.clear();
	mStaticObjectMapData.clear();
}

/// <summary>
/// jsonファイルをRapidJsonで読み込んで、マップデータを可変長配列に格納する
/// </summary>
void MapCreate::OpenFile()
{
	// プレイヤーのデータの読み込み
	if (!readTiledJson(mPlayerMapData, "Assets/Config/Fix3dActionGame.json", "Player"))
	{
		printf("don't have Layer/Player\n");
		return;
	}

	// 静的マップデータの読み込み
	if (!readTiledJson(mStaticObjectMapData, "Assets/Config/Fix3dActionGame.json", "StaticObject"))
	{
		printf("don't have Layer/StaticObject\n");
		return;
	}

	mSizeX = mStaticObjectMapData[0].size();
	mSizeY = mStaticObjectMapData.size();
	
	AccessMapData(mPlayerMapData);
	AccessMapData(mStaticObjectMapData);
}

/// <summary>
/// マップデータにアクセスする
/// </summary>
/// <param name="_mapData"> マップデータ </param>
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
/// オブジェクトを生成する
/// </summary>
/// <param name="_Name"> マップデータの要素 </param>
/// <param name="_ObjectPos"> オブジェクトの座標 </param>
void MapCreate::CreateGameObject(const unsigned int _Name, const Vector3 _ObjectPos)
{
	switch (_Name)
	{
	case(MapDataNum::ePlayerNum):

		mPlayerPtr = new PlayerObject(_ObjectPos, MPersonSize
			                          , "Assets/Model/Player/Player.gpmesh"
			                          , "Assets/Model/Player/Player.gpskel"
			                          , Tag::ePlayer
			                          , SceneBase::tutorial);
		break;

	case(MapDataNum::eGroundNum):

		new GroundObject(_ObjectPos - Vector3(0.0f, 0.0f, 100.0f), MStaticObjectSize, "Assets/Model/Ground/19Times19_Ground.gpmesh", Tag::eGround, SceneBase::tutorial);
		break;

	case(MapDataNum::eEnemyGeneratorNum):
	
		new EnemyObject(_ObjectPos, MPersonSize, "Assets/Model/Enemy/Enemy.gpmesh"
						, "Assets/Model/Enemy/Enemy.gpskel"
						, Tag::eEnemyGenerator
						, SceneBase::tutorial
						, mPlayerPtr);
		break;

	case(MapDataNum::eTranslucentWallNum):

		//new WallObject(_ObjectPos, MStaticObjectSize, "Assets/Model/Wall/VerticalSuperLongWall.gpmesh", Tag::eTranslucentWall, SceneBase::tutorial);
		break;
	
	case(MapDataNum::eTowerNum):

		new WallObject(_ObjectPos, MStaticObjectSize * 100.0f, "Assets/Model/Wall/Block.gpmesh", Tag::eTranslucentWall, SceneBase::tutorial);
		break;
    }
}

bool MapCreate::readTiledJson(std::vector<std::vector<int>>& _mapData, const char* _fileName, const char* _layerName)
{
	//RapidJsonドキュメントとして開けるか？
	rapidjson::Document doc;
	if (!openJsonFile(doc,_fileName))
	{
		return false;
	}

	//開いたdocumentのtypeはmapか？
	if (!IsExistMemberAndValue(doc,"type","map"))
	{
		return false;
	}
	//開いたdocumentにlayerはあるか？
	if (!IsExistArrayName(doc,"layers"))
	{
		return false;
	}
	//layer数を取得
	auto layer = doc["layers"].GetArray();
	int layerSize = layer.Size();

	//layer名から該当layerの添え字を調べる
	std::string layerNameString(_layerName);
	int layerIndex = findLayerIndex(layer, layerNameString);
	if (layerIndex<0)
	{
		return false;
	}

	//layer内にデータはあるか？
	rapidjson::Value::ConstMemberIterator itr = layer[layerIndex].FindMember("data");
	if (itr==layer[layerIndex].MemberEnd())
	{
		printf("レイヤー名:%sにマップデータがありません\n", _layerName);
		return false;
	}

	//レイヤーよりrapidjson配列作成
	const rapidjson::Value& rapidArrayData = layer[layerIndex]["data"].GetArray();
	int width, height;
	width = layer[layerIndex]["width"].GetInt();
	height = layer[layerIndex]["height"].GetInt();

	//ユーザー配列確保　行方向、列方向の順番にサイズ確保
	_mapData.resize(height);
	for (auto&mapIter:_mapData)
	{
		mapIter.resize(width);
	}

	//ユーザー配列（2次元）にデータをコピー
	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			//なぜかIDが+1ずれているので補正する
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
