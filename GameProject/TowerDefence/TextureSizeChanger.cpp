#include "pch.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="_owner"> �A�^�b�`�����I�u�W�F�N�g�̃|�C���^ </param>
/// <param name="_gameObjectPtr"> ���N���X�̃|�C���^ </param>
/// <param name="_IsInitScaleChange"> �ŏ��ɃI�u�W�F�N�g�̑傫���̕ύX���s���� </param>
TextureSizeChanger::TextureSizeChanger(GameObject* _owner, GameObject* _gameObjectPtr, const bool& _IsInitScaleChange)
	: Component(_owner)
	, mNowScaleLeftSideValue(0)
	, mScaleRightSideValue(0)
	, mInitScale(mOwner->GetScale())
	, mGameObjectPtr(_gameObjectPtr)
{
	if (_IsInitScaleChange)
	{
		mNowScaleLeftSideValue = 1;
	}
}

/// <summary>
/// �t���[�����̏���
/// </summary>
/// <param name="_deltaTime"> �Ō�̃t���[������������̂ɗv�������� </param>
void TextureSizeChanger::Update(float _deltaTime)
{
	// 1�t���[���O�̃X�P�[���T�C�Y�����߂邽�߂̍��ӂ̒l
	int mPreScaleLeftSideValue = mNowScaleLeftSideValue;
	// ���݂̃X�P�[���T�C�Y�����߂邽�߂̍��ӂ̒l
	mNowScaleLeftSideValue = mGameObjectPtr->GetScaleLeftSideValue();

	// 1�t���[���O�̍��ӂ̒l�ƌ��݂̍��ӂ̒l���������e�N�X�`���̉�����ύX
	if (mPreScaleLeftSideValue != mNowScaleLeftSideValue)
	{
		mScaleRightSideValue = static_cast<float>(mGameObjectPtr->GetScaleRightSideValue());
		// ���k��
		float scaleContractionRate = mNowScaleLeftSideValue / mScaleRightSideValue;
		// �A�^�b�`�����I�u�W�F�N�g�̑傫��
 		Vector3 scale = Vector3(mInitScale.x * scaleContractionRate, mInitScale.y, mInitScale.z);
		mOwner->SetScale(scale);
	}
}