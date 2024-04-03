#include "pch.h"
#include "SettingMenu.h"
#include <iostream>
#include "utils.h"

SettingMenu::SettingMenu() :
	m_PtrSoundManager{ nullptr },
	m_Menu{ "Images/Menu/Menu.png" },
	m_LessHitbox{ 118.0f, 108.0f, 8.0f, 8.0f },
	m_MoreHitbox{ 174.0f, 108.0f, 8.0f, 8.0f },
	m_RestartHitbox{ 120.0f, 94.0f, 58.0f, 8.0f },
	m_Open{ false }

{
	
}

void SettingMenu::SetGameInformation(SoundManager& soundManager)
{
	m_PtrSoundManager = &soundManager;
}

void SettingMenu::Draw() const
{
	if(m_Open)
	{
		const Point2f position{ (300.0f / 2.0f) - (m_Menu.GetWidth() / 2.0f), (224.0f / 2.0f) - (m_Menu.GetHeight() / 2.0f) };
		m_Menu.Draw(position);
		
		// To check the placements of the hitboxes
		
		//const Color4f black{ 0.0f, 0.0f, 0.0f, 1.0f };
		//utils::SetColor(black);
		//utils::FillRect(m_LessHitbox);
		//utils::FillRect(m_MoreHitbox);
		//utils::FillRect(m_RestartHitbox);
	}
	
}

void SettingMenu::OpenClose()
{
	m_Open = !m_Open;
}

bool SettingMenu::IsOpen() const
{
	return m_Open;
}

bool SettingMenu::ProcessClick(Point2f&& position)
{
	position.x /= 3;
	position.y /= 3;

	if (utils::IsPointInRect(position, m_LessHitbox))
	{
		m_PtrSoundManager->ChangeVolume(false);
		m_PtrSoundManager->MenuClick();
	}
	else if (utils::IsPointInRect(position, m_MoreHitbox))
	{
		m_PtrSoundManager->MenuClick();
		m_PtrSoundManager->ChangeVolume(true);
	}
	else if (utils::IsPointInRect(position, m_RestartHitbox))
	{
		m_PtrSoundManager->MenuClick();
		m_Open = false;
		return true;
	}

	return false;
}