#pragma once

/// <summary>
/// �|�����G�l�~�[�̃J�E���gUI
/// </summary>
class DeadEnemyCountText : public GameObject
{
public:

    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    /// <param name="_Pos"> UI�̐����ꏊ(�X�N���[�����W) </param>
    /// <param name="_ObjectTag"> �A�^�b�`�����Q�[���I�u�W�F�N�g�̃^�O </param>
    /// <param name="_Scale"> �e�N�X�`���̊g��T�C�Y </param>
    DeadEnemyCountText(const Vector3& _Pos, const Tag& _ObjectTag, const Vector2& _Scale = Vector2(1.0f, 1.0f));

    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    ~DeadEnemyCountText() {};

private:
};