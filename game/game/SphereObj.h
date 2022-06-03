#pragma once
#include "Actor.h"
#include "Math.h"
#include "ShaderTag.h"

class SphereCollider;

class SphereObj : public Actor
{
public:
	SphereObj(const Vector3& pos);
	~SphereObj();

private:
	// 適用するシェーダーのタグ
	ShaderTag mShaderTag;

	// トリガー用のスフィアコライダー
	SphereCollider* mSphereCollider;
};