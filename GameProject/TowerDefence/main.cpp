#include "pch.h"

/// <summary>
/// クラス内での宣言順番はpublic>protected>private>public(GetSet)の順
/// </summary>

/// <summary>
/// main関数
/// </summary>
/// <param name="argc"> コマンドライン引数の数 </param>
/// <param name="argv"> コマンドライン引数 </param>
/// <returns> 終了するか </returns>
int main(int argc, char** argv)
{
	//ゲームクラスの定義
	Game game;
	//ゲームクラスの初期化が成功したか
	bool success = game.Initialize();
	game.SetFirstScene(new TitleScene());
	if (success)
	{
		game.GameLoop();
	}
	//ゲームクラスの終了処理
	game.Termination();

	return 0;
}