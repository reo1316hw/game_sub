#pragma once

/// <summary>
/// �|�����G�l�~�[���J�E���g����I�u�W�F�N�g�𖳌��ɂ���N���X
/// </summary>
class ActiveObjectDisable : public Component
{
public:

	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="_owner"> �A�^�b�`����Q�[���I�u�W�F�N�g�̃|�C���^ </param>
	/// <param name="_deadForObjectPtr"> �X�V���Ă���I�u�W�F�N�g���X�V�����Ȃ��悤�ɂ��邽�߂̃I�u�W�F�N�g�̊��N���X�̃|�C���^ </param>
	ActiveObjectDisable(GameObject* _owner, GameObject* _deadForObjectPtr);

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~ActiveObjectDisable() {};

	/// <summary>
	/// �t���[�����̏���
	/// </summary>
	/// <param name="_deltaTime"> �Ō�̃t���[������������̂ɗv�������� < /param>
	void Update(float _deltaTime)override;

private:

	// �X�V���Ă���I�u�W�F�N�g���X�V�����Ȃ��悤�ɂ��邽�߂̃I�u�W�F�N�g�̊��N���X�̃|�C���^
	GameObject* mDeadForObjectPtr;
};

