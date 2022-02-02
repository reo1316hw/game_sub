#include "pch.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="_owner"> �A�^�b�`����Q�[���I�u�W�F�N�g�̃|�C���^ </param>
/// <param name="_UpdateOrder"> �R���|�[�l���g�̍X�V���ԁi���l���������قǑ����X�V�����j </param>
Component::Component(GameObject* _owner, int _updateOrder)
	: mOwner(_owner)
	, mUpdateOrder(_updateOrder)
{
	mOwner->AddComponent(this);
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
Component::~Component()
{
	mOwner->RemoveComponent(this);
}