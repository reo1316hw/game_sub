#pragma once

/// <summary>
/// フォントデータの読み込みとフォントの生成を行う
/// </summary>
class Font
{
public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	Font();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~Font() {};

	/// <summary>
	/// フォントファイルの読み込みを行う
	/// </summary>
	/// <param name="_FileName"> 読み込むフォントファイルのパス </param>
	/// <returns> フォントファイルを読み込めたか </returns>
	bool Load(const std::string& _FileName);

	/// <summary>
	/// フォントファイルを破棄
	/// </summary>
	void Unload();

	/// <summary>
	/// フォントを使用したテクスチャの生成を行う
	/// </summary>
	/// <param name="_RenderingText"> 生成するテクスチャに使用する文字列 </param>
	/// <param name="_Color"> 指定する色（デフォルトは白） </param>
	/// <param name="_PointSize"> フォントのサイズ（デフォルトは30） </param>
	Texture* RenderText(const std::string& _RenderingText, const Vector3& _Color = Color::White, const int& _PointSize = 30);

private:

	// フォントサイズを格納するデータ連想配列
	std::unordered_map<int, TTF_Font*> mFontData;
};

