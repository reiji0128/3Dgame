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

	// �I�[�i�̍��W���擾
	Vector3 ownerPos = mOwner->GetPosition();

	switch (mDirMovement)
	{
	// X���ɓ����Ȃ���W��x�ɑ������
	case DirectionMovement::XAxis:
		ownerPos.x = sin;
		mOwner->SetPosition(ownerPos);

	// Y���ɓ����Ȃ���W��x�ɑ������
	case DirectionMovement::YAxis:
		ownerPos.y = sin;
		mOwner->SetPosition(ownerPos);

	// Z���ɓ����Ȃ���W��x�ɑ������
	case DirectionMovement::ZAxis:
		ownerPos.z = sin;
		mOwner->SetPosition(ownerPos);
	}
}
