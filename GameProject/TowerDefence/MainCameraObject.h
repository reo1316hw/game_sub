#pragma once

/// <summary>
/// ���C���J����
/// </summary>
class MainCameraObject : public GameObject
{
public:

	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
    /// <param name="_playerPtr"> �v���C���[�̃|�C���^ </param>
	/// <param name="_bossPtr"> �{�X�̃|�C���^ </param>
    /// <param name="_ReUseGameObject"> �ė��p���邩�̃t���O </param>
	MainCameraObject(PlayerObject* _playerPtr, BossObject* _bossPtr, const bool& _ReUseGameObject);

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~MainCameraObject() {};

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

	// �ŏ��p
	const float MMinLookDownAngle;
	// �ő�p
	const float MMaxLookDownAngle;
	// �����邽�߂̉E�X�e�B�b�N�̂������l
	const float MRightAxisThreshold;
	// ��]�ǉ��l
	const float MAddRotate;
	// �J�������W�Ƃ̍�
	const Vector3 MCameraOffset;
	// ���������W�Ƃ̍�
	const Vector3 MTargetOffset;
      
	// �J�������͉�]������]�p
	float mRotateZAngle;
	// �J�������~�낵������]�p
	float mRotateYAngle;

	// �Ǐ]��̃I�u�W�F�N�g���W
	Vector3 mTargetPos;
	// �������W
	Vector3 mInitPosition;

	// �v���C���[�̃|�C���^
	PlayerObject* mPlayerPtr;
	// �{�X�̃|�C���^
	BossObject* mBossPtr;
};

