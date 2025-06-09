# pragma once

# include "../Common.hpp"

class Title : public SM::Scene
{
public:
	Title(const InitData& init);

	void update() override;
	void draw() const override;

private:
	RoundRect m_startButton { Arg::center(Scene::Center() + Vec2{ 0, 100 }), 300, 60, 8};
	RoundRect m_exitButton  { Arg::center(Scene::Center() + Vec2{ 0, 170 }), 300, 60, 8};

	Transition m_startTransition { 0.2s, 0.2s };
	Transition m_exitTransition  { 0.2s, 0.2s };
};
