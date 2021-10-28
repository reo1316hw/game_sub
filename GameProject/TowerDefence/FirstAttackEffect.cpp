#include "pch.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>	
/// <param name="_playerPtr"> �v���C���[�̃|�C���^ </param>
/// <param name="_ObjectTag"> �I�u�W�F�N�g�̃^�O </param>
FirstAttackEffect::FirstAttackEffect(PlayerObject* _playerPtr, const Tag& _ObjectTag)
	: GameObject(_ObjectTag)
	, MEnableIsHitTiming(120)
	, mIsHitDisableCount(0)
	, mIsHit(false)
	, mDisableIsHit(false)
	, mPlayerPtr(_playerPtr)
{
	// ����̋�`�����蔻��
	mBox = AABB(Vector3(-100.0f, -100.0f, -100.0f), Vector3(100.0f, 100.0f, 100.0f));
	mBoxColliderPtr = new BoxCollider(this, _ObjectTag, GetOnCollisionFunc());
	mBoxColliderPtr->SetObjectBox(mBox);
	// �ŏ��͓����蔻����s��Ȃ��悤�ɂ���
	mBoxColliderPtr->SetCollisionState(CollisionState::eDisableCollision);

	// �Ռ��G�t�F�N�g����
	EffectComponent* ec = new EffectComponent(_playerPtr, u"Assets/Effect/SecondAttack.efk", true, true);
	ec->PlayEffect();
}

/// <summary>
/// �I�u�W�F�N�g�̍X�V����
/// </summary>
/// <param name="_deltaTime"> �Ō�̃t���[������������̂ɗv�������� </param>
void FirstAttackEffect::UpdateGameObject(float _deltaTime)
{
	// �q�b�g�X�g�b�v���ɃI�u�W�F�N�g�Ə�ɓ������Ă��܂��̂ŁA�q�b�g�t���O����莞�Ԗ����ɂ���
	if (mDisableIsHit)
	{
		mIsHit = false;
		++mIsHitDisableCount;

		if (mIsHitDisableCount >= MEnableIsHitTiming)
		{
			mIsHitDisableCount = 0;
			mDisableIsHit = false;
		}
	}
}

/// <summary>
/// �q�b�g�������̏���
/// </summary>
/// <param name="_HitObject"> �q�b�g�����Q�[���I�u�W�F�N�g </param>
void FirstAttackEffect::OnCollision(const GameObject& _HitObject)
{
	// �I�u�W�F�N�g�̃^�O
	Tag tag = _HitObject.GetTag();

	if (tag == Tag::eEnemy && !mDisableIsHit && mPlayerPtr->GetPlayerState() == PlayerState::ePlayerStateThirdAttack)
	{
		mIsHit = true;
		mDisableIsHit = true;
	}
}