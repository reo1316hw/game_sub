#include "pch.h"

PlayerObjectStateSwordIdle::PlayerObjectStateSwordIdle()
{
    printf("Create : [PlayerObjectStateBase] PlayerObjectStateSwordIdle\n");
}

PlayerObjectStateSwordIdle::~PlayerObjectStateSwordIdle()
{
    printf("Remove : [PlayerObjectStateBase] PlayerObjectStateSwordIdle\n");
}

// �A�C�h����Ԃ��瑼�̏�Ԃւ̈ڍs
PlayerState PlayerObjectStateSwordIdle::Update(PlayerObject* _owner, float _deltaTime)
{
    if (mAttackFlag)
    {
        return PlayerState::PLAYER_STATE_ATTACK1;
    }

    if (mRunFlag)
    {
        return PlayerState::PLAYER_STATE_SWORD_RUN_LOOP;
    }

    if (mSwordDeliveryFlag)
    {
        return PlayerState::PLAYER_STATE_SWORD_DELIVERY;
    }

    return PlayerState::PLAYER_STATE_SWORD_IDLE;
}

void PlayerObjectStateSwordIdle::Inipt(PlayerObject* _owner, const InputState& _keyState)
{
    //// �W�����v�L�[�����͂��ꂽ��
   //if (sceneState.m_keyboard.GetKeyValue(SDL_SCANCODE_SPACE) == 1)
   //{
   //    return PlayerState::PLAYER_STATE_JUMPSTART;
   //}

   //�����L�[�����͂��ꂽ��
    mRunFlag = _keyState.m_keyboard.GetKeyValue(SDL_SCANCODE_W) ||
        _keyState.m_keyboard.GetKeyValue(SDL_SCANCODE_S) ||
        _keyState.m_keyboard.GetKeyValue(SDL_SCANCODE_A) ||
        _keyState.m_keyboard.GetKeyValue(SDL_SCANCODE_D);

    //Enter�L�[�����͂��ꂽ��
    mAttackFlag = _keyState.m_keyboard.GetKeyValue(SDL_SCANCODE_RETURN);

    //X�L�[�����͂��ꂽ��
    mSwordDeliveryFlag = _keyState.m_keyboard.GetKeyValue(SDL_SCANCODE_X);
}

void PlayerObjectStateSwordIdle::Enter(PlayerObject* _owner, float _deltaTime)
{
    // �A�C�h����Ԃ̃A�j���[�V�����Đ�
    SkeletalMeshComponent* meshcomp = _owner->GetSkeletalMeshComp();
    meshcomp->PlayAnimation(_owner->GetAnim(PlayerState::PLAYER_STATE_SWORD_IDLE));
}
