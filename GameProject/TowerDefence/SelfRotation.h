#pragma once

/// <summary>
/// 自身を回転する
/// </summary>
class SelfRotation : public Component
{
public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
    /// <param name="_owner"> アタッチするゲームオブジェクトのポインタ </param>
	/// <param name="_Axis"> 軸 </param>
	/// <param name="_Angle"> 角度 </param>
	SelfRotation(GameObject* _owner, const Vector3& _Axis, const float& _Angle);

	/// <summary>
	/// デストラクタ
	/// </summary>
	~SelfRotation() {};

	/// <summary>
	/// 回転
	/// </summary>
	/// <param name="_Axis"> 軸 </param>
	/// <param name="_Angle"> 角度 </param>
	void Rotation(const Vector3& _Axis, const float& _Angle);

private:
};