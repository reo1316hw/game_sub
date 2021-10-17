#pragma once

// 前方宣言
class CubeMapComponent;

/*
@file SkyBoxObject.h
@brief SkyBoxObject管理クラス
*/
class SkyBoxObject : public GameObject
{
public:

	/*
	@fn コンストラクタ
	@param	再利用するかフラグ
	@param	オブジェクト判別用tag
	*/
	SkyBoxObject(const Tag _objectTag, bool _reUseGameObject);

	/*
	@fn デストラクタ
	@brief  objectの削除を行う
	*/
	~SkyBoxObject();

	/*
	@fn アップデート関数
	@brief	更新処理を行う
	@param	_deltaTime 前のフレームでかかった時間
	*/
	void UpdateGameObject(float _deltaTime)override;

	/*
	@fn キューブマップComponentのgetter
	@return	cubeMapComp 使用しているキューブマップComponentを返す
	*/
	CubeMapComponent* GetCubeMapComp() { return cubeMapComp; }

private:

	// キューブマップComponentクラスのポインタ
	CubeMapComponent* cubeMapComp;
};

