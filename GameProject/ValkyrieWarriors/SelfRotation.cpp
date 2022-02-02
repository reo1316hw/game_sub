#include "pch.h"

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="_owner"> アタッチするゲームオブジェクトのポインタ </param>
/// <param name="_Axis"> 軸 </param>
/// <param name="_Angle"> 角度 </param>
SelfRotation::SelfRotation(GameObject* _owner, const Vector3& _Axis, const float& _Angle)
	: Component(_owner)
{
	// 回転処理
	Rotation(_Axis, _Angle);
}

/// <summary>
/// 回転
/// </summary>
/// <param name="_Axis"> 軸 </param>
/// <param name="_Angle"> 角度 </param>
void SelfRotation::Rotation(const Vector3& _Axis, const float& _Angle)
{
	float radian = Math::ToRadians(_Angle);
	Quaternion rot = mOwner->GetRotation();
	Quaternion inc(_Axis, radian);
	Quaternion target = Quaternion::Concatenate(rot, inc);
	mOwner->SetRotation(target);
}