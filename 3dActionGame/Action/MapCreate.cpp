#include "MapCreate.h"
#include "SceneBase.h"
#include "GroundObject.h"
#include "WallObject.h"
#include "PlayerObject.h"
#include "EnemyObject.h"

MapCreate::MapCreate() :GameObject(Tag::Other,SceneBase::Scene::other)
{
	sizeX = 0;
	sizeY = 0;
	sizeZ = 0;
	offset = 200;
}

MapCreate::~MapCreate()
{
	groundMapData.clear();
	wallMapData.clear();
	playerMapData.clear();
	enemyMapData.clear();
}

bool MapCreate::OpenFile()
{
	scene = SceneBase::GetScene();

	//-----------------------------------------------
	//----------------tutorial-----------------------
	//-----------------------------------------------
	if (scene == SceneBase::tutorial)
	{
		//床データの読み込み
		if (!readTiledJson(groundMapData, "Assets/Config/3dActionGame02.json", "Ground"))
		{
			printf("don't have Layer/Ground\n");
			return true;
		}

		sizeX = groundMapData[0].size();
		sizeY = groundMapData[0].size();
		//sizeZ = groundMapData[0].size();

		//壁データの読み込み
		if (!readTiledJson(wallMapData, "Assets/Config/3dActionGame02.json", "Wall"))
		{
			printf("don't have Layer/Wall\n");
			return true;
		}

		//プレイヤーデータの読み込み
		if (!readTiledJson(playerMapData, "Assets/Config/3dActionGame02.json", "Player"))
		{
			printf("don't have Layer/player\n");
			return true;
		}

		//エネミーデータの読み込み
		if (!readTiledJson(enemyMapData, "Assets/Config/3dActionGame02.json", "Enemy"))
		{
			printf("don't have Layer/Enemy\n");
			return true;
		}
	}

	return false;
}

void MapCreate::CreateGround()
{
	for (float ix = 0; ix < sizeX; ix++)
	{
		for (float iy = 0; iy < sizeY; iy++)
		{
			const unsigned int name = groundMapData[(int)ix][(int)iy];
			Vector3 objectPos		= Vector3(offset * ix, -offset * iy, 0.0f);
			Vector3 objectPosEvenX	= Vector3(offset * ix, -offset * iy + 100.0f, 0.0f);
			Vector3 objectPosEvenY	= Vector3(offset * ix + 100.0f, -offset * iy, 0.0f);
			//Vector3 objectPosEvenXY = Vector3(offset * ix - 100.0f, -100.0f, -offset * iz - 100.0f);
			Vector3 objectSize = Vector3(1.0f, 1.0f, 1.0f);

			switch (scene)
			{
			case SceneBase::tutorial:

				switch (name)
				{
				case(11):
					new GroundObject(objectPosEvenX, objectSize, "Assets/Ground/8Times17_Ground.gpmesh", Tag::EightTimesSeventeenGround, SceneBase::tutorial);
					break;
				case(12):
					new GroundObject(objectPosEvenX, objectSize, "Assets/Ground/6Times3_Ground.gpmesh", Tag::SixTimesThreeGround, SceneBase::tutorial);
					break;
				case(13):
					new GroundObject(objectPosEvenX, objectSize, "Assets/Ground/4Times5_Ground.gpmesh", Tag::FourTimesFiveGround, SceneBase::tutorial);
					break;
				case(14):
					new GroundObject(objectPosEvenY, objectSize, "Assets/Ground/3Times4_Ground.gpmesh", Tag::ThreeTimesFourGround, SceneBase::tutorial);
					break;
				case(15):
					new GroundObject(objectPosEvenY, objectSize, "Assets/Ground/25Times2_Ground.gpmesh", Tag::TwentyFiveTimesTwoGround, SceneBase::tutorial);
					break;
				case(16):
					new GroundObject(objectPosEvenX, objectSize, "Assets/Ground/12Times13_Ground.gpmesh", Tag::TwelveTimesThirteenGround, SceneBase::tutorial);
					break;
				case(17):
					new GroundObject(objectPos, objectSize, "Assets/Ground/3Times9_Ground.gpmesh", Tag::ThreeTimesNineGround01, SceneBase::tutorial);
					break;
				case(18):
					new GroundObject(objectPosEvenY, objectSize, "Assets/Ground/9Times2_Ground.gpmesh", Tag::NineTimesTwoGround, SceneBase::tutorial);
					break;
				case(19):
					new GroundObject(objectPos, objectSize, "Assets/Ground/3Times9_Ground.gpmesh", Tag::ThreeTimesNineGround02, SceneBase::tutorial);
					break;
				case(20):
					new GroundObject(objectPos, objectSize, "Assets/Ground/7Times7_Ground.gpmesh", Tag::SevenTimesSevenGround, SceneBase::tutorial);
					break;
				case(21):
					new GroundObject(objectPos, objectSize, "Assets/Ground/13Times3_Ground.gpmesh", Tag::ThirteenTimesThreeGround, SceneBase::tutorial);
					break;
				case(22):
					new GroundObject(objectPos, objectSize, "Assets/Ground/3Times3_Ground.gpmesh", Tag::ThreeTimesThreeGround, SceneBase::tutorial);
					break;
				case(23):
					new GroundObject(objectPos, objectSize, "Assets/Ground/11Times1_Ground.gpmesh", Tag::ElevenTimesOneGround, SceneBase::tutorial);
					break;
				case(24):
					new GroundObject(objectPos, objectSize, "Assets/Ground/19Times19_Ground.gpmesh", Tag::NineteenTimesNineteenGround, SceneBase::tutorial);
					break;
				}
				break;
			}
		}
	}
}

void MapCreate::CreateWall()
{
	for (float ix = 0; ix < sizeX; ix++)
	{
		for (float iy = 0; iy < sizeY; iy++)
		{
			const unsigned int name = wallMapData[(int)ix][(int)iy];
			Vector3 objectPos	= Vector3(offset * ix, -offset * iy + 100.0f, 1000.0f);
			Vector3 objectPos02 = Vector3(offset * ix + 100.0f, -offset * iy, 1000.0f);
			Vector3 objectSize	= Vector3(1.0f, 1.0f, 1.0f);

			switch (scene)
			{
			case SceneBase::tutorial:

				switch (name)
				{
				case(2):
					new WallObject(objectPos, objectSize, "Assets/Wall/SideSuperShortWall.gpmesh", Tag::SideSuperShortWall, SceneBase::tutorial);
					break;
				case(3):
					new WallObject(objectPos02, objectSize, "Assets/Wall/VerticalSuperShortWall.gpmesh", Tag::VerticalSuperShortWall, SceneBase::tutorial);
					break;
				case(4):
					new WallObject(objectPos, objectSize, "Assets/Wall/SideShortWall.gpmesh", Tag::SideShortWall, SceneBase::tutorial);
					break;
				case(5):
					new WallObject(objectPos02, objectSize, "Assets/Wall/VerticalShortWall.gpmesh", Tag::VerticalShortWall, SceneBase::tutorial);
					break;
				case(6):
					new WallObject(objectPos, objectSize, "Assets/Wall/UsuallyWall.gpmesh", Tag::UsuallyWall, SceneBase::tutorial);
					break;
				case(7):
					new WallObject(objectPos, objectSize, "Assets/Wall/SideLongWall.gpmesh", Tag::SideLongWall, SceneBase::tutorial);
					break;
				case(8):
					new WallObject(objectPos02, objectSize, "Assets/Wall/VerticalLongWall.gpmesh", Tag::VerticalLongWall, SceneBase::tutorial);
					break;
				case(9):
					new WallObject(objectPos, objectSize, "Assets/Wall/SideSuperLongWall.gpmesh", Tag::SideSuperLongWall, SceneBase::tutorial);
					break;
				case(10):
					new WallObject(objectPos02, objectSize, "Assets/Wall/VerticalSuperLongWall.gpmesh", Tag::VerticalSuperLongWall, SceneBase::tutorial);
					break;
				}
				break;
			}

		}
	}
}

void MapCreate::CreateEnemy()
{
	for (float ix = 0; ix < sizeX; ix++)
	{
		for (float iy = 0; iy < sizeY; iy++)
		{
			const unsigned int name = enemyMapData[(int)ix][(int)iy];
			Vector3 objectPos = Vector3(offset * ix, -offset * iy, 100.0f);
			Vector3 objectSize = Vector3(0.5f, 0.5f, 0.5f);

			switch (scene)
			{
			case SceneBase::tutorial:

				switch (name)
				{
				case(25):
					new EnemyObject(objectPos, objectSize , "Assets/Model/Enemy/Enemy.gpmesh"
														  , "Assets/Model/Enemy/Enemy.gpskel"
														  , "Assets/Model/Enemy/EnemyIdle.gpanim"
														  , Tag::Enemy
														  , SceneBase::tutorial);
					break;
				}
				break;
			}
		}
	}
}

void MapCreate::CreatePlayer()
{
	for (float ix = 0; ix < sizeX; ix++)
	{
		for (float iy = 0; iy < sizeY; iy++)
		{
			const unsigned int name = playerMapData[(int)ix][(int)iy];
			Vector3 objectPos = Vector3(offset * ix, -offset * iy, 100.0f);
			Vector3 objectSize = Vector3(0.5f, 0.5f, 0.5f);

			switch (scene)
			{
			case SceneBase::tutorial:

				switch (name)
				{
				case(1):
					new PlayerObject(objectPos, objectSize, "Assets/Model/Player/Player.gpmesh"
														  , "Assets/Model/Player/Player.gpskel"
						                                  , "Assets/Model/Player/PlayerIdle.gpanim"
														  , Tag::Player
						                                  , SceneBase::tutorial);
					break;
				}
				break;
			}
		}
	}

}

bool MapCreate::readTiledJson(std::vector<std::vector<int>>& mapData, const char* fileName, const char* layerName)
{
	//RapidJsonドキュメントとして開けるか？
	rapidjson::Document doc;
	if (!openJsonFile(doc,fileName))
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
	std::string layerNameString(layerName);
	int layerIndex = findLayerIndex(layer, layerNameString);
	if (layerIndex<0)
	{
		return false;
	}

	//layer内にデータはあるか？
	rapidjson::Value::ConstMemberIterator itr = layer[layerIndex].FindMember("data");
	if (itr==layer[layerIndex].MemberEnd())
	{
		printf("レイヤー名:%sにマップデータがありません\n", layerName);
		return false;
	}

	//レイヤーよりrapidjson配列作成
	const rapidjson::Value& rapidArrayData = layer[layerIndex]["data"].GetArray();
	int width, height;
	width = layer[layerIndex]["width"].GetInt();
	height = layer[layerIndex]["height"].GetInt();

	//ユーザー配列確保　行方向、列方向の順番にサイズ確保
	mapData.resize(height);
	for (auto&mapIter:mapData)
	{
		mapIter.resize(width);
	}

	//ユーザー配列（2次元）にデータをコピー
	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			//なぜかIDが+1ずれているので補正する
			mapData[y][x] = rapidArrayData[y * width + x].GetInt();
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
