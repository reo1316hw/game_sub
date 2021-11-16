#pragma once
#include "Component.h"

// �O���錾
class EnemyObject;
class EnemyHitPointGauge;
class EnemyHitPointFrame;

/// <summary>
/// �G�l�~�[�𐧌䂷��
/// </summary>
class EnemysControler : public Component
{
public:
	
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="_owner"> �A�^�b�`����Q�[���I�u�W�F�N�g�̃|�C���^ </param>
	/// <param name="_createEnemysPtr"> �G�l�~�[�����𐶐�����N���X�̃|�C���^ </param>
	/// <param name="_playerPtr"> �v���C���[�̃|�C���^ </param>
	EnemysControler(GameObject* _owner, CreateEnemys* _createEnemysPtr, PlayerObject* _playerPtr);
	
	/// <summary>
    /// �f�X�g���N�^
    /// </summary>
	~EnemysControler() {};

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
	void ActiveEnemy(EnemyObject* _enemyObjectPtr);

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
	void InvadeWithinRange(GameObject* _referenceEnemyItr, GameObject* _targetEnemyItr);

	/// <summary>
	/// �G�l�~�[������|���������J�E���g
	/// </summary>
	/// <param name="_EnemysCount"> �G�l�~�[�����̗v�f���w�肷�邽�߂̃J�E���g�ϐ� </param>
	/// <param name="_EnemysSize"> �G�l�~�[�����̐� </param>
	/// <param name="_referenceEnemyItr"> �ΏۂƂȂ�G�l�~�[�̃|�C���^ </param>
	void EnemysDeathCount(const int& _EnemysCount, const int& _EnemysSize, EnemyObject* _referenceEnemyItr);

	// 1�t���[���O��hp���I�z��	
	std::vector<int> mPreHpList;

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
	// �̗͂�0�ɂȂ�X�V���Ȃ��Ȃ����I�u�W�F�N�g�̐�
	int mDeadCount;
	// �`���[�g���A���G�l�~�[��|������
	int mTutorialEnemyDeadCount;

	// �G�l�~�[�����𐶐�����N���X�̃|�C���^
	CreateEnemys* mCreateEnemysPtr;
	// �G�l�~�[��hp�Q�[�W�̃|�C���^
	EnemyHitPointGauge* mEnemyHitPointGaugePtr;
	// �G�l�~�[��hp�̘g�̃|�C���^
	EnemyHitPointFrame* mEnemyHitPointFramePtr;

public:// �Q�b�^�[�Z�b�^�[

	/// <summary>
	/// �̗͂�0�ɂȂ�X�V���Ȃ��Ȃ����I�u�W�F�N�g�̐����擾
	/// </summary>
	/// <returns> �̗͂�0�ɂȂ�X�V���Ȃ��Ȃ����I�u�W�F�N�g�̐� </returns>
	int GetDeadCount() { return mDeadCount; }
};