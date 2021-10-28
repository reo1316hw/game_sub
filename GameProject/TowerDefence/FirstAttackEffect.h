#pragma once

/// <summary>
/// �v���C���[��1�i�K�ڂ̒ʏ�U���G�t�F�N�g
/// </summary>
class FirstAttackEffect : public GameObject
{
public:

	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="_playerPtr"> �v���C���[�̃|�C���^ </param>
	/// <param name="_ObjectTag"> �I�u�W�F�N�g�̃^�O </param>
	FirstAttackEffect(PlayerObject* _playerPtr, const Tag& _ObjectTag);

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~FirstAttackEffect() {};

	/// <summary>
	/// �I�u�W�F�N�g�̍X�V����
	/// </summary>
	/// <param name="_deltaTime"> �Ō�̃t���[������������̂ɗv�������� </param>
	void UpdateGameObject(float _deltaTime)override;

	/// <summary>
	/// �q�b�g�������m�F
	/// </summary>
	/// <returns> �q�b�g������ </returns>
	bool IsHitCheck() { return mIsHit == true; }

private:

	/// <summary>
	/// �q�b�g�������̏���
	/// </summary>
	/// <param name="_HitObject"> �q�b�g�����Q�[���I�u�W�F�N�g </param>
	void OnCollision(const GameObject& _HitObject)override;

	// �q�b�g�t���O��L���ɂ���^�C�~���O
	const int MEnableIsHitTiming;

	// �q�b�g������
	bool mIsHit;
	// �q�b�g�t���O�𖳌��ɂ���t���O
	bool mDisableIsHit;

	// �q�b�g�t���O�𖳌�����
	int mIsHitDisableCount;

	// �v���C���[�̃|�C���^
	PlayerObject* mPlayerPtr;
};