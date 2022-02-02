#pragma once

// �O���錾
class ParticleComponent;

/// <summary>
/// �p�[�e�B�N���Q�[�W��UI
/// </summary>
class ParticleGauge : public GameObject
{
public:

	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="_owner"> �A�^�b�`�����Q�[���I�u�W�F�N�g�̃|�C���^ </param>
	/// <param name="_Scale"> �摜�̊g��T�C�Y </param>
	/// <param name="_TextureName"> �e�N�X�`���̃p�X </param>
	/// <param name="_ObjectTag"> �Q�[���I�u�W�F�N�g�̃^�O </param>
	/// <param name="_IsInitScaleChange"> �ŏ��ɃI�u�W�F�N�g�̑傫���̕ύX���s���� </param>
	ParticleGauge(GameObject* _owner, const Vector3& _Scale,
		const std::string& _TextureName, const Tag& _ObjectTag,
		const bool& _IsInitScaleChange = false);

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~ParticleGauge() {};

	/// <summary>
	/// �Q�[���I�u�W�F�N�g�̃A�b�v�f�[�g
	/// </summary>
	/// <param name="_deltaTime"> �Ō�̃t���[������������̂ɗv�������� </param>
	void UpdateGameObject(float _deltaTime)override;

private:

	// �G�l�~�[����̋����x�N�g��
	const Vector3 MOffset;

	// �A�^�b�`�����Q�[���I�u�W�F�N�g�̃|�C���^
	GameObject* mOwner;
};
