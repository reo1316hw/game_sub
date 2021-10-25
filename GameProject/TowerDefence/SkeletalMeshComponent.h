#pragma once

/*
@file SkeletalMeshComponent.h
@brief スケルトンデータの描画とアニメーション
*/
class SkeletalMeshComponent : public MeshComponent
{
public:

	SkeletalMeshComponent(class GameObject* _owner);

	void Update(float _deltaTime) override;

	/*
	@brief　描画処理
	@param	_shader 使用するシェーダークラスのポインタ
	*/
	void Draw(class Shader* _shader) override;

	/// <summary>
	/// アニメーションの再生
	/// </summary>
	/// <param name="_AnimPtr"> アニメーションデータクラスのポインタ </param>
	/// <param name="_PlayRate"> アニメーションの再生速度 </param>
	/// <returns> アニメーションの残り時間 </returns>
	float PlayAnimation(const class Animation* _AnimPtr, const float& _PlayRate = 1.0f);

	// 現在再生中のアニメーション
	const class Animation* GetNowPlayingAnimation() { return mAnimation; }
	// 現在再生中のアニメーションは再生中か？ true : 再生中 false : 再生終了
	bool IsPlaying();

	int GetBoneIndexFromName(const char* _boneName) const;
	void GetMatrixFromBoneIndex(Matrix4& _boneWorldMatrix, int _boneIndex)const;

private:

	/*
	@fn 行列パレットの計算
	*/
	void ComputeMatrixPalette();

	// ヒットストップが終わるタイミング
	const int MHitStopEndTiming;

	// ヒットストップするか
	bool mIsHitStop;

	// ヒットストップするフレーム数
	int mHitStopCount;

	// 行列パレット
	MatrixPalette mPalette;
	// スケルトンデータ
	const class Skeleton* mSkeleton;
	// アニメーションデータ
	const class Animation* mAnimation; 

	// ヒットストップする時のアニメーションの再生速度
	float mHitStopRate;
	// アニメーションの再生速度
	float mAnimPlayRate;
	// アニメーション時間
	float mAnimTime;

	//スケルトンデータに乗算する色
	Vector3 mColor;

public://ゲッターセッター

	/*
	@param _skeleton スケルトンデータ
	*/
	void SetSkeleton(const class Skeleton* _skeleton) { mSkeleton = _skeleton; }
	/*
	@param _color スケルトンデータに乗算する色
	*/
	void SetColor(const Vector3& _color) { mColor = _color; }

	/// <summary>
	/// ヒットストップするかのフラグを設定
	/// </summary>
	/// <param name="_IsHitStop"> ヒットストップするかのフラグ </param>
	void SetIsHitStop(const bool& _IsHitStop) { mIsHitStop = _IsHitStop; }
};
