#pragma once

namespace RE
{
	enum class FIGHT_REACTION
	{
		kNeutral = 0,
		kEnemy = 1,
		kAlly = 2,
		kFriend = 3
	};
}

class Settings : public ISingleton<Settings>
{
public:
	void Load()
	{
		constexpr auto path = L"Data/SFSE/Plugins/po3_SimpleOffenceSuppression.ini";

		CSimpleIniA ini;
		ini.SetUnicode();

		ini.LoadFile(path);

		ini::get_value(ini, setAsAlly, "Settings", "bSetAsAlly", ";Whether neutral NPCs should be considered as friends or allies when hitting them. This affects the number of hits they'll take before turning hostile (see gamesettings)");
		ini::get_value(ini, onlyCombat, "Settings", "bOnlyCombat", ";Neutral NPCs will only ignore player hits during combat");
		ini::get_value(ini, ignoreFriendlyFire, "Settings", "bIgnoreFriendlyFire", ";Neutral NPCs will ALWAYS ignore hits from the player");
		ini::get_value(ini, changeGameSettings, "Settings", "bModifyGameSettings", ";Modify following gamesettings using config. These can still be modified by other mods during playtime");

		ini::get_value(ini, iFriendHitNonCombatAllowed, "GameSettings", "iFriendHitNonCombatAllowed", nullptr);
		ini::get_value(ini, iFriendHitCombatAllowed, "GameSettings", "iFriendHitCombatAllowed", nullptr);
		ini::get_value(ini, iAllyHitNonCombatAllowed, "GameSettings", "iAllyHitNonCombatAllowed", nullptr);
		ini::get_value(ini, iAllyHitCombatAllowed, "GameSettings", "iAllyHitCombatAllowed", nullptr);

		if (setAsAlly) {
			newReaction = RE::FIGHT_REACTION::kAlly;
		}

		(void)ini.SaveFile(path);
	}

	bool setAsAlly{ false };
	bool onlyCombat{ false };
	bool ignoreFriendlyFire{ false };

	bool changeGameSettings{ false };

	std::int32_t iFriendHitNonCombatAllowed{ 0 };
	std::int32_t iFriendHitCombatAllowed{ 4 };
	std::int32_t iAllyHitNonCombatAllowed{ 3 };
	std::int32_t iAllyHitCombatAllowed{ 1000 };

    RE::FIGHT_REACTION newReaction{ RE::FIGHT_REACTION::kFriend };
};
