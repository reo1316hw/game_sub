#pragma once

class TitleScene : public SceneBase
{
public:

	TitleScene();

	~TitleScene();

	SceneBase* Update(const InputState& _KeyState)override;

private:
};

