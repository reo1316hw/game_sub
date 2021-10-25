#pragma once

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

	/// <summary>
	/// �A�j���[�V�����̍Đ�
	/// </summary>
	/// <param name="_AnimPtr"> �A�j���[�V�����f�[�^�N���X�̃|�C���^ </param>
	/// <param name="_PlayRate"> �A�j���[�V�����̍Đ����x </param>
	/// <returns> �A�j���[�V�����̎c�莞�� </returns>
	float PlayAnimation(const class Animation* _AnimPtr, const float& _PlayRate = 1.0f);

	// ���ݍĐ����̃A�j���[�V����
	const class Animation* GetNowPlayingAnimation() { return mAnimation; }
	// ���ݍĐ����̃A�j���[�V�����͍Đ������H true : �Đ��� false : �Đ��I��
	bool IsPlaying();

	int GetBoneIndexFromName(const char* _boneName) const;
	void GetMatrixFromBoneIndex(Matrix4& _boneWorldMatrix, int _boneIndex)const;

private:

	/*
	@fn �s��p���b�g�̌v�Z
	*/
	void ComputeMatrixPalette();

	// �q�b�g�X�g�b�v���I���^�C�~���O
	const int MHitStopEndTiming;

	// �q�b�g�X�g�b�v���邩
	bool mIsHitStop;

	// �q�b�g�X�g�b�v����t���[����
	int mHitStopCount;

	// �s��p���b�g
	MatrixPalette mPalette;
	// �X�P���g���f�[�^
	const class Skeleton* mSkeleton;
	// �A�j���[�V�����f�[�^
	const class Animation* mAnimation; 

	// �q�b�g�X�g�b�v���鎞�̃A�j���[�V�����̍Đ����x
	float mHitStopRate;
	// �A�j���[�V�����̍Đ����x
	float mAnimPlayRate;
	// �A�j���[�V��������
	float mAnimTime;

	//�X�P���g���f�[�^�ɏ�Z����F
	Vector3 mColor;

public://�Q�b�^�[�Z�b�^�[

	/*
	@param _skeleton �X�P���g���f�[�^
	*/
	void SetSkeleton(const class Skeleton* _skeleton) { mSkeleton = _skeleton; }
	/*
	@param _color �X�P���g���f�[�^�ɏ�Z����F
	*/
	void SetColor(const Vector3& _color) { mColor = _color; }

	/// <summary>
	/// �q�b�g�X�g�b�v���邩�̃t���O��ݒ�
	/// </summary>
	/// <param name="_IsHitStop"> �q�b�g�X�g�b�v���邩�̃t���O </param>
	void SetIsHitStop(const bool& _IsHitStop) { mIsHitStop = _IsHitStop; }
};
