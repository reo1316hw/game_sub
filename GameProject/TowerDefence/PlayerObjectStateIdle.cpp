#include "pch.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
PlayerObjectStateIdle::PlayerObjectStateIdle()
    : mHitTagList{ Tag::eEnemyAttackDecision, Tag::eFrontCoreMagicEffect, Tag::eAreaMagicEffect, Tag::eOverheadMagicEffect }
    , MDamageValueEnemyAttack(25)
    , MLeftAxisThreshold(0.5f)
    , mIsDamage(false)
    , mDamageValue(0)
    , mHitTagListSize(sizeof(mHitTagList) / sizeof(int))
    , mHitTag(Tag::eOther)
    , mPosition(Vector3::Zero)
    , mPlayerPtr(nullptr)
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
    // ���W
    mPosition = _owner->GetPosition();
    _owner->SetPosition(mPosition);

    if (mIsDamage)
    {
        return PlayerState::ePlayerStateDamage;
    }

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
    else if (mIsAttack)
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
             _KeyState.m_keyboard.GetKeyValue(SDL_SCANCODE_D) ||
             _KeyState.m_controller.GetButtonValue(SDL_CONTROLLER_BUTTON_DPAD_UP) ||
             _KeyState.m_controller.GetButtonValue(SDL_CONTROLLER_BUTTON_DPAD_DOWN) ||
             _KeyState.m_controller.GetButtonValue(SDL_CONTROLLER_BUTTON_DPAD_LEFT) ||
             _KeyState.m_controller.GetButtonValue(SDL_CONTROLLER_BUTTON_DPAD_RIGHT);

    //���X�e�B�b�N�̓��͒l�̒l(-1~1)
    Vector2 leftAxis = _KeyState.m_controller.GetLAxisVec();

    if (leftAxis.LengthSq() >= MLeftAxisThreshold)
    {
        mIsRun = true;
    }

    //��Shift�L�[�����͂��ꂽ��
    mIsSprint = _KeyState.m_controller.GetButtonValue(SDL_CONTROLLER_BUTTON_RIGHTSHOULDER) ||
                _KeyState.m_keyboard.GetKeyValue(SDL_SCANCODE_LSHIFT);

    //Space�L�[�����͂��ꂽ��
    mIsAttack = _KeyState.m_controller.GetButtonValue(SDL_CONTROLLER_BUTTON_Y) ||
                _KeyState.m_keyboard.GetKeyValue(SDL_SCANCODE_SPACE);
}

/// <summary>
/// �v���C���[�̏�Ԃ��ύX���āA�ŏ���1�񂾂��Ăяo�����֐�
/// </summary>
/// <param name="_owner"> �v���C���[(�e)�̃|�C���^ </param>
/// <param name="_DeltaTime"> �Ō�̃t���[������������̂ɗv�������� </param>
void PlayerObjectStateIdle::Enter(PlayerObject* _owner, const float _DeltaTime)
{
    // �ҋ@��Ԃ̃A�j���[�V�����Đ�
    SkeletalMeshComponent* meshcomp = _owner->GetSkeletalMeshComponentPtr();
    meshcomp->PlayAnimation(_owner->GetAnimPtr(PlayerState::ePlayerStateIdle));
    mIsDamage = false;

    mIsIdle = true;
    _owner->SetIsEnable(mIsIdle);
}

/// <summary>
/// �q�b�g�������̏���
/// </summary>
/// <param name="_owner"> �v���C���[(�e)�̃|�C���^ </param>
/// <param name="_HitObject"> �q�b�g�����Q�[���I�u�W�F�N�g </param>
void PlayerObjectStateIdle::OnCollision(PlayerObject* _owner, const GameObject& _HitObject)
{
    mPlayerPtr = _owner;
 
    // �I�u�W�F�N�g�̃^�O
    mHitTag = _HitObject.GetTag();

    for (int i = 0; i < mHitTagListSize; i++)
    {
        // �U�����󂯂����̏���
        if (ReceivedAttack(mHitTagList[i], MDamageValueEnemyAttack))
        {
            return;
        }
    }
}

/// <summary>
/// �U�����󂯂����̏���
/// </summary>
/// <param name="_HitTag"> �q�b�g�����I�u�W�F�N�g�̃^�O </param>
/// <param name="_DamageValuePlayerAttack"> �_���[�W�� </param>
/// <returns> �q�b�g������ </returns>
bool PlayerObjectStateIdle::ReceivedAttack(const Tag& _hitTag, const int& _DamageValuePlayerAttack)
{
    if (mHitTag == _hitTag)
    {
        mDamageValue = _DamageValuePlayerAttack;
        mIsDamage = true;

        mPlayerPtr->SetDamageValue(mDamageValue);
        return true;
    }

    return false;
}