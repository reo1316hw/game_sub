#pragma once
#include "MeshComponent.h"
#include "MatrixPalette.h"

/*
@file SkeletalMeshComponent.h
@brief �X�P���g���f�[�^�̕`��ƃA�j���[�V����
*/
class SkeletalMeshComponent : public MeshComponent
{
public:
	SkeletalMeshComponent(class GameObject* _owner);

	void Update(float _deltaTime) override;

	/*
	@brief�@�`�揈��
	@param	_shader �g�p����V�F�[�_�[�N���X�̃|�C���^
	*/
	void Draw(class Shader* _shader) override;

   	/*
	@fn �A�j���[�V�����̍Đ�
	@param _anim �A�j���[�V�����f�[�^�N���X
	@param _playRate �A�j���[�V�����̍Đ����x
	@return �A�j���[�V�����̎c�莞��
	*/
	float PlayAnimation(const class Animation* _anim, float _playRate = 1.0f);

	// ���ݍĐ����̃A�j���[�V����
	const class Animation* GetNowPlayingAnimation() { return animation; }
	// ���ݍĐ����̃A�j���[�V�����͍Đ������H true : �Đ��� false : �Đ��I��
	bool IsPlaying();

	int GetBoneIndexFromName(const char* _boneName) const;
	void GetMatrixFromBoneIndex(Matrix4& _boneWorldMatrix, int boneIndex)const;

protected:
	/*
	@fn �s��p���b�g�̌v�Z
	*/
	void ComputeMatrixPalette();                                       
	// �s��p���b�g
	MatrixPalette mPalette;
	// �X�P���g���f�[�^
	const class Skeleton* mSkeleton;                                       
	// �A�j���[�V�����f�[�^
	const class Animation* animation;                                     
	// �A�j���[�V�����̍Đ����x
	float animPlayRate;                                                  
	// �A�j���[�V��������
	float animTime;                                                       
	//�X�P���g���f�[�^�ɏ�Z����F
	Vector3 color;
public://�Q�b�^�[�Z�b�^�[
	/*
	@param _skeleton �X�P���g���f�[�^
	*/
	void SetSkeleton(const class Skeleton* _skeleton) { mSkeleton = _skeleton; }
	/*
	@param _color �X�P���g���f�[�^�ɏ�Z����F
	*/
	void SetColor(const Vector3& _color) { color = _color; }
};
