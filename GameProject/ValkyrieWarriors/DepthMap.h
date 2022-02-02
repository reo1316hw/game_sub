#pragma once

// �O���錾
class Shader;

/// <summary>
/// �����̎��_���炻�̃t���O�����g�܂ł̋����������_�����O�����[�x�e�N�X�`�����o�͂��邽�߂̃N���X
/// </summary>
class DepthMap
{
public:

	DepthMap();

	~DepthMap();

	void DepthRenderingBegin();

	void DepthRenderignEnd();

	void CreateShadowMap(unsigned int shadowMapSize);

	void CalcLightSpaceMatrix(const Vector3& _CenterWorldPos, const Vector3& _LightDir,const Vector3& _UpVec, const float _LightDistance);

private:

	// �f�v�X�}�b�v�t���[���o�b�t�@�I�u�W�F�N�g
	unsigned int  mDepthMapFBO;
	// �f�v�X�e�N�X�`��
	unsigned int  mDepthMap;
	// �f�v�X�}�b�v�T�C�Y
	unsigned int  mDepthMapSize;

	// �f�v�X�}�b�v�����_�����O�̎B�e���_
	Vector3 mLightOrigin;
	// �����x�N�g������
	Vector3 mLightDir;
	// ���C�g��ԍs��
	Matrix4 mLightSpaceMatrix;

	// �f�v�X�}�b�v�p�V�F�[�_�[
	Shader* mDepthShader;

public:// �Q�b�^�[�Z�b�^�[

	unsigned int  GetDepthTexID() { return mDepthMap; }

	Vector3& GetLightDir() { return mLightDir; }

	Vector3& GetLightOriginPos() { return mLightOrigin; }

	Matrix4& GetLightSpaceMatrix() { return mLightSpaceMatrix; }

	Shader* GetDepthMapShader() { return mDepthShader; }
};