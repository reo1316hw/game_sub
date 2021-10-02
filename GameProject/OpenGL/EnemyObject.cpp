#include "pch.h"

EnemyObject::EnemyObject(const Vector3& _pos, const Vector3& _size, const std::string _gpmeshName, const char* _gpskelName, const char* _gpanimName, const Tag& _objectTag, const SceneBase::Scene _sceneTag)
	: GameObject(_objectTag, _sceneTag)
	, mOffsetPos(Vector3(0.0f, 50.0f, -150.0f))
{
	//GameObjectメンバ変数の初期化
	mTag = _objectTag;
	SetScale(_size);
	SetPosition(_pos);

	mMoveSpeed = ENENY_SPEED;

	//更新の度に左に移動するコンポーネントを生成 TestObjectの生成時と同じくComponent基底クラスは自動で管理クラスに追加され自動で解放される
	/*new TestComponent(this);*/

	///生成 TestObjectの生成時と同じくComponent基底クラスは自動で管理クラスに追加され自動で解放される
	mSkeltalMeshComponentPtr = new SkeletalMeshComponent(this);
	//Rendererクラス内のMesh読み込み関数を利用してMeshをセット(.gpmesh)
	mSkeltalMeshComponentPtr->SetMesh(RENDERER->GetMesh(_gpmeshName));
	//Rendererクラス内のSkeletonデータ読み込み関数を利用してSkeletonをセット(.gpskel)
	mSkeltalMeshComponentPtr->SetSkeleton(RENDERER->GetSkeleton(_gpskelName));
	//Rendererクラス内のSkeletonデータ読み込み関数を利用してAnimationをセット(.gpanim)
	const Animation* anim = RENDERER->GetAnimation(_gpanimName, true);
	//anim変数を速度0.5fで再生
	mSkeltalMeshComponentPtr->PlayAnimation(anim, 1.0f);

	// 当たり判定
	mMeshPtr = new Mesh;
	mMeshPtr = RENDERER->GetMesh(_gpmeshName);
	mBoxColliderPtr = new BoxCollider(this, ColliderTag::Enemy, GetOnCollisionFunc());
	mBoxColliderPtr->SetObjectBox(mMeshPtr->GetBox());
}

EnemyObject::~EnemyObject()
{

}

void EnemyObject::UpdateGameObject(float _deltaTime)
{
	//if (rotationFlag)
	//{
	//	SelfRotation(Vector3::UnitZ, angleZ);
	//	rotationFlag = false;
	//}

	//velocity.y -= gravity;

	//// 常に座標に速度を足す
	//position += velocity;

	//// 座標をセット
	//SetPosition(position);
}

void EnemyObject::OnCollision(const GameObject& _hitObject)
{

}

void EnemyObject::SelfRotation(Vector3 _axis, float _angle)
{
	float radian = Math::ToRadians(_angle);
	Quaternion rot = this->GetRotation();
	Quaternion inc(_axis, radian);
	Quaternion target = Quaternion::Concatenate(rot, inc);
	SetRotation(target);
}