#include "pch.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="_Pos"> UI�̐����ꏊ(�X�N���[�����W) </param>
/// <param name="_ObjectTag"> �A�^�b�`�����Q�[���I�u�W�F�N�g�̃^�O </param>
/// <param name="_State"> �Q�[���I�u�W�F�N�g�̏�� </param>
/// <param name="_FontDataNum"> �t�H���g�e�N�X�`���z��̗v�f�� </param>
/// <param name="_DefeatEnemyNum">  �|���G�l�~�[�̐� </param>
/// <param name="_enemysControlerPtr"> �G�l�~�[�����𐧌䂷��N���X�̃|�C���^ </param>
/// <param name="_Scale"> �e�N�X�`���̊g��T�C�Y </param>
DefeatEnemyNumberText::DefeatEnemyNumberText(const Vector3& _Pos, const Tag& _ObjectTag, const State& _State,
	const int& _FontDataNum, const int& _DefeatEnemyNum, EnemysControler* _enemysControlerPtr, const Vector3& _Scale)
	: GameObject(_ObjectTag)
{
	SetPosition(_Pos);
	SetScale(_Scale);
	SetState(_State);

	// �e�N�X�`���̎擾
	Texture* texture = RENDERER->GetFontTexture(_FontDataNum);

	// �X�N���[����ɕ`�悷��R���|�[�l���g�N���X
	new SpriteComponent(this, texture);
	// �|�����G�l�~�[���J�E���g����I�u�W�F�N�g�𖳌��ɂ���R���|�[�l���g�𐶐�
	new DeadEnemyCounterDisable(this, _DefeatEnemyNum, _enemysControlerPtr);
}