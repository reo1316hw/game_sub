#pragma once

// �O���錾
class Renderer;
class VertexArray;
class Texture;

enum class TextureStage;

	/*
@file Mesh.h
@brief ���b�V���f�[�^
*/
class Mesh
{
public:
    Mesh();
    ~Mesh();
	/*
	@brief  ���b�V���f�[�^�̓ǂݍ���
	@param	_fileName ���[�h���������b�V���̃t�@�C����
	@param	_renderer Renderer�N���X�̃|�C���^
	@return true : ���� , false : ���s
	*/
    bool Load(const std::string& _fileName, Renderer* _renderer);

	/*
	@brief  ���[�h�������b�V���f�[�^�̉��
	*/
    void Unload();
private:
    //���̃��b�V���Ɏg���e�N�X�`���̃|�C���^�̉ϒ��R���e�i
    std::vector<Texture*> mTextures;
	//���̃��b�V���Ɏg�����_�f�[�^
	std::vector<Vector3> mVerts;
	//�N���X�̃|�C���^
    VertexArray* mVertexArray;

    //���̃��b�V���Ɏg���V�F�[�_�[�̖��O
    std::string mShaderName;
    //�I�u�W�F�N�g��Ԃł̋��E���̔��a
    float mRadius;
    //���ʔ��ː����̑傫��
    float mSpecPower;
	// ���Ȕ������x(HDR)
	float mLuminance;
	// �����x
	float mAlpha;
	// ��`�����蔻��
	AABB mBox;

	// �e�N�X�`���X�e�[�W�Ɋ��蓖�Ă�ꂽ�e�N�X�`��
	std::unordered_map<TextureStage, int> mStageDefTexture;

public://�Q�b�^�[�Z�b�^�[
	/*
	@return	VertexArray�^�̃|�C���^
	*/
	VertexArray* GetVertexArray() { return mVertexArray; }

	/*
	@return Texture�N���X�̃|�C���^
	*/
	Texture* GetTexture(size_t _index);

	int GetTextureID(TextureStage _stage);

	/*
	@return Texture�N���X�̃|�C���^
	*/
	const std::string& GetShaderName() const { return mShaderName; }

	/*
	@return ���a
	*/
	float GetRadius() const { return mRadius; }

	/*
	@return ���ʔ��ː���
	*/
	float GetSpecPower() const { return mSpecPower; }

	/*
	@return ���Ȕ������x
	*/
	float GetLuminace() const { return mLuminance; }

	/*
	@return �����x
	*/
	float GetAlpha() const { return mAlpha; }

	const AABB& GetBox() const { return mBox; }

	/*
	@return ���_�f�[�^
	*/
	std::vector<Vector3> GetVerts() { return mVerts; }
};