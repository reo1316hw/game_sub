#include "pch.h"

SkeletalMeshComponent::SkeletalMeshComponent(GameObject* _owner)
	:MeshComponent(_owner, true)
	, mSkeleton(nullptr)
	, mColor(Vector3(0,0,0))
{
}

/*
@brief�@�`�揈��
@param	_shader �g�p����V�F�[�_�[�N���X�̃|�C���^
*/
void SkeletalMeshComponent::Draw(Shader* _shader)                 
{
	//�e�I�u�W�F�N�g�����X�V��ԂłȂ���
	if (mOwner->GetState() != State::eDead)
	{
		if (mMesh)
		{
			//���[���h�ϊ����Z�b�g
			_shader->SetMatrixUniform("uWorldTransform",
				mOwner->GetWorldTransform());
			// �s��p���b�g���Z�b�g    
			_shader->SetMatrixUniforms("uMatrixPalette", &mPalette.mEntry[0],
				MAX_SKELETON_BONES);
			//�X�y�L�����[���x���Z�b�g
			_shader->SetFloatUniform("uSpecPower", 100);

			_shader->SetVectorUniform("uColor", mColor);
			//  �e�N�X�`�����Z�b�g 
			Texture* t = mMesh->GetTexture(mTextureIndex);
			if (t)
			{
				glActiveTexture(GL_TEXTURE0);
				glBindTexture(GL_TEXTURE_2D, t->GetTextureID());
				_shader->SetIntUniform("uMeshTexture", 0);
			}
			//���b�V���̒��_�z����A�N�e�B�u��
			VertexArray* va = mMesh->GetVertexArray();
			va->SetActive();
			//�`��
			glDrawElements(GL_TRIANGLES, va->GetNumIndices(), GL_UNSIGNED_INT, nullptr);
		}
	}
}

void SkeletalMeshComponent::Update(float _deltaTime)
{
	if (mAnimation && mSkeleton)
	{
		mAnimTime += _deltaTime * mAnimPlayRate;

		// �A�j���[�V���������[�v�A�j���[�V�����Ȃ犪���߂�����
		if (mAnimation->IsLoopAnimation())
		{
			while (mAnimTime > mAnimation->GetDuration())
			{
				mAnimTime -= mAnimation->GetDuration();
			}
		}
		// ���[�v���Ȃ��A�j���ōĐ����Ԓ�������ŏI���Ԃ܂łƂ���
		else if (mAnimTime > mAnimation->GetDuration())
		{
			mAnimTime = mAnimation->GetDuration();
		}
		// �s��p���b�g�̍Čv�Z
		ComputeMatrixPalette();
	}
	
}

float SkeletalMeshComponent::PlayAnimation(const Animation* _anim, float _playRate) 
{
	mAnimation = _anim;
	mAnimTime = 0.0f;
	mAnimPlayRate = _playRate;

	if (!mAnimation)
	{
		return 0.0f;
	}

	ComputeMatrixPalette();

	return mAnimation->GetDuration();
}

// ���݃A�j���[�V�����Đ������H true : �Đ��� / false : �Đ��I��
bool SkeletalMeshComponent::IsPlaying()
{
	if (!mAnimation->IsLoopAnimation())
	{
		if (mAnimTime >= mAnimation->GetDuration())
		{
			return false;
		}
	}
	return true;
}

// �{�[�����̕����񂩂�{�[���C���f�b�N�X������
int SkeletalMeshComponent::GetBoneIndexFromName(const char* _boneName) const
{
	std::string name;
	name = _boneName;
	return mSkeleton->GetBoneIndexFromName(name);
}

// �{�[���C���f�b�N�X�l���炻�̃{�[���̍ŏI���[���h�s���Ԃ�
void SkeletalMeshComponent::GetMatrixFromBoneIndex(Matrix4& _boneWorldMatrix, int _boneIndex) const
{
	_boneWorldMatrix = mPalette.mEntry[_boneIndex] * mOwner->GetWorldTransform();
}

void SkeletalMeshComponent::ComputeMatrixPalette()                             
{
	// �O���[�o���t�o�C���h�s��z��̎擾
	const std::vector<Matrix4>& globalInvBindPoses = mSkeleton->GetGlobalInvBindPoses();
	// ���݂̃|�[�Y�s��
	std::vector<Matrix4> currentPoses;                                        
	// �A�j���������_�̃O���[�o���|�[�Y�̎擾
	mAnimation->GetGlobalPoseAtTime(currentPoses, mSkeleton, mAnimTime);
	// ���ꂼ��̃{�[���̍s��p���b�g�̃Z�b�g                                    
	for (size_t i = 0; i < mSkeleton->GetNumBones(); i++)
	{
		//�s��p���b�g[i] = �O���[�o���t�o�C���h�s��[i]�@�~�@���݂̃|�[�Y�s��[i]  (i�̓{�[��ID)         
		mPalette.mEntry[i] = globalInvBindPoses[i] * currentPoses[i];
	}
}
