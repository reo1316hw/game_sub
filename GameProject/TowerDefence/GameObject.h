#pragma once
#include <vector>
#include <functional>
#include "Math.h"
#include "Collision.h"
#include "SceneBase.h"

// �O���錾
class Game;
class Vector3;
class Matrix4;
class Component;
class ColliderComponent;
class SkeletalMeshComponent;
class MeshComponent;
class Mesh;
class BoxCollider;
struct InputState;

/// <summary>
/// �Q�[���I�u�W�F�N�g�̏��
/// </summary>
enum State
{
	//�A�N�e�B�u
	eActive,
	//�X�V����~���Ă���
	ePaused,
	//�I�u�W�F�N�g�̍X�V���I��(�O������̂�Active�ɕύX�\)
	eDead
};

/// <summary>
/// GameObject�^�O
/// �Փˑ���𔻕ʂ��邽�߂Ɏg�p
/// </summary>
enum Tag
{
	eOther = 0,
	eCamera,
	ePlayer,
	eWeapon,
	eGround,
	eEnemyManager,
	eEnemyGenerator,
	eEnemy,
	eEnemyAttackDecision,
	eBoss,
	eTranslucentWall
};

/// <summary>
/// �Q�[���I�u�W�F�N�g�̍X�V���~����C�x���g��
/// </summary>
enum PauzingEvent
{
	//�{�X�̓��ꉉ�o
	SummonMageEvent,
	//�|�[�Y��ʒ�
	PausingEvent,
	//�v���C���[�����j����Ă��܂����ۂ̉��o
	DeadPlayerEvent,
	//�Q�[���I�[�o�[���̉��o DeadPlayerEvent�Ɗ֘A
	GameOverEvent,
	//�Q�[���I�u�W�F�N�g�̍X�V���s���Ă���B
	NoneEvent
};

/// <summary>
/// �I�u�W�F�N�g�̊��N���X
/// </summary>
class GameObject
{
public:

	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="_ObjectTag"> �I�u�W�F�N�g�̃^�O </param>
	/// <param name="_reUseGameObject"> �ė��p���邩 </param>
	GameObject(const Tag& _ObjectTag, bool _reUseGameObject = false);

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	virtual ~GameObject();

	/// <summary>
	/// �t���[�����̏���
	/// </summary>
	/// <param name="_deltaTime"> �Ō�̃t���[������������̂ɗv�������� </param>
	void Update(float _deltaTime);

	/// <summary>
	/// �A�^�b�`����Ă�R���|�[�l���g�̃A�b�v�f�[�g
	/// </summary>
	/// <param name="_deltaTime"> �Ō�̃t���[������������̂ɗv�������� </param>
	void UpdateComponents(float _deltaTime);

	/// <summary>
	/// �Q�[���I�u�W�F�N�g�̃A�b�v�f�[�g
	/// </summary>
	/// <param name="_deltaTime"> �Ō�̃t���[������������̂ɗv�������� </param>
	virtual void UpdateGameObject(float _deltaTime) {};

	/// <summary>
	/// �Q�[���I�u�W�F�N�g���Î~���ɍX�V�����A�b�v�f�[�g�֐�
	/// pauzingUpdate��true�̂Ƃ������Ă΂��X�V�֐�
	/// </summary>
	virtual void PausingUpdateGameObject() {};

	/// <summary>
	/// ���͏�Ԃ��󂯎��GameObject��Component�̓��͍X�V�֐����Ăяo��
	/// </summary>
	/// <param name="_KeyState"> �L�[�{�[�h�A�}�E�X�A�R���g���[���[�̓��͏�� </param>
	void ProcessInput(const InputState& _KeyState);

	/// <summary>
	/// ���͂������Ŏ󂯎��X�V�֐�
	/// ��{�I�ɂ����œ��͏���ϐ��ɕۑ���UpdateGameObject�ōX�V���s��
	/// </summary>
	/// <param name="_KeyState"> �L�[�{�[�h�A�}�E�X�A�R���g���[���[�̓��͏�� </param>
	virtual void GameObjectInput(const InputState& _KeyState) {};

	/// <summary>
	/// �R���|�[�l���g��ǉ�����
	/// </summary>
	/// <param name="_component"> �ǉ�����R���|�[�l���g�̃|�C���^ </param>
	void AddComponent(Component* _component);

	/// <summary>
	/// �R���|�[�l���g���폜����
	/// </summary>
	/// <param name="_component"> �폜����R���|�[�l���g�̃|�C���^ </param>
	void RemoveComponent(Component* _component);

	///// <summary>
	///// ���݂̎d�l��s�����Ƃ��ł��Ȃ��������O�����狭���ɍs�����߂̊֐�
	///// �Q�[���I�u�W�F�N�g�S�̂̍X�V����~���ɑΏۂ̃Q�[���I�u�W�F�N�g���X�V����
	///// </summary>
	//void ExceptionUpdate();

	/// <summary>
	/// Transform�̃��[���h�ϊ�
	/// </summary>
	void ComputeWorldTransform();

	/// <summary>
	/// �����߂�
	/// </summary>
	/// <param name="_MyAABB"> ���g��AABB </param>
	/// <param name="_PairAABB"> �������������AABB </param>
	/// <param name="_PairTag"> ������������̃^�O </param>
	virtual void FixCollision(const AABB& _MyAABB, const AABB& _PairAABB, const Tag& _PairTag);

	/// <summary>
	/// �O���x�N�g���̌����ɉ�]����
	/// </summary>
	/// <param name="_Forward"> �����������O���x�N�g�� </param>
	void RotateToNewForward(const Vector3& _Forward);

	/// <summary>
	/// �ÓI��mainCamera�𐶐�����
	/// </summary>
	static void CreateMainCamera();

	/// <summary>
	/// �I�u�W�F�N�g�̈�������
	/// </summary>
	/// <param name="_DirTargetEnemyVec"> �ΏۂƂȂ�I�u�W�F�N�g�Ɍ������x�N�g�� </param>
	virtual void Separation(const Vector3& _DirTargetEnemyVec) {};

protected:

	std::function<void(GameObject&)> GetOnCollisionFunc() { return std::bind(&GameObject::OnCollision, this, std::placeholders::_1); }
	virtual void OnCollision(const GameObject& _hitObject) {};

	// ���C���J�����@
	// ������GameObjectManager�������ɍs����
	static class MainCameraObject* mMainCamera;
	// �Q�[���I�u�W�F�N�g�̍X�V���~�߂�C�x���g���
	static PauzingEvent mPauzingEvent;
	// �Փˎ��̃��A�N�V�����֐�(ColliderComponent�ɂ��̊֐��̃A�h���X��n��) Enter...�Փ˂��� Stay...�Փ˂��Ă���
	virtual void OnTriggerEnter(ColliderComponent* _colliderPair) {};
	// �Փˎ��̃��A�N�V�����֐�(ColliderComponent�ɂ��̊֐��̃A�h���X��n��) Enter...�Փ˂��� Stay...�Փ˂��Ă���
	virtual void OnTriggerStay(ColliderComponent* _colliderPair) {};

	// �I�u�W�F�N�g��AABB
	AABB mBox;
	// �Q�[���I�u�W�F�N�g�̏��
	State mState;
	// �Q�[���I�u�W�F�N�g�̃^�O
	Tag mTag;
	// �Q�[���I�u�W�F�N�g��ID�A�J�E���g�p
	static int mGameObjectId;
	// ���̃Q�[���I�u�W�F�N�g��ID
	int mMyObjectId;
	// �̗�
	int mHitPoint;

	// �Q�[���I�u�W�F�N�g�̃��b�V��
	MeshComponent* mMeshComponentPtr;
	// ��`�̓����蔻����s���N���X�̃|�C���^
	BoxCollider* mBoxColliderPtr;
	// �����蔻���mesh�ɂ��邽�߂̃C���X�^���X
	Mesh* mMeshPtr;

	// Transform
	Vector3 mPosition;
	Vector3 mScale;
	Quaternion  mRotation;
	// ���x
	Vector3 mVelocity;
	// ���[���h�s��
	Matrix4		mWorldTransform;
	// �ړ����x
	float mMoveSpeed;
	// ���[���h�ϊ��̏������s���K�v�������邩
	bool mRecomputeWorldTransform;
	
	// �A�^�b�`����Ă���R���|�[�l���g
	std::vector<class Component*>mComponents;

private:

	// �V�[�����ׂ��ۂɉ�������I�u�W�F�N�g���ǂ����A�J�����Ȃǂ��ΏۂɂȂ�
	bool mReUseObject;

public:// �Q�b�^�[�Z�b�^�[

	/// <summary>
	/// �I�u�W�F�N�g�̍��W���擾����
	/// </summary>
	/// <returns> �I�u�W�F�N�g�̍��W </returns>
	const Vector3& GetPosition() const { return mPosition; }

	/// <summary>
	/// �I�u�W�F�N�g�̍��W��ݒ�
	/// </summary>
	/// <param name="_Pos"> �I�u�W�F�N�g�̍��W </param>
	virtual void SetPosition(const Vector3& _Pos) { mPosition = _Pos; mRecomputeWorldTransform = true; }

	/// <summary>
	/// ���[���h�s��ϊ����s�����̃t���O���擾
	/// </summary>
	/// <returns> ���[���h�s��ϊ����s���� </returns>
	bool GetRecomputeWorldTransform() { return mRecomputeWorldTransform; }

	/// <summary>
	/// �I�u�W�F�N�g�̑傫����Vector3�^�Ŏ擾����
	/// </summary>
	/// <returns> �I�u�W�F�N�g�̑傫��(Vector3�^) </returns>
	Vector3 GetScale() const { return mScale; }

	/// <summary>
	/// �I�u�W�F�N�g�̑傫����float�^�Ŏ擾����
	/// </summary>
	/// <returns> �I�u�W�F�N�g�̑傫��(float�^) </returns>
	float GetScaleFloat() { return mScale.x; }

	/// <summary>
	/// �I�u�W�F�N�g�̑傫��(Vector3�^)��ݒ肷��
	/// </summary>
	/// <param name="_scale"> �I�u�W�F�N�g�̑傫��(Vector3�^) </param>
	void SetScale(Vector3 _scale) { mScale.x = _scale.x; mScale.y = _scale.y; mScale.z = _scale.z; mRecomputeWorldTransform = true; }

	/// <summary>
	/// �I�u�W�F�N�g�̑傫��(float�^)��ݒ肷��
	/// </summary>
	/// <param name="_scale"> �I�u�W�F�N�g�̑傫��(float�^) </param>
	void SetScale(float _scale) { mScale.x = _scale; mScale.y = _scale; mScale.z = _scale; mRecomputeWorldTransform = true; }

	/// <summary>
	/// �I�u�W�F�N�g�̉�]�l���擾����
	/// </summary>
	/// <returns> �I�u�W�F�N�g�̉�]�l </returns>
	const Quaternion& GetRotation() const { return mRotation; }

	/// <summary>
	/// �I�u�W�F�N�g�̉�]�l��ݒ肷��
	/// </summary>
	/// <param name="_Rotation"> �I�u�W�F�N�g�̉�]�l </param>
	virtual void SetRotation(const Quaternion& _Rotation) { mRotation = _Rotation;  mRecomputeWorldTransform = true; }

	/// <summary>
	/// �I�u�W�F�N�g�̏�Ԃ��擾����
	/// </summary>
	/// <returns> �I�u�W�F�N�g�̏�� </returns>
	State GetState() const { return mState; }

	/// <summary>
	/// �I�u�W�F�N�g�̏�Ԃ�ݒ肷��
	/// </summary>
	/// <param name="_state"> �I�u�W�F�N�g�̏�� </param>
	virtual void SetState(State _state) { mState = _state; }

	/// <summary>
	/// �I�u�W�F�N�g�̃��[���h�s����擾����
	/// </summary>
	/// <returns> �I�u�W�F�N�g�̃��[���h�s�� </returns>
	const Matrix4& GetWorldTransform() const { return mWorldTransform; }

	/// <summary>
	/// �I�u�W�F�N�g�̑O���x�N�g�����擾����
	/// </summary>
	/// <returns> �I�u�W�F�N�g�̑O���x�N�g�� </returns>
	Vector3 GetForward() const { return Vector3::Transform(Vector3::UnitX, mRotation); }

	/// <summary>
	/// �I�u�W�F�N�g�̉E���x�N�g�����擾����
	/// </summary>
	/// <returns> �I�u�W�F�N�g�̉E���x�N�g�� </returns>
	Vector3 GetRight() const { return Vector3::Transform(Vector3::UnitY, mRotation); }

	/// <summary>
	/// �I�u�W�F�N�g�̏���x�N�g�����擾����
	/// </summary>
	/// <returns> �I�u�W�F�N�g�̏���x�N�g�� </returns>
	Vector3 GetUp() const { return Vector3::Transform(Vector3::UnitZ, mRotation); }

	/// <summary>
	/// �I�u�W�F�N�g�̃^�O���擾����
	/// </summary>
	/// <returns> �I�u�W�F�N�g�̃^�O </returns>
	Tag GetTag() const { return mTag; }

	/// <summary>
	/// �I�u�W�F�N�g��id���擾����
	/// </summary>
	/// <returns> �I�u�W�F�N�g��id </returns>
	int GetObjectId() { return mMyObjectId; }

	/// <summary>
	/// �I�u�W�F�N�g�̗̑͂��擾����
	/// </summary>
	/// <returns> �I�u�W�F�N�g�̗̑� </returns>
	int GetHitPoint() { return mHitPoint; }

	/// <summary>
	/// �I�u�W�F�N�g�̗̑͂�ݒ肷��
	/// </summary>
	/// <param name="_hitPoint"> �I�u�W�F�N�g�̗̑� </param>
	void SetScale(int _hitPoint) { mHitPoint = _hitPoint; }

	/// <summary>
	/// ��������I�u�W�F�N�g���擾����
	/// </summary>
	/// <returns> ��������I�u�W�F�N�g </returns>
	bool GetReUseGameObject() { return mReUseObject; }

	/// <summary>
	/// �I�u�W�F�N�g��AABB���擾����
	/// </summary>
	/// <returns> �I�u�W�F�N�g��AABB </returns>
	AABB GetObjectAABB() const { return mBox; }

	/// <summary>
	/// ��`�̓����蔻����s���N���X�̃|�C���^���擾
	/// </summary>
	/// <returns> ��`�̓����蔻����s���N���X�̃|�C���^ </returns>
	BoxCollider* GetBoxCollider() { return mBoxColliderPtr; }
};

