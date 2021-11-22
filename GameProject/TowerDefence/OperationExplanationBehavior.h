#pragma once

/// <summary>
/// �������UI�̋���
/// </summary>
class OperationExplanationBehavior : public Component
{
public:

	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="_owner"> �A�^�b�`�����I�u�W�F�N�g�̃|�C���^ </param>
	/// <param name="_playerPtr"> �v���C���[�̃|�C���^ </param>
	OperationExplanationBehavior(GameObject* _owner, PlayerObject* _playerPtr);

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~OperationExplanationBehavior() {};

	/// <summary>
	/// �t���[�����̏���
	/// </summary>
	/// <param name="_deltaTime"> �Ō�̃t���[������������̂ɗv�������� </param>
	void Update(float _deltaTime)override;

private:

	// �ړ����x
	const float MMoveSpeed;
	// �~�߂邽�߂̋���
	const float MStopForDistance;

	// �������W
	const Vector3 MInitPosition;
	// �E�����̃x�N�g��
	const Vector3 MRightDirVec;
	// �������̃x�N�g��
	const Vector3 MLeftDirVec;

	// �����ɂ��邩�̃t���O
	bool mIsDisable;

	// �v���C���[�̃|�C���^
	PlayerObject* mPlayerPtr;
};