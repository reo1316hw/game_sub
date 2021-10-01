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

/*
@brief	�Q�[���I�u�W�F�N�g�̏��
*/
enum State
{
	//�A�N�e�B�u
	Active,
	//�X�V����~���Ă���
	Paused,
	//�I�u�W�F�N�g�̍X�V���I��(�O������̂�Active�ɕύX�\)
	Dead,
};

/*
	@enum�@GameObject�^�O
	�Փˑ���𔻕ʂ��邽�߂Ɏg�p
	*/
enum Tag
{
	Other = 0,
	Camera = 1,
	Player = 2,
	EightTimesSeventeenGround = 3,
	SixTimesThreeGround = 4,
	FourTimesFiveGround = 5,
	ThreeTimesFourGround = 6,
	TwentyFiveTimesTwoGround = 7,
	TwelveTimesThirteenGround = 8,
	ThreeTimesNineGround01 = 9,
	NineTimesTwoGround = 10,
	ThreeTimesNineGround02 = 11,
	SevenTimesSevenGround = 12,
	ThirteenTimesThreeGround = 13,
	ThreeTimesThreeGround = 14,
	ElevenTimesOneGround = 15,
	NineteenTimesNineteenGround = 16,
	SideSuperShortWall = 17,
	VerticalSuperShortWall = 18,
	SideShortWall = 19,
	VerticalShortWall = 20,
	UsuallyWall = 21,
	SideLongWall = 22,
	VerticalLongWall = 23,
	SideSuperLongWall = 24,
	VerticalSuperLongWall = 25,
	Enemy = 26,
	Swith = 27
};

/*
@enum �Q�[���I�u�W�F�N�g�̍X�V���~����C�x���g��
*/
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

class GameObject
{
public:

	/*
	@param	�Q�[���N���X�̃|�C���^
	*/
	GameObject(const Tag& _objectTag ,SceneBase::Scene _sceneTag, bool _reUseGameObject = false);
	virtual ~GameObject();

	/*
	@brief	�t���[�����̏���
	@param	�Ō�̃t���[������������̂ɗv��������
	*/
	void Update(float _deltaTime);

	/*
	@brief	�A�^�b�`����Ă�R���|�[�l���g�̃A�b�v�f�[�g
	@param	�Ō�̃t���[������������̂ɗv��������
	*/
	void UpdateComponents(float _deltaTime);

	/*
	@brief	�Q�[���I�u�W�F�N�g�̃A�b�v�f�[�g
	@param	�Ō�̃t���[������������̂ɗv��������
	*/
	virtual void UpdateGameObject(float _deltaTime);

	/*
	@fn �Q�[���I�u�W�F�N�g���Î~���ɍX�V�����A�b�v�f�[�g�֐�
	@brief pauzingUpdate��true�̂Ƃ������Ă΂��X�V�֐�
	*/
	virtual void PausingUpdateGameObject();

	/*
	@fn ���͏�Ԃ��󂯎��GameObject��Component�̓��͍X�V�֐����Ăяo��
	*/
	void ProcessInput(const InputState& _keyState);

	/*
	@fn ���͂������Ŏ󂯎��X�V�֐�
	@brief ��{�I�ɂ����œ��͏���ϐ��ɕۑ���UpdateGameObject�ōX�V���s��
	*/
	virtual void GameObjectInput(const InputState& _keyState);

	/*
	@brief	�R���|�[�l���g��ǉ�����
	@param	�ǉ�����R���|�[�l���g�̃|�C���^
	*/
	void AddComponent(Component* _component);

	/*
	@brief	�R���|�[�l���g���폜����
	@param	�폜����R���|�[�l���g�̃|�C���^
	*/
	void RemoveComponent(Component* _component);

	/*
	@fn ���݂̎d�l��s�����Ƃ��ł��Ȃ��������O�����狭���ɍs�����߂̊֐�
	@exsample �Q�[���I�u�W�F�N�g�S�̂̍X�V����~���ɑΏۂ̃Q�[���I�u�W�F�N�g���X�V����
	*/
	void ExceptionUpdate();
	/*
	@brief	Transform�̃��[���h�ϊ�
	*/
	void ComputeWorldTransform();

	/*
	@brief�@�I�u�W�F�N�g�̃|�W�V�������擾����
	@return	position
	*/
	const Vector3& GetPosition() const { return mPosition; }

	/*
	@brief�@�I�u�W�F�N�g�̃|�W�V������ݒ肷��
	@param	position
	*/
	virtual void SetPosition(const Vector3& _pos) { mPosition = _pos; mRecomputeWorldTransform = true; }
	bool GetRecomputeWorldTransform() { return mRecomputeWorldTransform; }

	/*
	@brief�@�I�u�W�F�N�g�̃X�P�[�����擾����
	@return	scale
	*/
	Vector3 GetScaleFloat() const { return mScale; }

	/*
	@brief�@�I�u�W�F�N�g�̃X�P�[����ݒ肷��
	@param	scale
	*/
	void SetScale(float _scale) { mScale.x = _scale; mScale.y = _scale; mScale.z = _scale; mRecomputeWorldTransform = true; }
	void SetScale(Vector3 _scale) { mScale.x = _scale.x; mScale.y = _scale.y; mScale.z = _scale.z; mRecomputeWorldTransform = true; }

	float GetScale() { return mScale.x; }
	/*
	@brief�@�I�u�W�F�N�g�̃N�H�[�^�j�I�����擾����
	@return	rotation�iQuaternion�^�j
	*/
	const Quaternion& GetRotation() const { return mRotation; }

	/*
	@brief�@�I�u�W�F�N�g�̃N�H�[�^�j�I����ݒ肷��
	@param	rotation�iQuaternion�^�j
	*/
	virtual void SetRotation(const Quaternion& _qotation) { mRotation = _qotation;  mRecomputeWorldTransform = true; }

	/*
	@brief�@�I�u�W�F�N�g�̏�Ԃ��擾����
	@return	state
	*/
	State GetState() const { return mState; }

	/*
	@brief�@�I�u�W�F�N�g�̏�Ԃ�ݒ肷��
	@param	state
	*/
	virtual void SetState(State _state) { mState = _state; }

	/*
	@brief�@�I�u�W�F�N�g�̃��[���h�s����擾����
	@return	worldTransform
	*/
	const Matrix4& GetWorldTransform() const { return mWorldTransform; }

	/*
	@brief�@�I�u�W�F�N�g�̑O����\���x�N�g�����擾����
	@param	forward(Vector3�^)
	*/
	Vector3 GetForward() const { return Vector3::Transform(Vector3::UnitX, mRotation); }

	/*
	@brief�@�I�u�W�F�N�g�̉E��\���x�N�g�����擾����
	@param	right(Vector3�^)
	*/
	Vector3 GetRight() const { return Vector3::Transform(Vector3::UnitY, mRotation); }

	/*
	@brief�@�I�u�W�F�N�g�̏��\���x�N�g�����擾����
	@param	up(Vector3�^)
	*/
	Vector3 GetUp() const { return Vector3::Transform(Vector3::UnitZ, mRotation); };
	
	/*
	@brief�@�I�u�W�F�N�g�̃^�O���擾����
	@return	tag
	*/
	Tag GetTag() const { return mTag; };

	/*
	@brief�@�I�u�W�F�N�g��id���擾����
	@return	myObjectId(int�^)
	*/
	int GetObjectId() { return mMyObjectId; };

	/*
	@brief�@��������I�u�W�F�N�g���擾����
	@return	reUseObject(bool�^)
	*/
	bool GetReUseGameObject() { return mReUseObject; };

	virtual void FixCollision(const AABB& _myAABB, const AABB& _pairAABB, const Tag& _pairTag);

	void RotateToNewForward(const Vector3& _forward);

	/*
	@fn �ÓI��mainCamera�𐶐�����
	*/
	static void CreateMainCamera();

	/*
	@brief�@�V�[���̃^�O���擾����
	@return	sceneTag
	*/
	SceneBase::Scene GetScene() const { return mSceneTag; };

	/*
	@brief�@�I�u�W�F�N�g��AABB���擾����
	@return	mAabb
	*/
	AABB GetObjectAABB() const { return mAabb; };

protected:
	std::function<void(GameObject&)> GetOnCollisionFunc() { return std::bind(&GameObject::OnCollision, this, std::placeholders::_1); }
	virtual void OnCollision(const GameObject& _hitObject) {}

	//���C���J�����@������GameObjectManager�������ɍs����
	static class MainCameraObject* mMainCamera;
	//�Q�[���I�u�W�F�N�g�̍X�V���~�߂�C�x���g���
	static PauzingEvent mPauzingEvent;
	//�Փˎ��̃��A�N�V�����֐�(ColliderComponent�ɂ��̊֐��̃A�h���X��n��) Enter...�Փ˂��� Stay...�Փ˂��Ă���
	virtual void OnTriggerEnter(ColliderComponent* _colliderPair) {};
	//�Փˎ��̃��A�N�V�����֐�(ColliderComponent�ɂ��̊֐��̃A�h���X��n��) Enter...�Փ˂��� Stay...�Փ˂��Ă���
	virtual void OnTriggerStay(ColliderComponent* _colliderPair) {};

	//�I�u�W�F�N�g��AABB
	AABB mAabb;
	//�Q�[���I�u�W�F�N�g�̏��
	State mState;
	//�Q�[���I�u�W�F�N�g�̃^�O
	Tag mTag;
	//�Q�[���I�u�W�F�N�g��ID�A�J�E���g�p
	static int mGameObjectId;
	//���̃Q�[���I�u�W�F�N�g��ID
	int mMyObjectId;

	//�Q�[���I�u�W�F�N�g�̃X�P���g�����b�V��
	SkeletalMeshComponent* mSkeltalMeshComponent;
	//�Q�[���I�u�W�F�N�g�̃��b�V��
	MeshComponent* mMeshComponent;
	//�Q�[���I�u�W�F�N�g�̓����蔻��
	BoxCollider* mBoxCollider;
	//�����蔻���mesh�ɂ��邽�߂̃C���X�^���X
	Mesh* mMesh;

	//Transform
	Vector3 mPosition;
	Vector3 mVelocity;
	Vector3 mScale;
	//�@�ړ���
	Vector3 mEndPos;
	//�@�������W
	Vector3		mInitPos;
	Quaternion  mRotation;
	Matrix4		mWorldTransform;
	// �ړ����x
	float mMoveSpeed;
	//�d��
	float mGravity;
	//���[���h�ϊ��̏������s���K�v�������邩
	bool mRecomputeWorldTransform;
	// �����������ǂ���
	bool mHitFlag;
	// �����ʒu�ɖ߂���
	bool mOriginalPosFlag;
	
	//�V�[���̃^�O
	SceneBase::Scene mSceneTag;
	//�A�^�b�`����Ă���R���|�[�l���g
	std::vector<class Component*>mComponents;
private:
	//�V�[�����ׂ��ۂɉ�������I�u�W�F�N�g���ǂ����A�J�����Ȃǂ��ΏۂɂȂ�
	bool mReUseObject;
};

