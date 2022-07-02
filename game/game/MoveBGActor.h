#pragma once
#include "Actor.h"
#include "ShaderTag.h"

// 移動する方向軸
enum DirectionMovement
{
	XAxis,
	YAxis,
	ZAxis,
};

class MoveBGActor :public Actor
{
public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="position">位置</param>
	/// <param name="gpmeshFileName">メッシュのファイルパス</param>
	MoveBGActor(const Vector3& position, const char* gpmeshFileName);

	/// <summary>
	/// デストラクタ
	/// </summary>
	~MoveBGActor();

private:
	// 適用するシェーダーのタグ
	ShaderTag mShaderTag;
};