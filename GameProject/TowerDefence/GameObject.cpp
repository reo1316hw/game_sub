#include "pch.h"

int GameObject::mGameObjectId = 0;
PauzingEvent GameObject::mPauzingEvent = PauzingEvent::NoneEvent;

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="_ObjectTag"> �I�u�W�F�N�g�̃^�O </param>
/// <param name="_reUseGameObject"> �ė��p���邩 </param>
GameObject::GameObject(const Tag& _objectTag, bool _reUseGameObject)
	: mState(eActive)
	, mWorldTransform()
	, mPosition(Vector3::Zero)
	, mVelocity(Vector3::Zero)
	, mBox(Vector3::Zero, Vector3::Zero)
	, mScale(Vector3(1.0f, 1.0f, 1.0f))
	, mRotation(Quaternion::Identity)
	, mHitPoint(0)
	, mMyObjectId(mGameObjectId)
	, mMaxHp(0)
	, mTag(_objectTag)
	, mMoveSpeed(0.0f)
	, mReUseObject(_reUseGameObject)
	, mRecomputeWorldTransform(true)
{
	mGameObjectId++;
	//GameObjectManager�Ƀ|�C���^��n��
	GAME_OBJECT_MANAGER->AddGameObject(this);
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
GameObject::~GameObject()
{
	//GameObjectManager����|�C���^���폜����
	GAME_OBJECT_MANAGER->RemoveGameObject(this);
	while (!mComponents.empty())
	{
		delete mComponents.back();
	}
}

/// <summary>
/// �t���[�����̏���
/// </summary>
/// <param name="_deltaTime"> �Ō�̃t���[������������̂ɗv�������� </param>
void GameObject::Update(float _deltaTime)
{
	//�X�V��~�̃C�x���g���łȂ���(�|�[�Y��ʂȂ�)
	if (mPauzingEvent == PauzingEvent::NoneEvent)
	{
		if (mState == eActive)
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
	else if(mPauzingEvent == PauzingEvent::PausingEvent)
	{
		PausingUpdateGameObject();
	}
	else
	{
		PausingUpdateGameObject();
		UpdateComponents(_deltaTime);
	}
}

/// <summary>
/// �A�^�b�`����Ă�R���|�[�l���g�̃A�b�v�f�[�g
/// </summary>
/// <param name="_deltaTime"> �Ō�̃t���[������������̂ɗv�������� </param>
void GameObject::UpdateComponents(float _deltaTime)
{
	if (mState != eDead)
	{	
		for (auto itr : mComponents)
		{
			itr->Update(_deltaTime);
		}
	}
}

/// <summary>
/// ���͏�Ԃ��󂯎��GameObject��Component�̓��͍X�V�֐����Ăяo��
/// </summary>
/// <param name="_KeyState"> �L�[�{�[�h�A�}�E�X�A�R���g���[���[�̓��͏�� </param>
void GameObject::ProcessInput(const InputState& _keyState)
{
	if (mState == eActive)
	{
		//�R���|�[�l���g�̓��͊֐��ɃR���g���[���[�̓��͏�Ԃ�
		for (auto comp : mComponents)
		{
			comp->ProcessInput(_keyState);
		}
		//�Q�[���I�u�W�F�N�g�̓��͊֐��ɃR���g���[���[�̓��͏�Ԃ�
		GameObjectInput(_keyState);
	}
}

/// <summary>
/// �R���|�[�l���g��ǉ�����
/// </summary>
/// <param name="_component"> �ǉ�����R���|�[�l���g�̃|�C���^ </param>
void GameObject::AddComponent(Component * _component)
{
	int order = _component->GetUpdateOder();
	auto itr = mComponents.begin();
	for (;
		itr != mComponents.end();
		++itr)
	{
		if (order < (*itr)->GetUpdateOder())
		{
			break;
		}
	}
	mComponents.insert(itr, _component);
}

/// <summary>
/// �R���|�[�l���g���폜����
/// </summary>
/// <param name="_component"> �폜����R���|�[�l���g�̃|�C���^ </param>
void GameObject::RemoveComponent(Component * _component)
{
	auto itr = std::find(mComponents.begin(), mComponents.end(), _component);
	if (itr != mComponents.end())
	{
		mComponents.erase(itr);
	}
}

/// <summary>
/// Transform�̃��[���h�ϊ�
/// </summary>
void GameObject::ComputeWorldTransform()
{
	//���[���h�ϊ����K�v���ǂ����H
	//�����K�v�������烏�[���h�ϊ����s��
	if (mRecomputeWorldTransform)
	{
		//object��
		//�ϊ����K�v�t���O���~�낷
		mRecomputeWorldTransform = false;
		//�X�P�[���̃��[���h�ϊ�
		mWorldTransform = Matrix4::CreateScale(mScale);
		//��]�̃��[���h�ϊ��i�N�E�H�[�^�j�I���j
		mWorldTransform *= Matrix4::CreateFromQuaternion(mRotation);
		//���s�ړ��̍X�V
		mWorldTransform *= Matrix4::CreateTranslation(mPosition);

		//object�iowner�j�������Ă���component�ɂ����W�ϊ��n
		for (auto itr : mComponents)
		{
			itr->OnUpdateWorldTransform();
		}
	}
}

/// <summary>
/// �����߂�
/// </summary>
/// <param name="_MyAABB"> ���g��AABB </param>
/// <param name="_PairAABB"> �������������AABB </param>
/// <param name="_PairTag"> ������������̃^�O </param>
void GameObject::FixCollision(const AABB & _myAABB, const AABB & _pairAABB, const Tag& _pairTag)
{
	Vector3 ment = Vector3(0, 0, 0);
	CalcCollisionFixVec(_myAABB, _pairAABB, ment);
	SetPosition(GetPosition() + (ment));
}

/// <summary>
/// �O���x�N�g���̌����ɉ�]����
/// </summary>
/// <param name="_Forward"> �����������O���x�N�g�� </param>
void GameObject::RotateToNewForward(const Vector3& _forward)
{
	// X���x�N�g��(1,0,0)��forward�̊Ԃ̊p�x�����߂�
	float dot = Vector3::Dot(Vector3::UnitX, _forward);
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
		Vector3 axis = Vector3::Cross(Vector3::UnitX, _forward);
		axis.Normalize();
		SetRotation(Quaternion(axis, angle));
	}
}