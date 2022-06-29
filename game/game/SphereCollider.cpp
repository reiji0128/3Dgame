#include "SphereCollider.h"
#include "Game.h"
#include "Actor.h"
#include "PhysicsWorld.h"
#include "BoxCollider.h"
#include "WallCollider.h"

SphereCollider::SphereCollider(Actor* owner, int updateOrder)
	:ColliderComponent(owner,ColliderTypeEnum::Sphere,updateOrder)
{
	// �X�t�B�A�R���C�_�[��PhysicsWorld�ɓo�^
	GAMEINSTANCE.GetPhysics()->AddCollider(this);
}

SphereCollider::~SphereCollider()
{
	printf("remove LineCollider : [%5d] owner->(0x%p)\n", GetID(), mOwner);
	GAMEINSTANCE.GetPhysics()->RemoveCollider(this);
}

/// <summary>
/// ���[���h�ϊ�����
/// </summary>
void SphereCollider::OnUpdateWorldTransform()
{
	mWorldSphere = mLocalSphere;
	
	// ���s�ړ�����
	//mWorldSphere.mCenter += mOwner->GetPosition();
}

/// <summary>
/// �Փˌ��o
/// </summary>
/// <param name="other">�Փˑ����ColliderComponent�̃|�C���^</param>
/// <returns>
/// true  : �Փˌ��o
/// false : �Փˌ��o�Ȃ�
/// </returns>
bool SphereCollider::CollisionDetection(ColliderComponent* other)
{
	return other->Check(this);
}

/// <summary>
/// BoxCollider�ƏՓ˂������H
/// </summary>
/// <param name="other">�Փˑ����BoxCollider�̃|�C���^</param>
/// <returns>
/// true  : �Փ˂���
/// false : �Փ˂��Ă��Ȃ�
/// </returns>
bool SphereCollider::Check(BoxCollider* other)
{
	if (Intersect(mWorldSphere, other->GetWorldBox()))
	{
		return true;
	}
	return false;
}
