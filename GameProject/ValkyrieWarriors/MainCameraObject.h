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
	/// <param name="_gateList"> ��̃��X�g </param>
    /// <param name="_ReUseGameObject"> �ė��p���邩�̃t���O </param>
	MainCameraObject(PlayerObject* _playerPtr, BossObject* _bossPtr, std::vector<GateObject*> _gateList, const bool& _ReUseGameObject);

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~MainCameraObject();

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

	// ��ɒ��ڂ�����
	bool mIsLookGate;
	// ��ɒ��ڂ��鏈���̏��������������邽�߂̃t���O
	bool mIsInitOpenGate;

	// ��̃��X�g�̔ԍ�
	int mGateListNum;
      
	// �J�������͉�]������]�p
	float mRotateZAngle;
	// �J�������~�낵������]�p
	float mRotateYAngle;

	// �Ǐ]��̃I�u�W�F�N�g���W
	Vector3 mTargetPos;
	//// ��ɒ��ڂ���O�̒Ǐ]��̃I�u�W�F�N�g���W
	//Vector3 mNotLookGateTargetPos;
	//// ��ɒ��ڂ���O�̃J�������W
	//Vector3 mNotLookGateCameraPos;
	// �������W
	Vector3 mInitPosition;
	// ��̍��W
	Vector3 mGatePos;

	// �v���C���[�̃|�C���^
	PlayerObject* mPlayerPtr;
	// �{�X�̃|�C���^
	BossObject* mBossPtr;
	// ��̃��X�g
	std::vector<GateObject*> mGateList;
	// ����J�������R���|�[�l���g�̃��X�g
	std::vector<OpenGate*> mOpenGateComponentList;
};

