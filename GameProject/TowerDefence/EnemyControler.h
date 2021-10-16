#pragma once
#include "Component.h"

// �O���錾
class EnemyObject;

/// <summary>
/// �G�l�~�[�𐧌䂷��
/// </summary>
class EnemyControler : public Component
{
public:
	
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="_enemyObjectManagerPtr"> �G�l�~�[�}�l�[�W���[�̃|�C���^ </param>
	/// <param name="_createEnemysPtr"> �G�l�~�[�����𐶐�����N���X�̃|�C���^ </param>
	EnemyControler(EnemyObjectManager* _enemyObjectManagerPtr, CreateEnemys* _createEnemysPtr);
	
	/// <summary>
    /// �f�X�g���N�^
    /// </summary>
	~EnemyControler() {};

	/// <summary>
    /// �t���[�����̏���
    /// </summary>
    /// <param name="_deltaTime"> �Ō�̃t���[������������̂ɗv�������� </param>
	void Update(float _deltaTime)override;

private:

	/// <summary>
	/// ��莞�Ԃ��o�������A�N�e�B�u�ȃG�l�~�[���A�N�e�B�u�ɂ���
	/// </summary>
	/// <param name="_enemyObjectPtr"> �G�l�~�[�̃|�C���^ </param>
	/// <returns> �����𑱂��邩 </returns>
	bool ActiveEnemy(EnemyObject* _enemyObjectPtr);

	/// <summary>
	/// �ΏۂƂȂ�G�l�~�[������
	/// </summary>
	/// <param name="_enemyObjectList"> �G�l�~�[�̓��I�z�� </param>
	/// <param name="_referenceEnemyItr"> ��ƂȂ�G�l�~�[ </param>
	void SearchTargetEnemy(std::vector<EnemyObject*> _enemyObjectList, EnemyObject* _referenceEnemyItr);

	/// <summary>
	/// �͈͓��ɐN�����Ă��������߂�
	/// </summary>
	/// <param name="_referenceEnemyItr"> ��ƂȂ�G�l�~�[ </param>
	/// <param name="_targetEnemyItr"> �ΏۂƂȂ�G�l�~�[ </param>
	void InvadeWithinRange(EnemyObject* _referenceEnemyItr, EnemyObject* _targetEnemyItr);

	// �z��̗v�f������^�C�~���O
	const int MInElementsTiming;
	// 1��ɃA�N�e�B�u�ɂł���G�l�~�[�̐��̏��
	const int MMaxActiveInOnce;
	// �����̂������l
	const float MDistanceThreshold;

	// �z��̗v�f������܂ł̃J�E���g
	int mUntilInElementsCount;

	// �A�N�e�B�u�ɂȂ����I�u�W�F�N�g�̐�
	int mActiveCount;

	// ��ƂȂ�G�l�~�[�̍��W
	Vector3 mReferenceEnemyPos;

	// �G�l�~�[�����𐶐�����N���X�̃|�C���^
	CreateEnemys* mCreateEnemysPtr;
};

