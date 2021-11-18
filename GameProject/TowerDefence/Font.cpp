#include "pch.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
Font::Font()
{
}

/// <summary>
/// �t�H���g�t�@�C���̓ǂݍ��݂��s��
/// </summary>
/// <param name="_FileName"> �ǂݍ��ރt�H���g�t�@�C���̃p�X </param>
/// <returns> �t�H���g�t�@�C����ǂݍ��߂��� </returns>
bool Font::Load(const std::string& _FileName)
{
	// �T�|�[�g����Ă���t�H���g�T�C�Y
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
/// �t�H���g�t�@�C����j��
/// </summary>
void Font::Unload()
{
	for (auto& font : mFontData)
	{
		TTF_CloseFont(font.second);
	}
}

/// <summary>
/// �t�H���g���g�p����texture�̐������s��
/// </summary>
/// <param name="_RenderingText"> ��������texture�Ɏg�p���镶���� </param>
/// <param name="_Color"> �w�肷��F�i�f�t�H���g�͔��j </param>
/// <param name="_PointSize"> �t�H���g�̃T�C�Y�i�f�t�H���g��30�j </param>
Texture* Font::RenderText(const std::string& _RenderingText, const Vector3& _Color, const int& _PointSize)
{
	Texture* texture = nullptr;

	// SDL_Color��ϊ�
	SDL_Color sdlColor;
	sdlColor.r = static_cast<Uint8>(_Color.x * 255);
	sdlColor.g = static_cast<Uint8>(_Color.y * 255);
	sdlColor.b = static_cast<Uint8>(_Color.z * 255);
	sdlColor.a = 255;

	// �t�H���g�f�[�^����|�C���g�T�C�Y��T��
	auto iter = mFontData.find(_PointSize);
	if (iter != mFontData.end())
	{
		TTF_Font* font = iter->second;
		const std::string& actualText = _RenderingText;

		SDL_Surface* surf = TTF_RenderUTF8_Blended(font, actualText.c_str(), sdlColor);
		if (surf != nullptr)
		{
			// �T�[�t�F�X����e�N�X�`���ɕϊ�����
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

