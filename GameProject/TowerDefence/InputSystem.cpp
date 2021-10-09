#include "pch.h"

bool InputSystem::mControllerConnected = 0;

/*
@brief	現在のキーの入力状態のみを取得する
@param	SDL_Scancodeのキーコード
@return	true : 押されている , false : 押されていない
*/
bool KeyboardState::GetKeyValue(SDL_Scancode _keyCode) const
{
	return mCurrState[_keyCode] == 1;
}

/*
@brief	現在と1フレーム前の状態からButtonStateを返す
@param	SDL_Scancodeのキーコード
@return	ButtonState型の現在の状態
*/
ButtonState KeyboardState::GetKeyState(SDL_Scancode _keyCode) const
{
	if (mPrevState[_keyCode] == 0)
	{
		if (mCurrState[_keyCode] == 0)
		{
			return None;
		}
		else
		{
			return Pressed;
		}
	}
	else // Prev state must be 1
	{
		if (mCurrState[_keyCode] == 0)
		{
			return Released;
		}
		else
		{
			return Held;
		}
	}
}

/*
@brief	現在の入力状態のみを取得する
@param	SDL_BUTTON定数
@return	true : 押されている , false : 押されていない
*/
bool MouseState::GetButtonValue(int _button) const
{
	return (SDL_BUTTON(_button) & mCurrButtons) == 1;
}

/*
@brief	現在と1フレーム前の状態からButtonStateを返す
@param	SDL_BUTTON定数
@return	ButtonState型の現在の状態
*/
ButtonState MouseState::GetButtonState(int _button) const
{
	int mask = SDL_BUTTON(_button);
	if ((mask & mPrevButtons) == 0)
	{
		if ((mask & mCurrButtons) == 0)
		{
			return None;
		}
		else
		{
			return Pressed;
		}
	}
	else
	{
		if ((mask & mCurrButtons) == 0)
		{
			return Released;
		}
		else
		{
			return Held;
		}
	}
}

/*
@brief	現在の入力状態のみを取得する
@param	SDL_GameControllerButtonのボタンコード
@return	true : 押されている , false : 押されていない
*/
bool ControllerState::GetButtonValue(SDL_GameControllerButton _button) const
{
	return mCurrButtons[_button] == 1;
}

/*
@brief	現在と1フレーム前の状態からButtonStateを返す
@param	SDL_GameControllerButtonのボタンコード
@return	ButtonState型の現在の状態
*/
ButtonState ControllerState::GetButtonState(SDL_GameControllerButton _button) const
{
	if (mPrevButtons[_button] == 0)
	{
		if (mCurrButtons[_button] == 0)
		{
			return None;
		}
		else
		{
			return Pressed;
		}
	}
	else // Prev state must be 1
	{
		if (mCurrButtons[_button] == 0)
		{
			return Released;
		}
		else
		{
			return Held;
		}
	}
}

float ControllerState::GetAxisValue(const SDL_GameControllerAxis _iAxis) const
{
	return mAxisValues[_iAxis];
}

/*
@brief  初期化処理
@return true : 成功 , false : 失敗
*/
bool InputSystem::Initialize()
{
	//キーボードの初期化処理
	//今のキーボードの状態を割り当てる
	mState.m_keyboard.mCurrState = SDL_GetKeyboardState(NULL);
	//１フレーム前の入力状態を初期化する
	memset(mState.m_keyboard.mPrevState, 0,
		SDL_NUM_SCANCODES);

	memset(mState.m_controller.mAxisValues, 0,
		sizeof(float) * SDL_CONTROLLER_AXIS_MAX);


	//現在と１フレーム前のマウスの入力状態を初期化する
	mState.m_mouse.mCurrButtons = 0;
	mState.m_mouse.mPrevButtons = 0;

	// パッドの設定ファイル gamecontrollerdb.txt の読み込みと問題が無いかのチェック
	int iNumOfControllers = SDL_GameControllerAddMappingsFromFile("Assets/Config/GameControllerdb.txt");
	if (iNumOfControllers == -1)
	{
		SDL_LogWarn(SDL_LOG_CATEGORY_INPUT, "Error loading database [%s]", SDL_GetError());
		return false;
	}

	//コントローラーを開く
	mController = nullptr;
	mController = SDL_GameControllerOpen(0);
	if (mController != nullptr)
	{
		mControllerConnected = true;
	}
	if (SDL_IsGameController(0))
	{
		printf("Controller :: %s \n", SDL_GameControllerMapping(mController));
	}

	// コントローライベントの無視（こちらからフレーム毎に状態を取得するため）
	SDL_GameControllerEventState(SDL_IGNORE);

	return true;
}

/*
@brief  終了処理
*/
void InputSystem::Shutdown()
{
	if (!mController)
	{
		SDL_GameControllerClose(mController);
	}
	mController = nullptr;
}

/*
@brief  Updateの準備をする（SDL_PollEventsの直前に呼ぶ）
*/
void InputSystem::PrepareForUpdate()
{
	//現在の入力状態を１フレーム前の入力状態にコピーする
	//キーボード
	memcpy(mState.m_keyboard.mPrevState,
		mState.m_keyboard.mCurrState,
		SDL_NUM_SCANCODES);

	//マウス
	mState.m_mouse.mPrevButtons = mState.m_mouse.mCurrButtons;
	mState.m_mouse.mRelativeFlag = false;
	mState.m_mouse.mScrollWheel = Vector2::Zero;

	//コントローラー
	memcpy(mState.m_controller.mPrevButtons,
		mState.m_controller.mCurrButtons,
		SDL_CONTROLLER_BUTTON_MAX);
}

/*
@brief  フレーム毎の処理（SDL_PollEventsの直後に呼ぶ）
*/
void InputSystem::Update()
{
	//マウス
	int x = 0, y = 0;
	if (mState.m_mouse.mRelativeFlag)
	{
		mState.m_mouse.mCurrButtons =
			SDL_GetRelativeMouseState(&x, &y);
	}
	else
	{
		mState.m_mouse.mCurrButtons =
			SDL_GetMouseState(&x, &y);
	}

	mState.m_mouse.mMousePos.x = static_cast<float>(x) - 1024.0f / 2;
	mState.m_mouse.mMousePos.y = 768.0f / 2 - static_cast<float>(y);

	// コントローラが無い場合は early exitする
	if (mController != NULL)
	{
		// 前のフレームのコントローラの状態をコピーする
		memcpy(&mState.m_controller.mPrevButtons, &mState.m_controller.mCurrButtons, sizeof(Uint8) * SDL_CONTROLLER_BUTTON_MAX);

		// コントローラの状態を更新する
		SDL_GameControllerUpdate();

		// 現在のコントローラのボタン状態を保存
		for (int b = 0; b < SDL_CONTROLLER_BUTTON_MAX; ++b)
		{
			mState.m_controller.mCurrButtons[b] = SDL_GameControllerGetButton(mController, (SDL_GameControllerButton)b);
		}

		// 現在のコントローラの軸情報を保存
		for (int a = 0; a < SDL_CONTROLLER_AXIS_MAX; ++a)
		{
			mState.m_controller.mAxisValues[a] = SDL_GameControllerGetAxis(mController, (SDL_GameControllerAxis)a);
		}

		// LPAD入力をベクトル化する
		const float maxInput = 32767.0f;
		mState.m_controller.mLAxis.x = (float)mState.m_controller.mAxisValues[SDL_CONTROLLER_AXIS_LEFTX];
		mState.m_controller.mLAxis.y = (float)mState.m_controller.mAxisValues[SDL_CONTROLLER_AXIS_LEFTY];
		mState.m_controller.mRAxis.x = (float)mState.m_controller.mAxisValues[SDL_CONTROLLER_AXIS_RIGHTX];
		mState.m_controller.mRAxis.y = (float)mState.m_controller.mAxisValues[SDL_CONTROLLER_AXIS_RIGHTY];
		
		//スティックの入力に最低値を設ける(定数以下はカット)
		mState.m_controller.mLAxis.x = (fabs(mState.m_controller.mLAxis.x) < (float)7849) ? 0.0f : mState.m_controller.mLAxis.x / maxInput;
		mState.m_controller.mLAxis.y = (fabs(mState.m_controller.mLAxis.y) < (float)8689) ? 0.0f : mState.m_controller.mLAxis.y / maxInput;
		mState.m_controller.mRAxis.x = (fabs(mState.m_controller.mRAxis.x) < (float)7849) ? 0.0f : mState.m_controller.mRAxis.x / maxInput;
		mState.m_controller.mRAxis.y = (fabs(mState.m_controller.mRAxis.y) < (float)8689) ? 0.0f : mState.m_controller.mRAxis.y / maxInput;
	}
}

/*
@brief  SDLイベントをInputSystemに渡す
*/
void InputSystem::ProcessEvent(SDL_Event& _event)
{
	switch (_event.type)
	{
	case SDL_MOUSEWHEEL:
		mState.m_mouse.mScrollWheel = Vector2(
			static_cast<float>(_event.wheel.x),
			static_cast<float>(_event.wheel.y));
		break;
	default:
		break;
	}
}

/*
@brief  マウスのモードを設定する
@param	true : 相対モード , false : デフォルトモード
*/
void InputSystem::SetRelativeMouseMode(bool _value)
{
	SDL_bool set = _value ? SDL_TRUE : SDL_FALSE;
	SDL_SetRelativeMouseMode(set);

	mState.m_mouse.mRelativeFlag = _value;
}

/*
@brief  入力された値（int）をフィルタリングする（範囲内に収めて-1.0~1.0にまとめる）
@param	入力された値（int）
@return	フィルタリングされた値
*/
float InputSystem::Filter1D(int _input)
{
	//デッドゾーン（この値より小さいなら0.0にする）
	const int deadZone = 250;
	//最大値（この値より大きくても1.0にする）
	const int maxValue = 30000;

	float retVal = 0.0f;

	//入力値の絶対値を取る
	int absValue = _input > 0 ? _input : -_input;
	//入力値がデッドゾーンより小さいなら
	if (absValue > deadZone)
	{
		//デッドゾーンと最大値の間で1.0以下になるよう計算する
		retVal = static_cast<float>(absValue - deadZone) /
			(maxValue - deadZone);
		//符号を元の値と同じにする
		retVal = _input > 0 ? retVal : -1.0f * retVal;
		//-1.0~1.0の間に収める
		retVal = Math::Clamp(retVal, -1.0f, 1.0f);
	}

	return retVal;
}

/*
@brief  入力された値（int）をフィルタリングする（範囲内に収めて0.0~1.0にまとめる）
@param	入力された値のx（int）
@param	入力された値のy（int）
@return	フィルタリングされた値
*/
Vector2 InputSystem::Filter2D(int _inputX, int _inputY)
{
	//デッドゾーン（この値より小さいなら0.0にする）
	const float deadZone = 8000.0f;
	//最大値（この値より大きくても1.0にする）
	const float maxValue = 30000.0f;

	//2次元ベクトルにする
	Vector2 dir;
	dir.x = static_cast<float>(_inputX);
	dir.y = static_cast<float>(_inputY);

	float length = dir.Length();

	//入力値のベクトルの長さがデッドゾーンより小さいなら
	if (length < deadZone)
	{
		dir = Vector2::Zero;
	}
	else
	{
		//デッドゾーンと最大値の間で1.0以下になるよう計算する
		float f = (length - deadZone) / (maxValue - deadZone);
		//0.0と1.0の間に収める
		f = Math::Clamp(f, 0.0f, 1.0f);
		//ベクトルを正規化して、分数の値にスケーリングする
		dir *= f / length;
	}

	return dir;
}
