#include "pch.h"

/// <summary>
/// コンストラクタ
/// </summary>	
/// <param name="_bossPtr"> ボスのポインタ </param>
/// <param name="_playerPtr"> プレイヤーのポインタ </param>
/// <param name="_Scale"> 大きさ </param>
/// <param name="_ObjectTag"> オブジェクトのタグ </param>
DangerSignalEffect::DangerSignalEffect(BossObject* _bossPtr, PlayerObject* _playerPtr, const Vector3& _Scale, const Tag& _ObjectTag)
	: GameObject(_ObjectTag)
	, MEffectPositionUnUpdateTiming(1.8f)
	, MHeightCorrection(Vector3(0.0f, 0.0f, 5.0f))
	, mElapseTime(0.0f)
	, mBossPtr(_bossPtr)
	, mPlayerPtr(_playerPtr)
	, mEffectComponentPtr(nullptr)
{
	// エフェクト生成
	mEffectComponentPtr = new EffectComponent(this, _Scale, u"Assets/Effect/DangerSignal.efk", true, true);
}

/// <summary>
/// オブジェクトの更新処理
/// </summary>
/// <param name="_deltaTime"> 最後のフレームを完了するのに要した時間 </param>
void DangerSignalEffect::UpdateGameObject(float _deltaTime)
{
	// 現在のステート
	BossState nowState = mBossPtr->GetNowState();

	if (nowState != BossState::eBossStateOverheadAttack)
	{
		mEffectComponentPtr->StopEffect();
		mElapseTime = 0.0f;
		return;
	}

	mElapseTime += _deltaTime;

	if (mElapseTime < MEffectPositionUnUpdateTiming)
	{
		mPosition = mPlayerPtr->GetPosition() + MHeightCorrection;
		SetPosition(mPosition);
	}

	// 再生済みじゃなかったらエフェクトを再生する
	if (mEffectComponentPtr->IsPlayedEffect())
	{
		// エフェクトを再生
		mEffectComponentPtr->PlayEffect();
	}
}