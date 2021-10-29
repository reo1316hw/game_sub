#pragma once

/// <summary>
/// �v���C���[��1�i�K�ڂ̒ʏ�U���G�t�F�N�g
/// </summary>
class DashAttackEffect : public GameObject
{
public:

	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="_playerPtr"> �v���C���[�̃|�C���^ </param>
	/// <param name="_Scale"> �傫�� </param>
	/// <param name="_ObjectTag"> �I�u�W�F�N�g�̃^�O </param>
	/// <param name="_dashAttackPtr"> �_�b�V���U����Ԃ̃N���X�̃|�C���^ </param>
	DashAttackEffect(PlayerObject* _playerPtr, const Vector3& _Scale, const Tag& _ObjectTag, PlayerObjectStateDashAttack* _dashAttackPtr);

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~DashAttackEffect() {};

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

	/// <summary>
	/// �q�b�g�������m�F
	/// </summary>
	/// <returns> �q�b�g������ </returns>
	bool IsHitCheck() { return mIsHit == true; }

private:

	// ���W�Ƃ̍�
	const float MOffset;
	// �����̕␳�l
	const Vector3 MHeightCorrection;

	// �q�b�g������
	bool mIsHit;
	// �q�b�g�t���O�𖳌��ɂ���t���O
	bool mDisableIsHit;

	// �v���C���[�̃|�C���^
	PlayerObject* mPlayerPtr;
	// �G�t�F�N�g�R���|�[�l���g�N���X�̃|�C���^
	EffectComponent* mEffectComponentPtr;
	// �_�b�V���U����Ԃ̃N���X�̃|�C���^
	PlayerObjectStateDashAttack* mDashAttackPtr;
};