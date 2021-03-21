#pragma once

#include <vector>
#include <string>
#include <unordered_map>
#include "Math.h"
#include "Collision.h"

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
    std::vector<Texture*> textures;
	//���̃��b�V���Ɏg�����_�f�[�^
	std::vector<Vector3> verts;
	//�N���X�̃|�C���^
    VertexArray* vertexArray;

    //���̃��b�V���Ɏg���V�F�[�_�[�̖��O
    std::string shaderName;
    //�I�u�W�F�N�g��Ԃł̋��E���̔��a
    float radius;
    //���ʔ��ː����̑傫��
    float specPower;
	// ���Ȕ������x(HDR)
	float luminance;
	// �����x
	float alpha;

	AABB mBox;

	// �e�N�X�`���X�e�[�W�Ɋ��蓖�Ă�ꂽ�e�N�X�`��
	std::unordered_map<TextureStage, int> stageDefTexture;

public://�Q�b�^�[�Z�b�^�[
	/*
	@return	VertexArray�^�̃|�C���^
	*/
	VertexArray* GetVertexArray() { return vertexArray; }

	/*
	@return Texture�N���X�̃|�C���^
	*/
	Texture* GetTexture(size_t _index);

	int GetTextureID(TextureStage stage);

	/*
	@return Texture�N���X�̃|�C���^
	*/
	const std::string& GetShaderName() const { return shaderName; }

	/*
	@return ���a
	*/
	float GetRadius() const { return radius; }

	/*
	@return ���ʔ��ː���
	*/
	float GetSpecPower() const { return specPower; }

	/*
	@return ���Ȕ������x
	*/
	float GetLuminace() const { return luminance; }

	/*
	@return �����x
	*/
	float GetAlpha() const { return alpha; }

	const AABB& GetBox() const { return mBox; }

	/*
	@return ���_�f�[�^
	*/
	std::vector<Vector3> GetVerts() { return verts; }
};