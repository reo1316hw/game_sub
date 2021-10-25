#include "pch.h"

SkeletalMeshComponent::SkeletalMeshComponent(GameObject* _owner)
	:MeshComponent(_owner, true)
	, MHitStopEndTiming(10)
	, mIsHitStop(false)
	, mHitStopCount(0)
	, mHitStopRate(0.0f)
	, mColor(Vector3(0,0,0))
	, mSkeleton(nullptr)
{
}

/*
@brief　描画処理
@param	_shader 使用するシェーダークラスのポインタ
*/
void SkeletalMeshComponent::Draw(Shader* _shader)                 
{
	//親オブジェクトが未更新状態でないか
	if (mOwner->GetState() != State::eDead)
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

			_shader->SetVectorUniform("uColor", mColor);
			//  テクスチャをセット 
			Texture* t = mMesh->GetTexture(mTextureIndex);
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
	if (!mAnimation && !mSkeleton)
	{
		return;
	}

	mHitStopRate = 1.0f;

	if (mIsHitStop)
	{
		mHitStopRate = 0.0f;
		++mHitStopCount;

		if (mHitStopCount >= MHitStopEndTiming)
		{
			mHitStopCount = 0;
			mIsHitStop = false;
		}
	}

	mAnimTime += _deltaTime * mAnimPlayRate * mHitStopRate;

	// アニメーションがループアニメーションなら巻き戻し処理
	if (mAnimation->IsLoopAnimation())
	{
		while (mAnimTime > mAnimation->GetDuration())
		{
			mAnimTime -= mAnimation->GetDuration();
		}
	}
	// ループしないアニメで再生時間超えたら最終時間までとする
	else if (mAnimTime > mAnimation->GetDuration())
	{
		mAnimTime = mAnimation->GetDuration();
	}
	// 行列パレットの再計算
	ComputeMatrixPalette();
}

/// <summary>
/// アニメーションの再生
/// </summary>
/// <param name="_AnimPtr"> アニメーションデータクラスのポインタ </param>
/// <param name="_PlayRate"> アニメーションの再生速度 </param>
/// <returns> アニメーションの残り時間 </returns>
float SkeletalMeshComponent::PlayAnimation(const Animation* _AnimPtr, const float& _PlayRate)
{
	mAnimation = _AnimPtr;
	mAnimTime = 0.0f;
	mAnimPlayRate = _PlayRate;

	if (!mAnimation)
	{
		return 0.0f;
	}

	ComputeMatrixPalette();

	return mAnimation->GetDuration();
}

// 現在アニメーション再生中か？ true : 再生中 / false : 再生終了
bool SkeletalMeshComponent::IsPlaying()
{
	if (!mAnimation->IsLoopAnimation())
	{
		if (mAnimTime >= mAnimation->GetDuration())
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
void SkeletalMeshComponent::GetMatrixFromBoneIndex(Matrix4& _boneWorldMatrix, int _boneIndex) const
{
	_boneWorldMatrix = mPalette.mEntry[_boneIndex] * mOwner->GetWorldTransform();
}

void SkeletalMeshComponent::ComputeMatrixPalette()                             
{
	// グローバル逆バインド行列配列の取得
	const std::vector<Matrix4>& globalInvBindPoses = mSkeleton->GetGlobalInvBindPoses();
	// 現在のポーズ行列
	std::vector<Matrix4> currentPoses;                                        
	// アニメ時刻時点のグローバルポーズの取得
	mAnimation->GetGlobalPoseAtTime(currentPoses, mSkeleton, mAnimTime);
	// それぞれのボーンの行列パレットのセット                                    
	for (size_t i = 0; i < mSkeleton->GetNumBones(); i++)
	{
		//行列パレット[i] = グローバル逆バインド行列[i]　×　現在のポーズ行列[i]  (iはボーンID)         
		mPalette.mEntry[i] = globalInvBindPoses[i] * currentPoses[i];
	}
}
