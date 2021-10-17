#include "pch.h"

/*
@fn コンストラクタ
@param	再利用するかフラグ
@param	オブジェクト判別用tag
*/
SkyBoxObject::SkyBoxObject(const Tag _objectTag, bool _reUseGameObject)
	: GameObject(_objectTag, _reUseGameObject)
{
	// キューブマップコンポーネントを生成
	cubeMapComp = new CubeMapComponent(this);
	// レンダラーにActiveなキューブマップとしてポインタを渡す
	RENDERER->SetActiveSkyBox(cubeMapComp);
	// texture生成
	cubeMapComp->CreateTexture("Assets/Texture/SkyBox/");
}

/*
@fn デストラクタ
@brief  objectの削除を行う
*/
SkyBoxObject::~SkyBoxObject()
{
}

/*
@fn アップデート関数
@brief	更新処理を行う
@param	_deltaTime 前のフレームでかかった時間
*/
void SkyBoxObject::UpdateGameObject(float _deltaTime)
{
}