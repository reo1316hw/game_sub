#pragma once

/// <summary>
/// �t�H���g�f�[�^�̓ǂݍ��݂ƃt�H���g�̐������s��
/// </summary>
class Font
{
public:

	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	Font();

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~Font() {};

	/// <summary>
	/// �t�H���g�t�@�C���̓ǂݍ��݂��s��
	/// </summary>
	/// <param name="_FileName"> �ǂݍ��ރt�H���g�t�@�C���̃p�X </param>
	/// <returns> �t�H���g�t�@�C����ǂݍ��߂��� </returns>
	bool Load(const std::string& _FileName);

	/// <summary>
	/// �t�H���g�t�@�C����j��
	/// </summary>
	void Unload();

	/// <summary>
	/// �t�H���g���g�p�����e�N�X�`���̐������s��
	/// </summary>
	/// <param name="_RenderingText"> ��������e�N�X�`���Ɏg�p���镶���� </param>
	/// <param name="_Color"> �w�肷��F�i�f�t�H���g�͔��j </param>
	/// <param name="_PointSize"> �t�H���g�̃T�C�Y�i�f�t�H���g��30�j </param>
	Texture* RenderText(const std::string& _RenderingText, const Vector3& _Color = Color::White, const int& _PointSize = 30);

private:

	// �t�H���g�T�C�Y���i�[����f�[�^�A�z�z��
	std::unordered_map<int, TTF_Font*> mFontData;
};

