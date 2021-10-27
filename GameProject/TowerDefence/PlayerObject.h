#pragma once

// �O���錾
class SkeletalMeshComponent;
class Animation;
class PlayerObjectStateBase;
class AttackMeshComponent;
class SphereCollider;
class PlayerWeaponObject;
class MainCameraObject;
class PlayerObjectStateRunLoop;
class PlayerObjectStateSprintStart;
class PlayerObjectStateSprintLoop;

/// <summary>
/// �v���C���[�̏��
/// </summary>
enum class PlayerState
{
	ePlayerStateIdle = 0,		// �ҋ@
	ePlayerStateRunLoop,		// �����Ă���
	ePlayerStateSprintStart,	// �S�͎����n��
	ePlayerStateSprintLoop,		// �S�͎������Ă���
	ePlayerStateFirstAttack,	// 1�i�K�ڂ̒ʏ�U��
	ePlayerStateSecondAttack,	// 2�i�K�ڂ̒ʏ�U��
	ePlayerStateThirdAttack,	// 3�i�K�ڂ̒ʏ�U��
	ePlayerStateDashAttack,     // �_�b�V���U��
	ePlayerStateDamage,         // �_���[�W���󂯂�
	ePlayerStateDeath,          // ���S���

	ePlayerStateNum,            // ���A�j���[�V������
};

/// <summary>
/// �v���C���[
/// </summary>
class PlayerObject : public GameObject
{
public:

	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="_Pos"> ���W </param>
	/// <param name="_Scale"> �傫�� </param>
	/// <param name="_GpmeshName"> gpmesh�̃p�X </param>
	/// <param name="_GpskelName"> gpskel�̃p�X </param>
	/// <param name="_ObjectTag"> �I�u�W�F�N�g�̃^�O </param>
	PlayerObject(const Vector3& _Pos, const Vector3& _Scale, const char* _GpmeshName, const char* _GpskelName, const Tag& _ObjectTag);

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~PlayerObject() {};

	/// <summary>
	/// �I�u�W�F�N�g�̍X�V����
	/// </summary>
	/// <param name="_deltaTime"> �Ō�̃t���[������������̂ɗv�������� </param>
	void UpdateGameObject(float _deltaTime)override;

	/// <summary>
	/// ���͂������Ŏ󂯎��X�V�֐�
	/// ��{�I�ɂ����œ��͏���ϐ��ɕۑ���UpdateGameObject�ōX�V���s��
	/// </summary>
	/// <param name="_KeyState"> �L�[�{�[�h�A�}�E�X�A�R���g���[���[�̓��͏�� </param>
	void GameObjectInput(const InputState& _KeyState)override;

private:

	/// <summary>
	/// ��]����
	/// </summary>
	/// <param name="_Axis"> �� </param>
	/// <param name="_Angle"> �p�x </param>
	void SelfRotation(const Vector3 _Axis, const float _Angle);

	/// <summary>
	/// �q�b�g�������̏���
	/// </summary>
	/// <param name="_HitObject"> �q�b�g�����Q�[���I�u�W�F�N�g </param>
	void OnCollision(const GameObject& _HitObject)override;

	// �ő�̗�
	const int MMaxHp;
	// ���̏�����]�l
	const Vector3 MSwordRot;
	// ���̏������W
	const Vector3 MSwordPos;
	// �A�j���[�V�����̍Đ����x
	const float MPlayRate;
	// �p�x
	const float MAngle;

	// �A�j���[�V�����ϒ��R���e�i
	std::vector<const Animation*>       mAnimTypes;
	// �X�e�[�g�N���X�v�[��
	std::vector<PlayerObjectStateBase*> mStatePools;

	// ���݂̃X�e�[�g
	PlayerState mNowState;
	// ���̃X�e�[�g
	PlayerState mNextState;
	// �X�P���g�����b�V���̃|�C���^
	SkeletalMeshComponent* mSkeltalMeshComponentPtr;
	// �v���C���[����̃|�C���^
	PlayerWeaponObject* mWeaponPtr;
	// �J�����̃|�C���^
	MainCameraObject* mMainCameraPtr;
	// �����Ԃ̃N���X�̃|�C���^
	PlayerObjectStateRunLoop* mRunLoopPtr;
	// �S�͎����n�ߏ�Ԃ̃N���X�̃|�C���^
	PlayerObjectStateSprintStart* mSprintStartPtr;
	// �S�͎�����Ԃ̃N���X�̃|�C���^
	PlayerObjectStateSprintLoop* mSprintLoopPtr;

public:// �Q�b�^�[�Z�b�^�[

	/// <summary>
	/// Animation�̃|�C���^���擾
	/// </summary>
	/// <param name="_State"> �v���C���[�̏�� </param>
	/// <returns> Animation�̃|�C���^ </returns>
	const Animation* GetAnimPtr(const PlayerState _State) const { return mAnimTypes[(int)_State]; }

	/// <summary>
	/// �X�P���g�����b�V���̃|�C���^���擾
	/// </summary>
	/// <returns> �X�P���g�����b�V���̃|�C���^ </returns>
	SkeletalMeshComponent* GetSkeletalMeshComponentPtr() { return mSkeltalMeshComponentPtr; }

	/// <summary>
	/// ���݂̃X�e�[�g���擾
	/// </summary>
	/// <returns> ���݂̃X�e�[�g </returns>
	PlayerState GetPlayerState() { return mNowState; }

	/// <summary>
	/// �J�����̃|�C���^��ݒ�
	/// </summary>
	/// <param name="_mainCameraPtr"> �J�����̃|�C���^ </param>
	void SetMainCameraPtr(MainCameraObject* _mainCameraPtr);
};

