#include "pch.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="_owner"> �A�^�b�`�����Q�[���I�u�W�F�N�g�̃|�C���^ </param>
/// <param name="_Pos"> UI�̐����ꏊ(�X�N���[�����W) </param>
/// <param name="_TextureName"> �e�N�X�`���̃p�X </param>
/// <param name="_ObjectTag">�Q�[���I�u�W�F�N�g�̃^�O </param>
/// <param name="_State"> �Q�[���I�u�W�F�N�g�̏�� </param>
/// <param name="_Scale"> �摜�̊g��T�C�Y </param>
/// <param name="_IsInitScaleChange"> �ŏ��ɃI�u�W�F�N�g�̑傫���̕ύX���s���� </param>
SpriteGauge::SpriteGauge(GameObject* _owner, const Vector3& _Pos, const std::string& _TextureName,
	const Tag& _ObjectTag, const State& _State, const Vector3& _Scale, const bool& _IsInitScaleChange)
	: GameObject(_ObjectTag)
{
	SetPosition(_Pos);
	SetScale(_Scale);
	SetState(_State);

	// �e�N�X�`���̎擾
	Texture* texture = RENDERER->GetTexture(_TextureName);

	// hp�Q�[�W�𐧌䂷��R���|�[�l���g�N���X
	TextureSizeChanger* textureSizeChangerPtr = new TextureSizeChanger(this, _owner, _IsInitScaleChange);

	// �X�N���[����ɕ`�悷��R���|�[�l���g�N���X
	new SpriteComponent(this, texture);
}

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="_owner"> �A�^�b�`�����Q�[���I�u�W�F�N�g�̃|�C���^ </param>
/// <param name="_Pos"> UI�̐����ꏊ(�X�N���[�����W) </param>
/// <param name="_TextureName"> �e�N�X�`���̃p�X </param>
/// <param name="_ObjectTag">�Q�[���I�u�W�F�N�g�̃^�O </param>
/// <param name="_State"> �Q�[���I�u�W�F�N�g�̏�� </param>
/// <param name="_enemyObjectManagerPtr"> �G�l�~�[���Ǘ�����N���X�̊��N���X�̃|�C���^ </param>
/// <param name="_Scale"> �摜�̊g��T�C�Y </param>
/// <param name="_IsInitScaleChange"> �ŏ��ɃI�u�W�F�N�g�̑傫���̕ύX���s���� </param>
SpriteGauge::SpriteGauge(GameObject* _owner, const Vector3& _Pos, const std::string& _TextureName,
	const Tag& _ObjectTag, const State& _State, EnemyObjectManager* _enemyObjectManagerPtr,
	const Vector3& _Scale, const bool& _IsInitScaleChange)
	: GameObject(_ObjectTag)
{
	SetPosition(_Pos);
	SetScale(_Scale);
	SetState(_State);

	// �e�N�X�`���̎擾
	Texture* texture = RENDERER->GetTexture(_TextureName);

	// hp�Q�[�W�𐧌䂷��R���|�[�l���g�N���X
	TextureSizeChanger* textureSizeChangerPtr = new TextureSizeChanger(this, _owner, _IsInitScaleChange);

	// �X�N���[����ɕ`�悷��R���|�[�l���g�N���X
	new SpriteComponent(this, texture);

	// �I�u�W�F�N�g�𖳌��ɂ���R���|�[�l���g�𐶐�
	new ActiveObjectDisable(this, _enemyObjectManagerPtr);
}