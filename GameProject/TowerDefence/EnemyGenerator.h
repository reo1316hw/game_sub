#pragma once

/// <summary>
/// �G�l�~�[�̐�����
/// </summary>
class EnemyGenerator : GameObject
{
public:

	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="_Pos"> ���W </param>
	/// <param name="_Scale"> �傫�� </param>
	/// <param name="_ObjectTag"> �^�O </param>
	/// <param name="_SceneTag"> �V�[���^�O </param>
	/// <param name="_playerPtr"> �v���C���[�̃|�C���^ </param>
	EnemyGenerator(const Vector3& _Pos, const Vector3& _Scale, const Tag& _ObjectTag, const SceneBase::Scene _SceneTag, PlayerObject* _playerPtr);

	/// <summary>
    /// �f�X�g���N�^
    /// </summary>
	~EnemyGenerator() {};

	EnemyObject* CreateEnemyObject();

private:

	// �v���C���[�̃|�C���^
	PlayerObject* mPlayerPtr;
};