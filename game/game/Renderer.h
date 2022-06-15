#pragma once
#include <string>
#include <vector>
#include <unordered_map>
#include <SDL.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <Effekseer.h>
#include <EffekseerRendererGL.h>

#include "Math.h"
#include "VertexArray.h"
#include "ShaderTag.h"

// ディレクショナルライト構造体
typedef struct DirectionalLight
{
	//ライトの方向
	Vector3 mDirection;
	//拡散反射の色
	Vector3 mDiffuseColor;
	//鏡面反射の色
	Vector3 mSpecColor;
}DirectionalLight;

// 前方宣言
class SpriteComponent;

class Renderer
{
public:
	Renderer();

	~Renderer();

	/// <summary>
	/// SDLとGLの初期化
	/// </summary>
	/// <param name="screenWidth">スクリーンの幅</param>
	/// <param name="screenHeight">スクリーンの高さ</param>
	/// <param name="fullScreen">フルスクリーンにするか？</param>
	/// <returns>
	/// true  : 初期化成功
	/// false : 初期化失敗 
	/// </returns>
	bool Initialize(int screenWidth, int screenHeight, bool fullScreen);

	/// <summary>
	/// 終了処理
	/// </summary>
	void Shutdown();

	/// <summary>
	/// 描画処理
	/// </summary>
	void Draw();

// セッター //

	/// <summary>
	/// ビュー行列のセット
	/// </summary>
	/// <param name="view">セットするビュー行列</param>
	void SetViewMatrix(const Matrix4& view);

	/// <summary>
	/// プロジェクション行列にセット
	/// </summary>
	/// <param name="proj">セットするプロジェクション行列</param>
	void SetProjMatrix(const Matrix4& proj);

	/// <summary>
	/// アンビエントライトのセット
	/// </summary>
	/// <param name="ambientColor">セットするアンビエントライト</param>
	void SetAmbientLight(const Vector3& ambientColor){ mAmbientLight = ambientColor; }

	/// <summary>
	/// デプスマップで使うライト情報をセット
	/// </summary>
	/// <param name="centerPos">マップの中心座標</param>
	/// <param name="lightDir">ライトの向き</param>
	/// <param name="upVec">Z軸(縦軸)</param>
	/// <param name="lightDistance">ライトの距離</param>
	void SetDepthSetting(const Vector3& centerPos, const Vector3& lightDir, const Vector3& upVec, const float lightDistance);

// ゲッター //

	/// <summary>
	/// SDL系の描画に必要なSDLrendererを得る
	/// </summary>
	/// <returns>SDL_Rendererのポインタ</returns>
	SDL_Renderer* GetSDLRenderer() { return mSDLRenderer; }

	/// <summary>
	/// ファイル名からテクスチャを取得
	/// </summary>
	class Texture* GetTexture(const std::string& fileName);

	/// <summary>
	/// ファイル名からメッシュを取得
	/// </summary>
	class Mesh* GetMesh(const std::string& fileName);

	/// <summary>
	/// ファイル名からスケルタルモデルの取得
	/// </summary>
	const class Skeleton* GetSkeleton(const char* fileName);

	/// <summary>
	/// ファイル名からスケルタルアニメーションの取得
	/// </summary>
	/// <param name="loop">アニメーションをループさせるかどうか</param>
	const class Animation* GetAnimation(const char* fileName, bool loop);

	/// <summary>
	/// ファイル名からエフェクトの取得
	/// </summary>
	class EffekseerEffect* GetEffect(const char16_t* fileName);

	/// <summary>
	/// スクリーンの幅の取得
	/// </summary>
	/// <returns>スクリーンの幅</returns>
	float GetScreenWidth() { return static_cast<float>(mScreenWidth); }

	/// <summary>
	/// スクリーン高さの取得
	/// </summary>
	/// <returns>スクリーンの高さ</returns>
	float GetScreenHeight() { return static_cast<float>(mScreenHeight); }

	/// <summary>
	/// ディレクショナルライトの取得
	/// </summary>
	/// <returns>ディレクショナルライト</returns>
	DirectionalLight& GetDirectionalLight() { return mDirectionalLight; }

	/// <summary>
	/// ビュー行列の取得
	/// </summary>
	/// <returns>ビュー行列</returns>
	const Matrix4& GetViewMatrix() { return mView; }

	/// <summary>
	/// プロジェクション行列の取得
	/// </summary>
	/// <returns>プロジェクション行列</returns>
	const Matrix4& GetProjectionMatrix() { return mProjection; }

	/// <summary>
	/// メッシュコンポーネントの追加
	/// </summary>
	/// <param name="mesh">追加するMeshComponentのポインタ</param>
	/// <param name="shaderTag">適用するシェーダーのタグ</param>
	void AddMeshComponent(class MeshComponent* mesh, ShaderTag shaderTag);

	/// <summary>
	/// メッシュコンポーネントの削除
	/// </summary>
	/// <param name="mesh">削除するMeshComponentのポインタ</param>
	/// <param name="shaderTag">適用していたシェーダーのタグ</param>
	void RemoveMeshComponent(class MeshComponent* mesh,ShaderTag shaderTag);

	/// <summary>
	/// スプライトの追加
	/// </summary>
	/// <param name="Sprite">追加するスプライトのポインタ</param>
	void AddSprite(SpriteComponent* Sprite);

	/// <summary>
	/// スプライトの削除
	/// </summary>
	/// <param name="sprite">削除するスプライトのポインタ</param>
	void RemoveSprite(SpriteComponent* sprite);

	/// <summary>
	/// 登録されている テクスチャ・メッシュリソースの表示（デバッグ用）
	/// </summary>
	void ShowResource();

	/// <summary>
	/// ウィンドウ描画クリア
	/// </summary>
	void WindowClear() { glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); }

	/// <summary>
	/// ウィンドウフリップ
	/// </summary>
	void WindowFlip() { SDL_GL_SwapWindow(mWindow); }

	/// <summary>
	/// ウィンドウタイトルのセット
	/// </summary>
	/// <param name="title">ウィンドウタイトル</param>
	void SetWindowTitle(const std::string& title);

	/// <summary>
	/// スプライト描画の開始処理
	/// </summary>
	void SpriteDrawBegin();

	/// <summary>
	/// スプライト描画の終了処理
	/// </summary>
	void SpriteDrawEnd();

	/// <summary>
	/// テクスチャの描画
	/// </summary>
	/// <param name="texture">テクスチャのファイルパス</param>
	/// <param name="index"></param>
	/// <param name="xDivNum">画像の縦の数</param>
	/// <param name="yDivNum">画像の横の数</param>
	/// <param name="offset">オフセット位置</param>
	/// <param name="scale">拡大率</param>
	/// <param name="alpha">透明度</param>
	void DrawTexture(class Texture* texture,int index, int xDivNum, int yDivNum,
	               	 const Vector2& offset,float scale = 1.0f, float alpha = 1.0f);

	/// <summary>
	/// テクスチャの描画
	/// </summary>
	/// <param name="texture">テクスチャのファイルパス</param>
	/// <param name="offset">オフセット位置</param>
	/// <param name="scale">拡大率</param>
	/// <param name="alpha">透明度</param>
	void DrawTexture(class Texture* texture, const Vector2& offset,
		             float scale = 1.0f, float alpha = 1.0f);

	/// <summary>
	/// 体力ゲージの描画
	/// </summary>
	/// <param name="texture">ファイルパス</param>
	/// <param name="index"></param>
	/// <param name="xDivNum">画像の縦の数</param>
	/// <param name="yDivNum">画像の横の数</param>
	/// <param name="offset">オフセット位置</param>
	/// <param name="scaleX">Xの拡大率</param>
	/// <param name="scaleY">Yの拡大率</param>
	/// <param name="alpha">透明度</param>
	void DrawHelthGaugeTexture(class Texture* texture, int index, int xDivNum, int yDivNum,
		                       const Vector2& offset, float scaleX, float scaleY, float alpha);

	/// <summary>
	/// 体力ゲージの描画
	/// </summary>
	/// <param name="texture">テクスチャのファイルパス</param>
	/// <param name="offset">オフセット位置</param>
	/// <param name="scaleX">Xの拡大率</param>
	/// <param name="scaleY">Yの拡大率</param>
	/// <param name="alpha">透明度</param>
	void DrawHelthGauge(class Texture* texture, const Vector2& offset,
		                float scaleX, float scaleY, float alpha = 1.0f);

	/// <summary>
	/// デプスマップに焼きこみむ処理
	/// </summary>
	void BakeDepthMap();

	Effekseer::RefPtr<EffekseerRendererGL::Renderer> GetEffekseerRenderer() { return mEffekseerRenderer; }
	Effekseer::RefPtr<Effekseer::Manager> GetEffekseerManager() { return mEffekseerManager; }

private:
	/// <summary>
	/// シェーダーの読み込み
	/// </summary>
	/// <returns>
	///  true  : 読み込み成功
	///  false : 読み込み失敗
	/// </returns>
	bool LoadShaders();

	/// <summary>
	/// ライト情報をシェーダーにUniformにセット
	/// </summary>
	/// <param name="shader">シェーダーのポインタ</param>
	void SetLightUniforms(class Shader* shader);

	/// <summary>
	/// スプライト頂点作成
	/// </summary>
	void CreateSpriteVerts();

	/// <summary>
	/// 体力ゲージ用の頂点作成
	/// </summary>
	void CreateHealthGaugeVerts();

	/// <summary>
	/// 画面全体を覆う頂点定義
	/// </summary>
	/// <param name="vao"></param>
	void ScreenVAOSetting(unsigned int& vao);

	// スクリーン幅
	int mScreenWidth;

	// スクリーン高さ
	int mScreenHeight;

	// テクスチャ登録配列
	std::unordered_map<std::string, class Texture*> mTextures;

	// メッシュ登録配列
	std::unordered_map<std::string, class Mesh*> mMeshs;

	// メッシュコンポーネント登録配列
	std::vector<class MeshComponent*> mMeshComponents;

	// HDRを適用するメッシュコンポーネント登録配列
	std::vector<class MeshComponent*> mHighLightMeshes;

	// スケルタルメッシュの描画に使われる
	std::vector<class SkeletalMeshComponent*> mSkeletalMeshes;

	// スケルタルデータ
	std::unordered_map<std::string, class Skeleton*> mSkeletons;

	// アニメーションデータ
	std::unordered_map<std::string, class Animation*> mAnims;

	// スプライトの描画に使われるスプライトコンポーネントのポインタの可変長コンテナ
	std::vector<SpriteComponent*> mSprites;

	// エフェクト
	std::unordered_map<const char16_t*, class EffekseerEffect*> mEffects;

// シェーダー関連 //
 
	// スプライトシェーダー
	class Shader* mSpriteShader;

	// タイルマップシェーダー
	class Shader* mTilemapShader;

	// メッシュシェーダー
	class Shader* mMeshShader;

	// メッシュのデプスシェーダー
	class Shader* mMeshDepthShader;

	// スキンメッシュシェーダー
	class Shader* mSkinnedShader;

	// スキンメッシュのデプスシェーダー
	class Shader* mSkinnedDepthShader;

	// シャドウマップシェーダー
	class Shader* mShadowMapShader;

	// フォグシェーダー
	class Shader* mHighLightShader;

	// デプスレンダラー
	class DepthMap* mDepthMapRenderer;

	// HDRレンダラー
	class HDR* mHDRRenderer;

// 行列関連 //

	// ビュー行列
	Matrix4 mView;

	// プロジェクション行列
	Matrix4 mProjection;

	// ライト空間行列
	Matrix4 mLightSpaceMat;

// 頂点配列 //

	// スプライトの頂点配列
	class VertexArray* mSpriteVerts;

	// 体力ゲージ用の頂点配列
	class VertexArray* mHealthVerts;

// ライティング関連 //

	// アンビエントライト
	Vector3 mAmbientLight; 

	// ディレクショナルライト
	DirectionalLight mDirectionalLight;

// レンダリングベース情報関連 //

	// SDLウィンドウハンドル 
	SDL_Window* mWindow;

	// OpenGLコンテキスト
	SDL_GLContext mContext;

	// SDLレンダリングハンドル
	SDL_Renderer* mSDLRenderer;

	// GLSLのバージョン
	const char* mGlslVersion;

// Effekseer関連 //

	// Effekseerレンダラ
	Effekseer::RefPtr<EffekseerRendererGL::Renderer> mEffekseerRenderer;

	// Effekseerマネージャ
	Effekseer::RefPtr<Effekseer::Manager> mEffekseerManager;  
};

// OpenGLのエラーハンドル取得
bool GLErrorHandle(const char* location);