#pragma once

// �O���錾
class FirstAttackEffect;

/// <summary>
/// 1�i�K�ڂ̍U��
/// </summary>
class PlayerObjectStateFirstAttack : public PlayerObjectStateBase
{
public:

	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	PlayerObjectStateFirstAttack();

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~PlayerObjectStateFirstAttack() {};

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

	// �����p�x�̃��X�g
	float faceAngleList[8];

	// �����蔻���L���ɂ���^�C�~���O
	const int MBoxEnableTiming;
	// �����蔻��𖳌��ɂ���^�C�~���O
	const int MBoxDisableTiming;
	// �G�l�~�[�̍U���̃_���[�W�l
	const int MDamageValueEnemyAttack;
	// ����]�l
	const int MHalfRotation;
	// �U�����̑��x
	const float MAttackSpeed;
	// �A�j���[�V�����̍Đ����x
	const float MPlayRate;
	// ���X�e�B�b�N�̂������l
	const float MLeftAxisThreshold;
	// �x�N�g����Z������l
	const float MValueShortenVector;

	// �R���{�L���t���[��
	const size_t MValidComboFrame;

	// �����蔻��̏��
	// true : �L��, false : ����
	bool mIsCollisionState;

	// ��]���邩
	bool mIsRotation;

	// �_���[�W�l
	int mDamageValue;
	// �����蔻�肷��܂ł̃J�E���g
	int mHitUntilCount;

	// 2�̃x�N�g���̂Ȃ��p
	float mTwoVectorAngle;

	// �t���[����
	size_t mNumFrame;

	// ���X�e�B�b�N�̓��͒l���擾
	Vector2 mLeftAxis;
	// ���W
	Vector3 mPosition;
	// �O���x�N�g��
	Vector3 mForwardVec;
	// �E���x�N�g��
	Vector3 mRightVec;

	// �J�����̃|�C���^
	MainCameraObject* mMainCameraPtr;
	// 1�i�K�ڂ̒ʏ�U���G�t�F�N�g�̃|�C���^
	FirstAttackEffect* mFirstAttackEffect;

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
	/// 1�i�K�ڂ̒ʏ�U���G�t�F�N�g�̃|�C���^��ݒ�
	/// </summary>
	/// <param name="_firstAttackEffect"> 1�i�K�ڂ̒ʏ�U���G�t�F�N�g�̃|�C���^ </param>
	void SetFirstAttackEffectPtr(FirstAttackEffect* _firstAttackEffect) { mFirstAttackEffect = _firstAttackEffect; }
};