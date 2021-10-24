#include "pch.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="_Pos"> UI�̐����ꏊ(�X�N���[�����W) </param>
/// <param name="_TextureName"> �e�N�X�`���̃p�X </param>
/// <param name="_ObjectTag"> �A�^�b�`�����Q�[���I�u�W�F�N�g�̃^�O </param>
/// <param name="_playerPtr"> �v���C���[�̃|�C���^ </param>
/// <param name="_Scale"> �摜�̊g��T�C�Y </param>
PlayerHitPointFrame::PlayerHitPointFrame(const Vector3& _Pos, const std::string& _TextureName,
	const Tag& _ObjectTag, const float& _Scale)
	: GameObject(_ObjectTag)
	, mSpritePtr(nullptr)
{
	SetPosition(_Pos);

	// �e�N�X�`���̎擾
	Texture* texture = RENDERER->GetTexture(_TextureName);

	// �X�N���[����ɕ`�悷��R���|�[�l���g�N���X
	mSpritePtr = new SpriteComponent(this, texture);
}