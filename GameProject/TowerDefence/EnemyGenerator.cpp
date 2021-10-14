#include "pch.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="_Pos"> ���W </param>
/// <param name="_Scale"> �傫�� </param>
/// <param name="_ObjectTag"> �I�u�W�F�N�g�̃^�O </param>
/// <param name="_playerPtr"> �v���C���[�̃|�C���^ </param>
EnemyGenerator::EnemyGenerator(const Vector3& _Pos, const Vector3& _Scale, const Tag& _ObjectTag, PlayerObject* _playerPtr)
	: GameObject(_ObjectTag)
	, mPlayerPtr(_playerPtr)
{
	//GameObject�����o�ϐ��̏�����
	SetScale(_Scale);
	SetPosition(_Pos);
}

/// <summary>
/// �G�l�~�[�̐���
/// </summary>
/// <returns> �G�l�~�[�̃|�C���^</returns>
EnemyObject* EnemyGenerator::CreateEnemyObject()
{
	return new EnemyObject(mPosition, mScale, "Assets/Model/Enemy/Enemy.gpmesh"
		, "Assets/Model/Enemy/Enemy.gpskel"
		, Tag::eEnemy
		, mPlayerPtr);
}