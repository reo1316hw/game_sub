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
	//GameObject�����o�ϐ��̏�����
	tag = objectTag;
	SetScale(_size);
	SetPosition(_pos);

	moveSpeed = PLAYER_SPEED;

	//�X�V�̓x�ɍ��Ɉړ�����R���|�[�l���g�𐶐� TestObject�̐������Ɠ�����Component���N���X�͎����ŊǗ��N���X�ɒǉ����ꎩ���ŉ�������
	/*new TestComponent(this);*/

	///���� TestObject�̐������Ɠ�����Component���N���X�͎����ŊǗ��N���X�ɒǉ����ꎩ���ŉ�������
	skeltalMeshComponent = new SkeletalMeshComponent(this);
	//Renderer�N���X����Mesh�ǂݍ��݊֐��𗘗p����Mesh���Z�b�g(.gpmesh)
	skeltalMeshComponent->SetMesh(RENDERER->GetMesh("Assets/Model/Player/erika_archer_bow_arrow.gpmesh"));
	//Renderer�N���X����Skeleton�f�[�^�ǂݍ��݊֐��𗘗p����Skeleton���Z�b�g(.gpskel)
	skeltalMeshComponent->SetSkeleton(RENDERER->GetSkeleton("Assets/Model/Player/erika_archer_bow_arrow.gpskel"));
	//Renderer�N���X����Skeleton�f�[�^�ǂݍ��݊֐��𗘗p����Animation���Z�b�g(.gpanim)
	const Animation* anim = RENDERER->GetAnimation("Assets/Model/Player/run.gpanim");
	//anim�ϐ��𑬓x0.5f�ōĐ�
	skeltalMeshComponent->PlayAnimation(anim, 1.0f);

	//Z����270�x��]������
	float radian = Math::ToRadians(90);
	Quaternion rot = this->GetRotation();
	Quaternion inc(Vector3::UnitZ, radian);
	Quaternion target = Quaternion::Concatenate(rot, inc);
	SetRotation(target);

	//X����-90�x��]������
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

	// ��ɍ��W�ɑ��x�𑫂�
	position += velocity;

	// ���W���Z�b�g
	SetPosition(position);
}

//void Player::PausingUpdateGameObject()
//{
//
//}

void Player::GameObjectInput(const InputState& _keyState)
{
	// �R���g���[���[�̏\����������̓L�[�{�[�h�AW�����͂��ꂽ��z�𑫂�
	if (_keyState.Controller.GetButtonValue(SDL_CONTROLLER_BUTTON_DPAD_UP) == 1 || 
		_keyState.Keyboard.GetKeyValue(SDL_SCANCODE_W) == 1)
	{
		velocity.z = moveSpeed;
	}
	// �R���g���[���[�̏\�����������́A�L�[�{�[�hS�����͂��ꂽ��-z�𑫂�
	else if (_keyState.Controller.GetButtonValue(SDL_CONTROLLER_BUTTON_DPAD_DOWN) == 1 ||
			 _keyState.Keyboard.GetKeyValue(SDL_SCANCODE_S) == 1)
	{
		velocity.z = -moveSpeed;
	}
	// �R���g���[���[�̏\���ォ�R���g���[���[�̏\�������L�[�{�[�hW���L�[�{�[�hS�����͂���Ȃ������瑬�x��0�ɂ���
	else if (_keyState.Controller.GetButtonValue(SDL_CONTROLLER_BUTTON_DPAD_UP) == 0  ||
			 _keyState.Controller.GetButtonValue(SDL_CONTROLLER_BUTTON_DPAD_DOWN) == 0  ||
			 _keyState.Keyboard.GetKeyValue(SDL_SCANCODE_W) == 0 ||
			 _keyState.Keyboard.GetKeyValue(SDL_SCANCODE_S) == 0)
	{
		velocity.z *= 0;
	}

	 //�R���g���[���[�̏\�����������́A�L�[�{�[�hA�����͂��ꂽ��-x�𑫂�
	if (_keyState.Controller.GetButtonValue(SDL_CONTROLLER_BUTTON_DPAD_LEFT) == 1 ||
		_keyState.Keyboard.GetKeyValue(SDL_SCANCODE_A) == 1)
	{
		velocity.x = -moveSpeed;
	}
	// �R���g���[���[�̏\���E�������́A�L�[�{�[�hD�����͂��ꂽ��x�𑫂�
	else if (_keyState.Controller.GetButtonValue(SDL_CONTROLLER_BUTTON_DPAD_RIGHT) == 1 ||
		_keyState.Keyboard.GetKeyValue(SDL_SCANCODE_D) == 1)
	{
		velocity.x = moveSpeed;
	}

	// �R���g���[���[�̏\�������R���g���[���[�̏\���E���L�[�{�[�hA���L�[�{�[�hD�����͂���Ȃ������瑬�x��0�ɂ���
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
