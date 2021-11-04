#include "pch.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="_playerPtr"> �v���C���[�̃|�C���^ </param>
/// <param name="_bossPtr"> �{�X�̃|�C���^ </param>
/// <param name="_ReUseGameObject"> �ė��p���邩�̃t���O </param>
MainCameraObject::MainCameraObject(PlayerObject* _playerPtr, BossObject* _bossPtr, const bool& _ReUseGameObject)
	: GameObject(Tag::eCamera, _ReUseGameObject)
	, MMinLookDownAngle(Math::ToRadians(0.0f))
	, MMaxLookDownAngle(Math::ToRadians(80.0f))
	, MRightAxisThreshold(0.3f)
	, MAddRotate(0.04f)
	, MCameraOffset(Vector3(-150.0f, -150.0f, -150.0f))
	, MTargetOffset(Vector3(0.0f, 0.0f, 40.0f))
	, mRotateZAngle(Math::Pi)
	, mRotateYAngle(0.5f)
	, mTargetPos(Vector3::Zero)
	, mInitPosition(Vector3::Zero)
	, mPlayerPtr(_playerPtr)
	, mBossPtr(_bossPtr)
{
	mTargetPos = mPlayerPtr->GetPosition() + MTargetOffset;
	SetPosition(mTargetPos);
}

/// <summary>
/// �I�u�W�F�N�g�̍X�V����
/// </summary>
/// <param name="_deltaTime"> �Ō�̃t���[������������̂ɗv�������� </param>
void MainCameraObject::UpdateGameObject(float _deltaTime)
{
	// �v���C���[���{�X��hp��0�ȉ��������珉�����W�ɖ߂�
	if (mPlayerPtr->GetHitPoint() <= 0 /*|| mBossPtr->GetHitPoint() <= 0*/)
	{
		mPosition = mInitPosition;
		SetPosition(mPosition);

		return;
	}

	mTargetPos = mPlayerPtr->GetPosition() + MTargetOffset;

	// ���~�낵�p�x�̊p�x����
	if (mRotateYAngle < MMinLookDownAngle)
	{
		mRotateYAngle = MMinLookDownAngle;
	}
	if (mRotateYAngle > MMaxLookDownAngle)
	{
		mRotateYAngle = MMaxLookDownAngle;
	}

	// ��]��̍��W
	Vector3 rotatePos;

	// ���[��]�E�s�b�`��]
	rotatePos.x = MCameraOffset.x * cosf(mRotateYAngle) * sinf(mRotateZAngle);
	rotatePos.y = MCameraOffset.y * cosf(mRotateYAngle) * cosf(mRotateZAngle);
	rotatePos.z = MCameraOffset.z * sinf(-mRotateYAngle);

	mPosition = rotatePos + mTargetPos;

	// ���������W�����鏈��
	Matrix4 view = Matrix4::CreateLookAt(mPosition, mTargetPos, Vector3::UnitZ);
	RENDERER->SetViewMatrix(view);
	SetPosition(mPosition);
}

/// <summary>
/// ���͂������Ŏ󂯎��X�V�֐�
/// ��{�I�ɂ����œ��͏���ϐ��ɕۑ���UpdateGameObject�ōX�V���s��
/// </summary>
/// <param name="_KeyState"> �L�[�{�[�h�A�}�E�X�A�R���g���[���[�̓��͏�� </param>
void MainCameraObject::GameObjectInput(const InputState& _KeyState)
{
	//�E�X�e�B�b�N�̓��͒l�̒l(-1~1)
	Vector2 rightAxis = _KeyState.m_controller.GetRAxisVec();

	// �R���g���[���[�̏\����������̓L�[�{�[�h�AW�����͂��ꂽ��z�𑫂�
	if (_KeyState.m_keyboard.GetKeyState(SDL_SCANCODE_UP) == Held)
	{
		mRotateYAngle -= MAddRotate;
	}
	// �R���g���[���[�̏\�����������́A�L�[�{�[�hS�����͂��ꂽ��-z�𑫂�
	if (_KeyState.m_keyboard.GetKeyState(SDL_SCANCODE_DOWN) == Held)
	{
		mRotateYAngle += MAddRotate;
	}
	//�R���g���[���[�̏\�����������́A�L�[�{�[�hA�����͂��ꂽ��-x�𑫂�
	if (_KeyState.m_keyboard.GetKeyState(SDL_SCANCODE_LEFT) == Held)
	{
		mRotateZAngle += MAddRotate;
	}
	// �R���g���[���[�̏\���E�������́A�L�[�{�[�hD�����͂��ꂽ��x�𑫂�
	if (_KeyState.m_keyboard.GetKeyState(SDL_SCANCODE_RIGHT) == Held)
	{
		mRotateZAngle -= MAddRotate;
	}

	//�E�X�e�B�b�N���͎��̑O�ړ�
	if (rightAxis.y <= -MRightAxisThreshold)
	{
		mRotateYAngle -= MAddRotate;
	}
	//�E�X�e�B�b�N���͎��̌�ړ�
	if (rightAxis.y >= MRightAxisThreshold)
	{
		mRotateYAngle += MAddRotate;
	}
	//�E�X�e�B�b�N���͎��̍��ړ�
	if (rightAxis.x <= -MRightAxisThreshold)
	{
		mRotateZAngle += MAddRotate;
	}
	//�E�X�e�B�b�N���͎��̉E�ړ�
	if (rightAxis.x >= MRightAxisThreshold)
	{
		mRotateZAngle -= MAddRotate;
	}
}