#pragma once

/// <summary>
/// �������̕�
/// </summary>
class SemitransparentWall : public GameObject
{
public:

	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="_Pos"> ���W </param>
	/// <param name="_Scale"> �傫�� </param>
	/// <param name="_ObjectTag"> �I�u�W�F�N�g�̃^�O </param>
	SemitransparentWall(const Vector3& _Pos, const Vector3& _Scale, const Tag& _ObjectTag);

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~SemitransparentWall() {};

	/// <summary>
	/// �I�u�W�F�N�g�̍X�V����
	/// </summary>
	/// <param name="_deltaTime"> �Ō�̃t���[������������̂ɗv�������� </param>
	void UpdateGameObject(float _deltaTime)override;

private:
};