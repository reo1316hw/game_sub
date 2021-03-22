#pragma once

/*
@file FPS.h
@brief �t���[���ɂ����������Ԃ��v���������݂���N���X
*/
class FPS
{
public:
	FPS();
	~FPS();

	/*
	@brief	�t���[�����̏���
	*/
	void Update();
private:
	/*
	@brief	FPS���ݒ�l���傫���Ȃ�Ȃ����߂̐���
	*/
	void Wait();
	//�t���[�����[�g�̍ō��l
	const Uint32 mSetFps;				
	//�P�t���[���ɂ����鎞��
	const Uint32 mOneFrameTickCount;		
	//�t���[���̃J�E���^�[
	Uint32 mFpsCount;					
	//FPS�̌v�Z���n�߂����̎���
	Uint32 mFrameStartTickTime;			
	//�v�Z�����t���[�����[�g
	Uint32 mFps;							
	//�O�̃t���[���̂�����������
	int mBeforetickCount;				
	//���݂̃t���[���̂�����������
	float mDeltaTime;					
public://�Q�b�^�[�Z�b�^�[
	/*
	@return ���݂̃t���[���ɂ�����������
	*/
	float GetDeltaTime() { return mDeltaTime; }
};

