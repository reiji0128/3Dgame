#include "SphereCollider.h"
#include "Game.h"
#include "Actor.h"
#include "PhysicsWorld.h"
#include "BoxCollider.h"
#include "WallCollider.h"

SphereCollider::SphereCollider(Actor* owner, int updateOrder)
	:ColliderComponent(owner,ColliderTypeEnum::Sphere,updateOrder)
{
	// スフィアコライダーをPhysicsWorldに登録
	GAMEINSTANCE.GetPhysics()->AddCollider(this);
}

SphereCollider::~SphereCollider()
{
	printf("remove LineCollider : [%5d] owner->(0x%p)\n", GetID(), mOwner);
	GAMEINSTANCE.GetPhysics()->RemoveCollider(this);
}

/// <summary>
/// ワールド変換処理
/// </summary>
void SphereCollider::OnUpdateWorldTransform()
{
	mWorldSphere = mLocalSphere;
	
	// 平行移動処理
	//mWorldSphere.mCenter += mOwner->GetPosition();
}

/// <summary>
/// 衝突検出
/// </summary>
/// <param name="other">衝突相手のColliderComponentのポインタ</param>
/// <returns>
/// true  : 衝突検出
/// false : 衝突検出なし
/// </returns>
bool SphereCollider::CollisionDetection(ColliderComponent* other)
{
	return other->Check(this);
}

/// <summary>
/// BoxColliderと衝突したか？
/// </summary>
/// <param name="other">衝突相手のBoxColliderのポインタ</param>
/// <returns>
/// true  : 衝突した
/// false : 衝突していない
/// </returns>
bool SphereCollider::Check(BoxCollider* other)
{
	if (Intersect(mWorldSphere, other->GetWorldBox()))
	{
		return true;
	}
	return false;
}
