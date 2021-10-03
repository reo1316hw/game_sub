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
	MainCameraObject();

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
	//�ړ����邽�߂̉E�X�e�B�b�N�̂������l
	const float MRightAxisThreshold;
	// ��]�ǉ��l
	const float MAddRotate;

	//�Ǐ]��̃I�u�W�F�N�g���������Ă��邩
	bool mHasTarget;
      
	// �J�������͉�]������]�p
	float mRotateZAngle;
	// �J�������~�낵������]�p
	float mRotateYAngle;

	//�e�I�u�W�F�N�g�Ƃ̍�
	Vector3 mOwnerOffset;
	//�Ǐ]��̃I�u�W�F�N�g���W
	Vector3 mTargetPos;
	
public://�Z�b�^�[�Q�b�^�[

	/// <summary>
	/// ���������W��ݒ�
	/// </summary>
	/// <param name="_Offset"> ���������W�Ƃ̍� </param>
	/// <param name="_TargetPos"> ������W </param>
	void SetViewObject(const Vector3& _Offset, const Vector3& _TargetPos);
};

