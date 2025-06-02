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
	int current_stage = 1;
};

using App = SceneManager<SceneState, SceneData>;

// 物理衝突処理用のカテゴリ（最大16個）
namespace CollisionCategory
{
	constexpr uint16 All     = 0xFFFF;
	constexpr uint16 None    = 0x0000;
	constexpr uint16 Default = 0x0001;
	constexpr uint16 Player  = 0x0002;
	constexpr uint16 Enemy   = 0x0004;
	constexpr uint16 Box1    = 0x0008;
	constexpr uint16 Box2    = 0x0010;
}
