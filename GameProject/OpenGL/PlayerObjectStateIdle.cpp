#include "pch.h"

PlayerObjectStateIdle::PlayerObjectStateIdle()
{
    printf("Create : [PlayerObjectStateBase] PlayerObjectStateIdle\n");
}

PlayerObjectStateIdle::~PlayerObjectStateIdle()
{
    printf("Remove : [PlayerObjectStateBase] PlayerObjectStateIdle\n");
}

// �A�C�h����Ԃ��瑼�̏�Ԃւ̈ڍs
PlayerState PlayerObjectStateIdle::Update(PlayerObject* _owner, float _deltaTime)
{
    if (mSprintFlag)
    {
        if (mRunFlag)
        {
            return PlayerState::ePlayerStateSprintStart;
        }
    }
    else if (mRunFlag)
    {
        return PlayerState::ePlayerStateRunLoop;
    }

    if (mAttackFlag)
    {
        return PlayerState::ePlayerStateFirstAttack;
    }

    return PlayerState::ePlayerStateIdle;
}

void PlayerObjectStateIdle::Inipt(PlayerObject* _owner, const InputState& _keyState)
{
    //��Shift�L�[�����͂��ꂽ��
    mSprintFlag = _keyState.m_keyboard.GetKeyState(SDL_SCANCODE_LSHIFT);

   //�����L�[�����͂��ꂽ��
    mRunFlag = _keyState.m_keyboard.GetKeyValue(SDL_SCANCODE_W) ||
        _keyState.m_keyboard.GetKeyValue(SDL_SCANCODE_S) ||
        _keyState.m_keyboard.GetKeyValue(SDL_SCANCODE_A) ||
        _keyState.m_keyboard.GetKeyValue(SDL_SCANCODE_D);

    //Enter�L�[�����͂��ꂽ��
    mAttackFlag = _keyState.m_keyboard.GetKeyValue(SDL_SCANCODE_SPACE);
}

void PlayerObjectStateIdle::Enter(PlayerObject* _owner, float _deltaTime)
{
    // �A�C�h����Ԃ̃A�j���[�V�����Đ�
    SkeletalMeshComponent* meshcomp = _owner->GetSkeletalMeshComp();
    meshcomp->PlayAnimation(_owner->GetAnim(PlayerState::ePlayerStateIdle));
}
