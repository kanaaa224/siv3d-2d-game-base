# pragma once

# include <Siv3D.hpp> // Siv3D v0.6.16

// シーンのステート
enum class SceneState
{
	Title,
	Game
};

// シーン間で共有するデータ
struct SceneData
{
	int32 current_stage = 1;
	int32 level         = 0;
};

using SM = SceneManager<SceneState, SceneData>;

// 物理衝突処理用のカテゴリ（最大16個）
namespace CollisionCategory
{
	constexpr uint16 All      = 0xFFFF;
	constexpr uint16 None     = 0x0000;
	constexpr uint16 Default  = 1 << 0;
	constexpr uint16 Player   = 1 << 1;
	constexpr uint16 Enemy    = 1 << 2;
	constexpr uint16 Crate    = 1 << 3;
	constexpr uint16 Scaffold = 1 << 4;
	constexpr uint16 Terrain  = 1 << 5;
	constexpr uint16 Bullet   = 1 << 6;
}
