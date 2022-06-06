#pragma once
#include "Actor.h"
#include "Math.h"
#include "ShaderTag.h"

class Lantern : public  Actor
{
public:
	Lantern(const Vector3& pos, const Vector3& rot,
		    const char* gpmeshFileName, class SkeletalMeshComponent* skelComp,const char* boneName);

	~Lantern();

private:
	// アタッチ先のボーン名
	const char* mBoneName;

	// SkeletalMeshComponentクラスのポインタ
	class SkeletalMeshComponent* mSkelComp;

	// AttachMeshComponentクラスのポインタ
	class AttachMeshComponent* mAttachComp;

	// 適用するシェーダーのタグ
	ShaderTag mShaderTag;
};