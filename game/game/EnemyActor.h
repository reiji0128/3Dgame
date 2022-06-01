#pragma once
#include "Actor.h"
#include <vector>
#include "SkeletalMeshComponent.h"
#include "ShaderTag.h"

enum class EnemyState
{
	STATE_IDLE,
	STATE_PATROL,
	STATE_RUN,
	STATE_ATTACK,
	STATE_HIT,
	STATE_DEATH,

	STATE_NUM
};

class EnemyActor : public Actor
{
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="pos">�ʒu</param>
	/// <param name="dir">����</param>
	EnemyActor(const Vector3& pos, const Vector3& dir);

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~EnemyActor();

	void UpdateActor(float deltaTime)override;
	void OnCollisionEnter(class ColliderComponent* ownCollider, class ColliderComponent* otherCollider) override;

//�Z�b�^�[ //
	void SetIsHitTrig(bool hitTrig) { mIsHitTrig = hitTrig; }

//�Q�b�^�[ //
	SkeletalMeshComponent* GetSkeltalMeshComp() { return mSkelComp; }
	const Animation* GetAnim(EnemyState state) const { return mAnimations[static_cast<unsigned int>(state)]; }
	const bool GetIsBGTrig() const { return mIsBGTrig; }
	const bool GetIsHitTrig() const { return mIsHitTrig; }
	const Vector3& GetVelosity() const { return mVelocity; }
	void SetVelosity(Vector3 velosity) { mVelocity = velosity; }

private:
	class SkeletalMeshComponent* mSkelComp; // ���b�V��
	class BoxCollider* mHitBox; // ������p�{�b�N�X
	class BoxCollider* mBGTrigger; // �w�i�Ɠ�������������]�����邽�߂̃g���K�[
	class LineCollider* mLineCollider; // �����𒲂ׂ�R���C�_�[

	class Health* mEnemyHealth; //�G�l�~�[�̗̑�

	std::vector<const class Animation*> mAnimations; // �A�j���[�V����

	Vector3                             mAimVec; // �ڕW��]����
	Vector3                             mVelocity; // �ړ��X�s�[�h
	bool                                mIsOnGround; // �ڒn���Ă��邩 
	bool                                mIsBGTrig; // �w�i�{�b�N�X�ƃq�b�g�������H
	bool                                mIsHitTrig; // �A�^�b�N�I�u�W�F�N�g�ƃq�b�g�������H
	bool                                mRotateNow; // ��]����
	EnemyState                             mNowState; // ���݂̃X�e�[�g
	EnemyState                             mNextState; // ���̃X�e�[�g
	float                               mStateTimer; // �X�e�[�g���̌o�ߎ����𑪂�G�p�^�C�}�[  

	std::vector<class EnemyStateBase*>     mStatePools;    // �X�e�[�g�N���X�v�[��

	ShaderTag mShaderTag;
};