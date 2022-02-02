#include "pch.h"

/// <summary>
/// コンストラクタ
/// </summary>
Font::Font()
{
}

/// <summary>
/// フォントファイルの読み込みを行う
/// </summary>
/// <param name="_FileName"> 読み込むフォントファイルのパス </param>
/// <returns> フォントファイルを読み込めたか </returns>
bool Font::Load(const std::string& _FileName)
{
	// サポートされているフォントサイズ
	std::vector<int> fontSizes = {
		8, 9,
		10, 11, 12, 14, 16, 18,
		20, 22, 24, 26, 28,
		30, 32, 34, 36, 38,
		40, 42, 44, 46, 48,
		52, 56,
		60, 64, 68,
		72
	};

	for (auto& size : fontSizes)
	{
		TTF_Font* font = TTF_OpenFont(_FileName.c_str(), size);
		if (font == nullptr)
		{
			SDL_Log("Failed to load font %s in size %d", _FileName.c_str(), size);
			return false;
		}
		mFontData.emplace(size, font);
	}
	return true;
}

/// <summary>
/// フォントファイルを破棄
/// </summary>
void Font::Unload()
{
	for (auto& font : mFontData)
	{
		TTF_CloseFont(font.second);
	}
}

/// <summary>
/// フォントを使用したtextureの生成を行う
/// </summary>
/// <param name="_RenderingText"> 生成するtextureに使用する文字列 </param>
/// <param name="_Color"> 指定する色（デフォルトは白） </param>
/// <param name="_PointSize"> フォントのサイズ（デフォルトは30） </param>
Texture* Font::RenderText(const std::string& _RenderingText, const Vector3& _Color, const int& _PointSize)
{
	Texture* texture = nullptr;

	// SDL_Colorを変換
	SDL_Color sdlColor;
	sdlColor.r = static_cast<Uint8>(_Color.x * 255);
	sdlColor.g = static_cast<Uint8>(_Color.y * 255);
	sdlColor.b = static_cast<Uint8>(_Color.z * 255);
	sdlColor.a = 255;

	// フォントデータからポイントサイズを探す
	auto iter = mFontData.find(_PointSize);
	if (iter != mFontData.end())
	{
		TTF_Font* font = iter->second;
		const std::string& actualText = _RenderingText;

		SDL_Surface* surf = TTF_RenderUTF8_Blended(font, actualText.c_str(), sdlColor);
		if (surf != nullptr)
		{
			// サーフェスからテクスチャに変換する
			texture = new Texture();
			texture->CreateFromSurface(surf);
			SDL_FreeSurface(surf);
		}
	}
	else
	{
		SDL_Log("Point size %d is unsupported", _PointSize);
	}

	return texture;
}

