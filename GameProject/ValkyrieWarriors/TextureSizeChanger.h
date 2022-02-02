#pragma once

/// <summary>
/// hp�Q�[�W�𐧌䂷��
/// </summary>
class TextureSizeChanger : public Component
{
public:

	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="_owner"> �A�^�b�`�����I�u�W�F�N�g�̃|�C���^ </param>
	/// <param name="_gameObjectPtr"> ���N���X�̃|�C���^ </param>
	/// <param name="_IsInitScaleChange"> �ŏ��ɃI�u�W�F�N�g�̑傫���̕ύX���s���� </param>
	TextureSizeChanger(GameObject* _owner, GameObject* _gameObjectPtr, const bool& _IsInitScaleChange);
	
	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~TextureSizeChanger() {};

	/// <summary>
	/// �t���[�����̏���
	/// </summary>
	/// <param name="_deltaTime"> �Ō�̃t���[������������̂ɗv�������� </param>
	void Update(float _deltaTime)override;

private:

	// ���݂̃X�P�[���T�C�Y�����߂邽�߂̍��ӂ̒l
	int mNowScaleLeftSideValue;

	// �X�P�[���T�C�Y�����߂邽�߂̉E�ӂ̒l
	float mScaleRightSideValue;

	// �A�^�b�`�����I�u�W�F�N�g�̏����̑傫��
	Vector3 mInitScale;

	// ���N���X�̃|�C���^
	GameObject* mGameObjectPtr;
};