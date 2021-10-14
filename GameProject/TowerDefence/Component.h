#pragma once

// �O���錾
class GameObject;

class Component
{
public:

	/*
	@param	�A�^�b�`����Q�[���I�u�W�F�N�g�̃|�C���^
	@param	�R���|�[�l���g�̍X�V���ԁi���l���������قǑ����X�V�����j
	*/
	Component(GameObject* _owner,int _updateOrder = 100);
	virtual ~Component();

	/*
	@brief	�t���[�����̏���
	@param	�Ō�̃t���[������������̂ɗv��������
	*/
	virtual void Update(float _deltaTime);

	/*
	@brief	���͏���
	@param	InputState�\����
	*/
	virtual void ProcessInput(const struct InputState& _state) {}

	/*
	@brief	Transform�̃��[���h�ϊ�
	*/
	virtual void OnUpdateWorldTransform() {}

protected:

	//�A�^�b�`���Ă���Q�[���I�u�W�F�N�g�̃|�C���^
	GameObject* mOwner;			
	// �R���|�[�l���g�̍X�V���ԁi���l���������قǑ����X�V�����j
	int mUpdateOrder;

public: //�Q�b�^�[�Z�b�^�[

	/*
	@return �X�V����
	*/
	int GetUpdateOder() { return mUpdateOrder; }

	/*
	@return �A�^�b�`���Ă���Q�[���I�u�W�F�N�g�ւ̃|�C���^
	*/
	GameObject* GetOwner() { return mOwner; }
};

