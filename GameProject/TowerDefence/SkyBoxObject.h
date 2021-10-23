#pragma once

// 前方宣言
class CubeMapComponent;

/// <summary>
/// スカイボックス
/// </summary>
class SkyBoxObject : public GameObject
{
public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="_ObjectTag"> オブジェクトのタグ </param>
	/// <param name="_ReUseGameObject"> 再利用するかのフラグ </param>
	SkyBoxObject(const Tag& _ObjectTag, const bool& _ReUseGameObject);

	/// <summary>
	/// デストラクタ
	/// </summary>
	~SkyBoxObject() {};

private:

	// キューブマップComponentクラスのポインタ
	CubeMapComponent* cubeMapComp;

public:// ゲッターセッター

	/// <summary>
	/// キューブマップコンポーネントクラスのポインタを取得
	/// </summary>
	/// <returns> キューブマップコンポーネントクラスのポインタ </returns>
	CubeMapComponent* GetCubeMapComp() { return cubeMapComp; }
};

