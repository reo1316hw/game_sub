#pragma once

class GameObject;
class Shader;
class SkeletalMeshComponent;

/// <summary>
/// スケルタルメッシュの関節に取り付け可能なメッシュ
/// </summary>
class AttackMeshComponent : public MeshComponent
{
public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="_owner"> 親クラスのポインタ </param>
	/// <param name="_skMesh"></param>
	/// <param name="_AttachBoneName"></param>
	AttackMeshComponent(GameObject* _owner, SkeletalMeshComponent* _skMesh, const char* _AttachBoneName);

	/// <summary>
	/// デストラクタ
	/// </summary>
	~AttackMeshComponent() {};

	/// <summary>
	/// 描画
	/// </summary>
	/// <param name="_shader"> 使用するシェーダークラスのポインタ </param>
	void Draw(Shader* _shader)override;
	
protected:

	// gpSkelファイルの任意のボーン
	int mAttackBoneIndex;

	// アタッチした座標
	Vector3                      mComputeAttachPos;
	// アタッチしたワールド行列
	Matrix4                      mComputeTransMatrix;
	// 差分の平行移動行列
	Matrix4                      mOffsetPos;
	// 差分の回転行列
	Matrix4                      mOffsetRotation;

	// スケルトンメッシュのポインタ
	SkeletalMeshComponent* mAttackSkeletalMesh;

public:// ゲッターセッター

	/// <summary>
	/// アタッチした座標を取得
	/// </summary>
	/// <returns> アタッチした座標 </returns>
	const Vector3& GetAttachPosisiton()const { return mComputeAttachPos; }

	/// <summary>
	/// アタッチしたワールド行列を取得
	/// </summary>
	/// <returns> アタッチしたワールド行列 </returns>
	const Matrix4& GetAttachTransMatrix()const { return mComputeTransMatrix; }

	/// <summary>
	/// gpSkelファイルの任意のボーンを取得
	/// </summary>
	/// <returns> gpSkelファイルの任意のボーン </returns>
	int GetAttackBoneIndex() { return mAttackBoneIndex; }

	/// <summary>
	/// gpSkelファイルの任意のボーンを設定
	/// </summary>
	/// <param name="_attackBoneIndex"> gpSkelファイルの任意のボーン </param>
	void SetAttackBoneIndex(int _attackBoneIndex) { mAttackBoneIndex = _attackBoneIndex; }

	/// <summary>
	/// 差分の平行移動行列を設定
	/// </summary>
	/// <param name="_Offset"> 差分の平行移動行列 </param>
	void SetOffsetPosition(const Vector3& _Offset);

	/// <summary>
	/// 差分の回転行列を設定
	/// </summary>
	/// <param name="_Rotation"> 差分の回転行列 </param>
	void SetOffsetRotation(const Vector3& _Rotation);
};