#pragma once

/// <summary>
/// �G�l�~�[�̐�����
/// </summary>
class EnemyGenerator : public GameObject
{
public:

	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="_Pos"> ���W </param>
	/// <param name="_Scale"> �傫�� </param>
	/// <param name="_ObjectTag"> �I�u�W�F�N�g�̃^�O </param>
	/// <param name="_playerPtr"> �v���C���[�̃|�C���^ </param>
	EnemyGenerator(const Vector3& _Pos, const Vector3& _Scale, const Tag& _ObjectTag, PlayerObject* _playerPtr);

	/// <summary>
    /// �f�X�g���N�^
    /// </summary>
	~EnemyGenerator() {};

	/// <summary>
	/// �G�l�~�[�̐���
	/// </summary>
	/// <returns> �G�l�~�[�̃|�C���^</returns>
	EnemyObject* CreateEnemyObject();

private:

	// �v���C���[�̃|�C���^
	PlayerObject* mPlayerPtr;
};