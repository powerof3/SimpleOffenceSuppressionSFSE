#include "Hooks.h"

namespace RE
{
	void* BGSScaleFormManager()
	{
		static REL::Relocation<void**> singleton{ REL::ID(879512) };
		return *singleton;
	}
	void ExecuteCommand(void* a_scaleformManager, const char* a_command)
	{
		using func_t = decltype(&ExecuteCommand);
		REL::Relocation<func_t> func{ REL::ID(166307) };
		func(a_scaleformManager, a_command);
	}
}

namespace SimpleOffenceSuppression
{
	RE::FIGHT_REACTION GetFactionFightReaction::thunk(RE::Actor* a_subject, RE::Actor* a_player)
	{
		const auto fightReaction = func(a_subject, a_player);
		if (fightReaction == RE::FIGHT_REACTION::kNeutral) {
			if (a_subject && !a_subject->IsHostileToActor(a_player)) {
				const auto settings = Settings::GetSingleton();
				if (settings->onlyCombat && !a_player->IsInCombat()) {
					return fightReaction;
				}
				if (settings->ignoreCreatures && a_subject->HasKeyword(actorTypeCreatureKYWD)) {
					return fightReaction;
				}
				if (settings->ignoreFriendlyFire && (a_subject->formFlags & 0x100000) == 0) {
					a_subject->formFlags |= 0x100000;
				}
				return settings->newReaction;
			}
		}
		return fightReaction;
	}

	RE::BSEventNotifyControl EventHandler::ProcessEvent(const RE::MenuOpenCloseEvent& a_event, RE::BSTEventSource<RE::MenuOpenCloseEvent>*)
	{
		if (a_event.menuName == "HUDMenu" && a_event.opening) {
			constexpr auto set_gmst = [](const char* a_name, std::int32_t a_value) {
				RE::ExecuteCommand(RE::BGSScaleFormManager(), std::format("SetGS {} {}", a_name, a_value).c_str());
				logger::info("Gamesetting : {} : {}", a_name, a_value);
			};

			const auto settings = Settings::GetSingleton();
			set_gmst("iFriendHitNonCombatAllowed", settings->iFriendHitNonCombatAllowed);
			set_gmst("iFriendHitCombatAllowed", settings->iFriendHitCombatAllowed);
			set_gmst("iAllyHitNonCombatAllowed", settings->iAllyHitNonCombatAllowed);
			set_gmst("iAllyHitCombatAllowed", settings->iAllyHitCombatAllowed);

			RE::UI::GetSingleton()->UnregisterSink(GetSingleton());
		}
		return RE::BSEventNotifyControl::kContinue;
	}

	void InstallOnPostLoad()
	{
		const auto settings = Settings::GetSingleton();
		settings->Load();

		const REL::Relocation<std::uintptr_t> target{ REL::ID(151616), 0x244 };
		stl::write_thunk_call<GetFactionFightReaction>(target.address());

		if (settings->changeGameSettings) {
			RE::UI::GetSingleton()->RegisterSink(EventHandler::GetSingleton());
		}

		logger::info("Hooked GetFactionFightReaction");
	}
}
