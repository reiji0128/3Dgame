#include "LoopMotionComponent.h"
#include "Actor.h"

LoopMotionComponent::LoopMotionComponent(Actor* owner,DirectionMovement& dir)
	:Component(owner)
	,time(0)
{
	mOwner = owner;
	mDirMovement = dir;
}

LoopMotionComponent::~LoopMotionComponent()
{
}

void LoopMotionComponent::Update(float deltaTime)
{
	time += deltaTime;
}

void LoopMotionComponent::LoopMotion(float time)
{
	float sin = Math::Sin(time);

	// オーナの座標を取得
	Vector3 ownerPos = mOwner->GetPosition();

	switch (mDirMovement)
	{
	// X軸に動くなら座標のxに代入する
	case DirectionMovement::XAxis:
		ownerPos.x = sin;
		mOwner->SetPosition(ownerPos);

	// Y軸に動くなら座標のxに代入する
	case DirectionMovement::YAxis:
		ownerPos.y = sin;
		mOwner->SetPosition(ownerPos);

	// Z軸に動くなら座標のxに代入する
	case DirectionMovement::ZAxis:
		ownerPos.z = sin;
		mOwner->SetPosition(ownerPos);
	}
}
