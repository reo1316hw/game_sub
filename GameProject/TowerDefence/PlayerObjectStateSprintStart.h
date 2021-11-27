#pragma once

/// <summary>
/// �S�͎������n�߂���
/// </summary>
class PlayerObjectStateSprintStart : public PlayerObjectStateBase
{
public:
	
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	PlayerObjectStateSprintStart();

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~PlayerObjectStateSprintStart() {};

	/// <summary>
	/// �X�V����
	/// </summary>
	/// <param name="_owner"> �v���C���[(�e)�̃|�C���^ </param>
	/// <param name="_DeltaTime"> �Ō�̃t���[������������̂ɗv�������� </param>
	/// <returns> �v���C���[�̏�� </returns>
	PlayerState Update(PlayerObject* _owner, const float _DeltaTime)override;

	/// <summary>
	/// ���͏���
	/// </summary>
	/// <param name="_owner"> �v���C���[(�e)�̃|�C���^ </param>
	/// <param name="_KeyState"> �L�[�{�[�h�A�}�E�X�A�R���g���[���[�̓��͏�� </param>
	void Input(PlayerObject* _owner, const InputState& _KeyState)override;

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

	/// <summary>
	/// �U�����󂯂����̏���
	/// </summary>
	/// <param name="_HitTag"> �q�b�g�����I�u�W�F�N�g�̃^�O </param>
	/// <param name="_DamageValuePlayerAttack"> �_���[�W�� </param>
	/// <returns> �q�b�g������ </returns>
	bool ReceivedAttack(const Tag& _HitTag, const int& _DamageValuePlayerAttack);

	/// <summary>
	/// �ړ�����
	/// </summary>
	/// <param name="_owner"> �v���C���[(�e)�̃|�C���^ </param>
	/// <param name="_DeltaTime"> �Ō�̃t���[������������̂ɗv�������� </param>
	void MoveCalc(PlayerObject* _owner, const float _DeltaTime);

	// �q�b�g����I�u�W�F�N�g�̃��X�g
	Tag mHitTagList[4];

	// �_���[�W�l�̃��X�g
	int mDamageValueList[4];

	// �ړ����x
	const float MMoveSpeed;
	// �ő呬�x
	const float MMaxSpeed;
	// �A�j���[�V�����̍Đ����x
	const float MPlayRate;
	//�ړ����邽�߂̍��X�e�B�b�N�̂������l
	const float MLeftAxisThreshold;

	// �_���[�W���󂯂���
	bool mIsDamage;

	// �_���[�W�l
	int mDamageValue;
	// �q�b�g���鑊��̃��X�g�̗v�f��
	int mHitTagListSize;

	// ���W
	Vector3 mPosition;

	// �q�b�g�����I�u�W�F�N�g�̃^�O
	Tag mHitTag;

	// �v���C���[�̃|�C���^
	PlayerObject* mPlayerPtr;
	// �J�����̃|�C���^
	MainCameraObject* mMainCameraPtr;

public:// �Q�b�^�[�Z�b�^�[

    /// <summary>
    /// �J�����̃|�C���^��ݒ�
    /// </summary>
    /// <param name="_mainCameraPtr"> �J�����̃|�C���^ </param>
	void SetMainCameraPtr(MainCameraObject* _mainCameraPtr) { mMainCameraPtr = _mainCameraPtr; }
};