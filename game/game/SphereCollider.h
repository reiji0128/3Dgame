#pragma once

#include "Component.h"
#include "ColliderComponent.h"
#include "Collision.h"
#include "PhysicsWorld.h"
#include "Tag.h"

class SphereCollider : public ColliderComponent
{
public:
	SphereCollider(class Actor* owner, int updateOrder = 100);

	~SphereCollider();

	/// <summary>
	/// ワールド変換処理
	/// </summary>
	void OnUpdateWorldTransform() override;

	/// <summary>
	/// 衝突検出
	/// </summary>
	/// <param name="other">衝突相手のColliderComponentのポインタ</param>
	/// <returns>
	/// true  : 衝突検出
	/// false : 衝突検出なし
	/// </returns>
	bool CollisionDetection(ColliderComponent* other) override;

// セッター // 

	/// <summary>
	/// 当たり判定用スフィアをセット
	/// </summary>
	/// <param name="sphere"></param>
	void SetSphere(const Sphere& sphere) { mLocalSphere = sphere; }

// ゲッター //
	const Sphere& GetSphere() const { return mWorldSphere; }

protected:

	/// <summary>
	/// BoxColliderと衝突したか？
	/// </summary>
	/// <param name="other">衝突相手のBoxColliderのポインタ</param>
	/// <returns>
	/// true  : 衝突した
	/// false : 衝突していない
	/// </returns>
	bool Check(BoxCollider* other) override;

	// ローカル空間の球体
	Sphere mLocalSphere;

	// ワールド空間の球体
	Sphere mWorldSphere;

	// フレンドクラス
	friend class Physicsworld;
};