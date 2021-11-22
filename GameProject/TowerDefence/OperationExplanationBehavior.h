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

	// �������W
	const Vector3 MInitPosition;

	// �v���C���[�̃|�C���^
	PlayerObject* mPlayerPtr;
};