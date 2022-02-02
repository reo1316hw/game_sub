#pragma once

/// <summary>
/// �G�l�~�[���X�V�����邽�߂̓����蔻��p��`�I�u�W�F�N�g
/// </summary>
class EnemyActiveBox : public GameObject
{
public:

	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="_Pos"> ���W </param>
	/// <param name="_Scale"> �傫�� </param>
	/// <param name="_ObjectTag"> �I�u�W�F�N�g�̃^�O </param>
	EnemyActiveBox(const Vector3& _Pos, const Vector3& _Scale, const Tag& _ObjectTag);

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~EnemyActiveBox() {};

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

public:// �Q�b�^�[�Z�b�^�[

	/// <summary>
	/// �v���C���[�Ɠ����������t���O���擾
	/// </summary>
	/// <returns> �v���C���[�Ɠ��������� </returns>
	bool GetIsHitPlayer() { return mIsHitPlayer; }
};