#include "pch.h"

PlayerObjectStateRunLoop::PlayerObjectStateRunLoop()
{
	printf("Create : [PlayerObjectStateBase] PlayerObjectStateRunLoop\n");
}

PlayerObjectStateRunLoop::~PlayerObjectStateRunLoop()
{
	printf("Remove : [PlayerObjectStateBase] PlayerObjectStateRunLoop\n");
}

PlayerState PlayerObjectStateRunLoop::Update(PlayerObject* _owner, float _deltaTime)
{
	MoveCalc(_owner, _deltaTime);
	
	// いずれのボタンも押されていない
	if (!mIdleFlag && !mAttackFlag)
	{
		return PlayerState::ePlayerStateIdle;
	}

	if (mSprintStartFlag)
	{
		return PlayerState::ePlayerStateSprintStart;
	}

	// 攻撃ボタンが押されたか？
	if (mAttackFlag)
	{
		return PlayerState::ePlayerStateFirstAttack;
	}

	return PlayerState::ePlayerStateRunLoop;
}

void PlayerObjectStateRunLoop::Input(PlayerObject* _owner, const InputState& _keyState)
{
	//左Shiftキーが入力されたか
	mSprintFlag = _keyState.m_keyboard.GetKeyState(SDL_SCANCODE_LSHIFT) == Held;

	//方向キーが入力されたか
	mRunFlag = _keyState.m_keyboard.GetKeyState(SDL_SCANCODE_W) == Held ||
		_keyState.m_keyboard.GetKeyValue(SDL_SCANCODE_S) == Held ||
		_keyState.m_keyboard.GetKeyValue(SDL_SCANCODE_A) == Held ||
		_keyState.m_keyboard.GetKeyValue(SDL_SCANCODE_D) == Held;

	//Spaceキーが入力されたか
	mAttackFlag = _keyState.m_keyboard.GetKeyState(SDL_SCANCODE_SPACE) == Released;

	//値が更新され続けるのを防ぐために初期化
	mDirVec = Vector3::Zero;

	// コントローラーの十字上もしくはキーボード、Wが入力されたらzを足す
	if (_keyState.m_controller.GetButtonValue(SDL_CONTROLLER_BUTTON_DPAD_UP) == 1 ||
		_keyState.m_keyboard.GetKeyValue(SDL_SCANCODE_W) == 1)
	{
		mDirVec += mForwardVec;
	}
	// コントローラーの十字下もしくは、キーボードSが入力されたら-zを足す
	else if (_keyState.m_controller.GetButtonValue(SDL_CONTROLLER_BUTTON_DPAD_DOWN) == 1 ||
		_keyState.m_keyboard.GetKeyValue(SDL_SCANCODE_S) == 1)
	{
		mDirVec -= mForwardVec;
	}

	//コントローラーの十字左もしくは、キーボードAが入力されたら-xを足す
	if (_keyState.m_controller.GetButtonValue(SDL_CONTROLLER_BUTTON_DPAD_LEFT) == 1 ||
		_keyState.m_keyboard.GetKeyValue(SDL_SCANCODE_A) == 1)
	{
		mDirVec -= mRightVec;
	}
	// コントローラーの十字右もしくは、キーボードDが入力されたらxを足す
	else if (_keyState.m_controller.GetButtonValue(SDL_CONTROLLER_BUTTON_DPAD_RIGHT) == 1 ||
		_keyState.m_keyboard.GetKeyValue(SDL_SCANCODE_D) == 1)
	{
		mDirVec += mRightVec;
	}
}

// RUN状態への切り替え処理
void PlayerObjectStateRunLoop::Enter(PlayerObject* _owner, float _deltaTime)
{
    SkeletalMeshComponent* meshcomp = _owner->GetSkeletalMeshComp();
	meshcomp->PlayAnimation(_owner->GetAnim(PlayerState::ePlayerStateRunLoop));
}

void PlayerObjectStateRunLoop::MoveCalc(PlayerObject* _owner, float _deltaTime)
{
	// 移動速度
	const float PLAYER_SPEED = 300.0f;

	// カメラからみた前進方向を取得
	Vector3 targetPos = _owner->GetTargetPos();
	Vector3 viewPos = _owner->GetViewPos();
	mForwardVec = targetPos - viewPos;
	mForwardVec.z = 0.0f; // 高さ方向を無視

	// カメラ前方ベクトルと右方向ベクトル算出
	mForwardVec = Vector3::Normalize(mForwardVec);
	mRightVec = Vector3::Cross(Vector3::UnitZ, mForwardVec);

	// 入力キーの総和
	if (mDirVec.LengthSq() > 0.5f)
	{
		// 方向キー入力
		mCharaForwardVec = mDirVec;

		// 進行方向に向けて回転
		mCharaForwardVec.Normalize();
		_owner->RotateToNewForward(mCharaForwardVec);

		// 現在のスピードを保存
		mCharaSpeed = PLAYER_SPEED * _deltaTime;
	}

	// 移動処理
	Vector3 position = _owner->GetPosition();
	position += mCharaSpeed * mCharaForwardVec;

	// キャラの位置・スピード・変換行列の再計算の必要をセット
	_owner->SetPosition(position);
}
