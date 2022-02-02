#pragma once

// �O���錾
class CubeMapComponent;

/// <summary>
/// �X�J�C�{�b�N�X
/// </summary>
class SkyBoxObject : public GameObject
{
public:

	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="_ObjectTag"> �I�u�W�F�N�g�̃^�O </param>
	/// <param name="_ReUseGameObject"> �ė��p���邩�̃t���O </param>
	SkyBoxObject(const Tag& _ObjectTag, const bool& _ReUseGameObject);

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~SkyBoxObject() {};

private:

	// �L���[�u�}�b�vComponent�N���X�̃|�C���^
	CubeMapComponent* cubeMapComp;

public:// �Q�b�^�[�Z�b�^�[

	/// <summary>
	/// �L���[�u�}�b�v�R���|�[�l���g�N���X�̃|�C���^���擾
	/// </summary>
	/// <returns> �L���[�u�}�b�v�R���|�[�l���g�N���X�̃|�C���^ </returns>
	CubeMapComponent* GetCubeMapComp() { return cubeMapComp; }
};

