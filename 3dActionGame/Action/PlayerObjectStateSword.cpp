#include "PlayerObjectStateSword.h"
#include "SkeletalMeshComponent.h"
#include "InputSystem.h"
#include "Animation.h"
#include "GameObject.h"
#include "MainCameraObject.h"
#include "Math.h"

PlayerObjectStateSword::PlayerObjectStateSword(bool _moveFlag, bool _drawnSwordFlag)
	: mIsIdle(false)
	, mIsRunStart(false)
	, mIsAttack(false)
	, moveFlag(_moveFlag)
	, drawnSwordFlag(_drawnSwordFlag)
	, charaSpeed(0.0f)
	, dirVec(Vector3::Zero)
	, forwardVec(Vector3::Zero)
	, rightVec(Vector3::Zero)
	, mElapseTime(0.0f)
	, mTotalAnimTime(0.0f)
{
	printf("Create : [PlayerObjectStateBase] PlayerObjectStateDrawnSword\n");
}

PlayerObjectStateSword::~PlayerObjectStateSword()
{
	printf("Remove : [PlayerObjectStateBase] PlayerObjectStateDrawnSword\n");
}

PlayerState PlayerObjectStateSword::Update(PlayerObject* _owner, float _deltaTime)
{
	mElapseTime += _deltaTime;

	bool transitionFlag = mElapseTime > mTotalAnimTime;

	if (drawnSwordFlag)
	{
		_owner->SetSwordRot(Vector3(-Math::PiOver2 * 0.5f, Math::Pi * 0.9f, 0.0f));
		_owner->SetSwordPos(Vector3(-70.0f, -5.0f, 135.0f));

		if (moveFlag)
		{
			MoveCalc(_owner, _deltaTime);

			if (transitionFlag)
			{
				return PlayerState::PLAYER_STATE_RUN_LOOP;
			}

			return PlayerState::PLAYER_STATE_DRAWN_SWORD_MOVE;
		}
		else
		{
			if (transitionFlag)
			{
				return PlayerState::PLAYER_STATE_SWORD_IDLE;
			}

			return PlayerState::PLAYER_STATE_DRAWN_SWORD;
		}
	}
	else
	{
		if (moveFlag)
		{
			MoveCalc(_owner, _deltaTime);

			if (transitionFlag)
			{
				return PlayerState::PLAYER_STATE_RUN_LOOP;
			}

			return PlayerState::PLAYER_STATE_SWORD_DELIVERY_MOVE;
		}
		else
		{
			if (transitionFlag)
			{
				_owner->SetSwordRot(Vector3(-Math::PiOver2 * 0.6f, Math::Pi * 0.4f, 0.0f));
				_owner->SetSwordPos(Vector3(0.0f, 0.0f, 110.0f));

				return PlayerState::PLAYER_STATE_IDLE;
			}

			return PlayerState::PLAYER_STATE_SWORD_DELIVERY;
		}
	}
}

void PlayerObjectStateSword::Inipt(PlayerObject* _owner, const InputState& _keyState)
{

	//// コントローラ入力されたか
	//Vector2 stickL = INPUT_INSTANCE.GetLStick();
	//bool isContollerInputOff = !INPUT_INSTANCE.IsLStickMove();

	//値が更新され続けるのを防ぐために初期化
	dirVec = Vector3::Zero;

	// コントローラーの十字上もしくはキーボード、Wが入力されたらzを足す
	if (_keyState.Controller.GetButtonValue(SDL_CONTROLLER_BUTTON_DPAD_UP) == 1 ||
		_keyState.Keyboard.GetKeyValue(SDL_SCANCODE_W) == 1)
	{
		dirVec += forwardVec;
	}
	// コントローラーの十字下もしくは、キーボードSが入力されたら-zを足す
	else if (_keyState.Controller.GetButtonValue(SDL_CONTROLLER_BUTTON_DPAD_DOWN) == 1 ||
		_keyState.Keyboard.GetKeyValue(SDL_SCANCODE_S) == 1)
	{
		dirVec -= forwardVec;
	}

	//コントローラーの十字左もしくは、キーボードAが入力されたら-xを足す
	if (_keyState.Controller.GetButtonValue(SDL_CONTROLLER_BUTTON_DPAD_LEFT) == 1 ||
		_keyState.Keyboard.GetKeyValue(SDL_SCANCODE_A) == 1)
	{
		dirVec -= rightVec;
	}
	// コントローラーの十字右もしくは、キーボードDが入力されたらxを足す
	else if (_keyState.Controller.GetButtonValue(SDL_CONTROLLER_BUTTON_DPAD_RIGHT) == 1 ||
		_keyState.Keyboard.GetKeyValue(SDL_SCANCODE_D) == 1)
	{
		dirVec += rightVec;
	}
}

// RUN状態への切り替え処理
void PlayerObjectStateSword::Enter(PlayerObject* _owner, float _deltaTime)
{

	if (drawnSwordFlag)
	{
		if (moveFlag)
		{
			SkeletalMeshComponent* meshcomp = _owner->GetSkeletalMeshComp();
			meshcomp->PlayAnimation(_owner->GetAnim(PlayerState::PLAYER_STATE_DRAWN_SWORD_MOVE));

			// アニメーション再生時間取得
			mTotalAnimTime = _owner->GetAnim(PlayerState::PLAYER_STATE_DRAWN_SWORD_MOVE)->GetDuration();
			mElapseTime = 0.0f;
		}
		else
		{
			SkeletalMeshComponent* meshcomp = _owner->GetSkeletalMeshComp();
			meshcomp->PlayAnimation(_owner->GetAnim(PlayerState::PLAYER_STATE_DRAWN_SWORD));

			// アニメーション再生時間取得
			mTotalAnimTime = _owner->GetAnim(PlayerState::PLAYER_STATE_DRAWN_SWORD)->GetDuration();
			mElapseTime = 0.0f;
		}
	}
	else
	{
		if (moveFlag)
		{
			SkeletalMeshComponent* meshcomp = _owner->GetSkeletalMeshComp();
			meshcomp->PlayAnimation(_owner->GetAnim(PlayerState::PLAYER_STATE_SWORD_DELIVERY_MOVE));

			// アニメーション再生時間取得
			mTotalAnimTime = _owner->GetAnim(PlayerState::PLAYER_STATE_SWORD_DELIVERY_MOVE)->GetDuration();
			mElapseTime = 0.0f;
		}
		else
		{
			SkeletalMeshComponent* meshcomp = _owner->GetSkeletalMeshComp();
			meshcomp->PlayAnimation(_owner->GetAnim(PlayerState::PLAYER_STATE_SWORD_DELIVERY));

			// アニメーション再生時間取得
			mTotalAnimTime = _owner->GetAnim(PlayerState::PLAYER_STATE_SWORD_DELIVERY)->GetDuration();
			mElapseTime = 0.0f;
		}
	}
}

void PlayerObjectStateSword::MoveCalc(PlayerObject* _owner, float _deltaTime)
{
	/*if (buttonFlag == false)
	{
		charaSpeed -= 1.0f;
		if (charaSpeed <= 0.0f)
		{
			charaSpeed = 0.0f;
		}
	}*/

	// 移動速度
	const float PLAYER_SPEED = 300.0f;

	// カメラからみた前進方向を取得
	Vector3 targetPos = _owner->GetTargetPos();
	Vector3 viewPos = _owner->GetViewPos();
	forwardVec = targetPos - viewPos;
	forwardVec.z = 0.0f; // 高さ方向を無視

	// カメラ前方ベクトルと右方向ベクトル算出
	forwardVec = Vector3::Normalize(forwardVec);
	rightVec = Vector3::Cross(Vector3::UnitZ, forwardVec);
	//jumpVec = Vector3::Cross(Vector3::UnitY, forwardVec);

	//// 右方向ベクトルからカメラ回転角を算出
	//float forwardAngle = 0.0f;
	//float angleSign;
	//Vector3 tmpVec;
	//forwardAngle = acosf(Vector3::Dot(Vector3::UnitX, rightVec));

	//// 右回転か左回転か？
	//tmpVec = Vector3::Cross(Vector3::UnitX, rightVec);
	//angleSign = (tmpVec.z > 0.0) ? 1.0f : -1.0f;
	//forwardAngle *= angleSign;

	// 入力キーの総和
	if (dirVec.LengthSq() > 0.5f)
	{
		// 方向キー入力
		charaForwardVec = dirVec;

		// 進行方向に向けて回転
		charaForwardVec.Normalize();
		_owner->RotateToNewForward(charaForwardVec);

		// 現在のスピードを保存
		charaSpeed = PLAYER_SPEED * _deltaTime;

		/*if (charaSpeed >= 10.0f)
		{
			charaSpeed = 10.0f;
		}*/
	}

	// 移動処理
	Vector3 position = _owner->GetPosition();
	position += charaSpeed * charaForwardVec;

	// キャラの位置・スピード・変換行列の再計算の必要をセット
	_owner->SetPosition(position);
}
