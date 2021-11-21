#pragma once

// 前方宣言
class PlayerObject;
class BossObject;
class EnemyObjectManager;
class CreateEnemys;
class EnemysControler;
class DeadObjectActiveBox;

/// <summary>
/// マップデータのオブジェクトの番号
/// </summary>
enum MapDataNum
{
	ePlayerNum = 1,
	eGroundNum,
	eLateralWallNum,
	eVerticalWallNum,
	eAisleVerticalWallNum,
	eGateNum,
	eTutorialGateNum,
	eRightEnemyGeneratorNum,
	eLeftEnemyGeneratorNum,
	eFrontEnemyGeneratorNum,
	eBossNum,
	eTutorialEnemyNum,
	eEnemyActiveBoxNum,
	eBossActiveBoxNum,
	eEnemyBootSemitransparentWallNum,
	eBossBootSemitransparentWallNum
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

private:

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

	bool readTiledJson(std::vector<std::vector<int>>& _mapData, const char* _fileName, const char* _layerName);
	int  findLayerIndex(rapidjson::GenericArray<false,rapidjson::Value>& _layer,std::string& _layerName);
	
	// 門を開くために倒すエネミーの数
	const int OpenToDefeatEnemyNum;
	// 門を開くために倒すチュートリアルエネミーの数
	const int OpenToDefeatTutorialEnemyNum;

	// マップ右側のエネミー生成器を回転するための角度
	const float MRightEnemyGeneratorAngle;
	// マップ左側のエネミー生成器を回転するための角度
	const float MLeftEnemyGeneratorAngle;

	// 静的オブジェクトの大きさ
	const Vector3 MStaticObjectSize;
	// プレイヤーの大きさ
	const Vector3 MPersonSize;
	// 床を丁度よい位置にずらすためのベクトル
	const Vector3 MGroundShiftVec;
	// 壁を丁度よい位置にずらすためのベクトル
	const Vector3 MWallShiftVec;
	// 門を丁度よい位置にずらすためのベクトル
	const Vector3 MGateShiftVec;
	// 通路の縦壁を丁度よい位置にずらすためのベクトル
	const Vector3 MAisleVerticalWallShiftVec;
	// マップ右側のエネミー生成器を丁度よい位置にずらすためのベクトル
	const Vector3 MRightEnemyGeneratorShiftVec;
	// マップ左側のエネミー生成器を丁度よい位置にずらすためのベクトル
	const Vector3 MLeftEnemyGeneratorShiftVec;
	// マップ正面側のエネミー生成器を丁度よい位置にずらすためのベクトル
	const Vector3 MFrontEnemyGeneratorShiftVec;
	// エネミーたちを更新させるための当たり判定用矩形オブジェクトの座標を丁度よい位置にずらすためのベクトル
	const Vector3 MEnemysActiveBoxShiftVec;

	//jsonから読み込んだ上層オブジェクトのマップデータを格納するための可変長配列
	std::vector<std::vector<int>> mUpperObjectMapData;
	//jsonから読み込んだ下層オブジェクトのマップデータを格納するための可変長配列
	std::vector<std::vector<int>> mUnderObjectMapData;
	//jsonから読み込んだ最下層オブジェクトのマップデータを格納するための可変長配列
	std::vector<std::vector<int>> mBottomObjectMapData;
	//jsonから読み込んだプレイヤーのマップデータを格納するための可変長配列
	std::vector<std::vector<int>> mPlayerMapData;
	//jsonから読み込んだエネミーたちのマップデータを格納するための可変長配列
	std::vector<std::vector<int>> mEnemysMapData;

	// マップデータの横のタイル数
	int   mSizeX;
	// マップデータの縦のタイル数
	int   mSizeY;
	// オブジェクトごとの距離
	float mOffset;

	// プレイヤーのポインタ
	PlayerObject* mPlayerPtr;
	// ボスのポインタ
	BossObject* mBossPtr;
	// エネミーを管理するクラスのポインタ
	EnemyObjectManager* mEnemyObjectManagerPtr;
	// エネミーを更新させるための当たり判定用矩形オブジェクトのポインタ
	DeadObjectActiveBox* mEnemyActiveBoxPtr;
	// ボスを更新させるための当たり判定用矩形オブジェクトのポインタ
	DeadObjectActiveBox* mBossActiveBoxPtr;
	// エネミーが起動することによって出現する半透明の壁のポインタ
	GameObject* mEnemyBootSemitransparentWallPtr;
	// ボスが起動することによって出現する半透明の壁のポインタ
	GameObject* mBossBootSemitransparentWallPtr;

	// エネミーたちを生成するクラスのポインタ
	CreateEnemys* mCreateEnemysPtr;
	// エネミーたちを制御するクラスのポインタ
	EnemysControler* mEnemysControlerPtr;

public:// ゲッターセッター

	/// <summary>
	/// プレイヤーのポインタを取得
	/// </summary>
	/// <returns> プレイヤーのポインタ </returns>
	PlayerObject* GetPlayerPtr() { return mPlayerPtr; }

	/// <summary>
	/// ボスのポインタを取得
	/// </summary>
	/// <returns> ボスのポインタ </returns>
	BossObject* GetBossPtr() { return mBossPtr; }

	/// <summary>
	/// エネミーを管理するクラスのポインタを取得
	/// </summary>
	/// <returns> エネミーを管理するクラスのポインタ </returns>
	EnemyObjectManager* GetEnemyObjectManagerPtr() { return mEnemyObjectManagerPtr; }

	/// <summary>
	/// エネミーたちを制御するクラスのポインタを取得
	/// </summary>
	/// <returns> エネミーたちを制御するクラスのポインタ </returns>
	EnemysControler* GetEnemysControlerPtr() { return mEnemysControlerPtr; }

	/// <summary>
	/// エネミーを更新させるための当たり判定用矩形オブジェクトのポインタを取得
	/// </summary>
	/// <returns> エネミーを更新させるための当たり判定用矩形オブジェクトのポインタ </returns>
	DeadObjectActiveBox* GetEnemyActiveBoxPtr() { return mEnemyActiveBoxPtr; }

	/// <summary>
	/// ボスを更新させるための当たり判定用矩形オブジェクトのポインタを取得
	/// </summary>
	/// <returns> ボスを更新させるための当たり判定用矩形オブジェクトのポインタ </returns>
	DeadObjectActiveBox* GetBossActiveBoxPtr() { return mBossActiveBoxPtr; }
};