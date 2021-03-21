#include "SkeletalMeshComponent.h"
#include "Shader.h"
#include "Mesh.h"
#include "GameObject.h"
#include "Game.h"
#include "Renderer.h"
#include "Texture.h"
#include "VertexArray.h"
#include "Animation.h"
#include "Skeleton.h"
#include "GameObject.h"

SkeletalMeshComponent::SkeletalMeshComponent(GameObject* _owner)
	:MeshComponent(_owner, true)
	, mSkeleton(nullptr)
	, color(Vector3(0,0,0))
{
}

/*
@brief�@�`�揈��
@param	_shader �g�p����V�F�[�_�[�N���X�̃|�C���^
*/
void SkeletalMeshComponent::Draw(Shader* _shader)                 
{
	//�e�I�u�W�F�N�g�����X�V��ԂłȂ���
	if (mOwner->GetState() != State::Dead)
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

			_shader->SetVectorUniform("uColor", color);
			//  �e�N�X�`�����Z�b�g 
			Texture* t = mMesh->GetTexture(textureIndex);
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
		if (animation && mSkeleton)
		{
			animTime += _deltaTime * animPlayRate;

			// �A�j���[�V���������[�v�A�j���[�V�����Ȃ犪���߂�����
			if (animation->IsLoopAnimation())
			{
				while (animTime > animation->GetDuration())
				{
					animTime -= animation->GetDuration();
				}
			}
			// ���[�v���Ȃ��A�j���ōĐ����Ԓ�������ŏI���Ԃ܂łƂ���
			else if (animTime > animation->GetDuration())
			{
				animTime = animation->GetDuration();
			}
			// �s��p���b�g�̍Čv�Z
			ComputeMatrixPalette();
		}
	
}

float SkeletalMeshComponent::PlayAnimation(const Animation* _anim, float _playRate) 
{
	animation = _anim;
	animTime = 0.0f;
	animPlayRate = _playRate;

	if (!animation)
	{
		return 0.0f;
	}

	ComputeMatrixPalette();

	return animation->GetDuration();
}

// ���݃A�j���[�V�����Đ������H true : �Đ��� / false : �Đ��I��
bool SkeletalMeshComponent::IsPlaying()
{
	if (!animation->IsLoopAnimation())
	{
		if (animTime >= animation->GetDuration())
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
void SkeletalMeshComponent::GetMatrixFromBoneIndex(Matrix4& boneWorldMatrix, int boneIndex) const
{
	boneWorldMatrix = mPalette.mEntry[boneIndex] * mOwner->GetWorldTransform();
}

void SkeletalMeshComponent::ComputeMatrixPalette()                             
{
	// �O���[�o���t�o�C���h�s��z��̎擾
	const std::vector<Matrix4>& globalInvBindPoses = mSkeleton->GetGlobalInvBindPoses();
	// ���݂̃|�[�Y�s��
	std::vector<Matrix4> currentPoses;                                        
	// �A�j���������_�̃O���[�o���|�[�Y�̎擾
	animation->GetGlobalPoseAtTime(currentPoses, mSkeleton, animTime);
	// ���ꂼ��̃{�[���̍s��p���b�g�̃Z�b�g                                    
	for (size_t i = 0; i < mSkeleton->GetNumBones(); i++)
	{
		//�s��p���b�g[i] = �O���[�o���t�o�C���h�s��[i]�@�~�@���݂̃|�[�Y�s��[i]  (i�̓{�[��ID)         
		mPalette.mEntry[i] = globalInvBindPoses[i] * currentPoses[i];
	}
}
