#pragma once

// ‘O•ûéŒ¾
class DebugGrid;

class Tutorial : public SceneBase
{
public:
	Tutorial(const Scene& _scene);
	~Tutorial();

	SceneBase* Update(const InputState& _KeyState)override;

	static bool GetContinueTutorialFlag() { return mSendContinueTutorialFlag; };
	static void SetContinueTutorialFlag(bool _continue) { mSendContinueTutorialFlag = _continue; };

private:

	static bool mSendContinueTutorialFlag;

	bool mContinueTutorialFlag;
};

