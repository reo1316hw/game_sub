#include "pch.h"

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="_ObjectTag"> オブジェクトのタグ </param>
/// <param name="_ReUseGameObject"> 再利用するかのフラグ </param>
SkyBoxObject::SkyBoxObject(const Tag& _ObjectTag, const bool& _ReUseGameObject)
	: GameObject(_ObjectTag, _ReUseGameObject)
{
	// キューブマップコンポーネントを生成
	cubeMapComp = new CubeMapComponent(this);
	// texture生成
	cubeMapComp->CreateTexture("Assets/Texture/SkyBox/");
}