#pragma once

// �O���錾
class ParticleComponent;

/// <summary>
/// �G�l�~�[��hp�Q�[�W
/// </summary>
class EnemyHitPointGauge : public GameObject
{
public:

	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="_Scale"> �摜�̊g��T�C�Y </param>
	/// <param name="_TextureName"> �e�N�X�`���̃p�X </param>
	/// <param name="_ObjectTag"> �A�^�b�`�����Q�[���I�u�W�F�N�g�̃^�O </param>
	/// <param name="_enemyPtr"> �v���C���[�̃|�C���^ </param>
	EnemyHitPointGauge(const Vector3& _Scale, const std::string& _TextureName, 
		               const Tag& _ObjectTag, EnemyObject* _enemyPtr);

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~EnemyHitPointGauge() {};

	/// <summary>
	/// �Q�[���I�u�W�F�N�g�̃A�b�v�f�[�g
	/// </summary>
	/// <param name="_deltaTime"> �Ō�̃t���[������������̂ɗv�������� </param>
	void UpdateGameObject(float _deltaTime)override;

private:

	// �G�l�~�[����̋����x�N�g��
	const Vector3 MOffset;

	// hp�Q�[�W�𐧌䂷��R���|�[�l���g�N���X�̃|�C���^
	HitPointGaugeController* mHitPointGaugeControllerPtr;
	// �X�N���[����ɕ`�悷��R���|�[�l���g�N���X�̃|�C���^
	ParticleComponent* mParticlePtr;
	// �G�l�~�[�̃|�C���^
	EnemyObject* mEnemyPtr;
};