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
	// �K�p����V�F�[�_�[�̃^�O
	ShaderTag mShaderTag;

	// �g���K�[�p�̃X�t�B�A�R���C�_�[
	SphereCollider* mSphereCollider;
};