#include <string>

#include "player.h"
#include "SkeletalMeshComponent.h"
#include "Skeleton.h"
#include "MeshComponent.h"
#include "Mesh.h"
#include "Animation.h"
#include "Renderer.h"
#include "MainCameraObject.h"
#include "InputSystem.h"

Player::Player(const Vector3& _pos, const Vector3& _size, const Tag& objectTag, const SceneBase::Scene _sceneTag)
	: GameObject(_sceneTag, objectTag)
{
	//GameObjectメンバ変数の初期化
	tag = objectTag;
	SetScale(_size);
	SetPosition(_pos);

	moveSpeed = PLAYER_SPEED;

	//更新の度に左に移動するコンポーネントを生成 TestObjectの生成時と同じくComponent基底クラスは自動で管理クラスに追加され自動で解放される
	/*new TestComponent(this);*/

	///生成 TestObjectの生成時と同じくComponent基底クラスは自動で管理クラスに追加され自動で解放される
	skeltalMeshComponent = new SkeletalMeshComponent(this);
	//Rendererクラス内のMesh読み込み関数を利用してMeshをセット(.gpmesh)
	skeltalMeshComponent->SetMesh(RENDERER->GetMesh("Assets/Model/Player/erika_archer_bow_arrow.gpmesh"));
	//Rendererクラス内のSkeletonデータ読み込み関数を利用してSkeletonをセット(.gpskel)
	skeltalMeshComponent->SetSkeleton(RENDERER->GetSkeleton("Assets/Model/Player/erika_archer_bow_arrow.gpskel"));
	//Rendererクラス内のSkeletonデータ読み込み関数を利用してAnimationをセット(.gpanim)
	const Animation* anim = RENDERER->GetAnimation("Assets/Model/Player/run.gpanim");
	//anim変数を速度0.5fで再生
	skeltalMeshComponent->PlayAnimation(anim, 1.0f);

	//Z軸を270度回転させる
	float radian = Math::ToRadians(90);
	Quaternion rot = this->GetRotation();
	Quaternion inc(Vector3::UnitZ, radian);
	Quaternion target = Quaternion::Concatenate(rot, inc);
	SetRotation(target);

	//X軸を-90度回転させる
	radian = Math::ToRadians(-90);
	rot = this->GetRotation();
	inc = Quaternion(Vector3::UnitX, radian);
	target = Quaternion::Concatenate(rot, inc);
	SetRotation(target);
}

Player::~Player()
{

}

void Player::UpdateGameObject(float _deltaTime)
{
	mainCamera->SetViewMatrixLerpObject(Vector3(0, 500, -500), position);

	// 常に座標に速度を足す
	position += velocity;

	// 座標をセット
	SetPosition(position);
}

//void Player::PausingUpdateGameObject()
//{
//
//}

void Player::GameObjectInput(const InputState& _keyState)
{
	// コントローラーの十字上もしくはキーボード、Wが入力されたらzを足す
	if (_keyState.Controller.GetButtonValue(SDL_CONTROLLER_BUTTON_DPAD_UP) == 1 || 
		_keyState.Keyboard.GetKeyValue(SDL_SCANCODE_W) == 1)
	{
		velocity.z = moveSpeed;
	}
	// コントローラーの十字下もしくは、キーボードSが入力されたら-zを足す
	else if (_keyState.Controller.GetButtonValue(SDL_CONTROLLER_BUTTON_DPAD_DOWN) == 1 ||
			 _keyState.Keyboard.GetKeyValue(SDL_SCANCODE_S) == 1)
	{
		velocity.z = -moveSpeed;
	}
	// コントローラーの十字上かコントローラーの十字下かキーボードWかキーボードSが入力されなかったら速度を0にする
	else if (_keyState.Controller.GetButtonValue(SDL_CONTROLLER_BUTTON_DPAD_UP) == 0  ||
			 _keyState.Controller.GetButtonValue(SDL_CONTROLLER_BUTTON_DPAD_DOWN) == 0  ||
			 _keyState.Keyboard.GetKeyValue(SDL_SCANCODE_W) == 0 ||
			 _keyState.Keyboard.GetKeyValue(SDL_SCANCODE_S) == 0)
	{
		velocity.z *= 0;
	}

	 //コントローラーの十字左もしくは、キーボードAが入力されたら-xを足す
	if (_keyState.Controller.GetButtonValue(SDL_CONTROLLER_BUTTON_DPAD_LEFT) == 1 ||
		_keyState.Keyboard.GetKeyValue(SDL_SCANCODE_A) == 1)
	{
		velocity.x = -moveSpeed;
	}
	// コントローラーの十字右もしくは、キーボードDが入力されたらxを足す
	else if (_keyState.Controller.GetButtonValue(SDL_CONTROLLER_BUTTON_DPAD_RIGHT) == 1 ||
		_keyState.Keyboard.GetKeyValue(SDL_SCANCODE_D) == 1)
	{
		velocity.x = moveSpeed;
	}

	// コントローラーの十字左かコントローラーの十字右かキーボードAかキーボードDが入力されなかったら速度を0にする
	else if (_keyState.Controller.GetButtonValue(SDL_CONTROLLER_BUTTON_DPAD_LEFT) == 0 ||
		_keyState.Controller.GetButtonValue(SDL_CONTROLLER_BUTTON_DPAD_RIGHT) == 0 ||
		_keyState.Keyboard.GetKeyValue(SDL_SCANCODE_A) == 0 ||
		_keyState.Keyboard.GetKeyValue(SDL_SCANCODE_D) == 0)
	{
		velocity.x *= 0;
	}
}
void Player::OnCollision(const GameObject& _hitObject)
{
	
}
