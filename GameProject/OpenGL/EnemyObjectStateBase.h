#pragma once

/// <summary>
/// �G�l�~�[�X�e�[�g�̊��N���X
/// </summary>
class EnemyObjectStateBase
{
public:

	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	EnemyObjectStateBase();

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	virtual ~EnemyObjectStateBase() {};

	/// <summary>
	/// �X�V����
	/// </summary>
	/// <param name="_owner"> �G�l�~�[(�e)�̃|�C���^ </param>
	/// <param name="_DeltaTime"> �Ō�̃t���[������������̂ɗv�������� </param>
	/// <returns> �G�l�~�[�̏�� </returns>
	virtual EnemyState Update(EnemyObject* _owner, const float _DeltaTime) = 0;

	/// <summary>
	/// �G�l�~�[�̏�Ԃ��ύX���āA�ŏ���1�񂾂��Ăяo�����֐�
	/// </summary>
	/// <param name="_owner"> �G�l�~�[(�e)�̃|�C���^ </param>
	/// <param name="_DeltaTime"> �Ō�̃t���[������������̂ɗv�������� </param>
	virtual void Enter(EnemyObject* _owner, const float _DeltaTime) = 0;

	/// <summary>
	/// �G�l�~�[�̏�Ԃ��ύX���āA�Ō��1�񂾂��Ăяo�����֐�
	/// </summary>
	/// <param name="_owner"> �G�l�~�[(�e)�̃|�C���^ </param>
	/// <param name="_DeltaTime"> �Ō�̃t���[������������̂ɗv�������� </param>
	virtual void Exit(EnemyObject* _owner, const float _DeltaTime) {};

	/// <summary>
    /// �q�b�g���ꂽ���̏���
    /// </summary>
    /// <param name="_HitObject"> �q�b�g�����Q�[���I�u�W�F�N�g </param>
	virtual void OnColision(const GameObject& _HitObject) {};

private:
};