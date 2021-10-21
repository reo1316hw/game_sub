#pragma once

// �O���錾
class PlayerObject;
class EnemyObjectManager;
class CreateEnemys;

/// <summary>
/// �}�b�v�f�[�^�̃I�u�W�F�N�g�̔ԍ�
/// </summary>
enum MapDataNum
{
	ePlayerNum = 1,
	eGroundNum,
	eEnemyGeneratorNum,
	eTranslucentWallNum
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

private:

	bool readTiledJson(std::vector<std::vector<int>>& _mapData, const char* _fileName, const char* _layerName);
	int  findLayerIndex(rapidjson::GenericArray<false,rapidjson::Value>& _layer,std::string& _layerName);
	
	// �{�X�𐶐�������W
	const Vector3 MCreateBossPosition;
	// �v���C���[��hp�Q�[�W�𐶐�������W
	const Vector3 MCreateHitPointGaugePosition;
	// �ÓI�I�u�W�F�N�g�̑傫��
	const Vector3 MStaticObjectSize;
	// �v���C���[�̑傫��
	const Vector3 MPersonSize;
	// ���x�悢�ʒu�ɂ��炷���߂̃x�N�g��
	const Vector3 MShiftVec;

	//json����ǂݍ��񂾃v���C���[�̃}�b�v�f�[�^���i�[���邽�߂̉ϒ��z��
	std::vector<std::vector<int>> mPlayerMapData;
	//json����ǂݍ��񂾐ÓI�I�u�W�F�N�g�̃}�b�v�f�[�^���i�[���邽�߂̉ϒ��z��
	std::vector<std::vector<int>> mStaticObjectMapData;

	// �}�b�v�f�[�^�̉��̃^�C����
	int   mSizeX;
	// �}�b�v�f�[�^�̏c�̃^�C����
	int   mSizeY;
	// �I�u�W�F�N�g���Ƃ̋���
	float mOffset;

	// �v���C���[�̃|�C���^
	PlayerObject* mPlayerPtr;
	// �G�l�~�[�}�l�[�W���[�̃|�C���^
	EnemyObjectManager* mEnemyObjectManagerPtr;
	// �G�l�~�[�����𐶐�����N���X�̃|�C���^
	CreateEnemys* mCreateEnemysPtr;
};