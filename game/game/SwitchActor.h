#pragma once

#include "Actor.h"
#include "Math.h"
#include "ShaderTag.h"

class SwitchActor : public Actor
{
public:
	SwitchActor(const Vector3& position, const char* gpmeshFileName);

	~SwitchActor();

// ゲッター //
	bool GetSwitchFlag() { return mSwitchFlag; }

private:
	// スイッチフラグ
	bool mSwitchFlag;

	// 適用するシェーダーのタグ
	ShaderTag mShaderTag;

	// ボックスコライダーのポインタ
	class BoxCollider* mBoxCollider;
};