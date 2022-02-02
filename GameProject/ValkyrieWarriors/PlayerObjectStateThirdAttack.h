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
	/// �c�L�[���͑���
	/// </summary>
	/// <param name="_KeyState"> �L�[�{�[�h�A�}�E�X�A�R���g���[���[�̓��͏�� </param>
	/// <param name="_KeyScancode"> ���L�[���������� </param>
	/// <param name="_ButtonScancode"> ���{�^������������ </param>
	/// <param name="_AngleBorderMinAKey"> A�L�[���͎��̋��ڂ̊p�x�̍ŏ��l </param>
	/// <param name="_AngleBorderMaxAKey"> A�L�[���͎��̋��ڂ̊p�x�̍ő�l </param>
	/// <param name="_AngleBorderMinDKey"> D�L�[���͎��̋��ڂ̊p�x�̍ŏ��l </param>
	/// <param name="_AngleBorderMaxDKey"> D�L�[���͎��̋��ڂ̊p�x�̍ő�l </param>
	/// <param name="_ValueShortenVector"> �x�N�g����Z������l </param>
	/// <returns> true : ����������, false : ���������Ȃ����� </returns>
	bool VerticalKeyInputOperation(const InputState& _KeyState, const SDL_Scancode& _KeyScancode, const SDL_GameControllerButton& _ButtonScancode,
		const float& _AngleBorderMinAKey, const float& _AngleBorderMaxAKey, const float& _AngleBorderMinDKey, const float& _AngleBorderMaxDKey, const float& _ValueShortenVector);

	/// <summary>
	/// ���L�[���͑���
	/// </summary>
	/// <param name="_KeyState"> �L�[�{�[�h�A�}�E�X�A�R���g���[���[�̓��͏�� </param>
	/// <param name="_KeyScancode"> ���L�[���������� </param>
	/// <param name="_ButtonScancode"> ���{�^������������ </param>
	/// <param name="_AngleBorderMin"> ���ڂ̊p�x�̍ŏ��l </param>
	/// <param name="_AngleBorderMax"> ���ڂ̊p�x�̍ő�l </param>
	/// <param name="_ValueShortenVector"> �x�N�g����Z������l </param>
	/// <returns> true : ����������, false : ���������Ȃ����� </returns>
	bool LateralKeyInputOperation(const InputState& _KeyState, const SDL_Scancode& _KeyScancode, const SDL_GameControllerButton& _ButtonScancode,
		const float& _AngleBorderMin, const float& _AngleBorderMax, const float& _ValueShortenVector);

	/// <summary>
	/// ���X�e�B�b�N�����ɓ|�����Ƃ��̑���
	/// </summary>
	/// <param name="_AngleBorderMin"> ���ڂ̊p�x�̍ŏ��l </param>
	/// <param name="_AngleBorderMax"> ���ڂ̊p�x�̍ő�l </param>
	/// <param name="_ValueShortenVector"></param>
	/// <returns> true : �X�e�B�b�N��|����, false : �X�e�B�b�N��|���Ȃ����� </returns>
	bool LeftStickDefeatLeftInputOperation(const float& _AngleBorderMin, const float& _AngleBorderMax, const float& _ValueShortenVector);

	/// <summary>
	/// ���X�e�B�b�N���E�ɓ|�����Ƃ��̑���
	/// </summary>
	/// <param name="_AngleBorderMin"> ���ڂ̊p�x�̍ŏ��l </param>
	/// <param name="_AngleBorderMax"> ���ڂ̊p�x�̍ő�l </param>
	/// <param name="_ValueShortenVector"> �x�N�g����Z������l </param>
	/// <returns> true : �X�e�B�b�N��|����, false : �X�e�B�b�N��|���Ȃ����� </returns>
	bool LeftStickDefeatRightInputOperation(const float& _AngleBorderMin, const float& _AngleBorderMax, const float& _ValueShortenVector);

	/// <summary>
	/// �͈͊p�x�ŉ�]������
	/// </summary>
	/// <param name="_AngleBorderMin"> ���ڂ̊p�x�̍ŏ��l </param>
	/// <param name="_AngleBorderMax"> ���ڂ̊p�x�̍ő�l </param>
	/// <param name="_ValueShortenVector"> �x�N�g����Z������l </param>
	void RotateInRangeAngle(const float& _AngleBorderMin, const float& _AngleBorderMax, const float& _ValueShortenVector);

	// �q�b�g����I�u�W�F�N�g�̃��X�g
	Tag mHitTagList[4];

	// �_���[�W�l�̃��X�g
	int mDamageValueList[4];

	// �����p�x�̃��X�g
	float faceAngleList[8];

	// �q�b�g�X�g�b�v���I���^�C�~���O
	const int MHitStopEndTiming;
	// ����]�l
	const int MHalfRotation;
	// �S��]�l
	const int MAllRotation;
	// �U�����̑��x
	const float MAttackSpeed;
	// �A�j���[�V�����̍Đ����x
	const float MPlayRate;
	// �����蔻���L���ɂ���^�C�~���O
	const float MBoxEnableTiming;
	// ���X�e�B�b�N�̂������l
	const float MLeftAxisThreshold;
	// �x�N�g����Z������l
	const float MValueShortenVector;

	// �����蔻��̏��
	// true : �L��, false : ����
	bool mIsCollisionState;
	// ���݂̃X�e�[�g�ɓ�����1�񂾂������蔻���L���ɂ���
	bool mIsOneCollisionState;
	// �q�b�g�X�g�b�v���邩
	bool mIsHitStop;
	// �_���[�W���󂯂���
	bool mIsDamage;

	// �_���[�W�l
	int mDamageValue;
	// �q�b�g���鑊��̃��X�g�̗v�f��
	int mHitTagListSize;
	// �����蔻�肷��܂ł̃J�E���g
	int mHitUntilCount;
	// �q�b�g�X�g�b�v����t���[����
	int mHitStopCount;

	// 2�̃x�N�g���̂Ȃ��p
	float mTwoVectorAngle;
	// �����蔻��𖳌��ɂ���^�C�~���O
	float mBoxDisableTiming;

	// ���X�e�B�b�N�̓��͒l���擾
	Vector2 mLeftAxis;
	// ���W
	Vector3 mPosition;
	// �O���x�N�g��
	Vector3 mForwardVec;
	// �E���x�N�g��
	Vector3 mRightVec;

	// �q�b�g�����I�u�W�F�N�g�̃^�O
	Tag mHitTag;

	// �v���C���[�̃|�C���^
	PlayerObject* mPlayerPtr;
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
	/// �J�����̃|�C���^��ݒ�
	/// </summary>
	/// <param name="_mainCameraPtr"> �J�����̃|�C���^ </param>
	void SetMainCameraPtr(MainCameraObject* _mainCameraPtr) { mMainCameraPtr = _mainCameraPtr; }

	/// <summary>
	/// 3�i�K�ڂ̒ʏ�U���G�t�F�N�g�̃N���X�̃|�C���^��ݒ�
	/// </summary>
	/// <param name="_thirdAttackEffectPtr"> 3�i�K�ڂ̒ʏ�U���G�t�F�N�g�̃N���X�̃|�C���^ </param>
	void SetThirdAttackEffectPtr(ThirdAttackEffect* _thirdAttackEffectPtr) { mThirdAttackEffectPtr = _thirdAttackEffectPtr; }
};