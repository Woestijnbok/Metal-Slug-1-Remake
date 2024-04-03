#include "pch.h"
#include "Game.h"
#include "iostream"
#include "Vector2f.h"
#include "utils.h"
#include "RebelSoldier.h"
#include "RebelSoldierRifle.h"
#include "Boss.h"

Game::Game( const Window& window ) :
	BaseGame{ window },
	m_Camera{ GetViewPort() },
	m_Level{},
	m_Avatar{},
	m_EnemyManager{},
	m_ProjectileManager{},
	m_SoundManager{},
	m_Hud{ m_Avatar.GetLives() },
	m_SettingsMenu{}
{	 
	Enemy::SetGameInformation(m_Level, m_Avatar, m_EnemyManager, m_ProjectileManager, m_SoundManager);
	m_Avatar.SetGameInformation(m_Level, m_ProjectileManager, m_SoundManager, m_Hud);
	m_ProjectileManager.SetGameInformation(m_Level, m_Avatar, m_EnemyManager);
	m_Camera.SetGameInformation(m_Level, m_Avatar);
	m_SettingsMenu.SetGameInformation(m_SoundManager);
	Reset();
}

void Game::Update(float elapsedSec)
{
	if (!m_SettingsMenu.IsOpen())
	{
		const Uint8* const ptrKeyboardState = SDL_GetKeyboardState(nullptr);

		m_Level.Update(elapsedSec);
		m_Avatar.Update(elapsedSec, ptrKeyboardState);
		m_Camera.Update();
		m_EnemyManager.Update(elapsedSec);
		m_ProjectileManager.Update(elapsedSec);
		m_Hud.Update(elapsedSec);
	}

	if (m_Avatar.GetLives() == 0)
	{
		Reset();
	}
}

void Game::Draw( ) const
{
	ClearBackground();

	glPushMatrix();
		glScalef(3.0f, 3.0f, 1.0f);
		m_Camera.Translate();
		m_Level.DrawBackground();
		m_EnemyManager.Draw();
		m_Avatar.Draw();
		m_ProjectileManager.Draw();
		m_Level.DrawForeground();
		//DrawDebug();
	glPopMatrix();

	glPushMatrix();
		glScalef(3.0f, 3.0f, 1.0f);
		m_Hud.Draw();
		m_SettingsMenu.Draw();
	glPopMatrix();
}

void Game::ProcessKeyDownEvent( const SDL_KeyboardEvent & e )
{
	
}

void Game::ProcessKeyUpEvent( const SDL_KeyboardEvent& e )
{
	switch (e.keysym.sym)
	{
		case SDLK_i:
			std::cout << "W: jump" << std::endl;
			std::cout << "D: move right" << std::endl;
			std::cout << "A: move left" << std::endl;
			std::cout << "Left mouse button: shoot" << std::endl;
			std::cout << "Esc: menu" << std::endl;
			break;
		case SDLK_ESCAPE:
			m_SettingsMenu.OpenClose();
			break;
	}
}

void Game::ProcessMouseMotionEvent( const SDL_MouseMotionEvent& e )
{
	
}

void Game::ProcessMouseDownEvent( const SDL_MouseButtonEvent& e )
{
	switch (e.button)
	{
		case SDL_BUTTON_LEFT:
			if (m_SettingsMenu.IsOpen())
			{
				if (m_SettingsMenu.ProcessClick(Point2f{ float(e.x), float(e.y) }))
				{
					Reset();
				}
			}
			else
			{
				m_Avatar.Shoot();
			}
			break;
	}
}

void Game::ProcessMouseUpEvent( const SDL_MouseButtonEvent& e )
{

}

void Game::ClearBackground( ) const
{
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
}

void Game::DrawDebug() const
{
	m_Camera.DrawDebug();
	m_Avatar.DrawDebug();
	m_Level.DrawDebug();
	m_EnemyManager.DrawDebug();
	m_ProjectileManager.DrawDebug();
}

void Game::Reset()
{
	m_Camera.Reset();
	m_Avatar.Reset();
	m_EnemyManager.Reset();
	m_ProjectileManager.Reset();
	m_SoundManager.Reset();
	m_Hud.Reset();

	m_EnemyManager.Pushback(new RebelSoldier{ Point2f{ 100.0f, 150.0f }, Rectf{ 300.0f, 0.0f, 300.0f, 500.0f } });
	m_EnemyManager.Pushback(new RebelSoldierRifle{ Point2f{ 350.0f, 50.0f } });
	m_EnemyManager.Pushback(new RebelSoldier{ Point2f{ 100.0f, 150.0f }, Rectf{ 600.0f, 0.0f, 300.0f, 500.0f } });
	m_EnemyManager.Pushback(new RebelSoldierRifle{ Point2f{ 650.0f, 50.0f } });
	m_EnemyManager.Pushback(new RebelSoldier{ Point2f{ 100.0f, 150.0f }, Rectf{ 1000.0f, 0.0f, 300.0f, 500.0f } });
	m_EnemyManager.Pushback(new RebelSoldierRifle{ Point2f{ 1050.0f, 50.0f } });
	m_EnemyManager.Pushback(new RebelSoldier{ Point2f{ 100.0f, 150.0f }, Rectf{ 1500.0f, 0.0f, 300.0f, 500.0f } });
	m_EnemyManager.Pushback(new RebelSoldier{ Point2f{ 100.0f, 150.0f }, Rectf{ 1900.0f, 0.0f, 300.0f, 500.0f } });
	m_EnemyManager.Pushback(new RebelSoldierRifle{ Point2f{ 1950.0f, 50.0f } });
	m_EnemyManager.Pushback(new RebelSoldier{ Point2f{ 100.0f, 150.0f }, Rectf{ 2300.0f, 0.0f, 300.0f, 500.0f } });
	m_EnemyManager.Pushback(new RebelSoldierRifle{ Point2f{ 2350.0f, 50.0f } });
	m_EnemyManager.Pushback(new RebelSoldier{ Point2f{ 100.0f, 150.0f }, Rectf{ 2700.0f, 0.0f, 300.0f, 500.0f } });
	m_EnemyManager.Pushback(new RebelSoldierRifle{ Point2f{ 2750.0f, 50.0f } });
	m_EnemyManager.Pushback(new RebelSoldier{ Point2f{ 100.0f, 150.0f }, Rectf{ 3200.0f, 0.0f, 300.0f, 500.0f } });
	m_EnemyManager.Pushback(new RebelSoldier{ Point2f{ 100.0f, 150.0f }, Rectf{ 3500.0f, 0.0f, 300.0f, 500.0f } });
	m_EnemyManager.Pushback(new Boss{});
}