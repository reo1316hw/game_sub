#include "pch.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="_Scale"> �摜�̊g��T�C�Y </param>
/// <param name="_TextureName"> �e�N�X�`���̃p�X </param>
/// <param name="_ObjectTag"> �A�^�b�`�����Q�[���I�u�W�F�N�g�̃^�O </param>
/// <param name="_enemyPtr"> �v���C���[�̃|�C���^ </param>
EnemyHitPointGauge::EnemyHitPointGauge(const Vector3& _Scale, const std::string& _TextureName,
	const Tag& _ObjectTag, EnemyObject* _enemyPtr)
	: GameObject(_ObjectTag)
	, MOffset(Vector3(0.0f, 0.0f, 100.0f))
	, mEnemyPtr(_enemyPtr)
{
	SetScale(_Scale);
	SetState(eDead);

	// �e�N�X�`���̎擾
	Texture* texture = RENDERER->GetTexture(_TextureName);

	// hp�Q�[�W�𐧌䂷��R���|�[�l���g�N���X
	HitPointGaugeController* hitPointGaugeControllerPtr = new HitPointGaugeController(this, mEnemyPtr);

	// �X�N���[����ɕ`�悷��R���|�[�l���g�N���X
	new ParticleComponent(this, texture);
}

/// <summary>
/// �Q�[���I�u�W�F�N�g�̃A�b�v�f�[�g
/// </summary>
/// <param name="_deltaTime"> �Ō�̃t���[������������̂ɗv�������� </param>
void EnemyHitPointGauge::UpdateGameObject(float _deltaTime)
{
	mPosition = mEnemyPtr->GetPosition() + MOffset;
	SetPosition(mPosition);
}