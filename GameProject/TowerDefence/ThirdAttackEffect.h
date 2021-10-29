#pragma once

/// <summary>
/// �v���C���[��3�i�K�ڂ̒ʏ�U���G�t�F�N�g
/// </summary>
class ThirdAttackEffect : public GameObject
{
public:

	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="_playerPtr"> �v���C���[�̃|�C���^ </param>
	/// <param name="_Scale"> �傫�� </param>
	/// <param name="_ObjectTag"> �I�u�W�F�N�g�̃^�O </param>
	/// <param name="_thirdAttackPtr"> 3�i�K�ڂ̒ʏ�U����Ԃ̃N���X�̃|�C���^ </param>
	ThirdAttackEffect(PlayerObject* _playerPtr, const Vector3& _Scale, const Tag& _ObjectTag, PlayerObjectStateThirdAttack* _thirdAttackPtr);

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~ThirdAttackEffect() {};

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
	// 3�i�K�ڂ̒ʏ�U����Ԃ̃N���X�̃|�C���^
	PlayerObjectStateThirdAttack* mThirdAttackPtr;
};