#pragma once

/// <summary>
/// �摜���Ǘ��������3D��ԏ�ɕ`�悷��N���X
/// </summary>
class ParticleComponent : public Component
{
public:

	/// <summary>
	/// �p�[�e�B�N���ɑ΂���u�����h�̎��
	/// </summary>
	typedef enum ParticleBlendType
	{
		eParticleBlendAlpha,
		eParticleBlendAdd,
		eParticleBlendMult
	}ParticleType;

	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="_owner"> �A�^�b�`����Q�[���I�u�W�F�N�g�̃|�C���^ </param>
	/// <param name="_texture"> �e�N�X�`���̃|�C���^ </param>
	/// <param name="_Scale"> �摜�̕`��T�C�Y </param>
	/// <param name="_UpdateOrder"> �R���|�[�l���g�̍X�V���ԁi���l���������قǑ����X�V�����j</param>
	ParticleComponent(GameObject* _owner, Texture* _texture, const Vector3& _Scale = Vector3(1.0f, 1.0f, 1.0f), const int& _UpdateOrder = 100);

	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="_owner"> �A�^�b�`����Q�[���I�u�W�F�N�g�̃|�C���^ </param>
	/// <param name="_texture"> �e�N�X�`���̃|�C���^ </param>
	/// <param name="_hitPointGaugeControllerconst"> hp�Q�[�W�𐧌䂷��N���X�̃|�C���^ </param>
	/// <param name="_Scale"> �摜�̕`��T�C�Y </param>
	/// <param name="_UpdateOrder"> �R���|�[�l���g�̍X�V���ԁi���l���������قǑ����X�V�����j</param>
	ParticleComponent(GameObject* _owner, Texture* _texture, HitPointGaugeController* _hitPointGaugeControllerconst, const Vector3& _Scale = Vector3(1.0f,1.0f,1.0f), const int& _updateOrder = 100);
	
	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~ParticleComponent();

	/// <summary>
	/// �`�揈��
	/// </summary>
	/// <param name="_shader"> �g�p����V�F�[�_�[�N���X�̃|�C���^ </param>
	void Draw(class Shader* _shader);

	/// <summary>
	/// �r���{�[�h�s��쐬
	/// </summary>
	/// <returns></returns>
	Matrix4 CreateBillboardMatrix();

private:

	// �`����s����
	bool mVisible;

	// �`�揇(���������Ȃ����̂���`�悳���)
	int mDrawOrder;
	// �e�N�X�`���̉���
	int mTextureWidth;
	// �e�N�X�`���̏c��
	int mTextureHeight;

	// �����x
	float mAlpha;

	// �T�C�Y
	Vector3 mScale;
	// �摜�ɏ�Z����F
	Vector3 mColor;
	// �r���{�[�h�s��
	Matrix4 mBillboardMat;
	// �u�����h�^�C�v
	ParticleType mBlendType;

	// hp�Q�[�W�𐧌䂷��R���|�[�l���g�N���X�̃|�C���^
	HitPointGaugeController* mHitPointGaugeControllerPtr;
	// �N���X�̃|�C���^
	Texture* mTexture;

public:// �Q�b�^�[�Z�b�^�[

	/// <summary>
	/// �`������邩�ǂ����̃t���O���擾����
	/// </summary>
	/// <returns> true : �`�悷�� , false : �`�悵�Ȃ� </returns>
	bool GetVisible() const { return mVisible; }

	/// <summary>
	/// �`������邩�ǂ����̃t���O��ݒ�
	/// </summary>
	/// <param name="_visible"> �`������邩�ǂ����̃t���O </param>
	void SetVisible(bool _visible) { mVisible = _visible; }

	/// <summary>
	/// �`�揇���擾
	/// </summary>
	/// <returns> �`�揇 </returns>
	int GetDrawOrder() { return mDrawOrder; }

	/// <summary>
	/// �`�揇��ݒ�
	/// </summary>
	/// <param name="_drawOrder"> �`�揇 </param>
	void SetDrawOrder(int _drawOrder) { mDrawOrder = _drawOrder; }

	/// <summary>
	/// �u�����h�^�C�v���擾
	/// </summary>
	/// <returns> �u�����h�^�C�v </returns>
	ParticleType GetBlendType() { return mBlendType; }

	/// <summary>
	/// �u�����h�^�C�v��ݒ�
	/// </summary>
	/// <param name="_blendType"> �u�����h�^�C�v </param>
	void SetBlendMode(ParticleType _blendType) { mBlendType = _blendType; }

	/// <summary>
	/// �e�N�X�`���̃|�C���^�擾
	/// </summary>
	/// <returns> �e�N�X�`���̃|�C���^ </returns>
	Texture* GetTexture() { return mTexture; }
};