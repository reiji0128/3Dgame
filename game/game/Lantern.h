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
	// �A�^�b�`��̃{�[����
	const char* mBoneName;

	// SkeletalMeshComponent�N���X�̃|�C���^
	class SkeletalMeshComponent* mSkelComp;

	// AttachMeshComponent�N���X�̃|�C���^
	class AttachMeshComponent* mAttachComp;

	// �K�p����V�F�[�_�[�̃^�O
	ShaderTag mShaderTag;
};