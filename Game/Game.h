#pragma once
#include "BaseGame.h"
#include "Camera.h"
#include "Level.h"
#include "Avatar.h"
#include "EnemyManager.h"
#include "ProjectileManager.h"
#include "SoundManager.h"
#include "Hud.h"
#include "SettingMenu.h"

class Game final : public BaseGame
{
public:
	explicit Game(const Window& window);
	virtual ~Game() = default;

	Game(const Game& other) = delete;
	Game& operator=(const Game& other) = delete;
	Game(Game&& other) = delete;
	Game& operator=(Game&& other) = delete;

	void Update(float elapsedSec);
	void Draw() const;
	void ProcessKeyDownEvent(const SDL_KeyboardEvent& e);
	void ProcessKeyUpEvent(const SDL_KeyboardEvent& e);
	void ProcessMouseMotionEvent(const SDL_MouseMotionEvent& e);
	void ProcessMouseDownEvent(const SDL_MouseButtonEvent& e);
	void ProcessMouseUpEvent(const SDL_MouseButtonEvent& e);

private:
	Camera m_Camera;
	Level m_Level;
	Avatar m_Avatar;
	EnemyManager m_EnemyManager;
	ProjectileManager m_ProjectileManager;
	SoundManager m_SoundManager;
	Hud m_Hud;
	SettingMenu m_SettingsMenu;

	void ClearBackground() const;
	void DrawDebug() const;
	void Reset();
};