#pragma once

/// <summary>
/// �{�X�X�e�[�g�̊��N���X
/// </summary>
class BossObjectStateBase
{
public:

	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	BossObjectStateBase();

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	virtual ~BossObjectStateBase() {};

	/// <summary>
	/// �X�V����
	/// </summary>
	/// <param name="_owner"> �{�X(�e)�̃|�C���^ </param>
	/// <param name="_DeltaTime"> �Ō�̃t���[������������̂ɗv�������� </param>
	/// <returns> �{�X�̏�� </returns>
	virtual BossState Update(BossObject* _owner, const float _DeltaTime) = 0;

	/// <summary>
	/// �{�X�̏�Ԃ��ύX���āA�ŏ���1�񂾂��Ăяo�����֐�
	/// </summary>
	/// <param name="_owner"> �{�X(�e)�̃|�C���^ </param>
	/// <param name="_DeltaTime"> �Ō�̃t���[������������̂ɗv�������� </param>
	virtual void Enter(BossObject* _owner, const float _DeltaTime) = 0;

	/// <summary>
	/// �{�X�̏�Ԃ��ύX���āA�Ō��1�񂾂��Ăяo�����֐�
	/// </summary>
	/// <param name="_owner"> �{�X(�e)�̃|�C���^ </param>
	/// <param name="_DeltaTime"> �Ō�̃t���[������������̂ɗv�������� </param>
	virtual void Exit(BossObject* _owner, const float _DeltaTime) {};

	/// <summary>
	/// �{�X�ƃG�l�~�[�̈�������
	/// </summary>
	/// <param name="_owner"> �{�X(�e)�̃|�C���^ </param>
	/// <param name="_SeparationVec"> �ΏۂƂȂ�G�l�~�[�Ɍ������x�N�g�� </param>
	virtual void Separation(BossObject* _owner, const Vector3& _DirTargetEnemyVec) {};

	/// <summary>
	/// �q�b�g�������̏���
	/// </summary>
	/// <param name="_owner"> �{�X(�e)�̃|�C���^ </param>
	/// <param name="_HitObject"> �q�b�g�����Q�[���I�u�W�F�N�g </param>
	virtual void OnCollision(BossObject* _owner, const GameObject& _HitObject) {};

private:

};