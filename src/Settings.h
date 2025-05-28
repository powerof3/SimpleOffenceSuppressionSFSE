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

class Settings : public REX::Singleton<Settings>
{
public:
	void Load()
	{
		constexpr auto path = L"Data/SFSE/Plugins/po3_SimpleOffenceSuppression.ini";

		CSimpleIniA ini;
		ini.SetUnicode();

		ini.LoadFile(path);

		ini::get_value(ini, mode, "Settings", "iSuppressionMode", ";Whether neutral NPCs should be considered as friends or allies upon hitting them. This affects the number of hits they'll take before turning hostile (see gamesettings).\n;0 - Friends, 1 - Allies");
		ini::get_value(ini, onlyCombat, "Settings", "bOnlyCombat", ";Neutral NPCs will only ignore player hits during combat");
		ini::get_value(ini, ignoreFriendlyFire, "Settings", "bIgnoreFriendlyFire", ";Neutral NPCs will ALWAYS ignore hits from the player");
		ini::get_value(ini, ignoreCreatures, "Settings", "bDisableCreatureOffenceSuppression", ";Disable offence suppression for animals/creatures (they will turn hostile when hit)");
		ini::get_value(ini, changeGameSettings, "Settings", "bModifyGameSettings", ";Modify following gamesettings using config. These can still be modified by other mods during playtime");

		ini::get_value(ini, iFriendHitNonCombatAllowed, "GameSettings", "iFriendHitNonCombatAllowed", nullptr);
		ini::get_value(ini, iFriendHitCombatAllowed, "GameSettings", "iFriendHitCombatAllowed", nullptr);
		ini::get_value(ini, iAllyHitNonCombatAllowed, "GameSettings", "iAllyHitNonCombatAllowed", nullptr);
		ini::get_value(ini, iAllyHitCombatAllowed, "GameSettings", "iAllyHitCombatAllowed", nullptr);

		if (mode == 1) {
			newReaction = RE::FIGHT_REACTION::kAlly;
		}

		(void)ini.SaveFile(path);
	}

	std::uint32_t mode{ 0 };
	bool          onlyCombat{ false };
	bool          ignoreFriendlyFire{ false };
	bool          ignoreCreatures{ true };

	bool changeGameSettings{ false };

	std::int32_t iFriendHitNonCombatAllowed{ 0 };
	std::int32_t iFriendHitCombatAllowed{ 4 };
	std::int32_t iAllyHitNonCombatAllowed{ 3 };
	std::int32_t iAllyHitCombatAllowed{ 1000 };

	RE::FIGHT_REACTION newReaction{ RE::FIGHT_REACTION::kFriend };
};
