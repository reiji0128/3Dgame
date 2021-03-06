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
#include "SwitchActor.h"
#include "MoveBGActor.h"

GameScene::GameScene()
	:mFont(nullptr)
	,mTex (nullptr)
	,mGrid(nullptr)
	,mHealthScaleX(0.3f)
	,mLightDistance(6000.0f)
{
	printf("-----------------GameScene-----------------\n");
	// フォント初期化
	mFont = new BitmapText;
	mFont->SetFontImage(16, 6, "Assets/Font/font.png");
	mFont->ReMapText(" !\"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_\tabcdefghijklmnopqrstuvwxyz{|}~\\");

	// 行列初期化
	Matrix4 proj;
	proj = Matrix4::CreatePerspectiveFOV(Math::ToRadians(45.0f), GAMEINSTANCE.GetRenderer()->GetScreenWidth(), GAMEINSTANCE.GetRenderer()->GetScreenHeight(), 1.0, 10000.0f);
	GAMEINSTANCE.GetRenderer()->SetProjMatrix(proj);

	//デバッググリッド
	Vector3 color(0, 1, 0);
	mGrid = new DebugGrid(2000, 20, color);

	// ライティング設定
	GAMEINSTANCE.GetRenderer()->SetAmbientLight(Vector3(0.2f, 0.2f, 0.2f));
	DirectionalLight& dir = GAMEINSTANCE.GetRenderer()->GetDirectionalLight();
	dir.mDirection = Vector3(0.7f, 0.7f, -0.7f);
	dir.mDiffuseColor = Vector3(0.78f, 0.88f, 1.0f);
	dir.mSpecColor = Vector3(0.8f, 0.8f, 0.8f);
	Vector3 lightDir = dir.mDirection;
	RENDERER->SetDepthSetting(Vector3(-1272, -100, 490), lightDir, Vector3::UnitZ, mLightDistance);

	// プレイヤーの生成
	player = new PlayerActor(Vector3(-4000.0, 34.0, 470.0),            // 座標
	                       	 1.0,                                      // スケール
	                         "Assets/Player/Sword_And_Shield.gpmesh",  // gpMeshのファイルパス
	                         "Assets/Player/Sword_And_Shield.gpskel"); // gpSkelのファイルパス

    // カメラの生成
	ThirdPersonCameraActor* camera = new ThirdPersonCameraActor(player);
	camera->SetCameraLength(800.0f);

	// バックグラウンドの生成
	new StaticBGActor(Vector3(0.0, 0.0, 0.0), "Assets/BackGround/BackGround.gpmesh");

	// スイッチの生成
	SwitchActor* firstSw = new SwitchActor(Vector3(-3623.0, -382.0, 520.0), "Assets/Sphere/Sphere.gpmesh", false);
	SwitchActor* secondSw = new SwitchActor(Vector3(-3423.0, -382.0, 520.0), "Assets/Sphere/Sphere.gpmesh", false);
	SwitchActor* thirdSw = new SwitchActor(Vector3(-3023.0, -382.0, 520.0), "Assets/Sphere/Sphere.gpmesh", false);


	// レシーバーの作成
	MoveBGActor* moveBG = new MoveBGActor(Vector3(-3215.0, -125.0, 420.0), Vector3(-3300.0, 34.0, 420.0), 10, "Assets/BackGround/MoveBlock.gpmesh");
	moveBG->SetScale(4.0f);

	// スイッチに対応するレシーバーを登録
	firstSw->AddReceiver(moveBG);

	// バックグラウンドの当たり判定の生成
	new BGCollisionSetter("Assets/BackGround/BackGroundCollision.json");

	// ゲームシステムに当たり判定リストを登録する
	GAMEINSTANCE.GetPhysics()->SetOneSideReactionCollisionPair(Tag::Enemy, Tag::Player);
	GAMEINSTANCE.GetPhysics()->SetOneSideReactionCollisionPair(Tag::BackGround, Tag::Player);
	GAMEINSTANCE.GetPhysics()->SetOneSideReactionCollisionPair(Tag::BackGround, Tag::Enemy);
	GAMEINSTANCE.GetPhysics()->SetOneSideReactionCollisionPair(Tag::ChangeBackGround, Tag::Player);
	GAMEINSTANCE.GetPhysics()->SetOneSideReactionCollisionPair(Tag::Switch, Tag::Player);
	GAMEINSTANCE.GetPhysics()->SetOneSideReactionCollisionPair(Tag::Light, Tag::Player);
	GAMEINSTANCE.GetPhysics()->SetOneSideReactionCollisionPair(Tag::Player, Tag::Light);
}

GameScene::~GameScene()
{
	delete mFont;
	delete mGrid;
}

SceneBase* GameScene::Update()
{
	static float time = 0;
	time += 0.01f;

	// 当たり判定表示モードの切り替え
	if (INPUT_INSTANCE.IsKeyPushdown(KEY_START))
	{
		GAMEINSTANCE.GetPhysics()->ToggleDebugMode();
	}

	// デプスマップで必要なライト情報をセット
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
	// 画面クリア
	GAMEINSTANCE.GetRenderer()->WindowClear();

	// ゲームシステム関連の描画（コンポーネント系のものはここですべて描画される)
	GAMEINSTANCE.GetRenderer()->Draw();

	// 2D描画の開始処理
	RENDERER->SpriteDrawBegin();
	{

	}
	// 2D描画の終了処理
	RENDERER->SpriteDrawEnd();

// エフェクト関連の処理 //
	// エフェクト描画の開始処理
	RENDERER->GetEffekseerRenderer()->BeginRendering();
	{
		RENDERER->GetEffekseerManager()->Draw();
		// エフェクト描画の終了処理
	}
	RENDERER->GetEffekseerRenderer()->EndRendering();

	// 画面フリップ
	GAMEINSTANCE.GetRenderer()->WindowFlip();
}
