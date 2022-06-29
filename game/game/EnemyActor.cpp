#include "EnemyActor.h"
#include "Animation.h"
#include "Mesh.h"
#include "Renderer.h"
#include "BoxCollider.h"
#include "LineCollider.h"

#include "EnemyStateIdle.h"
#include "EnemyStatePatrol.h"
#include "EnemyStateRun.h"
#include "EnemyStateAttack.h"
#include "EnemyStateHit.h"
#include "EnemyStateDeath.h"
#include "EnemyStateMoveLight.h"

EnemyActor::EnemyActor(const Vector3& pos, const Vector3& dir)
	:Actor(Tag::Enemy)
	, mSkelComp(nullptr)
	, mHitBox(nullptr)
	, mRotateNow(false)
	, mBGTrigger(nullptr)
	, mLineCollider(nullptr)
	, mIsOnGround(true)
	, mIsBGTrig(false)
	, mIsHitTrig(false)
	, mHitLight(false)
	, mNowState(EnemyState::STATE_IDLE)
	, mNextState(EnemyState::STATE_PATROL)
	, mAimVec(0.0f, 0.0f, 0.0f)
	, mVelocity(0.0f, 0.0f, 0.0f)
	, mStateTimer(0.0f)
	, mEnemyHealth(nullptr)
	, mShaderTag(ShaderTag::SkinnedDepthmapAndSkinnedShadowMap)
{
	mPosition = pos;
	mDirection = dir;

	// ���b�V���̓ǂݍ���
	Mesh* mesh = RENDERER->GetMesh("Assets/Enemy/FlyingDemon.gpmesh");
	mSkelComp = new SkeletalMeshComponent(this,mShaderTag);
	mSkelComp->SetMesh(mesh);

	// �X�P���g���̓ǂݍ���
	mSkelComp->SetSkeleton(RENDERER->GetSkeleton("Assets/Enemy/FlyingDemon.gpskel"));

	// �A�j���[�V�����̎擾 & �A�j���[�V�����z��ɃZ�b�g
	mAnimations.resize(static_cast<unsigned int>(EnemyState::STATE_NUM));
	mAnimations[static_cast<unsigned int>(EnemyState::STATE_IDLE)] = RENDERER->GetAnimation("Assets/Enemy/FlyingDemon_IdleAnim.gpanim", true);
	mAnimations[static_cast<unsigned int>(EnemyState::STATE_PATROL)] = RENDERER->GetAnimation("Assets/Enemy/FlyingDemon_WalkAnim.gpanim", true);
	mAnimations[static_cast<unsigned int>(EnemyState::STATE_RUN)] = RENDERER->GetAnimation("Assets/Enemy/FlyingDemon_RunAnim.gpanim", true);
	mAnimations[static_cast<unsigned int>(EnemyState::STATE_ATTACK)] = RENDERER->GetAnimation("Assets/Enemy/FlyingDemon_AttackAnim.gpanim", false);
	mAnimations[static_cast<unsigned int>(EnemyState::STATE_HIT)] = RENDERER->GetAnimation("Assets/Enemy/Beholder_DieAnim.gpanim", false);
	mAnimations[static_cast<unsigned int>(EnemyState::STATE_DEATH)] = RENDERER->GetAnimation("Assets/Enemy/FlyingDemon_DieAnim.gpanim", false);
	mAnimations[static_cast<unsigned int>(EnemyState::STATE_MOVE_LIGHT)] = RENDERER->GetAnimation("Assets/Enemy/FlyingDemon_RunAnim.gpanim", true);


	// �A�C�h����Ԃ̃A�j���[�V�������Z�b�g
	mSkelComp->PlayAnimation(mAnimations[static_cast<unsigned int>(EnemyState::STATE_IDLE)]);

	// �A�N�^�[�X�e�[�g�v�[���̏�����
	mStatePools.push_back(new EnemyStateIdle);
	mStatePools.push_back(new EnemyStatePatrol);
	mStatePools.push_back(new EnemyStateRun);
	mStatePools.push_back(new EnemyStateAttack);
	mStatePools.push_back(new EnemyStateHit);
	mStatePools.push_back(new EnemyStateDeath);
	mStatePools.push_back(new EnemyStateMoveLight);

	// �����蔻��̃Z�b�g
	AABB box = mesh->GetCollisionBox();
	box.Scaling(1.0f, 1.0f, 1.0f);
	box.mMin.z = 30.0f;
	box.mIsRotatable = true;
	mHitBox = new BoxCollider(this);
	mHitBox->SetObjectBox(box);

	// �w�i�g���K�[
	AABB enemyForwardBox;
	enemyForwardBox.mMin.x = box.mMax.x;
	enemyForwardBox.mMin.y = box.mMin.y;
	enemyForwardBox.mMin.z = box.mMin.z + 20.0f;
	enemyForwardBox.mMax.x = enemyForwardBox.mMin.x + 30.0f;
	enemyForwardBox.mMax.y = enemyForwardBox.mMin.y + 60.0f;
	enemyForwardBox.mMax.z = enemyForwardBox.mMin.z + 30.0f;
	enemyForwardBox.mIsRotatable = true;
	mBGTrigger = new BoxCollider(this);
	mBGTrigger->SetObjectBox(enemyForwardBox);

	//�����𒲂ׂ�R���C�_�[
	mLineCollider = new LineCollider(this);
	Line footline(Vector3(0.0f, 0.0f, 100.0f), Vector3(0.0f, 0.0f, -20.0f));
	mLineCollider->SetLine(footline);

	//�̗͂̃Z�b�g
	//mEnemyHealth = new Health(10.0f, 0.0f, 10.0f);
}

EnemyActor::~EnemyActor()
{
}

void EnemyActor::UpdateActor(float deltaTime)
{
	// �X�e�[�g�O������X�e�[�g�ύX����������?
	if (mNowState != mNextState)
	{
		mStatePools[static_cast<unsigned int>(mNextState)]->Enter(this, deltaTime);
		mNowState = mNextState;
		return;
	}

	// �X�e�[�g���s
	mNextState = mStatePools[static_cast<unsigned int>(mNowState)]->Update(this, deltaTime);

	// �X�e�[�g��������ύX����������?
	if (mNowState != mNextState)
	{
		mStatePools[static_cast<unsigned int>(mNextState)]->Enter(this, deltaTime);
		mNowState = mNextState;
	}

	// �����ꂩ�̈ړ������œ������x�Ō��݈ʒu�X�V
	mPosition += mVelocity;
	SetComputeWorldTransform();

	// ���̃t���[���Ńg���K�[���q�b�g���Ă��邩�𒲂ׂ邽�߂Ƀ��Z�b�g
	mIsOnGround = false;
	mIsBGTrig = false;
}

void EnemyActor::OnCollisionEnter(ColliderComponent* ownCollider, ColliderComponent* otherCollider)
{
	Tag colliderTag = otherCollider->GetTag();

	//�Փˏ��
	CollisionInfo info;

	// �w�i�ƏՓ˂���?
	if (colliderTag == Tag::BackGround)
	{
		// �Փ˔w�i��Box?
		if (otherCollider->GetColliderType() == ColliderTypeEnum::Box)
		{
			// �w�iBox�ɏՓ˂����̂�Line?
			if (ownCollider == mLineCollider)
			{
				//�������Ă���Ƃ��̂ݔ���
				if (mVelocity.z < 0.0f)
				{
					info = ownCollider->GetCollisionInfo();
					mPosition = info.mCollisionPoint;
					mIsOnGround = true;
				}
			}

			// �w�i�R���C�_�[
			if (ownCollider == mBGTrigger)
			{
				mIsBGTrig = true;
			}

			// �����R���C�_�[
			if (ownCollider == mLineCollider)
			{
				info = ownCollider->GetCollisionInfo();
				mPosition = info.mCollisionPoint;
				mIsOnGround = true;
				ComputeWorldTransform();
			}

			// �w�iBox�ɏՓ˂����̂�Box�H
			if (ownCollider->GetColliderType() == ColliderTypeEnum::Box)
			{
				//�q�b�g�{�b�N�X�H
				if (ownCollider == mHitBox)
				{
					info = ownCollider->GetCollisionInfo();

					mPosition += info.mFixVec;
					ComputeWorldTransform();
				}
			}
		}
		// �X���[�v�Ƒ����������Փ˂����H
		if (otherCollider->GetColliderType() == ColliderTypeEnum::Slope)
		{
			if (ownCollider == mLineCollider)
			{
				info = ownCollider->GetCollisionInfo();
				mPosition = info.mCollisionPoint;
				mIsOnGround = true;
			}
		}
	}

	//�v���C���[�ƂԂ������H
	if (colliderTag == Tag::Player)
	{
		if (ownCollider == mHitBox)
		{
			info = ownCollider->GetCollisionInfo();
			mPosition += info.mFixVec;
			ComputeWorldTransform();
		}
	}

	if (colliderTag == Tag::Light)
	{
		if (otherCollider->GetColliderType() == ColliderTypeEnum::Sphere)
		{
			mHitLight = true;
		}
	}

	mHitLight = false;
}
