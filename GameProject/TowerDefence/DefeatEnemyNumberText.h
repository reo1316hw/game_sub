#pragma once

/// <summary>
/// �|���G�l�~�[�̐���UI
/// </summary>
class DefeatEnemyNumberText : public GameObject
{
public:

    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    /// <param name="_Pos"> UI�̐����ꏊ(�X�N���[�����W) </param>
    /// <param name="_ObjectTag"> �A�^�b�`�����Q�[���I�u�W�F�N�g�̃^�O </param>
    /// <param name="_State"> �Q�[���I�u�W�F�N�g�̏�� </param>
    /// <param name="_FontDataNum"> �t�H���g�e�N�X�`���z��̗v�f�� </param>
    /// <param name="_enemysControlerPtr"> �G�l�~�[�����𐧌䂷��N���X�̃|�C���^ </param>
    /// <param name="_Scale"> �e�N�X�`���̊g��T�C�Y </param>
    DefeatEnemyNumberText(const Vector3& _Pos, const Tag& _ObjectTag, const State& _State, const int& _FontDataNum,
        EnemysControler* _enemysControlerPtr, const Vector3& _Scale = Vector3(1.0f, 1.0f, 1.0f));

    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    ~DefeatEnemyNumberText() {};

private:
};