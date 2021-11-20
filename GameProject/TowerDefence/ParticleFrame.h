#pragma once

// �O���錾
class ParticleComponent;

/// <summary>
/// �p�[�e�B�N���t���[����UI
/// </summary>
class ParticleFrame : public GameObject
{
public:

	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="_owner"> �A�^�b�`�����Q�[���I�u�W�F�N�g�̃|�C���^ </param>
	/// <param name="_Scale"> �摜�̊g��T�C�Y </param>
	/// <param name="_TextureName"> �e�N�X�`���̃p�X </param>
	/// <param name="_ObjectTag"> �Q�[���I�u�W�F�N�g�̃^�O </param>
	ParticleFrame(GameObject* _owner, const Vector3& _Scale,
		const std::string& _TextureName, const Tag& _ObjectTag);

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~ParticleFrame() {};

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

