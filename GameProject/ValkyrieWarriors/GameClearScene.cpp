#include "pch.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
GameClearScene::GameClearScene()
	: MSpriteScale(Vector3(2.0f, 1.0f, 1.0f))
	, MTimingTransitionTitle(120)
	, mTitleTransitionUntilCount(0)
{
	// ���C�g��ݒ�(�ݒ肵�Ȃ��Ɖ����f��Ȃ�)
	RENDERER->SetAmbientLight(Vector3(0.4f, 0.4f, 0.4f));
	DirectionalLight& dir = RENDERER->GetDirectionalLight();
	dir.m_direction = Vector3(1.0f, 0.7f, -0.7f);
	dir.m_diffuseColor = Vector3(0.78f, 0.88f, 1.0f);
	dir.m_specColor = Vector3(0.8f, 0.8f, 0.8f);

	// �Q�[���N���A�p�̃X�v���C�g�𐶐�
	mSprite = new Sprite("Assets/Texture/GameClear.png", true, 1.0f, MSpriteScale);
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
GameClearScene::~GameClearScene()
{
	delete mSprite;
}

/// <summary>
/// �V�[���̍X�V
/// </summary>
/// <param name="_KeyState"> �L�[�{�[�h�A�}�E�X�A�R���g���[���[�̓��͏�� </param>
/// <returns> �V�[���N���X�̃|�C���^ </returns>
SceneBase* GameClearScene::Update(const InputState& _KeyState)
{
	++mTitleTransitionUntilCount;

	// �^�C�g���V�[���ɑJ��
	if (mTitleTransitionUntilCount >= MTimingTransitionTitle)
	{
		return new TitleScene();
	}

	return this;
}