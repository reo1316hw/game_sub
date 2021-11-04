#pragma once

// �O���錾
class FirstAttackEffect;

/// <summary>
/// 3�i�K�ڂ̍U��
/// </summary>
class PlayerObjectStateThirdAttack : public PlayerObjectStateBase
{
public:

	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	PlayerObjectStateThirdAttack();

	/// <summary>
    /// �f�X�g���N�^
    /// </summary>
	~PlayerObjectStateThirdAttack() {};

	/// <summary>
	/// �X�V����
	/// </summary>
	/// <param name="_owner"> �v���C���[(�e)�̃|�C���^ </param>
	/// <param name="_DeltaTime"> �Ō�̃t���[������������̂ɗv�������� </param>
	/// <returns> �v���C���[�̏�� </returns>
	PlayerState Update(PlayerObject* _owner, const float _DeltaTime)override;

	/// <summary>
	/// �v���C���[�̏�Ԃ��ύX���āA�ŏ���1�񂾂��Ăяo�����֐�
	/// </summary>
	/// <param name="_owner"> �v���C���[(�e)�̃|�C���^ </param>
	/// <param name="_DeltaTime"> �Ō�̃t���[������������̂ɗv�������� </param>
	void Enter(PlayerObject* _owner, const float _DeltaTime)override;

	/// <summary>
	/// �q�b�g�������̏���
	/// </summary>
	/// <param name="_owner"> �v���C���[(�e)�̃|�C���^ </param>
	/// <param name="_HitObject"> �q�b�g�����Q�[���I�u�W�F�N�g </param>
	void OnCollision(PlayerObject* _owner, const GameObject& _HitObject)override;

private:

	// �G�l�~�[�̍U���̃_���[�W�l
	const int MDamageValueEnemyAttack;
	// �����蔻���L���ɂ���^�C�~���O
	const int MBoxEnableTiming;
	// �����蔻��𖳌��ɂ���^�C�~���O
	const int MBoxDisableTiming;
	// �q�b�g�X�g�b�v���I���^�C�~���O
	const int MHitStopEndTiming;
	// �U�����̑��x
	const float MAttackSpeed;
	// �A�j���[�V�����̍Đ����x
	const float MPlayRate;

	// �����蔻��̏��
	// true : �L��, false : ����
	bool mIsCollisionState;
	// �q�b�g�X�g�b�v���邩
	bool mIsHitStop;

	// �_���[�W�l
	int mDamageValue;
	// �����蔻�肷��܂ł̃J�E���g
	int mHitUntilCount;
	// �q�b�g�X�g�b�v����t���[����
	int mHitStopCount;

	// ���W
	Vector3 mPosition;

	// �J�����̃|�C���^
	MainCameraObject* mMainCameraPtr;
	// �X�P���g���N���X�̃|�C���^
	SkeletalMeshComponent* skeletalMeshCompPtr;
	// 3�i�K�ڂ̒ʏ�U���G�t�F�N�g�̃N���X�̃|�C���^
	ThirdAttackEffect* mThirdAttackEffectPtr;

public:// �Q�b�^�[�Z�b�^�[

	/// <summary>
	/// �����蔻��̏�Ԃ��擾
	/// </summary>
	/// <returns> �����蔻��̏�� </returns>
	bool GetIsCollisionState() { return mIsCollisionState; }

	/// <summary>
	/// 3�i�K�ڂ̒ʏ�U���G�t�F�N�g�̃N���X�̃|�C���^��ݒ�
	/// </summary>
	/// <param name="_thirdAttackEffectPtr"> 3�i�K�ڂ̒ʏ�U���G�t�F�N�g�̃N���X�̃|�C���^ </param>
	void SetThirdAttackEffectPtr(ThirdAttackEffect* _thirdAttackEffectPtr) { mThirdAttackEffectPtr = _thirdAttackEffectPtr; }

	/// <summary>
	/// �J�����̃|�C���^��ݒ�
	/// </summary>
	/// <param name="_mainCameraPtr"> �J�����̃|�C���^ </param>
	void SetMainCameraPtr(MainCameraObject* _mainCameraPtr) { mMainCameraPtr = _mainCameraPtr; }
};