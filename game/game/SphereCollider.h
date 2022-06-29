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
	/// ���[���h�ϊ�����
	/// </summary>
	void OnUpdateWorldTransform() override;

	/// <summary>
	/// �Փˌ��o
	/// </summary>
	/// <param name="other">�Փˑ����ColliderComponent�̃|�C���^</param>
	/// <returns>
	/// true  : �Փˌ��o
	/// false : �Փˌ��o�Ȃ�
	/// </returns>
	bool CollisionDetection(ColliderComponent* other) override;

// �Z�b�^�[ // 

	/// <summary>
	/// �����蔻��p�X�t�B�A���Z�b�g
	/// </summary>
	/// <param name="sphere"></param>
	void SetSphere(const Sphere& sphere) { mLocalSphere = sphere; }

// �Q�b�^�[ //
	const Sphere& GetSphere() const { return mWorldSphere; }

protected:

	/// <summary>
	/// BoxCollider�ƏՓ˂������H
	/// </summary>
	/// <param name="other">�Փˑ����BoxCollider�̃|�C���^</param>
	/// <returns>
	/// true  : �Փ˂���
	/// false : �Փ˂��Ă��Ȃ�
	/// </returns>
	bool Check(BoxCollider* other) override;

	// ���[�J����Ԃ̋���
	Sphere mLocalSphere;

	// ���[���h��Ԃ̋���
	Sphere mWorldSphere;

	// �t�����h�N���X
	friend class Physicsworld;
};