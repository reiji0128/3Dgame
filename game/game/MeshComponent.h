﻿#pragma once

#include "Component.h"
#include <cstddef>
#include "ShaderTag.h"

class MeshComponent :public Component
{
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="owner">Actorのポインタ</param>
	/// <param name="shaderTag">適用するシェーダーのタグ</param>
	/// <param name="isSkeletal">スケルタルモデルかどうか?</param>
	MeshComponent(class Actor* owner, ShaderTag shaderTag, bool isSkeletal = false);

	/// <summary>
	/// デストラクタ
	/// </summary>
	~MeshComponent();

	/// <summary>
	/// メッシュコンポーネントの描画処理
	/// </summary>
	/// <param name="owner">Shaderのポインタ</param>
	virtual void Draw(class Shader* shader);

// セッター //
	/// <summary>
	/// メッシュのセット
	/// </summary>
	/// <param name="owner">Meshのポインタ</param>
	virtual void SetMesh(class Mesh* mesh) { mMesh = mesh; }

	/// <summary>
	/// テクスチャのインデックスのセット
	/// </summary>
	/// <param name="index">インデックス</param>
	void SetTextureIndex(size_t index) { mTextureIndex = index; }

	/// <summary>
	/// 表示フラグのセット
	/// </summary>
	/// <param name="visible"></param>
	void SetVisible(bool visible) { mVisible = visible; }

	void SetChangeLuminance(bool change) { mChangeLuminance = change; }

// ゲッター //
	/// <summary>
	/// 表示フラグの取得
	/// </summary>
	/// <returns></returns>
	bool GetVisible() const { return mVisible; }

	/// <summary>
	/// スケルタルモデルかどうかの取得
	/// </summary>
	/// <returns></returns>
	bool GetIsSkeletal() const { return mIsSkeletal; }

	bool GetChangeLuminance() const { return mChangeLuminance; }

protected:
	// Meshクラスのポインタ
	class Mesh* mMesh;

	// テクスチャのインデックス
	size_t mTextureIndex;

	// 表示フラグ
	bool mVisible;

	// スケルタルモデルかどうかのフラグ
	bool mIsSkeletal;

	// 輝度の変更フラグ
	bool mChangeLuminance;

	ShaderTag mShaderTag;
};
