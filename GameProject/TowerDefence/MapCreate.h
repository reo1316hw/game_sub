#pragma once

// 前方宣言
class PlayerObject;
class EnemyObjectManager;
class CreateEnemys;

/// <summary>
/// マップデータのオブジェクトの番号
/// </summary>
enum MapDataNum
{
	ePlayerNum = 1,
	eGroundNum,
	eEnemyGeneratorNum,
	eTranslucentWallNum
};

/// <summary>
/// マップを生成
/// </summary>
class MapCreate : public GameObject
{
public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	MapCreate();

	/// <summary>
    /// デストラクタ
    /// </summary>
	~MapCreate();

	/// <summary>
	/// jsonファイルをRapidJsonで読み込んで、マップデータを可変長配列に格納する
	/// </summary>
	void OpenFile();

	/// <summary>
	/// マップデータにアクセスする
	/// </summary>
	/// <param name="_mapData"> マップデータ </param>
	void AccessMapData(std::vector<std::vector<int>> _mapData);

	/// <summary>
	/// オブジェクトを生成する
	/// </summary>
	/// <param name="_Name"> マップデータの要素 </param>
	/// <param name="_ObjectPos"> オブジェクトの座標 </param>
	void CreateGameObject(const unsigned int _Name, const Vector3 _ObjectPos);

private:

	bool readTiledJson(std::vector<std::vector<int>>& _mapData, const char* _fileName, const char* _layerName);
	int  findLayerIndex(rapidjson::GenericArray<false,rapidjson::Value>& _layer,std::string& _layerName);
	
	// ボスを生成する座標
	const Vector3 MCreateBossPosition;
	// プレイヤーのhpゲージを生成する座標
	const Vector3 MCreateHitPointGaugePosition;
	// 静的オブジェクトの大きさ
	const Vector3 MStaticObjectSize;
	// プレイヤーの大きさ
	const Vector3 MPersonSize;
	// 丁度よい位置にずらすためのベクトル
	const Vector3 MShiftVec;

	//jsonから読み込んだプレイヤーのマップデータを格納するための可変長配列
	std::vector<std::vector<int>> mPlayerMapData;
	//jsonから読み込んだ静的オブジェクトのマップデータを格納するための可変長配列
	std::vector<std::vector<int>> mStaticObjectMapData;

	// マップデータの横のタイル数
	int   mSizeX;
	// マップデータの縦のタイル数
	int   mSizeY;
	// オブジェクトごとの距離
	float mOffset;

	// プレイヤーのポインタ
	PlayerObject* mPlayerPtr;
	// エネミーマネージャーのポインタ
	EnemyObjectManager* mEnemyObjectManagerPtr;
	// エネミーたちを生成するクラスのポインタ
	CreateEnemys* mCreateEnemysPtr;
};