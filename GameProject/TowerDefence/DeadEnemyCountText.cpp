#include "pch.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="_Pos"> UI�̐����ꏊ(�X�N���[�����W) </param>
/// <param name="_ObjectTag"> �A�^�b�`�����Q�[���I�u�W�F�N�g�̃^�O </param>
/// <param name="_Scale"> �e�N�X�`���̊g��T�C�Y </param>
DeadEnemyCountText::DeadEnemyCountText(const Vector3& _Pos, const Tag& _ObjectTag, const Vector2& _Scale)
	: GameObject(_ObjectTag)
{
	SetPosition(_Pos);

	// �e�N�X�`���̎擾
	Texture* texture = RENDERER->GetFontTexture(101);

	// �X�N���[����ɕ`�悷��R���|�[�l���g�N���X
	new SpriteComponent(this, texture, _Scale);
}