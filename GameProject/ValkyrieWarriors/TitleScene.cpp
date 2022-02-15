#include "pch.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
TitleScene::TitleScene()
    : MSpriteScale(Vector3(2.0f, 1.0f, 1.0f))
{
	// ���C�g��ݒ�(�ݒ肵�Ȃ��Ɖ����f��Ȃ�)
	RENDERER->SetAmbientLight(Vector3(0.4f, 0.4f, 0.4f));
	DirectionalLight& dir = RENDERER->GetDirectionalLight();
	dir.m_direction = Vector3(1.0f, 0.7f, -0.7f);
	dir.m_diffuseColor = Vector3(0.78f, 0.88f, 1.0f);
	dir.m_specColor = Vector3(0.8f, 0.8f, 0.8f);

	// �X�^�[�g��ʗp�̃X�v���C�g�𐶐�
	mSprite = new Sprite("Assets/Texture/Title.png", false, 1.0f, MSpriteScale);
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
TitleScene::~TitleScene()
{
	delete mSprite;
}

/// <summary>
/// �V�[���̍X�V
/// </summary>
/// <param name="_KeyState"> �L�[�{�[�h�A�}�E�X�A�R���g���[���[�̓��͏�� </param>
/// <returns> �V�[���N���X�̃|�C���^ </returns>
SceneBase* TitleScene::Update(const InputState& _KeyState)
{
	// �A�N�V�����V�[���ɑJ��
	if (_KeyState.m_controller.GetButtonState(SDL_CONTROLLER_BUTTON_A) == Released ||
		_KeyState.m_keyboard.GetKeyState(SDL_SCANCODE_SPACE) == Released)
	{
  		return new ActionScene();
	}

	return this;
}