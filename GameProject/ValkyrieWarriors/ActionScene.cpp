#include "pch.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
ActionScene::ActionScene()
	: MPlusAlpha(0.006f)
	, MAngleOfView(70.0f)
	, MLightDistance(100.0f)
	, MSpriteScale(Vector3(2.0f, 1.0f, 1.0f))
	, mPlayerPtr(nullptr)
	, mBossPtr(nullptr)
	, mMainCameraPtr(nullptr)
{
	// ���C�g��ݒ�(�ݒ肵�Ȃ��Ɖ����f��Ȃ�)
	RENDERER->SetAmbientLight(Vector3(0.2f, 0.2f, 0.2f));
	DirectionalLight& dir = RENDERER->GetDirectionalLight();
	dir.m_direction = Vector3(-0.5f, 0.5f, -0.5f);
	//dir.m_diffuseColor = Vector3(0.35f, 0.45f, 0.5f);
	dir.m_diffuseColor = Vector3(0.35f, 0.45f, 0.5f);
	dir.m_specColor = Vector3(0.4f, 0.4f, 0.4f);

	// �s�񏉊���
	Matrix4 proj;
	proj = Matrix4::CreatePerspectiveFOV(Math::ToRadians(MAngleOfView), RENDERER->GetScreenWidth(), RENDERER->GetScreenHeight(), 1.0, 10000.0f);
	RENDERER->SetProjMatrix(proj);

	// �}�b�v�𐶐����邽�߂̃N���X�𐶐�
    mMapCreate = new MapCreate();
	mMapCreate->OpenFile();
	mPlayerPtr = mMapCreate->GetPlayerPtr();
	mBossPtr = mMapCreate->GetBossPtr();

	// ��̃��X�g
	std::vector<GateObject*> gateList = mMapCreate->GetGateList();
	// �G�l�~�[���Ǘ�����N���X�̃|�C���^
	EnemyObjectManager* enemyObjectManagerPtr = mMapCreate->GetEnemyObjectManagerPtr();
	// �G�l�~�[���X�V�����邽�߂̓����蔻��p��`�I�u�W�F�N�g�̃|�C���^
	DeadObjectActiveBox* enemyActiveBoxPtr = mMapCreate->GetEnemyActiveBoxPtr();
	// �{�X���X�V�����邽�߂̓����蔻��p��`�I�u�W�F�N�g�̃|�C���^
	DeadObjectActiveBox* bossActiveBoxPtr = mMapCreate->GetBossActiveBoxPtr();

	// �J��������
	mMainCameraPtr = new MainCameraObject(mPlayerPtr, mBossPtr, gateList, true);
	// UI�̐e�N���X
	new UIRoot(Tag::eOther, mPlayerPtr, mBossPtr, enemyObjectManagerPtr, enemyActiveBoxPtr, bossActiveBoxPtr);

	// �v���C���[�N���X�ŃJ�����̃|�C���^��ݒ�
	mPlayerPtr->SetMainCameraPtr(mMainCameraPtr);

	// �X�J�C�{�b�N�X����
	new SkyBoxObject(Tag::eOther, false);

	// �X�v���C�g�̃��X�g
	std::vector<Sprite*> spriteList;

	// �t�F�[�h�C���p�̔��e�N�X�`��
	spriteList.emplace_back(new Sprite("Assets/Texture/FadeWhite.png", true, 0.0f, MSpriteScale));
	// �t�F�[�h�C���p�̍��e�N�X�`��
	spriteList.emplace_back(new Sprite("Assets/Texture/FadeBlack.png", true, 0.0f, MSpriteScale));

	for (auto spriteItr : spriteList)
	{
		mSpriteComponentList.emplace_back(spriteItr->GetSpriteComponentPtr());
	}
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
ActionScene::~ActionScene()
{
	mSpriteComponentList.clear();
	GAME_OBJECT_MANAGER->RemoveAllUsedGameObject();
}

/// <summary>
/// �V�[���̍X�V
/// </summary>
/// <param name="_KeyState"> �L�[�{�[�h�A�}�E�X�A�R���g���[���[�̓��͏�� </param>
/// <returns> �V�[���N���X�̃|�C���^ </returns>
SceneBase* ActionScene::Update(const InputState& _KeyState)
{
	// �t�F�[�h�C���p�̔��e�N�X�`���̓����x
	float whiteSpriteAlpha = 0.0f;
	// �t�F�[�h�C���p�̍��e�N�X�`���̓����x
	float blackSpriteAlpha = 0.0f;

	// �{�X��hp��0�ɂȂ����甒���t�F�[�h�C�����n�߂�
	if (mBossPtr->GetHitPoint() <= 0)
	{
		whiteSpriteAlpha = mSpriteComponentList[FadeInSpriteType::eWhite]->IncreaseAlpha(MPlusAlpha);
	}

	// �Q�[���N���A�V�[���֑J�ڂ���
	if (whiteSpriteAlpha >= 1.0f)
	{
		mSpriteComponentList[FadeInSpriteType::eWhite]->ResetAlpha();
		// �G�t�F�N�g��S�Ď~�߂�
		RENDERER->GetEffekseerManager()->StopAllEffects();
		return new GameClearScene();
	}
	
	// �v���C���[��hp��0�ɂȂ����獕���t�F�[�h�C�����n�߂�
	if (mPlayerPtr->GetHitPoint() <= 0)
	{
		blackSpriteAlpha = mSpriteComponentList[FadeInSpriteType::eBlack]->IncreaseAlpha(MPlusAlpha);
	}

	// �Q�[���I�[�o�[�V�[���֑J�ڂ���
	if (blackSpriteAlpha >= 1.0f)
	{
		mSpriteComponentList[FadeInSpriteType::eBlack]->ResetAlpha();
		// �G�t�F�N�g��S�Ď~�߂�
		RENDERER->GetEffekseerManager()->StopAllEffects();
		return new GameOverScene();
	}

	// �����蔻�������������f�o�b�O���[�h�̐؂�ւ�
	if (_KeyState.m_keyboard.GetKeyState(SDL_SCANCODE_0) == Released)
	{
		PHYSICS->ToggleDebugMode();
	}

	// �v���C���[�̍��W���擾
	Vector3 playerPos = mPlayerPtr->GetPosition();

	// �����_���ɓo�^����Ă���f�B���N�V���i�����C�g�������擾
	DirectionalLight dirLight = RENDERER->GetDirectionalLight();
	Vector3 lightDir = dirLight.m_direction;
	lightDir.Normalize();

	// �V���h�E�}�b�v�����_�����O�̂��߂̃��C�g���n��
	RENDERER->SetDepthSetting(playerPos, lightDir, Vector3::UnitZ, MLightDistance);

	RENDERER->GetEffekseerManager()->Update();

	return this;
}
