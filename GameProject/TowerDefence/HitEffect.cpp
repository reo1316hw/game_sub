#include "pch.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>	
/// <param name="_owner"> �e�N���X�̃|�C���^ </param>
/// <param name="_Scale"> �傫�� </param>
/// <param name="_ObjectTag"> �I�u�W�F�N�g�̃^�O </param>
HitEffect::HitEffect(GameObject* _owner, const Vector3& _Scale, const Tag& _ObjectTag)
	: GameObject(_ObjectTag)
	, mOwner(_owner)
	, mEffectComponentPtr(nullptr)
{
	SetScale(mOwner->GetScale());

	// �G�t�F�N�g����
	mEffectComponentPtr = new EffectComponent(this, _Scale, u"Assets/Effect/Hit.efk", true, true);
}

/// <summary>
/// �I�u�W�F�N�g�̍X�V����
/// </summary>
/// <param name="_deltaTime"> �Ō�̃t���[������������̂ɗv�������� </param>
void HitEffect::UpdateGameObject(float _deltaTime)
{
	mPosition = mOwner->GetPosition() + Vector3(0.0f, 0.0f, 50.0f);
	SetPosition(mPosition);
	SetRotation(mOwner->GetRotation());

	// 1�t���[���O��hp
	int preHp = mNowHp;
	// �ő�hp
	int maxHp = mOwner->GetMaxHp();
	// ���݂�hp
	mNowHp = mOwner->GetHitPoint();

	// 1�t���[���O��hp�ƌ��݂�hp���������e�N�X�`���̉�����ύX
	if (preHp != mNowHp && maxHp != mNowHp)
	{
		// �Đ��ς݂���Ȃ�������G�t�F�N�g���Đ�����
		if (mEffectComponentPtr->IsPlayedEffect())
		{
			// �G�t�F�N�g���Đ�
			mEffectComponentPtr->PlayEffect();
		}
	}
}