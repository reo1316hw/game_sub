
#include "BoneTransform.h"

/*
@fn 行列を出力
@return 回転と平行移動から、行列を返す
*/
Matrix4 BoneTransform::ToMatrix() const
{
	// 回転と平行移動から、行列を返す
	Matrix4 rot = Matrix4::CreateFromQuaternion(mRotation);
	Matrix4 trans = Matrix4::CreateTranslation(mTranslation);

	return rot * trans;
}

/*
@fn ボーン補間
*/
BoneTransform BoneTransform::Interpolate(const BoneTransform& _a, const BoneTransform& _b, float _f)
{
	BoneTransform retVal;
	retVal.mRotation = Quaternion::Slerp(_a.mRotation, _b.mRotation, _f);        // aからb に数値fで球面線形補間(slerp)する
	retVal.mTranslation = Vector3::Lerp(_a.mTranslation, _b.mTranslation, _f);   // 平行移動成分はf で線形補間(lerp)する
	return retVal;
}
