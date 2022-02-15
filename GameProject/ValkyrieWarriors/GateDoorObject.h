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
	/// <param name="_OpenToEnemyDefeatNum"> ����J�����߂ɓ|���G�l�~�[�̐� </param>
	/// <param name="_GpmeshName"> gpmesh�̃p�X </param>
	/// <param name="_ObjectTag"> �I�u�W�F�N�g�̃^�O </param>
	/// <param name="_enemysControlerPtr"> �G�l�~�[�𐧌䂷��R���|�[�l���g�N���X�̃|�C���^ </param>
	GateDoorObject(const Vector3& _Pos, const Vector3& _Scale, const float _AddAngle, const int& _OpenToDefeatEnemyNum,
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
	
	// ��]�p�𑝂₷���߂̒萔
	const float MAddAngle;

	// ����J�����߂̃N���X�̃|�C���^
	OpenGate* mOpenGatePtr;

public:// �Q�b�^�[�Z�b�^�[

	/// <summary>
	/// ����J�����߂̃N���X�̃|�C���^���擾
	/// </summary>
	/// <returns> ����J�����߂̃N���X�̃|�C���^ </returns>
	OpenGate* GetOpenGatePtr() { return mOpenGatePtr; }
};