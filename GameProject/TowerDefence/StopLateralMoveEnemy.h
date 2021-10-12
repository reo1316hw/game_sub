#pragma once

class StopLateralMoveEnemy : public GameObject
{
public:

	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="_owner"> �e�N���X�̃|�C���^ </param>
	/// <param name="_ObjectTag"> �I�u�W�F�N�g�̃^�O </param>
	/// <param name="_SceneTag"> �V�[���̃^�O</param>
	StopLateralMoveEnemy(GameObject* _owner, const Tag& _ObjectTag, const SceneBase::Scene _SceneTag);

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~StopLateralMoveEnemy() {};

	/// <summary>
	/// �I�u�W�F�N�g�̍X�V����
	/// </summary>
	/// <param name="_deltaTime"> �Ō�̃t���[������������̂ɗv�������� </param>
	void UpdateGameObject(float _deltaTime)override;

private:

	/// <summary>
	/// �q�b�g�������̏���
	/// </summary>
	/// <param name="_HitObject"> �q�b�g�����Q�[���I�u�W�F�N�g </param>
	void OnCollision(const GameObject& _HitObject)override;

	// �e�N���X�̃|�C���^
	GameObject* mEnemyOwner;

public:// �Q�b�^�[�Z�b�^�[

	GameObject* GetEnemyOwner() { return mEnemyOwner; };
};

