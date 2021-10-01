#include "pch.h"

PlayerObjectStateSprintLoop::PlayerObjectStateSprintLoop()
{
	printf("Create : [PlayerObjectStateBase] PlayerObjectStateSprintLoop\n");
}

PlayerObjectStateSprintLoop::~PlayerObjectStateSprintLoop()
{
	printf("Remove : [PlayerObjectStateBase] PlayerObjectStateSprintLoop\n");
}

PlayerState PlayerObjectStateSprintLoop::Update(PlayerObject* _owner, float _deltaTime)
{
	// いずれのボタンも押されていない
	if (!mIdleFlag /*&& !IsJump */)
	{
		return PlayerState::PLAYER_STATE_RUN_END;
	}

	//ボタンが押されていない時
	if (!mRunFlag)
	{
		return PlayerState::PLAYER_STATE_RUN_LOOP;
	}

	//// ジャンプボタンが押されたか？
	//if (IsJump)
	//{
	//	return PlayerState::PLAYER_STATE_JUMPSTART;
	//}

	MoveCalc(_owner, _deltaTime);

	return PlayerState::PLAYER_STATE_SPRINT_LOOP;
}

void PlayerObjectStateSprintLoop::Inipt(PlayerObject* _owner, const InputState& _keyState)
{

	//// コントローラ入力されたか
	//Vector2 stickL = INPUT_INSTANCE.GetLStick();
	//bool isContollerInputOff = !INPUT_INSTANCE.IsLStickMove();

	//方向キーが入力されたか
	mIdleFlag = _keyState.m_keyboard.GetKeyValue(SDL_SCANCODE_W) ||
		_keyState.m_keyboard.GetKeyValue(SDL_SCANCODE_S) ||
		_keyState.m_keyboard.GetKeyValue(SDL_SCANCODE_A) ||
		_keyState.m_keyboard.GetKeyValue(SDL_SCANCODE_D); //||
			  // isContollerInputOff;

	//左Shiftキーが入力されたか
	mRunFlag = _keyState.m_keyboard.GetKeyValue(SDL_SCANCODE_LSHIFT);

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
void PlayerObjectStateSprintLoop::Enter(PlayerObject* _owner, float _deltaTime)
{
	SkeletalMeshComponent* meshcomp = _owner->GetSkeletalMeshComp();
	meshcomp->PlayAnimation(_owner->GetAnim(PlayerState::PLAYER_STATE_SPRINT_LOOP));
}

void PlayerObjectStateSprintLoop::MoveCalc(PlayerObject* _owner, float _deltaTime)
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
	const float PLAYER_SPEED = 750.0f;

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
