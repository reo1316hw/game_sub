#pragma once

// �O���錾
class SelfRotation;

/// <summary>
/// ����J��
/// </summary>
class OpenGate : public Component
{
public:

	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="_owner"> �A�^�b�`����Q�[���I�u�W�F�N�g�̃|�C���^ </param>
	/// <param name="_Axis"> �� </param>
	/// <param name="_AddAngle"> ��]�p�𑝂₷���߂̒萔 </param>
	/// <param name="_OpenToEnemyDefeatNum"> ����J�����߂ɓ|���G�l�~�[�̐� </param>
	/// <param name="_enemysControlerPtr"> �G�l�~�[�𐧌䂷��R���|�[�l���g�N���X�̃|�C���^ </param>
	/// <param name="_selfRotationPtr"> ���g����]���邽�߂̃R���|�[�l���g�N���X�̃|�C���^ </param>
	OpenGate(GameObject* _owner, const Vector3& _Axis, const float& _AddAngle, const int& _OpenToDefeatEnemyNum,
		EnemysControler* _enemysControlerPtr, SelfRotation* _selfRotationPtr);

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~OpenGate() {};

	/// <summary>
	/// �t���[�����̏���
	/// </summary>
	/// <param name="_deltaTime"> �Ō�̃t���[������������̂ɗv�������� </param>
	void Update(float _deltaTime)override;

private:

	// ����J�����߂ɓ|���G�l�~�[�̐�
	const int& MOpenToDefeatEnemyNum;

	// ��]�p�𑝂₷���߂̒萔
	const float MAddAngle;
	// �傪�J���p�x
	const float MOpenAngle;

	// ��]��
	const Vector3& MAxis;
	
	// ��]�p
	float mAngle;

	// �G�l�~�[�𐧌䂷��R���|�[�l���g�N���X�̃|�C���^
	EnemysControler* mEnemysControlerPtr;
	// ���g����]���邽�߂̃R���|�[�l���g�N���X�̃|�C���^
	SelfRotation* mSelfRotationPtr;
};