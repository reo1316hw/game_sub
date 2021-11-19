#pragma once

/// <summary>
/// 倒したエネミーのカウントUIのテクスチャを変えるクラス
/// </summary>
class DeadEnemyCountTextChange : public Component
{
public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="_owner"> アタッチするゲームオブジェクトのポインタ </param>
	/// <param name="_spriteComponentPtr"> 画像データクラスを管理し、スクリーン上に描画するコンポーネントのポインタ </param>
	/// <param name="_enemysControlerPtr"> エネミーを制御するコンポーネントのポインタ </param>
	DeadEnemyCountTextChange(GameObject* _owner, SpriteComponent* _spriteComponentPtr, EnemysControler* _enemysControlerPtr);

	/// <summary>
	/// デストラクタ
	/// </summary>
	~DeadEnemyCountTextChange() {};

	/// <summary>
	/// フレーム毎の処理
	/// </summary>
	/// <param name="_deltaTime"> 最後のフレームを完了するのに要した時間 < /param>
	void Update(float _deltaTime)override;

private:

	// 現在の倒したエネミーの数
	int mNowDeadEnemyCount;

	// 画像データクラスを管理し、スクリーン上に描画するコンポーネントのポインタ
	SpriteComponent* mSpriteComponentPtr;
	// エネミーを制御するコンポーネントのポインタ
	EnemysControler* mEnemysControlerPtr;
};