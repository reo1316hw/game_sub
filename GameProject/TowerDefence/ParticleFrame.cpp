#include "pch.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="_owner"> �A�^�b�`�����Q�[���I�u�W�F�N�g�̃|�C���^ </param>
/// <param name="_Scale"> �摜�̊g��T�C�Y </param>
/// <param name="_TextureName"> �e�N�X�`���̃p�X </param>
/// <param name="_ObjectTag"> �Q�[���I�u�W�F�N�g�̃^�O </param>
ParticleFrame::ParticleFrame(GameObject* _owner, const Vector3& _Scale,
	const std::string& _TextureName, const Tag& _ObjectTag)
	: GameObject(_ObjectTag)
	, MOffset(Vector3(0.0f, 0.0f, 90.0f))
	, mOwner(_owner)
{
	SetScale(_Scale);
	SetState(eDead);

	// �e�N�X�`���̎擾
	Texture* texture = RENDERER->GetTexture(_TextureName);

	// �X�N���[����ɕ`�悷��R���|�[�l���g�N���X
	new ParticleComponent(this, texture);
}

/// <summary>
/// �Q�[���I�u�W�F�N�g�̃A�b�v�f�[�g
/// </summary>
/// <param name="_deltaTime"> �Ō�̃t���[������������̂ɗv�������� </param>
void ParticleFrame::UpdateGameObject(float _deltaTime)
{
	mPosition = mOwner->GetPosition() + MOffset;
	SetPosition(mPosition);
}