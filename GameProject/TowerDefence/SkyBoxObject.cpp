#include "pch.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="_ObjectTag"> �I�u�W�F�N�g�̃^�O </param>
/// <param name="_ReUseGameObject"> �ė��p���邩�̃t���O </param>
SkyBoxObject::SkyBoxObject(const Tag& _ObjectTag, const bool& _ReUseGameObject)
	: GameObject(_ObjectTag, _ReUseGameObject)
{
	// �L���[�u�}�b�v�R���|�[�l���g�𐶐�
	cubeMapComp = new CubeMapComponent(this);
	// texture����
	cubeMapComp->CreateTexture("Assets/Texture/SkyBox/");
}