#pragma once
#include "SoundManager.h"
#include "Texture.h"

class SettingMenu final
{
public:
	explicit SettingMenu();
	~SettingMenu() = default;

	SettingMenu(const SettingMenu&) = delete;
	SettingMenu& operator=(const SettingMenu&) = delete;
	SettingMenu(SettingMenu&&) = delete;
	SettingMenu& operator=(SettingMenu&&) = delete;

	void SetGameInformation(SoundManager& soundManager);
	void Draw() const;
	void OpenClose();
	bool IsOpen() const;
	bool ProcessClick(Point2f&& position);			// return true if we need to restart the game

private:
	SoundManager* m_PtrSoundManager;
	Texture m_Menu;
	const Rectf m_LessHitbox;
	const Rectf m_MoreHitbox;
	const Rectf m_RestartHitbox;
	bool m_Open;
};