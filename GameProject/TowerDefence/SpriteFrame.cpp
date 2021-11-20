#include "pch.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="_Pos"> UI�̐����ꏊ(�X�N���[�����W) </param>
/// <param name="_TextureName"> �e�N�X�`���̃p�X </param>
/// <param name="_ObjectTag"> �Q�[���I�u�W�F�N�g�̃^�O </param>
/// <param name="_State"> �Q�[���I�u�W�F�N�g�̏�� </param>
/// <param name="_Scale"> �摜�̊g��T�C�Y </param>
SpriteFrame::SpriteFrame(const Vector3& _Pos, const std::string& _TextureName,
	const Tag& _ObjectTag, const State& _State, const Vector3& _Scale)
	: GameObject(_ObjectTag)
{
	SetPosition(_Pos);
	SetScale(_Scale);
	SetState(_State);

	// �e�N�X�`���̎擾
	Texture* texture = RENDERER->GetTexture(_TextureName);

	// �X�N���[����ɕ`�悷��R���|�[�l���g�N���X
	new SpriteComponent(this, texture);
}