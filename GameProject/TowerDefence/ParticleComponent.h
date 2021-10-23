#pragma once

/*
 @file ParticleComponent.h
 @brief �摜���Ǘ��������3D��ԏ�ɕ`�悷��N���X�B
*/
class ParticleComponent : public Component
{
public:

	//�p�[�e�B�N���ɑ΂���u�����h�̎��
	typedef enum PARTICLE_BLEND_ENUM
	{
		PARTICLE_BLEND_ENUM_ALPHA,
		PARTICLE_BLEND_ENUM_ADD,
		PARTICLE_BLEND_ENUM_MULT
	}PARTICLE_ENUM;

	/*
	 @param _offset �e�I�u�W�F�N�g�N���X�Ɖ摜��`�悷��ʒu�̍�
	 @param _scale �摜�̕`��T�C�Y
	*/
	ParticleComponent(GameObject* _owner, Texture* _texture, float _scale = 1.0f, int _updateOrder = 100);
	ParticleComponent(GameObject* _owner, Texture* _texture, HitPointGaugeController* _hitPointGaugeControllerconst, float _scale = 1.0f, int _updateOrder = 100);
	~ParticleComponent();

	virtual void Update(float _deltaTime) override {};

	/*
	@brief�@�`�揈��
	@param	_shader �g�p����V�F�[�_�[�N���X�̃|�C���^
	*/
	void Draw(class Shader* _shader);

	Matrix4 GetBillboardMatrix();

	//// �J���������ł̃\�[�g�p
	//bool operator < (const ParticleComponent& _rhs) const;
	//bool operator > (const ParticleComponent& _rhs) const;

private:

	//���]���s����
	bool mReverce;
	//�`����s����
	bool mVisible;

	//�`�揇(���������Ȃ����̂���`�悳���)
	int mDrawOrder;
	//�e�N�X�`���̉���
	int mTextureWidth;
	//�e�N�X�`���̏c��
	int mTextureHeight;

	//�T�C�Y
	float mScale;
	//�����x
	float mAlpha;

	//�摜�ɏ�Z����F
	Vector3 mColor;
	//�u�����h�^�C�v
	PARTICLE_ENUM mBlendType;

	// �r���{�[�h�s��
	static Matrix4 mStaticBillboardMat;
	// �J�����̃��[���h���W
	static Vector3 mStaticCameraWorldPos;

	// hp�Q�[�W�𐧌䂷��R���|�[�l���g�N���X�̃|�C���^
	HitPointGaugeController* mHitPointGaugeControllerPtr;

	//�N���X�̃|�C���^
	Texture* mTexture;

public: //�Q�b�^�[�Z�b�^�[

	/*
	@return �e�N�X�`��
	*/
	Texture* GetTexture() { return mTexture; }

	/*
	@return �u�����h�^�C�v
	*/
	PARTICLE_ENUM GetBlendType() { return mBlendType; }

	/*
	@param _brendType �J�����̃��[���h���W
	*/
	void SetBlendMode(PARTICLE_ENUM _blendType) { mBlendType = _blendType; }

	/*
	@param _mat �r���{�[�h�s��
	*/
	void SetBillboardMat(const Matrix4& _mat) {	mStaticBillboardMat = _mat; }
	
	/*
	@brief�@�`������邩�ǂ������擾����
	@return	true : �`�悷�� , false : �`�悵�Ȃ�
	*/
	bool GetVisible() const { return mVisible; }

	/*
	@brief�@�`������邩�ǂ�����ݒ�
	@param	true : �`�悷�� , false : �`�悵�Ȃ�
	*/
	void SetVisible(bool _visible) { mVisible = _visible; }

	/*
	@return �`�揇
	*/
	int GetDrawOrder() { return mDrawOrder; }

	/*
	@param _drawOrder �`�揇
	*/
	void SetDrawOrder(int _drawOrder) { mDrawOrder = _drawOrder; }

	/*
	@param _flag ���]���s����
	*/
	void SetReverce(bool _flag) { mReverce = _flag; }
};