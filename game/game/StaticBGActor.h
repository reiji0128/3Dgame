﻿#pragma once

#include "Actor.h"
#include "Math.h"
#include "ShaderTag.h"

class StaticBGActor : public Actor
{
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="position">位置</param>
	/// <param name="gpmeshFileName">メッシュのファイルパス</param>
	StaticBGActor(const Vector3& position, const char* gpmeshFileName);

	/// <summary>
	/// デストラクタ
	/// </summary>
	~StaticBGActor();

private:
	// 適用するシェーダーのタグ
	ShaderTag mShaderTag;
};
