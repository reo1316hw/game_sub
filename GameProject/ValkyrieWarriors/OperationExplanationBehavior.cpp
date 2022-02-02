#include "pch.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="_owner"> �A�^�b�`�����I�u�W�F�N�g�̃|�C���^ </param>
/// <param name="_playerPtr"> �v���C���[�̃|�C���^ </param>
OperationExplanationBehavior::OperationExplanationBehavior(GameObject* _owner, PlayerObject* _playerPtr)
	: Component(_owner)
	, MMoveSpeed(20.0f)
	, MStopForDistance(200000.0f)
	, MInitPosition(mOwner->GetPosition())
	, MRightDirVec(Vector3(1.0f, 0.0f, 0.0f))
	, MLeftDirVec(Vector3(-1.0f, 0.0f, 0.0f))
	, mIsDisable(false)
	, mPlayerPtr(_playerPtr)
{
}

/// <summary>
/// �t���[�����̏���
/// </summary>
/// <param name="_deltaTime"> �Ō�̃t���[������������̂ɗv�������� </param>
void OperationExplanationBehavior::Update(float _deltaTime)
{
	// ���W
	Vector3 position = mOwner->GetPosition();
	// ����
	Vector3 distance = position - MInitPosition;

	mIsDisable = false;
	mOwner->SetIsDisable(mIsDisable);

	if (mPlayerPtr->GetNowState() == PlayerState::ePlayerStateIdle &&
		distance.LengthSq() <= MStopForDistance)
	{
		// ���x
		Vector3 velocity = MLeftDirVec * MMoveSpeed;
		position += velocity;
		mOwner->SetPosition(position);

		return;
	}

	if (mPlayerPtr->GetNowState() == PlayerState::ePlayerStateIdle)
	{
		return;
	}

	if (distance.LengthSq() <= 0.0f)
	{
		mIsDisable = true;
		mOwner->SetIsDisable(mIsDisable);
		return;
	}

	// ���x
	Vector3 velocity = MRightDirVec * MMoveSpeed;
	position += velocity;
	mOwner->SetPosition(position);
}