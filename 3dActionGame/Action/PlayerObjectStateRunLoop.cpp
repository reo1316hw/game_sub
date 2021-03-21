#include "PlayerObjectStateRunLoop.h"
#include "SkeletalMeshComponent.h"
#include "InputSystem.h"
#include "GameObject.h"
#include "MainCameraObject.h"

PlayerObjectStateRunLoop::PlayerObjectStateRunLoop(bool _isDrawnSword)
	: mIsIdle(false)
	, mIsRunStart(false)
	, mIsAttack(false)
	, mIsDrawnSword(false)
{
	mIsDrawnSword = _isDrawnSword;
	printf("Create : [PlayerObjectStateBase] PlayerObjectStateRunLoop\n");
}

PlayerObjectStateRunLoop::~PlayerObjectStateRunLoop()
{
	printf("Remove : [PlayerObjectStateBase] PlayerObjectStateRunLoop\n");
}

PlayerState PlayerObjectStateRunLoop::Update(PlayerObject* _owner, float _deltaTime)
{

	MoveCalc(_owner, _deltaTime);

	if (mIsDrawnSword)
	{
		// いずれのボタンも押されていない
		if (!mIsIdle /*&& !IsJump */ && !mIsAttack)
		{
			return PlayerState::PLAYER_STATE_SWORD_IDLE;
		}

		// 攻撃ボタンが押されたか？
		if (mIsAttack)
		{
			return PlayerState::PLAYER_STATE_ATTACK1;
		}

		return PlayerState::PLAYER_STATE_SWORD_RUN_LOOP;
	}
	else
	{
		// いずれのボタンも押されていない
		if (!mIsIdle /*&& !IsJump */ && !mIsAttack)
		{
			return PlayerState::PLAYER_STATE_RUN_END;
		}

		if (mIsRunStart)
		{
			return PlayerState::PLAYER_STATE_RUN_START;
		}

		return PlayerState::PLAYER_STATE_RUN_LOOP;
	}

	//// ジャンプボタンが押されたか？
	//if (IsJump)
	//{
	//	return PlayerState::PLAYER_STATE_JUMPSTART;
	//}
}

void PlayerObjectStateRunLoop::Inipt(PlayerObject* _owner, const InputState& _keyState)
{

	//// コントローラ入力されたか
	//Vector2 stickL = INPUT_INSTANCE.GetLStick();
	//bool isContollerInputOff = !INPUT_INSTANCE.IsLStickMove();

	//方向キーが入力されたか
	mIsIdle = _keyState.m_keyboard.GetKeyValue(SDL_SCANCODE_W) ||
				_keyState.m_keyboard.GetKeyValue(SDL_SCANCODE_S) ||
				_keyState.m_keyboard.GetKeyValue(SDL_SCANCODE_A) ||
				_keyState.m_keyboard.GetKeyValue(SDL_SCANCODE_D); //||
			  // isContollerInputOff;

	//左Shiftキーが入力されたか
	mIsRunStart = _keyState.m_keyboard.GetKeyValue(SDL_SCANCODE_LSHIFT);

	//Enterキーが入力されたか
	mIsAttack = _keyState.m_keyboard.GetKeyValue(SDL_SCANCODE_RETURN);
	//bool IsJump = INPUT_INSTANCE.IsKeyPushdown(KEY_B);

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
	if (mIsDrawnSword)
	{
		SkeletalMeshComponent* meshcomp = _owner->GetSkeletalMeshComp();
		meshcomp->PlayAnimation(_owner->GetAnim(PlayerState::PLAYER_STATE_SWORD_RUN_LOOP));
	}
	else
	{
		SkeletalMeshComponent* meshcomp = _owner->GetSkeletalMeshComp();
		meshcomp->PlayAnimation(_owner->GetAnim(PlayerState::PLAYER_STATE_RUN_LOOP));
	}
	
}

void PlayerObjectStateRunLoop::MoveCalc(PlayerObject* _owner, float _deltaTime)
{
	/*if (buttonFlag == false)
	{
		mCharaSpeed -= 1.0f;
		if (mCharaSpeed <= 0.0f)
		{
			mCharaSpeed = 0.0f;
		}
	}*/

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
	//jumpVec = Vector3::Cross(Vector3::UnitY, mForwardVec);

	//// 右方向ベクトルからカメラ回転角を算出
	//float forwardAngle = 0.0f;
	//float angleSign;
	//Vector3 tmpVec;
	//forwardAngle = acosf(Vector3::Dot(Vector3::UnitX, mRightVec));

	//// 右回転か左回転か？
	//tmpVec = Vector3::Cross(Vector3::UnitX, mRightVec);
	//angleSign = (tmpVec.z > 0.0) ? 1.0f : -1.0f;
	//forwardAngle *= angleSign;

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

		/*if (mCharaSpeed >= 10.0f)
		{
			mCharaSpeed = 10.0f;
		}*/
	}

	// 移動処理
	Vector3 position = _owner->GetPosition();
	position += mCharaSpeed * mCharaForwardVec;

	// キャラの位置・スピード・変換行列の再計算の必要をセット
	_owner->SetPosition(position);
}
