#pragma once
#include "SceneBase.h"

class Tutorial : public SceneBase
{
public:
	Tutorial(const Scene& _scene);
	~Tutorial();

	SceneBase* update() override;

	static bool GetContinueTutorialFlag() { return mSendContinueTutorialFlag; };
	static void SetContinueTutorialFlag(bool _continue) { mSendContinueTutorialFlag = _continue; };

private:
	static bool mSendContinueTutorialFlag;

	bool mContinueTutorialFlag;
};

