#pragma once

#include "Actor.h"
#include "Math.h"
#include "ShaderTag.h"
#include "Receiver.h"
#include <vector>

class SphereCollider;
class BoxCollider;

class SwitchActor : public Actor
{
public:
	SwitchActor(const Vector3& pos, const char* gpmeshFileName,bool switchFlag);

	~SwitchActor();

	void UpdateActor(float deltaTime)override;

	void OnCollisionEnter(class ColliderComponent* ownCollider, class ColliderComponent* otherCollider)override;
	
	void ChangeState();

// �Z�b�^�[ //
	void AddReceiver(Receiver* receiver) { mReceiverManager.push_back(receiver); }

private:
	// �X�C�b�`�t���O
	bool mSwitchFlag;

	// �K�p����V�F�[�_�[�̃^�O
	ShaderTag mShaderTag;

	// �g���K�[�p�̃X�t�B�A�R���C�_�[
	SphereCollider* mSphereCollider;

	BoxCollider* mBoxCollider;

	std::vector<Receiver*> mReceiverManager;
};