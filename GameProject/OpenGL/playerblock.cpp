#include "playerblock.h"
#include "MeshComponent.h"
#include <string>
#include "Renderer.h"
#include "TestComponent.h"
#include "MainCameraObject.h"
#include "TestObject.h"
#include "InputSystem.h"


playerblock::playerblock(const Vector3& _pos, const Vector3& _size, const Tag& objectTag): GameObject()
{
	//GameObjectメンバ変数の初期化
	tag = objectTag;
	SetScale(_size);
	SetPosition(_pos);

	//更新の度に左に移動するコンポーネントを生成 TestObjectの生成時と同じくComponent基底クラスは自動で管理クラスに追加され自動で解放される
	/*new TestComponent(this);*/

	//生成 TestObjectの生成時と同じくComponent基底クラスは自動で管理クラスに追加され自動で解放される
	meshComponent = new MeshComponent(this);
	//Rendererクラス内のMesh読み込み関数を利用してMeshをセット(.gpmesh)
	meshComponent->SetMesh(RENDERER->GetMesh("Assets/SM_VendorCrate_01_E.gpmesh"));

}

playerblock::~playerblock()
{
}

void playerblock::UpdateGameObject(float _deltaTime)
{
	//Vector3(-200, 140, -800)離した距離からpositionを緩やかに追跡する。
	mainCamera->SetViewMatrixLerpObject(Vector3(-200, 2000, -6000), position);
}

void playerblock::GameObjectInput(const InputState& _keyState)
{
	//キーボードAが入力されたら-xを足す
	if (_keyState.Keyboard.GetKeyValue(SDL_SCANCODE_A) == 1)
	{
		SetPosition(position + Vector3(-100, 0, 0));
	}

	//キーボードDが入力されたらxを足す
	if (_keyState.Keyboard.GetKeyValue(SDL_SCANCODE_D) == 1)
	{
		SetPosition(position + Vector3(100, 0, 0));
	}

	//キーボードWが入力されたらzを足す
	if (_keyState.Keyboard.GetKeyValue(SDL_SCANCODE_W) == 1)
	{
		SetPosition(position + Vector3(0, 0, 100));
	}

	//キーボードSが入力されたら-zを足す
	if (_keyState.Keyboard.GetKeyValue(SDL_SCANCODE_S) == 1)
	{
		SetPosition(position + Vector3(0, 0, -100));
	}
}
