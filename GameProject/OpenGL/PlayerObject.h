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
	PLAYER_STATE_IDLE = 0,				// �[�����̑ҋ@
	PLAYER_STATE_SWORD_IDLE,			// �������̑ҋ@
	PLAYER_STATE_DRAWN_SWORD,			// ����(�ړ����Ȃ�)
	PLAYER_STATE_DRAWN_SWORD_MOVE,		// ����(�ړ�����)
	PLAYER_STATE_SWORD_DELIVERY,		// �[��(�ړ����Ȃ�)
	PLAYER_STATE_SWORD_DELIVERY_MOVE,	// �[��(�ړ�����)
	PLAYER_STATE_RUN_START,				// �[�����̑���n��
	PLAYER_STATE_RUN_LOOP,				// �[�����̑����Ă�����
	PLAYER_STATE_SWORD_RUN_LOOP,		// �������̑����Ă�����
	PLAYER_STATE_SPRINT_LOOP,			// �[�����̑S�͎������Ă�����
	PLAYER_STATE_RUN_END,				// �[�����̑���I���
	PLAYER_STATE_ATTACK1,				// �U��1
	PLAYER_STATE_ATTACK2,				// �U��2
	PLAYER_STATE_ATTACK3,				// �U��3
	//PLAYER_STATE_JUMPSTART,			// �W�����v�X�^�[�g
	//PLAYER_STATE_JUMPLOOP,			// �W�����v���[�v
	//PLAYER_STATE_JUMPEND,				// �W�����v�I��
	//PLAYER_STATE_HIT,

	PLAYER_STATE_NUM,   // ���A�j���[�V������
};

class PlayerObject : public GameObject
{
public:
	PlayerObject(const Vector3& _pos, const Vector3& _size, const std::string _gpmeshName, const char* _gpskelName, const char* _gpanimName, const Tag& _objectTag, const SceneBase::Scene _sceneTag);
	//PlayerObject(const Vector3& _pos, const Vector3& _size, const std::string _gpmeshName, const char* _gpskelName, const char* _gpanimName);
	~PlayerObject();

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

	// �d��
	const float GRAVITY = 100.0f;
	
	void OnCollision(const GameObject& _hitObject)override;
};

