#pragma once

/// <summary>
/// �v���C���[��2�i�K�ڂ̒ʏ�U���G�t�F�N�g
/// </summary>
class SecondAttackEffect : public GameObject
{
public:

	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="_playerPtr"> �v���C���[�̃|�C���^ </param>
	/// <param name="_Scale"> �傫�� </param>
	/// <param name="_ObjectTag"> �I�u�W�F�N�g�̃^�O </param>
	/// <param name="_secondAttackPtr"> 2�i�K�ڂ̒ʏ�U����Ԃ̃N���X�̃|�C���^ </param>
	SecondAttackEffect(PlayerObject* _playerPtr, const Vector3& _Scale, const Tag& _ObjectTag, PlayerObjectStateSecondAttack* _secondAttackPtr);

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~SecondAttackEffect() {};

	/// <summary>
	/// �I�u�W�F�N�g�̍X�V����
	/// </summary>
	/// <param name="_deltaTime"> �Ō�̃t���[������������̂ɗv�������� </param>
	void UpdateGameObject(float _deltaTime)override;

	/// <summary>
    /// �q�b�g�������̏���
    /// </summary>
    /// <param name="_HitObject"> �q�b�g�����Q�[���I�u�W�F�N�g </param>
	void OnCollision(const GameObject& _HitObject)override;

private:

	/// <summary>
	/// �U���������������̏���
	/// </summary>
	/// <param name="_HitObject"> �q�b�g�����I�u�W�F�N�g </param>
	/// <param name="_HitTag"> �q�b�g�����I�u�W�F�N�g�̃^�O </param>
	void HitAttack(const GameObject& _HitObject, const Tag& _HitTag);

	// �q�b�g����I�u�W�F�N�g�̃��X�g
	Tag mHitTagList[2];

	// ���W�Ƃ̍�
	const float MOffset;

	// ���̃G�l�~�[�Ɠ������Ă��邩�J�E���g
	int mHitEnemyCount;
	// �q�b�g���鑊��̃��X�g�̗v�f��
	int mHitTagListSize;

	// �G�l�~�[�Ɍ������x�N�g��
	Vector3 mFaceInEnemyVec;
	// �q�b�g�����G�l�~�[�̌Q��̒��S�Ɍ����x�N�g��
	Vector3 mFaceInFlockCenterVec;
	// �q�b�g�����I�u�W�F�N�g�̃^�O
	Tag mHitTag;

	// �v���C���[�̃|�C���^
	PlayerObject* mPlayerPtr;
	// �G�t�F�N�g�R���|�[�l���g�N���X�̃|�C���^
	EffectComponent* mEffectComponentPtr;
	// 2�i�K�ڂ̒ʏ�U����Ԃ̃N���X�̃|�C���^
	PlayerObjectStateSecondAttack* mSecondAttackPtr;

public:// �Q�b�^�[�Z�b�^�[

    /// <summary>
    /// �q�b�g�����G�l�~�[�̌Q��̒��S�Ɍ����x�N�g�����擾
    /// </summary>
    /// <returns> �q�b�g�����G�l�~�[�̌Q��̒��S�Ɍ����x�N�g�� </returns>
	Vector3 GetFaceInFlockCenterVec() { return mFaceInFlockCenterVec; }
};