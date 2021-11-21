#pragma once

/// <summary>
/// �������UI
/// </summary>
class OperationExplanation : public GameObject
{
public:

	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="_Pos"> UI�̐����ꏊ(�X�N���[�����W) </param>
	/// <param name="_TextureName"> �e�N�X�`���̃p�X </param>
	/// <param name="_ObjectTag"> �Q�[���I�u�W�F�N�g�̃^�O </param>
	/// <param name="_Scale"> �e�N�X�`���̊g��T�C�Y </param>
	OperationExplanation(const Vector3& _Pos, const std::string& _TextureName,
		const Tag& _ObjectTag, const Vector3& _Scale = Vector3(1.0f, 1.0f, 1.0f));

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~OperationExplanation() {};

private:
};