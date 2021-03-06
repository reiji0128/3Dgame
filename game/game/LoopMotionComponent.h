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
	// 経過時間
	float time;

	// 動く向き
	DirectionMovement mDirMovement;
};