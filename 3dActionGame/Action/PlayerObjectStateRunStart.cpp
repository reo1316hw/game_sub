#include "PlayerObjectStateRunStart.h"
#include "SkeletalMeshComponent.h"
#include "game.h"
#include "Animation.h"
#include "InputSystem.h"
//#include "AudioManager.h"
//#include "SwordEffectActor.h"

PlayerObjectStateRunStart::PlayerObjectStateRunStart()
	: mIsIdle(false)
	, mIsAttack(false)
{
	printf("Create : [PlayerObjectStateBase] PlayerObjectStateRunStart\n");
}

PlayerObjectStateRunStart::~PlayerObjectStateRunStart()
{
	printf("Remove : [PlayerObjectStateBase] PlayerObjectStateRunStart\n");
}

PlayerState PlayerObjectStateRunStart::Update(PlayerObject* _owner, float _deltaTime)
{
	mElapseTime += _deltaTime;

	// アニメーションが終了したらcStopTime硬直後、RUN状態へ
	if (!_owner->GetSkeletalMeshComp()->IsPlaying())
	{
		if (mElapseTime > mTotalAnimTime)
		{
			return PlayerState::PLAYER_STATE_SPRINT_LOOP;
		}
		else
		{
			return PlayerState::PLAYER_STATE_RUN_START;
		}
	}


	//// ジャンプ開始・ジャンプループ/終了アニメ
	//const Animation* runStart = _owner->GetAnim(PlayerState::PLAYER_STATE_RUN_START);
	//const Animation* runLoop = _owner->GetAnim(PlayerState::PLAYER_STATE_RUN_LOOP);

	//// 現在再生中のアニメを取得
	//SkeletalMeshComponent* skeltalMesh = _owner->GetSkeletalMeshComp();
	//const Animation* nowAnim = skeltalMesh->GetNowPlayingAnimation();

	MoveCalc(_owner, _deltaTime);

	//// 開始アニメ終了ならジャンプループアニメに移行
	//if (nowAnim == runStart && skeltalMesh->IsPlaying())
	//{
	//	//skeltalMesh->PlayAnimation(runLoop);
	//	return PlayerState::PLAYER_STATE_RUN_LOOP;
	//}

	return PlayerState::PLAYER_STATE_RUN_START;
}

void PlayerObjectStateRunStart::Inipt(PlayerObject* _owner, const InputState& _keyState)
{
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

void PlayerObjectStateRunStart::Enter(PlayerObject* _owner, float _deltaTime)
{
	// RUN_STARTのアニメーション再生
	SkeletalMeshComponent* meshComp = _owner->GetSkeletalMeshComp();
	meshComp->PlayAnimation(_owner->GetAnim(PlayerState::PLAYER_STATE_RUN_START),1.2f);

	// アニメーション再生時間取得(アニメーションの総時間矯正)
	mTotalAnimTime = _owner->GetAnim(PlayerState::PLAYER_STATE_RUN_START)->GetDuration() - 0.3f;
	mElapseTime = 0.0f;
	mCharaSpeed = 0.0f;
}

void PlayerObjectStateRunStart::Exit(PlayerObject* _owner, float _deltaTime)
{

}

void PlayerObjectStateRunStart::MoveCalc(PlayerObject* _owner, float _deltaTime)
{
	// 移動速度
	const float PLAYER_SPEED = 100.0f;

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
	//forwardAngle *= angleSign

	// 入力キーの総和
	if (mDirVec.LengthSq() > 0.5f)
	{
		// 方向キー入力
		mCharaForwardVec = mDirVec;

		// 進行方向に向けて回転
		mCharaForwardVec.Normalize();
		_owner->RotateToNewForward(mCharaForwardVec);

		// 現在のスピードを保存
		mCharaSpeed += PLAYER_SPEED * _deltaTime;
	}

	if (mCharaSpeed >= 12.0f)
	{
		mCharaSpeed = 12.0f;
	}

	// 移動処理
	Vector3 position = _owner->GetPosition();
	position += mCharaSpeed * mCharaForwardVec;

	// キャラの位置・スピード・変換行列の再計算の必要をセット
	_owner->SetPosition(position);
}
