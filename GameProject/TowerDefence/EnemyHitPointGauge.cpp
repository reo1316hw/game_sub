#include "pch.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="_Pos"> UI�̐����ꏊ(�X�N���[�����W) </param>
/// <param name="_TextureName"> �e�N�X�`���̃p�X </param>
/// <param name="_ObjectTag"> �A�^�b�`�����Q�[���I�u�W�F�N�g�̃^�O </param>
/// <param name="_playerPtr"> �v���C���[�̃|�C���^ </param>
/// <param name="_Scale"> �摜�̊g��T�C�Y </param>
EnemyHitPointGauge::EnemyHitPointGauge(const Vector3& _Pos, const std::string& _TextureName, const Tag& _ObjectTag,
	PlayerObject* _playerPtr, const float& _Scale)
	: GameObject(_ObjectTag)
	, mHitPointGaugeControllerPtr(nullptr)
	, mParticlePtr(nullptr)
{
	SetPosition(_Pos);

	//�@�e�N�X�`���̎擾
	Texture* texture = RENDERER->GetTexture(_TextureName);

	// hp�Q�[�W�𐧌䂷��R���|�[�l���g�N���X
	mHitPointGaugeControllerPtr = new HitPointGaugeController(_playerPtr, texture);

	// �X�N���[����ɕ`�悷��R���|�[�l���g�N���X
	mParticlePtr = new ParticleComponent(this, mHitPointGaugeControllerPtr);
	mParticlePtr->SetTexture(texture);
}