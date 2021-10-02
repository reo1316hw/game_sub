#pragma once

// �O���錾
class SkeletalMeshComponent;
class MeshComponent;
class Mesh;
class BoxCollider;
class Animation;
class PlayerObjectStateBase;
class AttackMeshComponent;

enum class PlayerState
{
	ePlayerStateIdle = 0,		// �ҋ@
	ePlayerStateRunLoop,		// �����Ă�����
	ePlayerStateSprintStart,	// �S�͎����n��
	ePlayerStateSprintLoop,		// �S�͎������Ă�����
	ePlayerStateFirstAttack,	// �U��1
	ePlayerStateSecondAttack,	// �U��2
	ePlayerStateThirdAttack,	// �U��3
	ePlayerStateDashAttack,     // �_�b�V���U��

	ePlayerStateNum,   // ���A�j���[�V������
};

class PlayerObject : public GameObject
{
public:

	PlayerObject(const Vector3& _pos, const Vector3& _size, const std::string _gpmeshName, const char* _gpskelName, const Tag& _objectTag, const SceneBase::Scene _sceneTag);

	~PlayerObject() {};

	SkeletalMeshComponent* GetSkeletalMeshComp() { return mSkeltalMeshComponent; };
	const Animation* GetAnim(PlayerState _state) { return mAnimTypes[static_cast<unsigned int>(_state)]; };

	void UpdateGameObject(float _deltaTime)override;
	void GameObjectInput(const InputState& _keyState)override;
	void SelfRotation(Vector3 _axis, float _angle);
	void PausingUpdateGameObject()override;

	Vector3 GetTargetPos() { return mTargetPos; };
	Vector3 GetViewPos() { return mViewPos; };

	void SetAttackBoneIndex(int _attackBoneIndex) { mAttackBoneIndex = _attackBoneIndex; };

private:

	//���̏�����]�l
	const Vector3 MSwordRot;
	//���̏������W
	const Vector3 MSwordPos;

	// �d��
	const float GRAVITY = 100.0f;

	std::vector<const class Animation*>      mAnimTypes;
	// �X�e�[�g�N���X�v�[��
	std::vector<class PlayerObjectStateBase*> mStatePools;

	// ���݂̃X�e�[�g
	PlayerState mNowState;
	// ���̃X�e�[�g
	PlayerState mNextState;

	AABB mPlayerBox;

	// ���탁�b�V��
	AttackMeshComponent* mWeaponMesh;

	//���������W�Ƃ̍�
	Vector3 mOffsetPos;
	//����Ώۂ̃|�W�V����
	Vector3 mTargetPos;
	//�J�����̃|�W�V����
	Vector3 mViewPos;

	int mAttackBoneIndex;
	
	void OnCollision(const GameObject& _hitObject)override;
};

