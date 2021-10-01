#include "MapCreate.h"
#include "SceneBase.h"
#include "GroundObject.h"
#include "WallObject.h"
#include "PlayerObject.h"
#include "EnemyObject.h"

MapCreate::MapCreate() :GameObject(Tag::Other,SceneBase::Scene::other)
{
	mSizeX = 0;
	mSizeY = 0;
	mSizeZ = 0;
	mOffset = 200;
}

MapCreate::~MapCreate()
{
	mGroundMapData.clear();
	mWallMapData.clear();
	mPlayerMapData.clear();
	mEnemyMapData.clear();
}

bool MapCreate::OpenFile()
{
	mScene = SceneBase::GetScene();

	//-----------------------------------------------
	//----------------tutorial-----------------------
	//-----------------------------------------------
	if (mScene == SceneBase::tutorial)
	{
		//床データの読み込み
		if (!readTiledJson(mGroundMapData, "Assets/Config/3dActionGame.json", "Ground"))
		{
			printf("don't have Layer/Ground\n");
			return true;
		}

		mSizeX = mGroundMapData[0].size();
		mSizeY = mGroundMapData[0].size();
		//mSizeZ = mGroundMapData[0].size();

		//壁データの読み込み
		if (!readTiledJson(mWallMapData, "Assets/Config/3dActionGame.json", "Wall"))
		{
			printf("don't have Layer/Wall\n");
			return true;
		}

		//プレイヤーデータの読み込み
		if (!readTiledJson(mPlayerMapData, "Assets/Config/3dActionGame.json", "Player"))
		{
			printf("don't have Layer/player\n");
			return true;
		}

		//エネミーデータの読み込み
		if (!readTiledJson(mEnemyMapData, "Assets/Config/3dActionGame.json", "Enemy"))
		{
			printf("don't have Layer/Enemy\n");
			return true;
		}
	}

	return false;
}

void MapCreate::CreateGround()
{
	for (float ix = 0; ix < mSizeX; ix++)
	{
		for (float iy = 0; iy < mSizeY; iy++)
		{
			const unsigned int name = mGroundMapData[(int)ix][(int)iy];
			Vector3 objectPos		= Vector3(mOffset * ix, -mOffset * iy, 0.0f);
			Vector3 objectPosEvenX	= Vector3(mOffset * ix, -mOffset * iy + 100.0f, 0.0f);
			Vector3 objectPosEvenY	= Vector3(mOffset * ix + 100.0f, -mOffset * iy, 0.0f);
			//Vector3 objectPosEvenXY = Vector3(mOffset * ix - 100.0f, -100.0f, -mOffset * iz - 100.0f);
			Vector3 objectSize = Vector3(1.0f, 1.0f, 1.0f);

			switch (mScene)
			{
			case SceneBase::tutorial:

				switch (name)
				{
				case(11):
					new GroundObject(objectPosEvenX, objectSize, "Assets/Model/Ground/8Times17_Ground.gpmesh", Tag::EightTimesSeventeenGround, SceneBase::tutorial);
					break;
				case(12):
					new GroundObject(objectPosEvenX, objectSize, "Assets/Model/Ground/6Times3_Ground.gpmesh", Tag::SixTimesThreeGround, SceneBase::tutorial);
					break;
				case(13):
					new GroundObject(objectPosEvenX, objectSize, "Assets/Model/Ground/4Times5_Ground.gpmesh", Tag::FourTimesFiveGround, SceneBase::tutorial);
					break;
				case(14):
					new GroundObject(objectPosEvenY, objectSize, "Assets/Model/Ground/3Times4_Ground.gpmesh", Tag::ThreeTimesFourGround, SceneBase::tutorial);
					break;
				case(15):
					new GroundObject(objectPosEvenY, objectSize, "Assets/Model/Ground/25Times2_Ground.gpmesh", Tag::TwentyFiveTimesTwoGround, SceneBase::tutorial);
					break;
				case(16):
					new GroundObject(objectPosEvenX, objectSize, "Assets/Model/Ground/12Times13_Ground.gpmesh", Tag::TwelveTimesThirteenGround, SceneBase::tutorial);
					break;
				case(17):
					new GroundObject(objectPos, objectSize, "Assets/Model/Ground/3Times9_Ground.gpmesh", Tag::ThreeTimesNineGround01, SceneBase::tutorial);
					break;
				case(18):
					new GroundObject(objectPosEvenY, objectSize, "Assets/Model/Ground/9Times2_Ground.gpmesh", Tag::NineTimesTwoGround, SceneBase::tutorial);
					break;
				case(19):
					new GroundObject(objectPos, objectSize, "Assets/Model/Ground/3Times9_Ground.gpmesh", Tag::ThreeTimesNineGround02, SceneBase::tutorial);
					break;
				case(20):
					new GroundObject(objectPos, objectSize, "Assets/Model/Ground/7Times7_Ground.gpmesh", Tag::SevenTimesSevenGround, SceneBase::tutorial);
					break;
				case(21):
					new GroundObject(objectPos, objectSize, "Assets/Model/Ground/13Times3_Ground.gpmesh", Tag::ThirteenTimesThreeGround, SceneBase::tutorial);
					break;
				case(22):
					new GroundObject(objectPos, objectSize, "Assets/Model/Ground/3Times3_Ground.gpmesh", Tag::ThreeTimesThreeGround, SceneBase::tutorial);
					break;
				case(23):
					new GroundObject(objectPos, objectSize, "Assets/Model/Ground/11Times1_Ground.gpmesh", Tag::ElevenTimesOneGround, SceneBase::tutorial);
					break;
				case(24):
					new GroundObject(objectPos, objectSize, "Assets/Model/Ground/19Times19_Ground.gpmesh", Tag::NineteenTimesNineteenGround, SceneBase::tutorial);
					break;
				}
				break;
			}
		}
	}
}

void MapCreate::CreateWall()
{
	for (float ix = 0; ix < mSizeX; ix++)
	{
		for (float iy = 0; iy < mSizeY; iy++)
		{
			const unsigned int name = mWallMapData[(int)ix][(int)iy];
			Vector3 objectPos	= Vector3(mOffset * ix, -mOffset * iy + 100.0f, 1000.0f);
			Vector3 objectPos02 = Vector3(mOffset * ix + 100.0f, -mOffset * iy, 1000.0f);
			Vector3 objectSize	= Vector3(1.0f, 1.0f, 1.0f);

			switch (mScene)
			{
			case SceneBase::tutorial:

				switch (name)
				{
				case(2):
					new WallObject(objectPos, objectSize, "Assets/Model/Wall/SideSuperShortWall.gpmesh", Tag::SideSuperShortWall, SceneBase::tutorial);
					break;
				case(3):
					new WallObject(objectPos02, objectSize, "Assets/Model/Wall/VerticalSuperShortWall.gpmesh", Tag::VerticalSuperShortWall, SceneBase::tutorial);
					break;
				case(4):
					new WallObject(objectPos, objectSize, "Assets/Model/Wall/SideShortWall.gpmesh", Tag::SideShortWall, SceneBase::tutorial);
					break;
				case(5):
					new WallObject(objectPos02, objectSize, "Assets/Model/Wall/VerticalShortWall.gpmesh", Tag::VerticalShortWall, SceneBase::tutorial);
					break;
				case(6):
					new WallObject(objectPos, objectSize, "Assets/Model/Wall/UsuallyWall.gpmesh", Tag::UsuallyWall, SceneBase::tutorial);
					break;
				case(7):
					new WallObject(objectPos, objectSize, "Assets/Model/Wall/SideLongWall.gpmesh", Tag::SideLongWall, SceneBase::tutorial);
					break;
				case(8):
					new WallObject(objectPos02, objectSize, "Assets/Model/Wall/VerticalLongWall.gpmesh", Tag::VerticalLongWall, SceneBase::tutorial);
					break;
				case(9):
					new WallObject(objectPos, objectSize, "Assets/Model/Wall/SideSuperLongWall.gpmesh", Tag::SideSuperLongWall, SceneBase::tutorial);
					break;
				case(10):
					new WallObject(objectPos02, objectSize, "Assets/Model/Wall/VerticalSuperLongWall.gpmesh", Tag::VerticalSuperLongWall, SceneBase::tutorial);
					break;
				}
				break;
			}

		}
	}
}

void MapCreate::CreateEnemy()
{
	for (float ix = 0; ix < mSizeX; ix++)
	{
		for (float iy = 0; iy < mSizeY; iy++)
		{
			const unsigned int name = mEnemyMapData[(int)ix][(int)iy];
			Vector3 objectPos = Vector3(mOffset * ix, -mOffset * iy, 100.0f);
			Vector3 objectSize = Vector3(0.5f, 0.5f, 0.5f);

			switch (mScene)
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
	for (float ix = 0; ix < mSizeX; ix++)
	{
		for (float iy = 0; iy < mSizeY; iy++)
		{
			const unsigned int name = mPlayerMapData[(int)ix][(int)iy];
			Vector3 objectPos = Vector3(mOffset * ix, -mOffset * iy, 100.0f);
			Vector3 objectSize = Vector3(0.5f, 0.5f, 0.5f);

			switch (mScene)
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
