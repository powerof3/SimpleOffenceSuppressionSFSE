#include "Hooks.h"

namespace SimpleOffenceSuppression
{
	RE::BSEventNotifyControl EventHandler::ProcessEvent(const RE::MenuOpenCloseEvent& a_event, RE::BSTEventSource<RE::MenuOpenCloseEvent>*)
	{
		if (a_event.menuName == "HUDMenu" && a_event.opening) {
			constexpr auto set_gmst = [](const std::string_view a_name, std::int32_t a_value) {
				RE::GameSettingCollection::GetSingleton()->SetSetting(a_name, a_value);
				REX::INFO("Gamesetting : {} : {}", a_name, a_value);
			};

			const auto settings = Settings::GetSingleton();
			set_gmst("iFriendHitNonCombatAllowed", settings->iFriendHitNonCombatAllowed);
			set_gmst("iFriendHitCombatAllowed", settings->iFriendHitCombatAllowed);
			set_gmst("iAllyHitNonCombatAllowed", settings->iAllyHitNonCombatAllowed);
			set_gmst("iAllyHitCombatAllowed", settings->iAllyHitCombatAllowed);

			RE::UI::GetSingleton()->menuOpenCloseEvent.UnregisterSink(GetSingleton());
		}
		return RE::BSEventNotifyControl::kContinue;
	}

	void InstallOnPostLoad()
	{
		const auto settings = Settings::GetSingleton();
		settings->Load();

		if (settings->changeGameSettings) {
			RE::UI::GetSingleton()->menuOpenCloseEvent.RegisterSink(EventHandler::GetSingleton());
		}

		REX::INFO("Hooked GetFactionFightReaction");
	}
}
