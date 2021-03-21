#include "Game.h"
#include "Math.h"
#include "GameObject.h"
#include "Component.h"
#include "InputSystem.h"
#include "GameObjectManager.h"
#include "PhysicsWorld.h"
#include "MainCameraObject.h"

int GameObject::gameObjectId = 0;
MainCameraObject* GameObject::mainCamera = nullptr;
PauzingEvent GameObject::pauzingEvent = PauzingEvent::NoneEvent;

/*
@param	�Q�[���N���X�̃|�C���^
*/
GameObject::GameObject(const Tag& _objectTag, SceneBase::Scene _sceneTag, bool _reUseGameObject)
	: state(Active)
	, worldTransform()
	, position(Vector3::Zero)
	, velocity(Vector3::Zero)
	, scale(Vector3(1.0f, 1.0f, 1.0f))
	, rotation(Quaternion::Identity)
	, recomputeWorldTransform(true)
	, myObjectId(gameObjectId)
	, reUseObject(_reUseGameObject)
	, aabb(Vector3::Zero, Vector3::Zero)
	, moveSpeed(0)
	, gravity(0)
	, tag(_objectTag)
	, sceneTag(_sceneTag)
	, hitFlag(false)
{
	gameObjectId++;
	//GameObjectManager�Ƀ|�C���^��n��
	GAME_OBJECT_MANAGER->AddGameObject(this);
}

GameObject::~GameObject()
{
	//GameObjectManager����|�C���^���폜����
	GAME_OBJECT_MANAGER->RemoveGameObject(this);
	while (!components.empty())
	{
		delete components.back();
	}
}

/*
@brief	�t���[�����̏���
@param	�Ō�̃t���[������������̂ɗv��������
*/
void GameObject::Update(float _deltaTime)
{
	//�X�V��~�̃C�x���g���łȂ���(�|�[�Y��ʂȂ�)
	if (pauzingEvent == PauzingEvent::NoneEvent)
	{
		if (state == Active)
		{
			//Transform�̃��[���h�ϊ�
			ComputeWorldTransform();
			//�Q�[���I�u�W�F�N�g�̍X�V
			UpdateGameObject(_deltaTime);
			//���̃Q�[���I�u�W�F�N�g�ɕt������R���|�[�l���g�̍X�V
			UpdateComponents(_deltaTime);
			//Transform�̃��[���h�ϊ�
			ComputeWorldTransform();
		}
	}
	//�|�[�Y��ʂ̂Ƃ��R���|�[�l���g���X�V�����Ȃ�(�A�j���[�V�����Ȃǂ��~�߂邽��)
	else if(pauzingEvent == PauzingEvent::PausingEvent)
	{
		PausingUpdateGameObject();
	}
	else
	{
		PausingUpdateGameObject();
		UpdateComponents(_deltaTime);
	}
}

/*
@brief	�A�^�b�`����Ă�R���|�[�l���g�̃A�b�v�f�[�g
@param	�Ō�̃t���[������������̂ɗv��������
*/
void GameObject::UpdateComponents(float _deltaTime)
{
	if (state != Dead)
	{	
		for (auto itr : components)
		{
			itr->Update(_deltaTime);
		}
	}
}
/*
@brief	�Q�[���I�u�W�F�N�g�̃A�b�v�f�[�g
@param	�Ō�̃t���[������������̂ɗv��������
*/
void GameObject::UpdateGameObject(float _deltaTime)
{
}
/*
@fn �Q�[���I�u�W�F�N�g���Î~���ɍX�V�����A�b�v�f�[�g�֐�
@brief pauzingUpdate��true�̂Ƃ������Ă΂��X�V�֐�
*/
void GameObject::PausingUpdateGameObject()
{
}

/*
@fn ���͏�Ԃ��󂯎��GameObject��Component�̓��͍X�V�֐����Ăяo��
*/
void GameObject::ProcessInput(const InputState& _keyState)
{
	if (state == Active)
	{
		//�R���|�[�l���g�̓��͊֐��ɃR���g���[���[�̓��͏�Ԃ�
		for (auto comp : components)
		{
			comp->ProcessInput(_keyState);
		}
		//�Q�[���I�u�W�F�N�g�̓��͊֐��ɃR���g���[���[�̓��͏�Ԃ�
		GameObjectInput(_keyState);
	}
}

/*
@fn ���͂������Ŏ󂯎��X�V�֐�
@brief ��{�I�ɂ����œ��͏���ϐ��ɕۑ���UpdateGameObject�ōX�V���s��
*/
void GameObject::GameObjectInput(const InputState & _keyState)
{
}

/*
@brief	�R���|�[�l���g��ǉ�����
@param	�ǉ�����R���|�[�l���g�̃|�C���^
*/
void GameObject::AddComponent(Component * _component)
{
	int order = _component->GetUpdateOder();
	auto itr = components.begin();
	for (;
		itr != components.end();
		++itr)
	{
		if (order < (*itr)->GetUpdateOder())
		{
			break;
		}
	}
	components.insert(itr, _component);
}

/*
@brief	�R���|�[�l���g���폜����
@param	�폜����R���|�[�l���g�̃|�C���^
*/
void GameObject::RemoveComponent(Component * _component)
{
	auto itr = std::find(components.begin(), components.end(), _component);
	if (itr != components.end())
	{
		components.erase(itr);
	}
}
/*
@fn ���݂̎d�l��s�����Ƃ��ł��Ȃ��������O�����狭���ɍs�����߂̊֐�
@exsample �Q�[���I�u�W�F�N�g�S�̂̍X�V����~���ɑΏۂ̃Q�[���I�u�W�F�N�g���X�V����
*/
void GameObject::ExceptionUpdate()
{
	ComputeWorldTransform();

	UpdateGameObject(0.016f);
	UpdateComponents(0.016f);

	ComputeWorldTransform();
}


/*
@brief	Transform�̃��[���h�ϊ�
*/
void GameObject::ComputeWorldTransform()
{
	//���[���h�ϊ����K�v���ǂ����H
	//�����K�v�������烏�[���h�ϊ����s��
	if (recomputeWorldTransform)
	{
		//object��
		//�ϊ����K�v�t���O���~�낷
		recomputeWorldTransform = false;
		//�X�P�[���̃��[���h�ϊ�
		worldTransform = Matrix4::CreateScale(scale);
		//��]�̃��[���h�ϊ��i�N�E�H�[�^�j�I���j
		worldTransform *= Matrix4::CreateFromQuaternion(rotation);
		//���s�ړ��̍X�V
		worldTransform *= Matrix4::CreateTranslation(position);

		//object�iowner�j�������Ă���component�ɂ����W�ϊ��n
		for (auto itr : components)
		{
			itr->OnUpdateWorldTransform();
		}
	}
}

void GameObject::FixCollision(const AABB & myAABB, const AABB & pairAABB, const Tag& _pairTag)
{
	Vector3 ment = Vector3(0, 0, 0);
	calcCollisionFixVec(myAABB, pairAABB, ment);
	SetPosition(GetPosition() + (ment));
}

void GameObject::CreateMainCamera()
{
	mainCamera = new MainCameraObject();
}

// forward�x�N�g���̌����ɉ�]����
// in forward : �����������O�������x�N�g��
void GameObject::RotateToNewForward(const Vector3& forward)
{
	// X���x�N�g��(1,0,0)��forward�̊Ԃ̊p�x�����߂�
	float dot = Vector3::Dot(Vector3::UnitX, forward);
	float angle = Math::Acos(dot);
	//printf("%f\n", angle);
	// �������������ꍇ
	if (dot > 0.9999f)
	{
		SetRotation(Quaternion::Identity);
	}
	// ������������ꍇ
	else if (dot < -0.9999f)
	{
		SetRotation(Quaternion(Vector3::UnitZ, Math::Pi));
	}
	else
	{
		// ���x�N�g����forward�Ƃ̊O�ς����]�������Ƃ߁A��]������
		Vector3 axis = Vector3::Cross(Vector3::UnitX, forward);
		axis.Normalize();
		SetRotation(Quaternion(axis, angle));
	}
}
