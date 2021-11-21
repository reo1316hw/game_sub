#pragma once

// �O���錾
class PlayerObject;
class BossObject;
class EnemyObjectManager;
class CreateEnemys;
class EnemysControler;
class DeadObjectActiveBox;

/// <summary>
/// �}�b�v�f�[�^�̃I�u�W�F�N�g�̔ԍ�
/// </summary>
enum MapDataNum
{
	ePlayerNum = 1,
	eGroundNum,
	eLateralWallNum,
	eVerticalWallNum,
	eAisleVerticalWallNum,
	eGateNum,
	eTutorialGateNum,
	eRightEnemyGeneratorNum,
	eLeftEnemyGeneratorNum,
	eFrontEnemyGeneratorNum,
	eBossNum,
	eTutorialEnemyNum,
	eEnemyActiveBoxNum,
	eBossActiveBoxNum,
	eEnemyBootSemitransparentWallNum,
	eBossBootSemitransparentWallNum
};

/// <summary>
/// �}�b�v�𐶐�
/// </summary>
class MapCreate : public GameObject
{
public:

	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	MapCreate();

	/// <summary>
    /// �f�X�g���N�^
    /// </summary>
	~MapCreate();

	/// <summary>
	/// json�t�@�C����RapidJson�œǂݍ���ŁA�}�b�v�f�[�^���ϒ��z��Ɋi�[����
	/// </summary>
	void OpenFile();

private:

	/// <summary>
	/// �}�b�v�f�[�^�ɃA�N�Z�X����
	/// </summary>
	/// <param name="_mapData"> �}�b�v�f�[�^ </param>
	void AccessMapData(std::vector<std::vector<int>> _mapData);

	/// <summary>
	/// �I�u�W�F�N�g�𐶐�����
	/// </summary>
	/// <param name="_Name"> �}�b�v�f�[�^�̗v�f </param>
	/// <param name="_ObjectPos"> �I�u�W�F�N�g�̍��W </param>
	void CreateGameObject(const unsigned int _Name, const Vector3 _ObjectPos);

	bool readTiledJson(std::vector<std::vector<int>>& _mapData, const char* _fileName, const char* _layerName);
	int  findLayerIndex(rapidjson::GenericArray<false,rapidjson::Value>& _layer,std::string& _layerName);
	
	// ����J�����߂ɓ|���G�l�~�[�̐�
	const int OpenToDefeatEnemyNum;
	// ����J�����߂ɓ|���`���[�g���A���G�l�~�[�̐�
	const int OpenToDefeatTutorialEnemyNum;

	// �}�b�v�E���̃G�l�~�[���������]���邽�߂̊p�x
	const float MRightEnemyGeneratorAngle;
	// �}�b�v�����̃G�l�~�[���������]���邽�߂̊p�x
	const float MLeftEnemyGeneratorAngle;

	// �ÓI�I�u�W�F�N�g�̑傫��
	const Vector3 MStaticObjectSize;
	// �v���C���[�̑傫��
	const Vector3 MPersonSize;
	// ���𒚓x�悢�ʒu�ɂ��炷���߂̃x�N�g��
	const Vector3 MGroundShiftVec;
	// �ǂ𒚓x�悢�ʒu�ɂ��炷���߂̃x�N�g��
	const Vector3 MWallShiftVec;
	// ��𒚓x�悢�ʒu�ɂ��炷���߂̃x�N�g��
	const Vector3 MGateShiftVec;
	// �ʘH�̏c�ǂ𒚓x�悢�ʒu�ɂ��炷���߂̃x�N�g��
	const Vector3 MAisleVerticalWallShiftVec;
	// �}�b�v�E���̃G�l�~�[������𒚓x�悢�ʒu�ɂ��炷���߂̃x�N�g��
	const Vector3 MRightEnemyGeneratorShiftVec;
	// �}�b�v�����̃G�l�~�[������𒚓x�悢�ʒu�ɂ��炷���߂̃x�N�g��
	const Vector3 MLeftEnemyGeneratorShiftVec;
	// �}�b�v���ʑ��̃G�l�~�[������𒚓x�悢�ʒu�ɂ��炷���߂̃x�N�g��
	const Vector3 MFrontEnemyGeneratorShiftVec;
	// �G�l�~�[�������X�V�����邽�߂̓����蔻��p��`�I�u�W�F�N�g�̍��W�𒚓x�悢�ʒu�ɂ��炷���߂̃x�N�g��
	const Vector3 MEnemysActiveBoxShiftVec;

	//json����ǂݍ��񂾏�w�I�u�W�F�N�g�̃}�b�v�f�[�^���i�[���邽�߂̉ϒ��z��
	std::vector<std::vector<int>> mUpperObjectMapData;
	//json����ǂݍ��񂾉��w�I�u�W�F�N�g�̃}�b�v�f�[�^���i�[���邽�߂̉ϒ��z��
	std::vector<std::vector<int>> mUnderObjectMapData;
	//json����ǂݍ��񂾍ŉ��w�I�u�W�F�N�g�̃}�b�v�f�[�^���i�[���邽�߂̉ϒ��z��
	std::vector<std::vector<int>> mBottomObjectMapData;
	//json����ǂݍ��񂾃v���C���[�̃}�b�v�f�[�^���i�[���邽�߂̉ϒ��z��
	std::vector<std::vector<int>> mPlayerMapData;
	//json����ǂݍ��񂾃G�l�~�[�����̃}�b�v�f�[�^���i�[���邽�߂̉ϒ��z��
	std::vector<std::vector<int>> mEnemysMapData;

	// �}�b�v�f�[�^�̉��̃^�C����
	int   mSizeX;
	// �}�b�v�f�[�^�̏c�̃^�C����
	int   mSizeY;
	// �I�u�W�F�N�g���Ƃ̋���
	float mOffset;

	// �v���C���[�̃|�C���^
	PlayerObject* mPlayerPtr;
	// �{�X�̃|�C���^
	BossObject* mBossPtr;
	// �G�l�~�[���Ǘ�����N���X�̃|�C���^
	EnemyObjectManager* mEnemyObjectManagerPtr;
	// �G�l�~�[���X�V�����邽�߂̓����蔻��p��`�I�u�W�F�N�g�̃|�C���^
	DeadObjectActiveBox* mEnemyActiveBoxPtr;
	// �{�X���X�V�����邽�߂̓����蔻��p��`�I�u�W�F�N�g�̃|�C���^
	DeadObjectActiveBox* mBossActiveBoxPtr;
	// �G�l�~�[���N�����邱�Ƃɂ���ďo�����锼�����̕ǂ̃|�C���^
	GameObject* mEnemyBootSemitransparentWallPtr;
	// �{�X���N�����邱�Ƃɂ���ďo�����锼�����̕ǂ̃|�C���^
	GameObject* mBossBootSemitransparentWallPtr;

	// �G�l�~�[�����𐶐�����N���X�̃|�C���^
	CreateEnemys* mCreateEnemysPtr;
	// �G�l�~�[�����𐧌䂷��N���X�̃|�C���^
	EnemysControler* mEnemysControlerPtr;

public:// �Q�b�^�[�Z�b�^�[

	/// <summary>
	/// �v���C���[�̃|�C���^���擾
	/// </summary>
	/// <returns> �v���C���[�̃|�C���^ </returns>
	PlayerObject* GetPlayerPtr() { return mPlayerPtr; }

	/// <summary>
	/// �{�X�̃|�C���^���擾
	/// </summary>
	/// <returns> �{�X�̃|�C���^ </returns>
	BossObject* GetBossPtr() { return mBossPtr; }

	/// <summary>
	/// �G�l�~�[���Ǘ�����N���X�̃|�C���^���擾
	/// </summary>
	/// <returns> �G�l�~�[���Ǘ�����N���X�̃|�C���^ </returns>
	EnemyObjectManager* GetEnemyObjectManagerPtr() { return mEnemyObjectManagerPtr; }

	/// <summary>
	/// �G�l�~�[�����𐧌䂷��N���X�̃|�C���^���擾
	/// </summary>
	/// <returns> �G�l�~�[�����𐧌䂷��N���X�̃|�C���^ </returns>
	EnemysControler* GetEnemysControlerPtr() { return mEnemysControlerPtr; }

	/// <summary>
	/// �G�l�~�[���X�V�����邽�߂̓����蔻��p��`�I�u�W�F�N�g�̃|�C���^���擾
	/// </summary>
	/// <returns> �G�l�~�[���X�V�����邽�߂̓����蔻��p��`�I�u�W�F�N�g�̃|�C���^ </returns>
	DeadObjectActiveBox* GetEnemyActiveBoxPtr() { return mEnemyActiveBoxPtr; }

	/// <summary>
	/// �{�X���X�V�����邽�߂̓����蔻��p��`�I�u�W�F�N�g�̃|�C���^���擾
	/// </summary>
	/// <returns> �{�X���X�V�����邽�߂̓����蔻��p��`�I�u�W�F�N�g�̃|�C���^ </returns>
	DeadObjectActiveBox* GetBossActiveBoxPtr() { return mBossActiveBoxPtr; }
};