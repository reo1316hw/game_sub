#pragma once

// 前方宣言
class FirstAttackEffect;

/// <summary>
/// 1段階目の攻撃
/// </summary>
class PlayerObjectStateFirstAttack : public PlayerObjectStateBase
{
public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	PlayerObjectStateFirstAttack();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~PlayerObjectStateFirstAttack() {};

	/// <summary>
	/// 更新処理
	/// </summary>
	/// <param name="_owner"> プレイヤー(親)のポインタ </param>
	/// <param name="_DeltaTime"> 最後のフレームを完了するのに要した時間 </param>
	/// <returns> プレイヤーの状態 </returns>
	PlayerState Update(PlayerObject* _owner, const float _DeltaTime)override;

	/// <summary>
	/// 入力処理
	/// </summary>
	/// <param name="_owner"> プレイヤー(親)のポインタ </param>
	/// <param name="_KeyState"> キーボード、マウス、コントローラーの入力状態 </param>
	void Input(PlayerObject* _owner, const InputState& _KeyState)override;

	/// <summary>
	/// プレイヤーの状態が変更して、最初に1回だけ呼び出される関数
	/// </summary>
	/// <param name="_owner"> プレイヤー(親)のポインタ </param>
	/// <param name="_DeltaTime"> 最後のフレームを完了するのに要した時間 </param>
	void Enter(PlayerObject* _owner, const float _DeltaTime)override;

	/// <summary>
	/// ヒットした時の処理
	/// </summary>
	/// <param name="_owner"> プレイヤー(親)のポインタ </param>
	/// <param name="_HitObject"> ヒットしたゲームオブジェクト </param>
	void OnCollision(PlayerObject* _owner, const GameObject& _HitObject)override;

private:

	/// <summary>
	/// 攻撃を受けた時の処理
	/// </summary>
	/// <param name="_HitTag"> ヒットしたオブジェクトのタグ </param>
	/// <param name="_DamageValuePlayerAttack"> ダメージ量 </param>
	/// <returns> ヒットしたか </returns>
	bool ReceivedAttack(const Tag& _HitTag, const int& _DamageValuePlayerAttack);
	
	/// <summary>
	/// 縦キー入力操作
	/// </summary>
	/// <param name="_KeyState"> キーボード、マウス、コントローラーの入力状態 </param>
	/// <param name="_KeyScancode"> 何キーを押したか </param>
	/// <param name="_ButtonScancode"> 何ボタンを押したか </param>
	/// <param name="_AngleBorderMinAKey"> Aキー入力時の境目の角度の最小値 </param>
	/// <param name="_AngleBorderMaxAKey"> Aキー入力時の境目の角度の最大値 </param>
	/// <param name="_AngleBorderMinDKey"> Dキー入力時の境目の角度の最小値 </param>
	/// <param name="_AngleBorderMaxDKey"> Dキー入力時の境目の角度の最大値 </param>
	/// <param name="_ValueShortenVector"> ベクトルを短くする値 </param>
	/// <returns> true : 何か押した, false : 何も押さなかった </returns>
	bool VerticalKeyInputOperation(const InputState& _KeyState, const SDL_Scancode& _KeyScancode, const SDL_GameControllerButton& _ButtonScancode,
		const float& _AngleBorderMinAKey, const float& _AngleBorderMaxAKey, const float& _AngleBorderMinDKey, const float& _AngleBorderMaxDKey, const float& _ValueShortenVector);

	/// <summary>
	/// 横キー入力操作
	/// </summary>
	/// <param name="_KeyState"> キーボード、マウス、コントローラーの入力状態 </param>
	/// <param name="_KeyScancode"> 何キーを押したか </param>
	/// <param name="_ButtonScancode"> 何ボタンを押したか </param>
	/// <param name="_AngleBorderMin"> 境目の角度の最小値 </param>
	/// <param name="_AngleBorderMax"> 境目の角度の最大値 </param>
	/// <param name="_ValueShortenVector"> ベクトルを短くする値 </param>
	/// <returns> true : 何か押した, false : 何も押さなかった </returns>
	bool LateralKeyInputOperation(const InputState& _KeyState, const SDL_Scancode& _KeyScancode, const SDL_GameControllerButton& _ButtonScancode, 
		const float& _AngleBorderMin, const float& _AngleBorderMax, const float& _ValueShortenVector);

	/// <summary>
	/// 左スティックを左に倒したときの操作
	/// </summary>
	/// <param name="_AngleBorderMin"> 境目の角度の最小値 </param>
	/// <param name="_AngleBorderMax"> 境目の角度の最大値 </param>
	/// <param name="_ValueShortenVector"></param>
	/// <returns> true : スティックを倒した, false : スティックを倒さなかった </returns>
	bool LeftStickDefeatLeftInputOperation(const float& _AngleBorderMin, const float& _AngleBorderMax, const float& _ValueShortenVector);

	/// <summary>
	/// 左スティックを右に倒したときの操作
	/// </summary>
	/// <param name="_AngleBorderMin"> 境目の角度の最小値 </param>
	/// <param name="_AngleBorderMax"> 境目の角度の最大値 </param>
	/// <param name="_ValueShortenVector"> ベクトルを短くする値 </param>
	/// <returns> true : スティックを倒した, false : スティックを倒さなかった </returns>
	bool LeftStickDefeatRightInputOperation(const float& _AngleBorderMin, const float& _AngleBorderMax, const float& _ValueShortenVector);

	/// <summary>
	/// 範囲角度で回転させる
	/// </summary>
	/// <param name="_AngleBorderMin"> 境目の角度の最小値 </param>
	/// <param name="_AngleBorderMax"> 境目の角度の最大値 </param>
	/// <param name="_ValueShortenVector"> ベクトルを短くする値 </param>
	void RotateInRangeAngle(const float& _AngleBorderMin, const float& _AngleBorderMax, const float& _ValueShortenVector);

	// ヒットするオブジェクトのリスト
	Tag mHitTagList[4];

	// 向く角度のリスト
	float faceAngleList[8];

	// エネミーの攻撃のダメージ値
	const int MDamageValueEnemyAttack;
	// 半回転値
	const int MHalfRotation;
	// 全回転値
	const int MAllRotation;
	// 当たり判定を有効にするタイミング
	const float MBoxEnableTiming;
	// 攻撃時の速度
	const float MAttackSpeed;
	// アニメーションの再生速度
	const float MPlayRate;
	// 左スティックのしきい値
	const float MLeftAxisThreshold;
	// ベクトルを短くする値
	const float MValueShortenVector;

	// コンボ有効フレーム
	const float MValidComboFrame;

	// 当たり判定の状態
	// true : 有効, false : 無効
	bool mIsCollisionState;
	// 現在のステートに入って1回だけ当たり判定を有効にする
	bool mIsOneCollisionState;
	// ダメージを受けたか
	bool mIsDamage;

	// ダメージ値
	int mDamageValue;
	// ヒットする相手のリストの要素数
	int mHitTagListSize;

	// 2つのベクトルのなす角
	float mTwoVectorAngle;
	// 当たり判定を無効にするタイミング
	float mBoxDisableTiming;

	// 左スティックの入力値を取得
	Vector2 mLeftAxis;
	// 座標
	Vector3 mPosition;
	// 前方ベクトル
	Vector3 mForwardVec;
	// 右方ベクトル
	Vector3 mRightVec;

	// ヒットしたオブジェクトのタグ
	Tag mHitTag;

	// プレイヤーのポインタ
	PlayerObject* mPlayerPtr;
	// カメラのポインタ
	MainCameraObject* mMainCameraPtr;
	// 1段階目の通常攻撃エフェクトのポインタ
	FirstAttackEffect* mFirstAttackEffectPtr;

public:// ゲッターセッター

	/// <summary>
	/// 当たり判定の状態を取得
	/// </summary>
	/// <returns> 当たり判定の状態 </returns>
	bool GetIsCollisionState() { return mIsCollisionState; }

	/// <summary>
	/// カメラのポインタを設定
	/// </summary>
	/// <param name="_mainCameraPtr"> カメラのポインタ </param>
	void SetMainCameraPtr(MainCameraObject* _mainCameraPtr) { mMainCameraPtr = _mainCameraPtr; }

	/// <summary>
	/// 1段階目の通常攻撃エフェクトのポインタを設定
	/// </summary>
	/// <param name="_firstAttackEffect"> 1段階目の通常攻撃エフェクトのポインタ </param>
	void SetFirstAttackEffectPtr(FirstAttackEffect* _firstAttackEffectPtr) { mFirstAttackEffectPtr = _firstAttackEffectPtr; }
};