#pragma once

#include "Actor.h"
#include "Math.h"
#include "ShaderTag.h"
#include "Receiver.h"
#include <vector>

class SphereCollider;
class MeshComponent;

class SwitchActor : public Actor
{
public:
	SwitchActor(const Vector3& pos, const char* gpmeshFileName,bool switchFlag);

	~SwitchActor();

	void UpdateActor(float deltaTime)override;

	void OnCollisionEnter(class ColliderComponent* ownCollider, class ColliderComponent* otherCollider)override;
	
	void ChangeState();

// セッター //
	void AddReceiver(Receiver* receiver) { mReceiverManager.push_back(receiver); }

private:
	// スイッチフラグ
	bool mSwitchFlag;

	// 適用するシェーダーのタグ
	ShaderTag mShaderTag;

	// メッシュコンポーネントのポインタ
	MeshComponent* mMeshComp;

	// トリガー用のスフィアコライダー
	SphereCollider* mSphereCollider;

	std::vector<Receiver*> mReceiverManager;
};