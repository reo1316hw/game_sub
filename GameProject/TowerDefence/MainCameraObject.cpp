#include "pch.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
MainCameraObject::MainCameraObject() 
	: GameObject(Tag::eCamera,SceneBase::Scene::other,true)
	, MMinLookDownAngle(Math::ToRadians(0.0f))
	, MMaxLookDownAngle(Math::ToRadians(80.0f))
	, MRightAxisThreshold(0.3f)
	, MAddRotate(0.04f)
	, mHasTarget(false)
	, mRotateZAngle(Math::Pi)
	, mRotateYAngle(0.0f)
	, mOwnerOffset(Vector3::Zero)
	, mTargetPos(Vector3::Zero)
{
	SetPosition(Vector3(0,0,0));
	mTag = Tag::eCamera;
}

/// <summary>
/// �I�u�W�F�N�g�̍X�V����
/// </summary>
/// <param name="_deltaTime"> �Ō�̃t���[������������̂ɗv�������� </param>
void MainCameraObject::UpdateGameObject(float _deltaTime)
{
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
	rotatePos.x = mOwnerOffset.x * cosf(mRotateYAngle) * sinf(mRotateZAngle);
	rotatePos.y = mOwnerOffset.y * cosf(mRotateYAngle) * cosf(mRotateZAngle);
	rotatePos.z = mOwnerOffset.z * sinf(-mRotateYAngle);

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

/// <summary>
/// ���������W��ݒ�
/// </summary>
/// <param name="_Offset"> ���������W�Ƃ̍� </param>
/// <param name="_TargetPos"> ������W </param>
void MainCameraObject::SetViewObject(const Vector3 & _Offset, const Vector3 & _TargetPos)
{
	mHasTarget = true;
	mOwnerOffset = _Offset;
	mTargetPos = _TargetPos;
}
