#include "pch.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="_Pos"> ���W </param>
/// <param name="_Scale"> �傫�� </param>
/// <param name="_ObjectTag"> �^�O </param>
/// <param name="_SceneTag"> �V�[���^�O </param>
/// <param name="_playerPtr"> �v���C���[�̃|�C���^ </param>
EnemyGenerator::EnemyGenerator(const Vector3& _Pos, const Vector3& _Scale, const Tag& _ObjectTag, const SceneBase::Scene _SceneTag, PlayerObject* _playerPtr)
	: GameObject(_ObjectTag, _SceneTag)
	, mPlayerPtr(_playerPtr)
{
	//GameObject�����o�ϐ��̏�����
	mTag = _ObjectTag;
	SetScale(_Scale);
	SetPosition(_Pos);
}

EnemyObject* EnemyGenerator::CreateEnemyObject()
{
	return new EnemyObject(mPosition, mScale, "Assets/Model/Enemy/Enemy.gpmesh"
		, "Assets/Model/Enemy/Enemy.gpskel"
		, Tag::eEnemy
		, SceneBase::tutorial
		, mPlayerPtr);
}