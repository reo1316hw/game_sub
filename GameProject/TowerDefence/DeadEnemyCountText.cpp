#include "pch.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="_Pos"> UI�̐����ꏊ(�X�N���[�����W) </param>
/// <param name="_ObjectTag"> �A�^�b�`�����Q�[���I�u�W�F�N�g�̃^�O </param>
/// <param name="_enemysControlerPtr"> �G�l�~�[�����𐧌䂷��N���X�̃|�C���^ </param>
/// <param name="_Scale"> �e�N�X�`���̊g��T�C�Y </param>
DeadEnemyCountText::DeadEnemyCountText(const Vector3& _Pos, const Tag& _ObjectTag,
	EnemysControler* _enemysControlerPtr, const Vector3& _Scale)
	: GameObject(_ObjectTag)
{
	SetPosition(_Pos);
	SetScale(_Scale);

	// �e�N�X�`���̎擾
	Texture* texture = RENDERER->GetFontTexture(0);

	// �X�N���[����ɕ`�悷��R���|�[�l���g�N���X�𐶐�
	SpriteComponent* spriteComponentPtr = new SpriteComponent(this, texture);
	// �|�����G�l�~�[�̃J�E���gUI�̃e�N�X�`����ς���N���X�𐶐�
	new DeadEnemyCountTextChange(this, spriteComponentPtr, _enemysControlerPtr);
	// �|�����G�l�~�[���J�E���g����I�u�W�F�N�g�𖳌��ɂ���R���|�[�l���g�𐶐�
	new DeadEnemyCounterDisable(this, _enemysControlerPtr);
}