#pragma once

class TitleScene : public SceneBase
{
public:
	TitleScene(const Scene& _scene);
	~TitleScene();

	SceneBase* Update(const InputState& _KeyState)override;
private:
};

