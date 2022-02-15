#pragma once
#include "Component.h";

// �O���錾
class EnemyObject;
class EnemyHitPointGauge;
class EnemyHitPointFrame;
class ParticleGauge;
class ParticleFrame;

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
	/// <param name="_enemyActiveBoxPtr"> �G�l�~�[���X�V�����邽�߂̓����蔻��p��`�I�u�W�F�N�g�̃|�C���^ </param>
	/// <param name="_bossActiveBoxPtr"> �{�X���X�V�����邽�߂̓����蔻��p��`�I�u�W�F�N�g�̃|�C���^ </param>
	EnemysControler(GameObject* _owner, CreateEnemys* _createEnemysPtr, 
		DeadObjectActiveBox* _enemyActiveBoxPtr, DeadObjectActiveBox* _bossActiveBoxPtr);
	
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
	// �ŏ��ɓ|���G�l�~�[�̐�
	const int MFirstDefeatEnemyNum;
	// ���ɓ|���G�l�~�[�̐�
	const int MNextDefeatEnemyNum;
	// �����̂������l
	const float MDistanceThreshold;

	// �A�N�e�B�u���ǂ����̃t���O
	bool mIsActive;
	// �����ɂ��邩�̃t���O
	bool mIsDisable;

	// �z��̗v�f������܂ł̃J�E���g
	int mUntilInElementsCount;
	// �A�N�e�B�u�ɂȂ����I�u�W�F�N�g�̐�
	int mActiveCount;
	// �̗͂�0�ɂȂ�X�V���Ȃ��Ȃ����I�u�W�F�N�g�̐�
	int mDeadCount;
	// �`���[�g���A���G�l�~�[��|������
	int mTutorialEnemyDeadCount;
	// �G�l�~�[��|����
	int mDefeatEnemyNum;

	// �G�l�~�[�����𐶐�����N���X�̃|�C���^
	CreateEnemys* mCreateEnemysPtr;
	// �G�l�~�[���X�V�����邽�߂̓����蔻��p��`�I�u�W�F�N�g�̃|�C���^
	DeadObjectActiveBox* mEnemyActiveBoxPtr;
	// �{�X���X�V�����邽�߂̓����蔻��p��`�I�u�W�F�N�g�̃|�C���^
	DeadObjectActiveBox* mBossActiveBoxPtr;
	// �G�l�~�[��hp�Q�[�W�̃|�C���^
	ParticleGauge* mEnemyHitPointGaugePtr;
	// �G�l�~�[��hp�̘g�̃|�C���^
	ParticleFrame* mEnemyHitPointFramePtr;

public:// �Q�b�^�[�Z�b�^�[

    /// <summary>
    /// �̗͂�0�ɂȂ�X�V���Ȃ��Ȃ����I�u�W�F�N�g�̐����擾
    /// </summary>
    /// <returns> �̗͂�0�ɂȂ�X�V���Ȃ��Ȃ����I�u�W�F�N�g�̐� </returns>
	int GetDeadCount() { return mDeadCount; }
};