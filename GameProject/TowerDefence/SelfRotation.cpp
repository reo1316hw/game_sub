#include "pch.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="_owner"> �A�^�b�`����Q�[���I�u�W�F�N�g�̃|�C���^ </param>
/// <param name="_Axis"> �� </param>
/// <param name="_Angle"> �p�x </param>
SelfRotation::SelfRotation(GameObject* _owner, const Vector3& _Axis, const float& _Angle)
	: Component(_owner)
{
	// ��]����
	Rotation(_Axis, _Angle);
}

/// <summary>
/// ��]
/// </summary>
/// <param name="_Axis"> �� </param>
/// <param name="_Angle"> �p�x </param>
void SelfRotation::Rotation(const Vector3& _Axis, const float& _Angle)
{
	float radian = Math::ToRadians(_Angle);
	Quaternion rot = mOwner->GetRotation();
	Quaternion inc(_Axis, radian);
	Quaternion target = Quaternion::Concatenate(rot, inc);
	mOwner->SetRotation(target);
}