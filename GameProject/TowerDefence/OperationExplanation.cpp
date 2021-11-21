#include "pch.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="_Pos"> UI�̐����ꏊ(�X�N���[�����W) </param>
/// <param name="_TextureName"> �e�N�X�`���̃p�X </param>
/// <param name="_ObjectTag"> �Q�[���I�u�W�F�N�g�̃^�O </param>
/// <param name="_Scale"> �摜�̊g��T�C�Y </param>
OperationExplanation::OperationExplanation(const Vector3& _Pos, const std::string& _TextureName,
	const Tag& _ObjectTag, const Vector3& _Scale)
	: GameObject(_ObjectTag)
{
	SetPosition(_Pos);
	SetScale(_Scale);
	SetState(eActive);

	// �e�N�X�`���̎擾
	Texture* texture = RENDERER->GetTexture(_TextureName);

	// �X�N���[����ɕ`�悷��R���|�[�l���g�N���X
	new SpriteComponent(this, texture);

	// �������UI�̋����R���|�[�l���g�𐶐�
	new OperationExplanationBehavior(this);
}