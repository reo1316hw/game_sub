#include "pch.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
PlayerObjectStateIdle::PlayerObjectStateIdle()
{
}

/// <summary>
/// �X�V����
/// </summary>
/// <param name="_owner"> �v���C���[(�e)�̃|�C���^ </param>
/// <param name="_DeltaTime"> �Ō�̃t���[������������̂ɗv�������� </param>
/// <returns> �v���C���[�̏�� </returns>
PlayerState PlayerObjectStateIdle::Update(PlayerObject* _owner, const float _DeltaTime)
{
    if (mIsSprint)
    {
        if (mIsRun)
        {
            return PlayerState::ePlayerStateSprintStart;
        }
    }
    else if (mIsRun)
    {
        return PlayerState::ePlayerStateRunLoop;
    }

    if (mIsAttack)
    {
        return PlayerState::ePlayerStateFirstAttack;
    }

    return PlayerState::ePlayerStateIdle;
}

/// <summary>
/// ���͏���
/// </summary>
/// <param name="_owner"> �v���C���[(�e)�̃|�C���^ </param>
/// <param name="_KeyState"> �L�[�{�[�h�A�}�E�X�A�R���g���[���[�̓��͏�� </param>
void PlayerObjectStateIdle::Input(PlayerObject* _owner, const InputState& _KeyState)
{
   //�����L�[�����͂��ꂽ��
    mIsRun = _KeyState.m_keyboard.GetKeyValue(SDL_SCANCODE_W) ||
             _KeyState.m_keyboard.GetKeyValue(SDL_SCANCODE_S) ||
             _KeyState.m_keyboard.GetKeyValue(SDL_SCANCODE_A) ||
             _KeyState.m_keyboard.GetKeyValue(SDL_SCANCODE_D);

    //��Shift�L�[�����͂��ꂽ��
    mIsSprint = _KeyState.m_keyboard.GetKeyValue(SDL_SCANCODE_LSHIFT);

    //Space�L�[�����͂��ꂽ��
    mIsAttack = _KeyState.m_keyboard.GetKeyValue(SDL_SCANCODE_SPACE);
}

/// <summary>
/// �v���C���[�̏�Ԃ��ύX���āA�ŏ���1�񂾂��Ăяo�����֐�
/// </summary>
/// <param name="_owner"> �v���C���[(�e)�̃|�C���^ </param>
/// <param name="_DeltaTime"> �Ō�̃t���[������������̂ɗv�������� </param>
void PlayerObjectStateIdle::Enter(PlayerObject* _owner, const float _DeltaTime)
{
    // �A�C�h����Ԃ̃A�j���[�V�����Đ�
    SkeletalMeshComponent* meshcomp = _owner->GetSkeletalMeshComponentPtr();
    meshcomp->PlayAnimation(_owner->GetAnimPtr(PlayerState::ePlayerStateIdle));
}
