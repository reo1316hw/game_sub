#pragma once

/// <summary>
/// �{�X�̏u�Ԉړ�
/// </summary>
class BossObjectStateTeleportation : public BossObjectStateBase
{
public:

	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="_playerPtr"> �v���C���[�̃|�C���^ </param>
	BossObjectStateTeleportation(PlayerObject* _playerPtr);

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~BossObjectStateTeleportation() {};

	/// <summary>
	/// �X�V����
	/// </summary>
	/// <param name="_owner"> �{�X(�e)�̃|�C���^ </param>
	/// <param name="_DeltaTime"> �Ō�̃t���[������������̂ɗv�������� </param>
	/// <returns> �{�X�̏�� </returns>
	BossState Update(BossObject* _owner, const float _DeltaTime)override;

	/// <summary>
	/// �{�X�̏�Ԃ��ύX���āA�ŏ���1�񂾂��Ăяo�����֐�
	/// </summary>
	/// <param name="_owner"> �{�X(�e)�̃|�C���^ </param>
	/// <param name="_DeltaTime"> �Ō�̃t���[������������̂ɗv�������� </param>
	void Enter(BossObject* _owner, const float _DeltaTime)override;

	/// <summary>
	/// �{�X�̏�Ԃ��ύX���āA�Ō��1�񂾂��Ăяo�����֐�
	/// </summary>
	/// <param name="_owner"> �{�X(�e)�̃|�C���^ </param>
	/// <param name="_DeltaTime"> �Ō�̃t���[������������̂ɗv�������� </param>
	void Exit(BossObject* _owner, const float _DeltaTime)override;

	/// <summary>
	/// �q�b�g�������̏���
	/// </summary>
	/// <param name="_owner"> �{�X(�e)�̃|�C���^ </param>
	/// <param name="_HitObject"> �q�b�g�����Q�[���I�u�W�F�N�g </param>
	void OnCollision(BossObject* _owner, const GameObject& _HitObject)override;

private:

	// �e���|�[�g�I���^�C�~���O
	const int MTimingTeleportationEnding;
	// ��Ԃ�ς��邽�߂̋���
	const float MTransitionStateDistance;
	// �v���C���[�Ƃ̋���
	const float MDistanceWithPlayer;

	// �_���[�W���󂯂���
	bool mIsDamage;

	// �e���|�[�g�I���܂ł̃J�E���g
	int mUntilTeleportationEndingCount;

	// ���W
	Vector3 mPosition;
	// �e���|�[�g�������
	Vector3 mTeleportationVec;

	// �v���C���[�̃|�C���^
	PlayerObject* mPlayerPtr;
};