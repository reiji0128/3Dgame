#pragma once
#include <string>
#include <stdexcept>
#include <iterator>

// 適用するシェーダーのタグ
// BegienとEndの間に255個まで定義できる
enum class ShaderTag : unsigned char
{
	Begin,                                    // Tagの開始マーカー (Beginより手前に定義してはならない)
						                      
	Sprite,                                   // スプライトシェーダー
	Tilemap,                                  // タイルマップシェーダー
	Phong,                                    // フォグシェーダー
	DepthmapAndShadowMap,                     // デプスマップとシャドウマップ (メッシュ用)
	SkinnedDepthmapAndSkinnedShadowMap,       // デプスマップとシャドウマップ (スケルタルメッシュ用)
	HDRBloomBlend,                            // HDRとBloomのブレンドシェーダー
						                      
	None,                                     // 適用するシェーダーなし
						                      
	End                                       // Tagの終了マーカー (Endより後に定義してはならない)
};

// 前置インクリメント
ShaderTag& operator ++(ShaderTag& rhs);