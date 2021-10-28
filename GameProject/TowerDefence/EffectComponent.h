#pragma once

class EffectComponent : public Component
{
public:
	EffectComponent(GameObject* owner, const char16_t* effkseerFilename, bool moveOn = false, bool rotateOn = false, int updateOrder = 100);
	~EffectComponent() {};
	
	void Update(float deltaTime) override;
	
	void PlayEffect();
	
	void SetRelativePosition(const Vector3& relativePos) { mRelativePos = relativePos; }
	void SetRelativeRotate(const Matrix4& relativeRotMat) { mRelativeRot = relativeRotMat; }
	void SetMove(bool move) { mIsMove = move; }
	void SetRotate(bool rotate) { mIsRotate = rotate; }

private:

	Effekseer::Handle mHandle;           // エフェクトパラメータを管理するためのハンドル
	bool              mIsMove;           // オーナーアクターの移動に合わせる
	bool              mIsRotate;         // オーナーアクターの回転移動に合わせる
	Vector3           mRelativePos;      // オーナーアクターの相対座標
	Matrix4           mRelativeRot;      // 相対回転行列

	EffekseerEffect* mEffectPtr;
};