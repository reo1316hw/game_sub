#pragma once
#include "Math.h"
#include "BoneTransform.h"
#include <vector>
#include <string>

class BoneTransform;

/*
 @file Animation.h
 @fn Skeleton��p�����A�j���[�V�����̃f�[�^�N���X
*/
class Animation
{
public:

	/*
	@fn �A�j���[�V�����ǂݍ���
	@param �A�j���[�V�����ւ̃p�X
	*/
	bool Load(const std::string& _fileName, bool _loop);

private:

	//�A�j���[�V�����̂��߂̃{�[����
	size_t mNumBones;
	//�A�j���[�V�����̃t���[����
	size_t mNumFrames;
	//�A�j���[�V�����̍Đ�����
	float mDuration;
	//�A�j���[�V�����̃t���[���Ԃ̎���
	float mFrameDuration;
	/*
	�g���b�N��̊e�t���[���̕ϊ����B
	�O���̃x�N�g���̊e�C���f�b�N�X�̓{�[���A
	�����̃x�N�g���̓t���[���B�@�@�@�@�@�@�@
	mTracks[�{�[��][�t���[����]*/
	std::vector<std::vector<BoneTransform>> mTracks;

	// ���[�v�A�j���[�V�������邩�H
	bool mIsLoopAnimation;

public: //�Q�b�^�[�Z�b�^�[

	/*
	 @fn �{�[����
	*/
	size_t GetNumBones() const { return mNumBones; }                                
	/*
	 @fn �t���[����
	*/
	size_t GetNumFrames() const { return mNumFrames; }                              
	/*
	 @fn �A�j���[�V��������
	*/

	float GetDuration() const { return mDuration; }                               
	/*
	 @fn �t���[������
	*/
	float GetFrameDuration() const { return mFrameDuration; }     
	/*
	 @fn �A�j���[�V�����̓��[�v�A�j���[�V�������H
	*/
 	bool   IsLoopAnimation() const { return mIsLoopAnimation; }


	//�w�肳�ꂽ�z����A�A�j���[�V�����̎w�肳�ꂽ���ԂɁA
	//�e�{�[���̃O���[�o���i���݂́j�|�[�Y�}�g���b�N�X�Ŗ��߂�B
	//���Ԃ� > = 0.0f���� <= ���Ԃł���Ɨ\�z�����
	void GetGlobalPoseAtTime(std::vector<Matrix4>& _outPoses, const class Skeleton* _inSkeleton, float _inTime) const;
};
