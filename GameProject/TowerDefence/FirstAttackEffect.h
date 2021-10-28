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
	/// <param name="_firstAttackPtr"> 1�i�K�ڂ̒ʏ�U����Ԃ̃N���X�̃|�C���^ </param>
	FirstAttackEffect(PlayerObject* _playerPtr, const Tag& _ObjectTag, PlayerObjectStateFirstAttack* _firstAttackPtr);

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~FirstAttackEffect() {};

	/// <summary>
	/// �I�u�W�F�N�g�̍X�V����
	/// </summary>
	/// <param name="_deltaTime"> �Ō�̃t���[������������̂ɗv�������� </param>
	void UpdateGameObject(float _deltaTime)override;

private:

	// �v���C���[�̃|�C���^
	PlayerObject* mPlayerPtr;
	// �G�t�F�N�g�R���|�[�l���g�N���X�̃|�C���^
	EffectComponent* mEffectComponentPtr;
	// 1�i�K�ڂ̒ʏ�U����Ԃ̃N���X�̃|�C���^
	PlayerObjectStateFirstAttack* mFirstAttackPtr;
};