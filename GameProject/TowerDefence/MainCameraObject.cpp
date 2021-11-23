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
	, mCameraOffset(Vector3(-200.0f, -200.0f, -200.0f))
	, mTargetOffset(Vector3(0.0f, 0.0f, 70.0f))
	, mRotateZAngle(Math::Pi)
	, mRotateYAngle(0.5f)
	, mTargetPos(Vector3::Zero)
	, mInitPosition(Vector3::Zero)
	, mPlayerPtr(_playerPtr)
	, mBossPtr(_bossPtr)
{
	mTargetPos = mPlayerPtr->GetPosition() + mTargetOffset;
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

	mTargetPos = mPlayerPtr->GetPosition() + mTargetOffset;

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
	rotatePos.x = mCameraOffset.x * cosf(mRotateYAngle) * sinf(mRotateZAngle);
	rotatePos.y = mCameraOffset.y * cosf(mRotateYAngle) * cosf(mRotateZAngle);
	rotatePos.z = mCameraOffset.z * sinf(-mRotateYAngle);

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

	//if (_KeyState.m_keyboard.GetKeyState(SDL_SCANCODE_K) == Held)
	//{
	//	mCameraOffset.x += 1.0f;
	//}
	//if (_KeyState.m_keyboard.GetKeyState(SDL_SCANCODE_J) == Held)
	//{
	//	mCameraOffset.x -= 1.0f;
	//}
	//if (_KeyState.m_keyboard.GetKeyState(SDL_SCANCODE_I) == Held)
	//{
	//	mCameraOffset.y += 1.0f;
	//}
	//if (_KeyState.m_keyboard.GetKeyState(SDL_SCANCODE_M) == Held)
	//{
	//	mCameraOffset.y -= 1.0f;
	//}
	//if (_KeyState.m_keyboard.GetKeyState(SDL_SCANCODE_U) == Held)
	//{
	//	mCameraOffset.z += 1.0f;
	//}
	//if (_KeyState.m_keyboard.GetKeyState(SDL_SCANCODE_N) == Held)
	//{
	//	mCameraOffset.z -= 1.0f;
	//}

	//if (_KeyState.m_keyboard.GetKeyState(SDL_SCANCODE_H) == Held)
	//{
	//	mTargetOffset.x += 1.0f;
	//}
	//if (_KeyState.m_keyboard.GetKeyState(SDL_SCANCODE_G) == Held)
	//{
	//	mTargetOffset.x -= 1.0f;
	//}
	//if (_KeyState.m_keyboard.GetKeyState(SDL_SCANCODE_Y) == Held)
	//{
	//	mTargetOffset.y += 1.0f;
	//}
	//if (_KeyState.m_keyboard.GetKeyState(SDL_SCANCODE_B) == Held)
	//{
	//	mTargetOffset.y -= 1.0f;
	//}
	//if (_KeyState.m_keyboard.GetKeyState(SDL_SCANCODE_T) == Held)
	//{
	//	mTargetOffset.z += 1.0f;
	//}
	//if (_KeyState.m_keyboard.GetKeyState(SDL_SCANCODE_V) == Held)
	//{
	//	mTargetOffset.z -= 1.0f;
	//}

	//if (_KeyState.m_keyboard.GetKeyState(SDL_SCANCODE_P) == Released)
	//{
	//	mCameraOffset = Vector3(-200.0f, -200.0f, -200.0f);
	//	mTargetOffset = Vector3(0.0f, 0.0f, 60.0f);
	//}
}