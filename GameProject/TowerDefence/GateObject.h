#pragma once

/// <summary>
/// ��
/// </summary>
class GateObject : public GameObject
{
public:

	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="_Pos"> ���W </param>
	/// <param name="_Scale"> �傫�� </param>
	/// <param name="_GpmeshName"> gpmesh�̃p�X </param>
	/// <param name="_ObjectTag"> �I�u�W�F�N�g�̃^�O </param>
	GateObject(const Vector3& _Pos, const Vector3& _Scale, const std::string _GpmeshName, const Tag& _ObjectTag);

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~GateObject() {};

	/// <summary>
	/// �I�u�W�F�N�g�̍X�V����
	/// </summary>
	/// <param name="_deltaTime"> �Ō�̃t���[������������̂ɗv�������� </param>
	void UpdateGameObject(float _deltaTime)override;

private:

	// ��̉E���𒚓x�悢�ʒu�ɂ��炷���߂̃x�N�g��
	const Vector3 MRightGateDoorShiftVec;
	// ��̍����𒚓x�悢�ʒu�ɂ��炷���߂̃x�N�g��
	const Vector3 MLeftGateDoorShiftVec;
};