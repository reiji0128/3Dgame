#pragma once
#include "Actor.h"
#include "ShaderTag.h"

class DoorActor : public Actor
{
public:
	DoorActor(const Vector3& pos, const float& scale, const float addAngle, const char* gpmeshFileName);
	~DoorActor();

	void UpdateActor(float deltaTime)override;

	void Rotation(const Vector3& axis, const float& angle);

private:
	const float mAddAngle;
	bool mIsOpen;
	class SkeletalMeshComponent* mSkeltalMeshComp;
	class BoxCollider* mBoxCollider;
	ShaderTag mShaderTag;
};
