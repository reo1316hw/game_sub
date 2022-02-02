#pragma once

/// <summary>
/// �X�V���Ă��Ȃ��I�u�W�F�N�g���X�V�����邽�߂̓����蔻��p��`�I�u�W�F�N�g
/// </summary>
class DeadObjectActiveBox : public GameObject
{
public:

	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="_Pos"> ���W </param>
	/// <param name="_Scale"> �傫�� </param>
	/// <param name="_ObjectTag"> �I�u�W�F�N�g�̃^�O </param>
	DeadObjectActiveBox(const Vector3& _Pos, const Vector3& _Scale, const Tag& _ObjectTag);

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~DeadObjectActiveBox() {};

	/// <summary>
	/// �I�u�W�F�N�g�̍X�V����
	/// </summary>
	/// <param name="_deltaTime"> �Ō�̃t���[������������̂ɗv�������� </param>
	void UpdateGameObject(float _deltaTime)override;

	/// <summary>
	/// �q�b�g�������̏���
	/// </summary>
	/// <param name="_HitObject"> �q�b�g�����Q�[���I�u�W�F�N�g </param>
	void OnCollision(const GameObject& _HitObject)override;

private:

	// �v���C���[�Ɠ���������
	bool mIsHitPlayer;
	// �L���ɂ��邩�̃t���O
	bool mIsEnable;
};