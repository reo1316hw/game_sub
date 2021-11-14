#pragma once

/// <summary>
/// �G�l�~�[������̒��g�̍�������
/// </summary>
class EnemyGeneratorBlackBoard : public GameObject
{
public:

	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="_Pos"> ���W </param>
	/// <param name="_Scale"> �傫�� </param>
    /// <param name="_Angle"> ��]�p </param>
	/// <param name="_GpmeshName"> gpmesh�̃p�X </param>
	/// <param name="_ObjectTag"> �I�u�W�F�N�g�̃^�O </param>
	EnemyGeneratorBlackBoard(const Vector3& _Pos, const Vector3& _Scale, const float& _Angle,
		const std::string _GpmeshName, const Tag& _ObjectTag);

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~EnemyGeneratorBlackBoard() {};

private:

	/// <summary>
	/// ��]����
	/// </summary>
	/// <param name="_Axis"> �� </param>
	/// <param name="_Angle"> �p�x </param>
	void SelfRotation(const Vector3& _Axis, const float& _Angle);
};