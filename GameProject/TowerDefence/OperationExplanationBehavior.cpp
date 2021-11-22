#include "pch.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="_owner"> �A�^�b�`�����I�u�W�F�N�g�̃|�C���^ </param>
/// <param name="_playerPtr"> �v���C���[�̃|�C���^ </param>
OperationExplanationBehavior::OperationExplanationBehavior(GameObject* _owner, PlayerObject* _playerPtr)
	: Component(_owner)
	, MInitPosition(mOwner->GetPosition())
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

	if (distance.LengthSq() <= 50000.0f)
	{
		// ���x
		Vector3 velocity = Vector3(-1.0f, 0.0f, 0.0f) * 20.0f;
		position += velocity;
		mOwner->SetPosition(position);

		return;
	}

	if (mPlayerPtr->GetPlayerState() == PlayerState::ePlayerStateIdle)
	{
		return;
	}

	if (distance.LengthSq() <= 0.0f)
	{
		return;
	}

	// ���x
	Vector3 velocity = Vector3(1.0f, 0.0f, 0.0f) * 20.0f;
	position += velocity;
	mOwner->SetPosition(position);
}