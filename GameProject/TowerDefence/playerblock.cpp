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
	//GameObject�����o�ϐ��̏�����
	tag = objectTag;
	SetScale(_size);
	SetPosition(_pos);

	//�X�V�̓x�ɍ��Ɉړ�����R���|�[�l���g�𐶐� TestObject�̐������Ɠ�����Component���N���X�͎����ŊǗ��N���X�ɒǉ����ꎩ���ŉ�������
	/*new TestComponent(this);*/

	//���� TestObject�̐������Ɠ�����Component���N���X�͎����ŊǗ��N���X�ɒǉ����ꎩ���ŉ�������
	meshComponent = new MeshComponent(this);
	//Renderer�N���X����Mesh�ǂݍ��݊֐��𗘗p����Mesh���Z�b�g(.gpmesh)
	meshComponent->SetMesh(RENDERER->GetMesh("Assets/SM_VendorCrate_01_E.gpmesh"));

}

playerblock::~playerblock()
{
}

void playerblock::UpdateGameObject(float _deltaTime)
{
	//Vector3(-200, 140, -800)��������������position���ɂ₩�ɒǐՂ���B
	mainCamera->SetViewMatrixLerpObject(Vector3(-200, 2000, -6000), position);
}

void playerblock::GameObjectInput(const InputState& _keyState)
{
	//�L�[�{�[�hA�����͂��ꂽ��-x�𑫂�
	if (_keyState.Keyboard.GetKeyValue(SDL_SCANCODE_A) == 1)
	{
		SetPosition(position + Vector3(-100, 0, 0));
	}

	//�L�[�{�[�hD�����͂��ꂽ��x�𑫂�
	if (_keyState.Keyboard.GetKeyValue(SDL_SCANCODE_D) == 1)
	{
		SetPosition(position + Vector3(100, 0, 0));
	}

	//�L�[�{�[�hW�����͂��ꂽ��z�𑫂�
	if (_keyState.Keyboard.GetKeyValue(SDL_SCANCODE_W) == 1)
	{
		SetPosition(position + Vector3(0, 0, 100));
	}

	//�L�[�{�[�hS�����͂��ꂽ��-z�𑫂�
	if (_keyState.Keyboard.GetKeyValue(SDL_SCANCODE_S) == 1)
	{
		SetPosition(position + Vector3(0, 0, -100));
	}
}
