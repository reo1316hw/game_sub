#pragma once

// �O���錾
class Sprite;
class MapCreate;
struct InputState;

/// <summary>
/// �V�[���̊��N���X
/// </summary>
class SceneBase
{
public:

    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    SceneBase();
    
    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    virtual ~SceneBase() {};

    /// <summary>
    /// �V�[���̍X�V
    /// </summary>
    /// <param name="_KeyState"> �L�[�{�[�h�A�}�E�X�A�R���g���[���[�̓��͏�� </param>
    /// <returns> �V�[���N���X�̃|�C���^ </returns>
    virtual SceneBase* Update(const InputState& _KeyState) = 0;

protected:

    // �X�v���C�g�̃|�C���^
    Sprite*      mSprite;
    // �}�b�v�𐶐�����N���X�̃|�C���^
    MapCreate*    mMapCreate;

private:
};