#pragma once

/// <summary>
/// ��̔�
/// </summary>
class GateDoorObject : public GameObject
{
public:

	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="_Pos"> ���W </param>
	/// <param name="_Scale"> �傫�� </param>
	/// <param name="_AddAngle"> ��]�p�𑝂₷���߂̒萔 </param>
	/// <param name="_GpmeshName"> gpmesh�̃p�X </param>
	/// <param name="_ObjectTag"> �I�u�W�F�N�g�̃^�O </param>
	/// <param name="_enemysControlerPtr"> �G�l�~�[�𐧌䂷��R���|�[�l���g�N���X�̃|�C���^ </param>
	GateDoorObject(const Vector3& _Pos, const Vector3& _Scale, const float _AddAngle,
		const std::string _GpmeshName, const Tag& _ObjectTag, EnemysControler* _enemysControlerPtr);

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~GateDoorObject() {};

	/// <summary>
	/// �I�u�W�F�N�g�̍X�V����
	/// </summary>
	/// <param name="_deltaTime"> �Ō�̃t���[������������̂ɗv�������� </param>
	void UpdateGameObject(float _deltaTime)override;

private:

	/// <summary>
	/// ��]����
	/// </summary>
	/// <param name="_Axis"> �� </param>
	/// <param name="_Angle"> �p�x </param>
	void SelfRotation(const Vector3& _Axis, const float& _Angle);
	
	// ��]�p�𑝂₷���߂̒萔
	const float MAddAngle;

	// ��]�p
	float mAngle;

	// �G�l�~�[�𐧌䂷��R���|�[�l���g�N���X�̃|�C���^
	EnemysControler* mEnemysControlerPtr;
};