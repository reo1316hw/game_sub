#include "PlayerObjectStateIdle.h"
#include "InputSystem.h"
#include "SkeletalMeshComponent.h"
#include "AttackMeshComponent.h"

PlayerObjectStateIdle::PlayerObjectStateIdle(class AttackMeshComponent* _attackMesh, class SkeletalMeshComponent* _skMesh, const char* _AttachBoneName)
{
    mAttackMeshComponent = _attackMesh;
    mAttackBoneIndex = _skMesh->GetBoneIndexFromName(_AttachBoneName);

    mSwordDeliveryRot = Vector3(Math::Pi * 0.9, Math::Pi, Math::Pi * 0.5);
    mSwordDeliveryPos = Vector3(-10.0f, -20.0f, 160.0f);

    printf("Create : [PlayerObjectStateBase] PlayerObjectStateIdle\n");
}

PlayerObjectStateIdle::~PlayerObjectStateIdle()
{
    printf("Remove : [PlayerObjectStateBase] PlayerObjectStateIdle\n");
}

// �A�C�h����Ԃ��瑼�̏�Ԃւ̈ڍs
PlayerState PlayerObjectStateIdle::Update(PlayerObject* _owner, float _deltaTime)
{
    // ����̉~�������Z�b�g
    mAttackMeshComponent->SetOffsetRotation(mSwordDeliveryRot);
    // ����̍��W���Z�b�g
    mAttackMeshComponent->SetOffsetPosition(mSwordDeliveryPos);

    if (mSprintFlag)
    {
        if (mRunFlag)
        {
            return PlayerState::PLAYER_STATE_RUN_START;
        }
    }
    else if (mRunFlag)
    {
        return PlayerState::PLAYER_STATE_RUN_LOOP;
    }

    if (mDrawnSwordFlag)
    {
        return PlayerState::PLAYER_STATE_DRAWN_SWORD;
    }

    return PlayerState::PLAYER_STATE_IDLE;
}

void PlayerObjectStateIdle::Inipt(PlayerObject* _owner, const InputState& _keyState)
{
    //// �W�����v�L�[�����͂��ꂽ��
   //if (sceneState.Keyboard.GetKeyValue(SDL_SCANCODE_SPACE) == 1)
   //{
   //    return PlayerState::PLAYER_STATE_JUMPSTART;
   //}

   //�����L�[�����͂��ꂽ��
    mRunFlag = _keyState.m_keyboard.GetKeyValue(SDL_SCANCODE_W) ||
                 _keyState.m_keyboard.GetKeyValue(SDL_SCANCODE_S) ||
                 _keyState.m_keyboard.GetKeyValue(SDL_SCANCODE_A) ||
                 _keyState.m_keyboard.GetKeyValue(SDL_SCANCODE_D);

    //��Shift�L�[�����͂��ꂽ��
    mSprintFlag = _keyState.m_keyboard.GetKeyState(SDL_SCANCODE_LSHIFT);

    //X�L�[�����͂��ꂽ��
    mDrawnSwordFlag = _keyState.m_keyboard.GetKeyValue(SDL_SCANCODE_X);
}

void PlayerObjectStateIdle::Enter(PlayerObject* _owner, float _deltaTime)
{
    // �A�C�h����Ԃ̃A�j���[�V�����Đ�
    SkeletalMeshComponent* meshcomp = _owner->GetSkeletalMeshComp();
    meshcomp->PlayAnimation(_owner->GetAnim(PlayerState::PLAYER_STATE_IDLE));

    mAttackMeshComponent->SetAttackBoneIndex(mAttackBoneIndex);
}
