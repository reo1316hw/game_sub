#pragma once

/// <summary>
/// �{�X��hp�Q�[�W
/// </summary>
class BossHitPointGauge : public GameObject
{
public:

	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="_Pos"> UI�̐����ꏊ(�X�N���[�����W) </param>
	/// <param name="_TextureName"> �e�N�X�`���̃p�X </param>
	/// <param name="_ObjectTag"> �Q�[���I�u�W�F�N�g�̃^�O </param>
	/// <param name="_bossPtr"> �v���C���[�̃|�C���^ </param>
	/// <param name="_Scale"> �e�N�X�`���̊g��T�C�Y </param>
	BossHitPointGauge(const Vector3& _Pos, const std::string& _TextureName, const Tag& _ObjectTag,
		BossObject* _bossPtr, const Vector3& _Scale = Vector3(1.0f, 1.0f, 1.0f));

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~BossHitPointGauge() {};

private:
};