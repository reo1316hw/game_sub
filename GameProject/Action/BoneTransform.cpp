
#include "BoneTransform.h"

/*
@fn �s����o��
@return ��]�ƕ��s�ړ�����A�s���Ԃ�
*/
Matrix4 BoneTransform::ToMatrix() const
{
	// ��]�ƕ��s�ړ�����A�s���Ԃ�
	Matrix4 rot = Matrix4::CreateFromQuaternion(mRotation);
	Matrix4 trans = Matrix4::CreateTranslation(mTranslation);

	return rot * trans;
}

/*
@fn �{�[�����
*/
BoneTransform BoneTransform::Interpolate(const BoneTransform& _a, const BoneTransform& _b, float _f)
{
	BoneTransform retVal;
	retVal.mRotation = Quaternion::Slerp(_a.mRotation, _b.mRotation, _f);        // a����b �ɐ��lf�ŋ��ʐ��`���(slerp)����
	retVal.mTranslation = Vector3::Lerp(_a.mTranslation, _b.mTranslation, _f);   // ���s�ړ�������f �Ő��`���(lerp)����
	return retVal;
}
