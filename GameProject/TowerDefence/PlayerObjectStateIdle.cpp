#include "pch.h"

/// <summary>
/// コンストラクタ
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
/// 更新処理
/// </summary>
/// <param name="_owner"> プレイヤー(親)のポインタ </param>
/// <param name="_DeltaTime"> 最後のフレームを完了するのに要した時間 </param>
/// <returns> プレイヤーの状態 </returns>
PlayerState PlayerObjectStateIdle::Update(PlayerObject* _owner, const float _DeltaTime)
{
    // 座標
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
/// 入力処理
/// </summary>
/// <param name="_owner"> プレイヤー(親)のポインタ </param>
/// <param name="_KeyState"> キーボード、マウス、コントローラーの入力状態 </param>
void PlayerObjectStateIdle::Input(PlayerObject* _owner, const InputState& _KeyState)
{
   //方向キーが入力されたか
    mIsRun = _KeyState.m_keyboard.GetKeyValue(SDL_SCANCODE_W) ||
             _KeyState.m_keyboard.GetKeyValue(SDL_SCANCODE_S) ||
             _KeyState.m_keyboard.GetKeyValue(SDL_SCANCODE_A) ||
             _KeyState.m_keyboard.GetKeyValue(SDL_SCANCODE_D) ||
             _KeyState.m_controller.GetButtonValue(SDL_CONTROLLER_BUTTON_DPAD_UP) ||
             _KeyState.m_controller.GetButtonValue(SDL_CONTROLLER_BUTTON_DPAD_DOWN) ||
             _KeyState.m_controller.GetButtonValue(SDL_CONTROLLER_BUTTON_DPAD_LEFT) ||
             _KeyState.m_controller.GetButtonValue(SDL_CONTROLLER_BUTTON_DPAD_RIGHT);

    //左スティックの入力値の値(-1~1)
    Vector2 leftAxis = _KeyState.m_controller.GetLAxisVec();

    if (leftAxis.LengthSq() >= MLeftAxisThreshold)
    {
        mIsRun = true;
    }

    //左Shiftキーが入力されたか
    mIsSprint = _KeyState.m_controller.GetButtonValue(SDL_CONTROLLER_BUTTON_RIGHTSHOULDER) ||
                _KeyState.m_keyboard.GetKeyValue(SDL_SCANCODE_LSHIFT);

    //Spaceキーが入力されたか
    mIsAttack = _KeyState.m_controller.GetButtonValue(SDL_CONTROLLER_BUTTON_Y) ||
                _KeyState.m_keyboard.GetKeyValue(SDL_SCANCODE_SPACE);
}

/// <summary>
/// プレイヤーの状態が変更して、最初に1回だけ呼び出される関数
/// </summary>
/// <param name="_owner"> プレイヤー(親)のポインタ </param>
/// <param name="_DeltaTime"> 最後のフレームを完了するのに要した時間 </param>
void PlayerObjectStateIdle::Enter(PlayerObject* _owner, const float _DeltaTime)
{
    // 待機状態のアニメーション再生
    SkeletalMeshComponent* meshcomp = _owner->GetSkeletalMeshComponentPtr();
    meshcomp->PlayAnimation(_owner->GetAnimPtr(PlayerState::ePlayerStateIdle));
    mIsDamage = false;

    mIsIdle = true;
    _owner->SetIsEnable(mIsIdle);
}

/// <summary>
/// ヒットした時の処理
/// </summary>
/// <param name="_owner"> プレイヤー(親)のポインタ </param>
/// <param name="_HitObject"> ヒットしたゲームオブジェクト </param>
void PlayerObjectStateIdle::OnCollision(PlayerObject* _owner, const GameObject& _HitObject)
{
    mPlayerPtr = _owner;
 
    // オブジェクトのタグ
    mHitTag = _HitObject.GetTag();

    for (int i = 0; i < mHitTagListSize; i++)
    {
        // 攻撃を受けた時の処理
        if (ReceivedAttack(mHitTagList[i], MDamageValueEnemyAttack))
        {
            return;
        }
    }
}

/// <summary>
/// 攻撃を受けた時の処理
/// </summary>
/// <param name="_HitTag"> ヒットしたオブジェクトのタグ </param>
/// <param name="_DamageValuePlayerAttack"> ダメージ量 </param>
/// <returns> ヒットしたか </returns>
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