#pragma once

/// <summary>
/// ���g����]����
/// </summary>
class SelfRotation : public Component
{
public:

	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
    /// <param name="_owner"> �A�^�b�`����Q�[���I�u�W�F�N�g�̃|�C���^ </param>
	/// <param name="_Axis"> �� </param>
	/// <param name="_Angle"> �p�x </param>
	SelfRotation(GameObject* _owner, const Vector3& _Axis, const float& _Angle);

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~SelfRotation() {};

	/// <summary>
	/// ��]
	/// </summary>
	/// <param name="_Axis"> �� </param>
	/// <param name="_Angle"> �p�x </param>
	void Rotation(const Vector3& _Axis, const float& _Angle);

private:
};