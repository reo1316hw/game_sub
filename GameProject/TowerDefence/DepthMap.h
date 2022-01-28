#pragma once

// 前方宣言
class Shader;

/// <summary>
/// 光源の視点からそのフラグメントまでの距離をレンダリングした深度テクスチャを出力するためのクラス
/// </summary>
class DepthMap
{
public:

	DepthMap();

	~DepthMap();

	void DepthRenderingBegin();

	void DepthRenderignEnd();

	void CreateShadowMap(unsigned int shadowMapSize);

	void CalcLightSpaceMatrix(const Vector3& _CenterWorldPos, const Vector3& _LightDir,const Vector3& _UpVec, const float _LightDistance);

private:

	// デプスマップフレームバッファオブジェクト
	unsigned int  mDepthMapFBO;
	// デプステクスチャ
	unsigned int  mDepthMap;
	// デプスマップサイズ
	unsigned int  mDepthMapSize;

	// デプスマップレンダリングの撮影原点
	Vector3 mLightOrigin;
	// 光線ベクトル方向
	Vector3 mLightDir;
	// ライト空間行列
	Matrix4 mLightSpaceMatrix;

	// デプスマップ用シェーダー
	Shader* mDepthShader;

public:// ゲッターセッター

	unsigned int  GetDepthTexID() { return mDepthMap; }

	Vector3& GetLightDir() { return mLightDir; }

	Vector3& GetLightOriginPos() { return mLightOrigin; }

	Matrix4& GetLightSpaceMatrix() { return mLightSpaceMatrix; }

	Shader* GetDepthMapShader() { return mDepthShader; }
};