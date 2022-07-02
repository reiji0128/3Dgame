#pragma once
#include "Component.h"
#include "Math.h"
#include "MoveBGActor.h"

class Actor;

class LoopMotionComponent : public Component
{
public:
	LoopMotionComponent(Actor* owner,DirectionMovement& dir);
	~LoopMotionComponent();

	void Update(float deltaTime) override;
	void LoopMotion(float time);

private:
	// Œo‰ßŽžŠÔ
	float time;

	// “®‚­Œü‚«
	DirectionMovement mDirMovement;
};