#pragma once

class EffectComponent : public Component
{
public:
	EffectComponent(GameObject* owner, const Vector3& _Scale, const char16_t* effkseerFilename, bool moveOn = false, bool rotateOn = false, int updateOrder = 100);
	~EffectComponent() {};
	
	void Update(float deltaTime) override;
	
	void PlayEffect(const float& _PlayRate = 1.0f);

	/// <summary>
	/// �Đ��ς݂�
	/// </summary>
	bool IsPlayedEffect();
	
	void SetRelativePosition(const Vector3& relativePos) { mRelativePos = relativePos; }
	void SetRelativeRotate(const Matrix4& relativeRotMat) { mRelativeRot = relativeRotMat; }
	void SetMove(bool move) { mIsMove = move; }
	void SetRotate(bool rotate) { mIsRotate = rotate; }

private:

	Effekseer::Handle mHandle;           // �G�t�F�N�g�p�����[�^���Ǘ����邽�߂̃n���h��
	bool              mIsMove;           // �I�[�i�[�A�N�^�[�̈ړ��ɍ��킹��
	bool              mIsRotate;         // �I�[�i�[�A�N�^�[�̉�]�ړ��ɍ��킹��

	// �Đ����x
	float mPlayerRate;
	
	// �傫��
	Vector3           mScale;
	Vector3           mRelativePos;      // �I�[�i�[�A�N�^�[�̑��΍��W
	Matrix4           mRelativeRot;      // ���Ή�]�s��

	EffekseerEffect* mEffectPtr;
};