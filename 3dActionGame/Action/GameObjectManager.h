#pragma once
#define GAME_OBJECT_MANAGER GameObjectManager::GetInstance()

#include "SDL.h"
#include <unordered_map>
#include <vector>
#include <string>
#include "GameObject.h"

class GameObject;
struct InputState;

/*
@file GameObjectManager.h
@brief �Q�[���I�u�W�F�N�g�̍X�V���s��
*/
class GameObjectManager
{
public:
	/*
	@return ���g�̃C���X�^���X��Ԃ�
	*/
	static GameObjectManager* GetInstance() { return mManager; }
	/*
	@fn �C���X�^���X�𐶐�
	*/
	static void CreateInstance();
	/*
	@fn �C���X�^���X���폜
	*/
	static void DeleteInstance();

	/*
	@brief  �Q�[���I�u�W�F�N�g�̃A�b�v�f�[�g����
	*/
	void UpdateGameObject(float _deltaTime);

	/*
	@brief  �Q�[���I�u�W�F�N�g�̓��͏���
	*/
	void ProcessInput(const InputState& _state);

	/*
	@brief  �Q�[���I�u�W�F�N�g�̒ǉ�
	@param	�ǉ�����GameObject�N���X�̃|�C���^
	*/
	void AddGameObject(GameObject* _object);

	/*
	@brief  �Q�[���I�u�W�F�N�g�̍폜
	@param	�폜����GameObject�N���X�̃|�C���^
	*/
	void RemoveGameObject(GameObject* _object);
	void RemoveGameObjects(SceneBase::Scene _scene);

	/*
	@brief �g�p�������ׂẴQ�[���I�u�W�F�N�g���������
	@detail �V�[���J�ڂ̍ۂɎg�p�����BGameObject���̍ė��p�t���O�������Ă���I�u�W�F�N�g�͉�����Ȃ�
	*/
	void RemoveAllUsedGameObject();

	GameObject* FindGameObject(Tag _tag);
	std::vector<GameObject*> FindGameObjects(Tag _tag);

private:
	GameObjectManager();
	~GameObjectManager();

	static GameObjectManager* mManager;

	//�Q�[���I�u�W�F�N�g�̃|�C���^�̉ϒ��R���e�i
	//�J�������i�[���邽�߂̉ϒ��R���e�i
	std::vector<GameObject*> mCameraObjects;
	//�`���[�g���A�����̑S�ẴQ�[���I�u�W�F�N�g���i�[���邽�߂̉ϒ��R���e�i
	std::vector<GameObject*> mTutorialObjects; 
	//�X�e�[�W1�̎��̑S�ẴQ�[���I�u�W�F�N�g���i�[���邽�߂̉ϒ��R���e�i
	std::vector<GameObject*> mStage01Objects;
	//�X�e�[�W2�̎��̑S�ẴQ�[���I�u�W�F�N�g���i�[���邽�߂̉ϒ��R���e�i
	std::vector<GameObject*> mStage02Objects;

	//Update���ɒǉ����ꂽ�Q�[���I�u�W�F�N�g�̃|�C���^���ꎞ�I�ɕۑ�����ϒ��R���e�i
	std::vector<GameObject*> mPendingGameObjects;

	//Update�����ǂ���
	bool mUpdatingGameObject;

};
