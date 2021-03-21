#include "SkeletalMeshComponent.h"
#include "Shader.h"
#include "Mesh.h"
#include "GameObject.h"
#include "Game.h"
#include "Renderer.h"
#include "Texture.h"
#include "VertexArray.h"
#include "Animation.h"
#include "Skeleton.h"
#include "GameObject.h"

SkeletalMeshComponent::SkeletalMeshComponent(GameObject* _owner)
	:MeshComponent(_owner, true)
	, mSkeleton(nullptr)
	, color(Vector3(0,0,0))
{
}

/*
@brief　描画処理
@param	_shader 使用するシェーダークラスのポインタ
*/
void SkeletalMeshComponent::Draw(Shader* _shader)                 
{
	//親オブジェクトが未更新状態でないか
	if (mOwner->GetState() != State::Dead)
	{
		if (mMesh)
		{
			//ワールド変換をセット
			_shader->SetMatrixUniform("uWorldTransform",
				mOwner->GetWorldTransform());
			// 行列パレットをセット    
			_shader->SetMatrixUniforms("uMatrixPalette", &mPalette.mEntry[0],
				MAX_SKELETON_BONES);
			//スペキュラー強度をセット
			_shader->SetFloatUniform("uSpecPower", 100);

			_shader->SetVectorUniform("uColor", color);
			//  テクスチャをセット 
			Texture* t = mMesh->GetTexture(textureIndex);
			if (t)
			{
				glActiveTexture(GL_TEXTURE0);
				glBindTexture(GL_TEXTURE_2D, t->GetTextureID());
				_shader->SetIntUniform("uMeshTexture", 0);
			}
			//メッシュの頂点配列をアクティブに
			VertexArray* va = mMesh->GetVertexArray();
			va->SetActive();
			//描画
			glDrawElements(GL_TRIANGLES, va->GetNumIndices(), GL_UNSIGNED_INT, nullptr);
		}
	}
}

void SkeletalMeshComponent::Update(float _deltaTime)
{
		if (animation && mSkeleton)
		{
			animTime += _deltaTime * animPlayRate;

			// アニメーションがループアニメーションなら巻き戻し処理
			if (animation->IsLoopAnimation())
			{
				while (animTime > animation->GetDuration())
				{
					animTime -= animation->GetDuration();
				}
			}
			// ループしないアニメで再生時間超えたら最終時間までとする
			else if (animTime > animation->GetDuration())
			{
				animTime = animation->GetDuration();
			}
			// 行列パレットの再計算
			ComputeMatrixPalette();
		}
	
}

float SkeletalMeshComponent::PlayAnimation(const Animation* _anim, float _playRate) 
{
	animation = _anim;
	animTime = 0.0f;
	animPlayRate = _playRate;

	if (!animation)
	{
		return 0.0f;
	}

	ComputeMatrixPalette();

	return animation->GetDuration();
}

// 現在アニメーション再生中か？ true : 再生中 / false : 再生終了
bool SkeletalMeshComponent::IsPlaying()
{
	if (!animation->IsLoopAnimation())
	{
		if (animTime >= animation->GetDuration())
		{
			return false;
		}
	}
	return true;
}

// ボーン名の文字列からボーンインデックスを検索
int SkeletalMeshComponent::GetBoneIndexFromName(const char* _boneName) const
{
	std::string name;
	name = _boneName;
	return mSkeleton->GetBoneIndexFromName(name);
}

// ボーンインデックス値からそのボーンの最終ワールド行列を返す
void SkeletalMeshComponent::GetMatrixFromBoneIndex(Matrix4& boneWorldMatrix, int boneIndex) const
{
	boneWorldMatrix = mPalette.mEntry[boneIndex] * mOwner->GetWorldTransform();
}

void SkeletalMeshComponent::ComputeMatrixPalette()                             
{
	// グローバル逆バインド行列配列の取得
	const std::vector<Matrix4>& globalInvBindPoses = mSkeleton->GetGlobalInvBindPoses();
	// 現在のポーズ行列
	std::vector<Matrix4> currentPoses;                                        
	// アニメ時刻時点のグローバルポーズの取得
	animation->GetGlobalPoseAtTime(currentPoses, mSkeleton, animTime);
	// それぞれのボーンの行列パレットのセット                                    
	for (size_t i = 0; i < mSkeleton->GetNumBones(); i++)
	{
		//行列パレット[i] = グローバル逆バインド行列[i]　×　現在のポーズ行列[i]  (iはボーンID)         
		mPalette.mEntry[i] = globalInvBindPoses[i] * currentPoses[i];
	}
}
