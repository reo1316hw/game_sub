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
	OperationExplanationBehavior(GameObject* _owner);

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
};