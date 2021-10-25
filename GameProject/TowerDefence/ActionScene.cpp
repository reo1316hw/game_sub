#include "pch.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
ActionScene::ActionScene()
	: mPlayerPtr(nullptr)
	, mBossPtr(nullptr)
{
	// ���C�g��ݒ�(�ݒ肵�Ȃ��Ɖ����f��Ȃ�)
	RENDERER->SetAmbientLight(Vector3(0.8f, 0.8f, 0.8f));
	DirectionalLight& dir = RENDERER->GetDirectionalLight();
	dir.m_direction = Vector3(0.0f, 0.0f, 1.0f);
	dir.m_diffuseColor = Vector3(0.36f, 0.44f, 0.5f);
	dir.m_specColor = Vector3(0.4f, 0.4f, 0.4f);

	// �}�b�v�𐶐����邽�߂̃N���X�𐶐�
    mMapCreate = new MapCreate();
	mMapCreate->OpenFile();
	mPlayerPtr = mMapCreate->GetPlayerPtr();
	mBossPtr = mMapCreate->GetBossPtr();

	// �X�J�C�{�b�N�X����
	new SkyBoxObject(Tag::eOther, false);
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
ActionScene::~ActionScene()
{
	GAME_OBJECT_MANAGER->RemoveAllUsedGameObject();
}

/// <summary>
/// �V�[���̍X�V
/// </summary>
/// <param name="_KeyState"> �L�[�{�[�h�A�}�E�X�A�R���g���[���[�̓��͏�� </param>
/// <returns> �V�[���N���X�̃|�C���^ </returns>
SceneBase* ActionScene::Update(const InputState& _KeyState)
{
	// �{�X��hp��0�ɂȂ�����Q�[���N���A�V�[���֑J��
	if (mBossPtr->GetHitPoint() <= 0)
	{
		return new GameClearScene();
	}
	
	// �v���C���[��hp��0�ɂȂ�����Q�[���I�[�o�[�V�[���֑J��
	if (mPlayerPtr->GetHitPoint() <= 0)
	{
		return new GameOverScene();
	}

	// �����蔻�������������f�o�b�O���[�h�̐؂�ւ�
	if (_KeyState.m_keyboard.GetKeyState(SDL_SCANCODE_0) == Released)
	{
		PHYSICS->ToggleDebugMode();
	}

	return this;
}
