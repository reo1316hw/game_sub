#pragma once

/// <summary>
/// �ۂ��e
/// </summary>
class CircleShadowObject : public GameObject
{
public:

	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="_owner"> �e�N���X�̃|�C���^ </param>
	/// <param name="_Scale"> �傫�� </param>
	/// <param name="_GpmeshName"> gpmesh�̃p�X </param>
	/// <param name="_ObjectTag"> �I�u�W�F�N�g�̃^�O </param>
	CircleShadowObject(GameObject* _owner, const Vector3& _Scale, const std::string _GpmeshName, const Tag& _ObjectTag);

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~CircleShadowObject() {};

	/// <summary>
	/// �I�u�W�F�N�g�̍X�V����
	/// </summary>
	/// <param name="_deltaTime"> �Ō�̃t���[������������̂ɗv�������� </param>
	void UpdateGameObject(float _deltaTime)override;

private:

	// �e�I�u�W�F�N�g����̋���
	const Vector3 MDistance;

	// �e�N���X�̃|�C���^
	GameObject* mOwner;
};