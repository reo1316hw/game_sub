#pragma once
#include "MeshComponent.h"
#include "MatrixPalette.h"

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

   	/*
	@fn アニメーションの再生
	@param _anim アニメーションデータクラス
	@param _playRate アニメーションの再生速度
	@return アニメーションの残り時間
	*/
	float PlayAnimation(const class Animation* _anim, float _playRate = 1.0f);

	// 現在再生中のアニメーション
	const class Animation* GetNowPlayingAnimation() { return animation; }
	// 現在再生中のアニメーションは再生中か？ true : 再生中 false : 再生終了
	bool IsPlaying();

	int GetBoneIndexFromName(const char* _boneName) const;
	void GetMatrixFromBoneIndex(Matrix4& _boneWorldMatrix, int boneIndex)const;

protected:
	/*
	@fn 行列パレットの計算
	*/
	void ComputeMatrixPalette();                                       
	// 行列パレット
	MatrixPalette mPalette;
	// スケルトンデータ
	const class Skeleton* mSkeleton;                                       
	// アニメーションデータ
	const class Animation* animation;                                     
	// アニメーションの再生速度
	float animPlayRate;                                                  
	// アニメーション時間
	float animTime;                                                       
	//スケルトンデータに乗算する色
	Vector3 color;
public://ゲッターセッター
	/*
	@param _skeleton スケルトンデータ
	*/
	void SetSkeleton(const class Skeleton* _skeleton) { mSkeleton = _skeleton; }
	/*
	@param _color スケルトンデータに乗算する色
	*/
	void SetColor(const Vector3& _color) { color = _color; }
};
