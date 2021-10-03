#include "pch.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
PlayerObjectStateDashAttack::PlayerObjectStateDashAttack()
	: MPlayerAttackSpeed(300.0f)
	, mNumFrame(0)
	, MPlayRate(1.5f)
	, MValidComboFrame(5)
{
}

/// <summary>
/// �X�V����
/// </summary>
/// <param name="_owner"> �v���C���[(�e)�̃|�C���^ </param>
/// <param name="_DeltaTime"> �Ō�̃t���[������������̂ɗv�������� </param>
/// <returns> �v���C���[�̏�� </returns>
PlayerState PlayerObjectStateDashAttack::Update(PlayerObject* _owner, const float _DeltaTime)
{
	// �t���[���������炵�Ă���
	if (mNumFrame > 0)
	{
		--mNumFrame;
	}

	// �U�����ݍ��݈ړ��̂��߂̃A�j���[�V�����Đ����Ԃ̌o�ߊ������v�Z
	mElapseTime += _DeltaTime;

	// �o�ߊ��������ƂɈړ�����
	Vector3 pos, forward;
	pos = _owner->GetPosition();
	forward = _owner->GetForward();
	float differencePos = -MPlayerAttackSpeed * _DeltaTime;
	pos += Quintic::EaseIn(mElapseTime, MPlayerAttackSpeed * _DeltaTime, differencePos, mTotalAnimTime) * forward;

	_owner->SetPosition(pos);

	// �A�j���[�V�������I��������A�C�h����Ԃ��A���̃R���{��
	if (!_owner->GetSkeletalMeshComponentPtr()->IsPlaying())
	{
		if (mIsNextCombo)
		{
			return PlayerState::ePlayerStateFirstAttack;
		}

		return PlayerState::ePlayerStateIdle;
	}

	return PlayerState::ePlayerStateDashAttack;
}

/// <summary>
/// ���͏���
/// </summary>
/// <param name="_owner"> �v���C���[(�e)�̃|�C���^ </param>
/// <param name="_KeyState"> �L�[�{�[�h�A�}�E�X�A�R���g���[���[�̓��͏�� </param>
void PlayerObjectStateDashAttack::Input(PlayerObject* _owner, const InputState& _KeyState)
{
	// �U���{�^�������ꂽ�玟�̃X�e�[�g�ֈڍs���鏀��
	if (mNumFrame <= MValidComboFrame && _KeyState.m_controller.GetButtonState(SDL_CONTROLLER_BUTTON_A) == Released ||
		mNumFrame <= MValidComboFrame && _KeyState.m_keyboard.GetKeyState(SDL_SCANCODE_SPACE) == Released)
	{
		mIsNextCombo = true;
	}
}

/// <summary>
/// �v���C���[�̏�Ԃ��ύX���āA�ŏ���1�񂾂��Ăяo�����֐�
/// </summary>
/// <param name="_owner"> �v���C���[(�e)�̃|�C���^ </param>
/// <param name="_DeltaTime"> �Ō�̃t���[������������̂ɗv�������� </param>
void PlayerObjectStateDashAttack::Enter(PlayerObject* _owner, const float _DeltaTime)
{
	// ATTACK1�̃A�j���[�V�����Đ�
	SkeletalMeshComponent* meshComp = _owner->GetSkeletalMeshComponentPtr();
	meshComp->PlayAnimation(_owner->GetAnimPtr(PlayerState::ePlayerStateDashAttack), MPlayRate);
	mIsNextCombo = false;

	// �A�j���[�V�����Đ����Ԏ擾
	mTotalAnimTime = _owner->GetAnimPtr(PlayerState::ePlayerStateDashAttack)->GetDuration() - 0.4f;
	mNumFrame = _owner->GetAnimPtr(PlayerState::ePlayerStateDashAttack)->GetNumFrames();
	mElapseTime = 0.0f;
}