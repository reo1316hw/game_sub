#pragma once

// �O���錾
class GameObject;

/// <summary>
/// �R���|�[�l���g�̊��N���X
/// </summary>
class Component
{
public:

	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="_owner"> �A�^�b�`����Q�[���I�u�W�F�N�g�̃|�C���^ </param>
	/// <param name="_UpdateOrder"> �R���|�[�l���g�̍X�V���ԁi���l���������قǑ����X�V�����j </param>
	Component(GameObject* _owner, const int _UpdateOrder = 100);

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	virtual ~Component();

	/// <summary>
	/// �t���[�����̏���
	/// </summary>
	/// <param name="_deltaTime"> �Ō�̃t���[������������̂ɗv�������� < /param>
	virtual void Update(float _deltaTime) {};

	/// <summary>
	/// ���͏���
	/// </summary>
	/// <param name="_state"> InputState�\���� </param>
	virtual void ProcessInput(const struct InputState& _state) {}

	/// <summary>
	/// Transform�̃��[���h�ϊ�
	/// </summary>
	virtual void OnUpdateWorldTransform() {}

protected:

	// �R���|�[�l���g�̍X�V���ԁi���l���������قǑ����X�V�����j
	int mUpdateOrder;

	// �A�^�b�`���Ă���Q�[���I�u�W�F�N�g�̃|�C���^
	GameObject* mOwner;			
	
public://�Q�b�^�[�Z�b�^�[

	/// <summary>
	/// �X�V���Ԃ��擾
	/// </summary>
	/// <returns> �X�V���� </returns>
	int GetUpdateOder() { return mUpdateOrder; }

	/// <summary>
	/// �A�^�b�`���Ă���Q�[���I�u�W�F�N�g�ւ̃|�C���^���擾
	/// </summary>
	/// <returns> �A�^�b�`���Ă���Q�[���I�u�W�F�N�g�ւ̃|�C���^ </returns>
	GameObject* GetOwner() { return mOwner; }
};