#pragma once

/// <summary>
/// �{�X���v���C���[�̓���ɍU��������
/// </summary>
class BossObjectStateOverheadAttack : public BossObjectStateBase
{
public:

	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="_playerPtr"> �v���C���[�̃|�C���^ </param>
	BossObjectStateOverheadAttack(PlayerObject* _playerPtr);

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~BossObjectStateOverheadAttack() {};

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
	/// �{�X���m�̈�������
	/// </summary>
	/// <param name="_owner"> �{�X(�e)�̃|�C���^ </param>
	/// <param name="_DirTargetEnemyVec"> �ΏۂƂȂ�G�l�~�[�Ɍ������x�N�g�� </param>
	void Separation(BossObject* _owner, const Vector3& _DirTargetEnemyVec)override;

	/// <summary>
	/// �q�b�g�������̏���
	/// </summary>
	/// <param name="_owner"> �{�X(�e)�̃|�C���^ </param>
	/// <param name="_HitObject"> �q�b�g�����Q�[���I�u�W�F�N�g </param>
	void OnCollision(BossObject* _owner, const GameObject& _HitObject)override;

private:

	/// <summary>
	/// �v���C���[�̍U���Ƀq�b�g�������̏���
	/// </summary>
	/// <param name="_HitTag"> �q�b�g���鑊�� </param>
	/// <param name="_DamageValuePlayerAttack"> �_���[�W�� </param>
	/// <returns> �q�b�g������ </returns>
	bool HitAttack(const Tag& _HitTag, const int& _DamageValuePlayerAttack);

	// �q�b�g����I�u�W�F�N�g�̃��X�g
	Tag mHitTagList[4];

	// 1�i�K�ڂ̒ʏ�U���̃_���[�W�l
	const int MDamageValuePlayerFirstAttack;
	// ��Ԃ�ς��邽�߂̋���
	const float MTransitionStateDistance;
	// �x�N�g����Z������l
	const float MVecShortenVelue;
	// ���������x�N�g���̒���
	const float MSeparationVecLength;

	// �_���[�W���󂯂���
	bool mIsDamage;

	// �_���[�W�l
	int mDamageValue;
	// �q�b�g���鑊��̃��X�g�̗v�f��
	int mHitTagListSize;

	// ���W
	Vector3 mPosition;
	// ���x
	Vector3 mVelocity;
	// �q�b�g�����I�u�W�F�N�g�̃^�O
	Tag mHitTag;

	// �G�l�~�[�̃|�C���^
	BossObject* mBossPtr;
	// �v���C���[�̃|�C���^
	PlayerObject* mPlayerPtr;
};