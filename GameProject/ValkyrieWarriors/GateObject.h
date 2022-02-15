#pragma once

// �O���錾
class GateDoorObject;

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
	/// <param name="_OpenToEnemyDefeatNum"> ����J�����߂ɓ|���G�l�~�[�̐� </param>
	/// <param name="_GpmeshName"> gpmesh�̃p�X </param>
	/// <param name="_ObjectTag"> �I�u�W�F�N�g�̃^�O </param>
	/// <param name="_enemysControlerPtr"> �G�l�~�[�𐧌䂷��R���|�[�l���g�N���X�̃|�C���^ </param>
	GateObject(const Vector3& _Pos, const Vector3& _Scale, const int& _OpenToDefeatEnemyNum,
		const std::string _GpmeshName, const Tag& _ObjectTag, EnemysControler* _enemysControlerPtr);

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

	// ��`�����蔻��̐�
	const int BoxColliderNum;

	// ��̉E���̉�]�p�𑝂₷���߂̒萔
	const float MRightGateDoorAddAngle;
	// ��̍����̉�]�p�𑝂₷���߂̒萔
	const float MLeftGateDoorAddAngle;

	// ��̉E���𒚓x�悢�ʒu�ɂ��炷���߂̃x�N�g��
	const Vector3 MRightGateDoorShiftVec;
	// ��̍����𒚓x�悢�ʒu�ɂ��炷���߂̃x�N�g��
	const Vector3 MLeftGateDoorShiftVec;

	// ��̔��̃|�C���^
	GateDoorObject* mGateDoorPtr;

public:// �Q�b�^�[�Z�b�^�[

	/// <summary>
	/// ��̔��̃|�C���^���擾
	/// </summary>
	/// <returns> ��̔��̃|�C���^ </returns>
	GateDoorObject* GetGateDoorPtr() { return mGateDoorPtr; }
};