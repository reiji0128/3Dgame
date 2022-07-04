#pragma once
#include "Receiver.h"
#include "ShaderTag.h"

class MoveBGActor : public Receiver
{
public:
	MoveBGActor(const Vector3& startPos, const Vector3& endPos,const float mSpeed,const char* gpmeshFileName);
	~MoveBGActor();

	void UpdateActor(float deltaTime);

private:
	Vector3 mStartPos;
	Vector3 mEndPos;
	Vector3 mTempPos;
	Vector3 mVelosity;
	Vector3 mAimPos;

	ShaderTag mShaderTag;

	bool mMoveFlag;

	class BoxCollider* mBoxCollider; // “–‚½‚è”»’è
};