#pragma once

// �O���錾
class DeadObjectActiveBox;

/// <summary>
/// �{�X���N�����邱�Ƃɂ���ďo�����锼�����̕ǂ̂�L���ɂ���R���|�[�l���g
/// </summary>
class DeadObjectEnable : public Component
{
public:

	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="_owner"> �A�^�b�`����Q�[���I�u�W�F�N�g�̃|�C���^ </param>
	/// <param name="_activeForObjectPtr"> �X�V�����ĂȂ��I�u�W�F�N�g���X�V�����邽�߂̃I�u�W�F�N�g�̊��N���X�̃|�C���^ </param>
	/// <param name="_deadObjectPtr"> �X�V�����ĂȂ��I�u�W�F�N�g�̃|�C���^ </param>
	DeadObjectEnable(GameObject* _owner, GameObject* _activeForObjectPtr, GameObject* _deadObjectPtr);

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~DeadObjectEnable() {};

	/// <summary>
	/// �t���[�����̏���
	/// </summary>
	/// <param name="_deltaTime"> �Ō�̃t���[������������̂ɗv�������� < /param>
	void Update(float _deltaTime)override;

private:

	// �X�V�����ĂȂ��I�u�W�F�N�g���X�V�����邽�߂̃I�u�W�F�N�g�̊��N���X�̃|�C���^
	GameObject* mActiveForObjectPtr;
	// �X�V�����ĂȂ��I�u�W�F�N�g�̃|�C���^
	GameObject* mDeadObjectPtr;
};