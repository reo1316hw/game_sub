#include "pch.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="_playerPtr"> �v���C���[�̃|�C���^ </param>
/// <param name="_bossPtr"> �{�X�̃|�C���^ </param>
/// <param name="_gateList"> ��̃��X�g </param>
/// <param name="_ReUseGameObject"> �ė��p���邩�̃t���O </param>
MainCameraObject::MainCameraObject(PlayerObject* _playerPtr, BossObject* _bossPtr, std::vector<GateObject*> _gateList, const bool& _ReUseGameObject)
	: GameObject(Tag::eCamera, _ReUseGameObject)
	, MMinLookDownAngle(Math::ToRadians(0.0f))
	, MMaxLookDownAngle(Math::ToRadians(80.0f))
	, MRightAxisThreshold(0.3f)
	, MAddRotate(0.04f)
	, MCameraOffset(Vector3(-200.0f, -200.0f, -200.0f))
	, MTargetOffset(Vector3(0.0f, 0.0f, 70.0f))
	, mIsLookGate(false)
	, mIsInitOpenGate(true)
	, mGateListNum(1)
	, mRotateZAngle(Math::Pi)
	, mRotateYAngle(0.5f)
	, mTargetPos(Vector3::Zero)
	//, mNotLookGatePos(Vector3::Zero)
	//, mNotLookGateTargetPos(Vector3::Zero)
	, mInitPosition(Vector3::Zero)
	, mGatePos(Vector3::Zero)
	, mPlayerPtr(_playerPtr)
	, mBossPtr(_bossPtr)
	, mGateList(_gateList)
{
	for (auto gateItr : mGateList)
	{
		mOpenGateComponentList.emplace_back(gateItr->GetGateDoorPtr()->GetOpenGatePtr());
	}

	mTargetPos = mPlayerPtr->GetPosition() + MTargetOffset;
	SetPosition(mTargetPos);
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
MainCameraObject::~MainCameraObject()
{
	mGateList.clear();
	mOpenGateComponentList.clear();
}

/// <summary>
/// �I�u�W�F�N�g�̍X�V����
/// </summary>
/// <param name="_deltaTime"> �Ō�̃t���[������������̂ɗv�������� </param>
void MainCameraObject::UpdateGameObject(float _deltaTime)
{
	// �v���C���[���{�X��hp��0�ȉ��������珉�����W�ɖ߂�
	if (mPlayerPtr->GetHitPoint() <= 0 || mBossPtr->GetHitPoint() <= 0)
	{
		mPosition = mInitPosition;
		SetPosition(mPosition);

		return;
	}

	// �v���C���[�̍��W
	Vector3 playerPos = mPlayerPtr->GetPosition();

	// �咍�ڏ���
	if (mOpenGateComponentList[mGateListNum]->GetIsOpen())
	{
		if (mIsInitOpenGate)
		{
			mIsLookGate = true;
			// ��̍��W
			mGatePos = mGateList[mGateListNum]->GetPosition();

			mTargetPos = mGatePos + MTargetOffset;

			mIsInitOpenGate = false;
		}
		
		// �J�����Ɍ����x�N�g��
		Vector3 cameraToVec = mGatePos - playerPos;
		cameraToVec.Normalize();
		cameraToVec.z = -0.4f;

		mPosition = cameraToVec * MCameraOffset + playerPos;

		//mTargetPos = Vector3::Lerp(mTargetPos, mNotLookGateTargetPos, 0.05f);

		// ���������W�����鏈��
		Matrix4 view = Matrix4::CreateLookAt(mPosition, mTargetPos, Vector3::UnitZ);
		RENDERER->SetViewMatrix(view);
		SetPosition(mPosition);

		//// ��Ԓ��̍��W
		//Vector3 lerpPos = Vector3::Lerp(mPosition, mNotLookGatePos, 0.1f);

		//// ���������W�����鏈��
		//Matrix4 view = Matrix4::CreateLookAt(lerpPos, mTargetPos, Vector3::UnitZ);
		//RENDERER->SetViewMatrix(view);
		//SetPosition(lerpPos);

		return;
	}

	// �ŏ��̖傪���S�ɊJ������A���̖��Ώۂɂ��邽�߂ɔԍ���1���炷
	if (mIsLookGate && mGateListNum >= 1)
	{
		--mGateListNum;
	}

	// ���̍s�܂Ŏ��s���ꂽ���ɒ��ڂ��Ă��Ȃ��̂Ńt���O��߂�
	mIsLookGate = false;
	mIsInitOpenGate = true;

	mTargetPos = playerPos + MTargetOffset;
	//mNotLookGateTargetPos = mTargetPos;

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
	//mNotLookGatePos = mPosition;

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
	if (mOpenGateComponentList[mGateListNum]->GetIsOpen())
	{
		return;
	}

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