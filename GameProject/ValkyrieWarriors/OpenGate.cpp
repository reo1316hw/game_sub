#include "pch.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="_owner"> �A�^�b�`����Q�[���I�u�W�F�N�g�̃|�C���^ </param>
/// <param name="_Axis"> �� </param>
/// <param name="_AddAngle"> ��]�p�𑝂₷���߂̒萔 </param>
/// <param name="_OpenToEnemyDefeatNum"> ����J�����߂ɓ|���G�l�~�[�̐� </param>
/// <param name="_enemysControlerPtr"> �G�l�~�[�𐧌䂷��R���|�[�l���g�N���X�̃|�C���^ </param>
/// <param name="_selfRotationPtr"> ���g����]���邽�߂̃R���|�[�l���g�N���X�̃|�C���^ </param>
OpenGate::OpenGate(GameObject* _owner, const Vector3& _Axis, const float& _AddAngle, const int& _OpenToDefeatEnemyNum,
	EnemysControler* _enemysControlerPtr, SelfRotation* _selfRotationPtr)
	: Component(_owner)
	, MOpenToDefeatEnemyNum(_OpenToDefeatEnemyNum)
	, MAddAngle(_AddAngle)
	, MOpenAngle(90.0f)
	, MAxis(_Axis)
	, mIsOpen(false)
	, mAngle(0.0f)
	, mEnemysControlerPtr(_enemysControlerPtr)
	, mSelfRotationPtr(_selfRotationPtr)
{
}

/// <summary>
/// �t���[�����̏���
/// </summary>
/// <param name="_deltaTime"> �Ō�̃t���[������������̂ɗv�������� </param>
void OpenGate::Update(float _deltaTime)
{
	if (Math::Abs(mAngle) > MOpenAngle)
	{
		mIsOpen = false;
		return;
	}

	if (mEnemysControlerPtr->GetDeadCount() >= MOpenToDefeatEnemyNum)
	{
		mIsOpen = true;
	}

	if (mIsOpen)
	{
		mAngle += MAddAngle;

		// ��]����
		mSelfRotationPtr->Rotation(MAxis, MAddAngle);
	}
}