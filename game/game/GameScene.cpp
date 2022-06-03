#include "GameScene.h"
#include "Game.h"
#include <iostream>
#include "Math.h"
#include "Renderer.h"
#include "DebugGrid.h"
#include "AudioManager.h"
#include "BitmapText.h"
#include "Input.h"
#include "PhysicsWorld.h"
#include "Texture.h"
#include "StaticBGActor.h"
#include "BGCollisionSetter.h"
#include "PlayerActor.h"
#include "EnemyActor.h"
#include "ThirdPersonCameraActor.h";
#include "SphereObj.h"


GameScene::GameScene()
	:mFont(nullptr)
	,mTex (nullptr)
	,mGrid(nullptr)
	,mHealthScaleX(0.3f)
	,mLightDistance(4000.0f)
{
	printf("-----------------GameScene-----------------\n");
	// �t�H���g������
	mFont = new BitmapText;
	mFont->SetFontImage(16, 6, "Assets/Font/font.png");
	mFont->ReMapText(" !\"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_\tabcdefghijklmnopqrstuvwxyz{|}~\\");

	// �s�񏉊���
	Matrix4 proj;
	proj = Matrix4::CreatePerspectiveFOV(Math::ToRadians(45.0f), GAMEINSTANCE.GetRenderer()->GetScreenWidth(), GAMEINSTANCE.GetRenderer()->GetScreenHeight(), 1.0, 10000.0f);
	GAMEINSTANCE.GetRenderer()->SetProjMatrix(proj);

	//�f�o�b�O�O���b�h
	Vector3 color(0, 1, 0);
	mGrid = new DebugGrid(2000, 20, color);

	// ���C�e�B���O�ݒ�
	GAMEINSTANCE.GetRenderer()->SetAmbientLight(Vector3(0.2f, 0.2f, 0.2f));
	DirectionalLight& dir = GAMEINSTANCE.GetRenderer()->GetDirectionalLight();
	dir.mDirection = Vector3(0.7f, 0.7f, -0.7f);
	dir.mDiffuseColor = Vector3(0.78f, 0.88f, 1.0f);
	dir.mSpecColor = Vector3(0.8f, 0.8f, 0.8f);
	Vector3 lightDir = dir.mDirection;
	RENDERER->SetDepthSetting(Vector3(890, -130, 20), lightDir, Vector3::UnitZ, mLightDistance);

	mTex = new Texture;
	mTex = RENDERER->GetTexture("Assets/Player/Health.png");

	// �v���C���[�̐���
	player = new PlayerActor(Vector3(890, -50, -55),                // ���W
	                       	 1.0,                                   // �X�P�[��
	                         "Assets/Player/SpecialForces.gpmesh",  // gpMesh�̃t�@�C���p�X
	                         "Assets/Player/SpecialForces.gpskel"); // gpSkel�̃t�@�C���p�X

    // �J�����̐���
	ThirdPersonCameraActor* camera = new ThirdPersonCameraActor(player);
	camera->SetCameraLength(800.0f);

	// �o�b�N�O���E���h�̐���
	new StaticBGActor(Vector3(890, -130, 20), "Assets/BackGround/testMap.gpmesh");
	
	new SphereObj(Vector3(890, -50, 70));

	// �o�b�N�O���E���h�̓����蔻��̐���
	new BGCollisionSetter("Assets/BackGround/CollisionBox.json");

	
	// �Q�[���V�X�e���ɓ����蔻�胊�X�g��o�^����
	GAMEINSTANCE.GetPhysics()->SetOneSideReactionCollisionPair(Tag::Enemy, Tag::Player);
	GAMEINSTANCE.GetPhysics()->SetOneSideReactionCollisionPair(Tag::BackGround, Tag::Player);
	GAMEINSTANCE.GetPhysics()->SetOneSideReactionCollisionPair(Tag::BackGround, Tag::Enemy);
	GAMEINSTANCE.GetPhysics()->SetOneSideReactionCollisionPair(Tag::PlayerBullet, Tag::Enemy);
	GAMEINSTANCE.GetPhysics()->SetOneSideReactionCollisionPair(Tag::EnemyBullet, Tag::Player);
	GAMEINSTANCE.GetPhysics()->SetOneSideReactionCollisionPair(Tag::EnemyBullet, Tag::Altar);
}

GameScene::~GameScene()
{
	delete mGrid;
}

SceneBase* GameScene::Update()
{
	static float time = 0;
	time += 0.01f;

	// �����蔻��\�����[�h�̐؂�ւ�
	if (INPUT_INSTANCE.IsKeyPushdown(KEY_START))
	{
		GAMEINSTANCE.GetPhysics()->ToggleDebugMode();
	}

	DirectionalLight dirLight = RENDERER->GetDirectionalLight();
	Vector3 lightDir = dirLight.mDirection;
	Vector3 playerPos = player->GetPosition();
	RENDERER->SetDepthSetting(Vector3(890, -130, 20), lightDir, Vector3::UnitZ, mLightDistance);

	RENDERER->GetEffekseerManager()->Update();
	
	return this;
}

void GameScene::Draw()
{
	glClearColor(0.2f, 0.5f, 0.9f, 1.0f);
	// ��ʃN���A
	GAMEINSTANCE.GetRenderer()->WindowClear();

	// �Q�[���V�X�e���֘A�̕`��i�R���|�[�l���g�n�̂��̂͂����ł��ׂĕ`�悳���)
	GAMEINSTANCE.GetRenderer()->Draw();

	// 2D�`��̊J�n����
	RENDERER->SpriteDrawBegin();

	// �̗̓Q�[�W�`��
	/*mHealthScaleX = mAltar->GetHealth() / 1000 * 3.5f;
	if (mHealthScaleX <= 0.001)
	{
		mHealthScaleX = 0;
	}
	RENDERER->DrawHelthGauge(mTex, Vector2(10, 50), mHealthScaleX, 0.03f, 1.0f);*/
	//RENDERER->DrawHelthGauge(mUI, Vector2(1500, 540),1.0f ,1.0f, 1.0f);

	// 2D�`��̏I������
	RENDERER->SpriteDrawEnd();

// �G�t�F�N�g�֘A�̏��� //
	// �G�t�F�N�g�`��̊J�n����
	RENDERER->GetEffekseerRenderer()->BeginRendering();
	RENDERER->GetEffekseerManager()->Draw();
	// �G�t�F�N�g�`��̏I������
	RENDERER->GetEffekseerRenderer()->EndRendering();

	// ��ʃt���b�v
	GAMEINSTANCE.GetRenderer()->WindowFlip();
}
