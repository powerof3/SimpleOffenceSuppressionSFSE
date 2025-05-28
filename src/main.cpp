#include "Hooks.h"

struct GetFactionFightReaction
{
	static RE::FIGHT_REACTION GetFactionFightReactionFunc(RE::Actor* a_subject, RE::Actor* a_player)
	{
		const auto fightReaction = _GetFactionFightReactionFun(a_subject, a_player);
		if (fightReaction == RE::FIGHT_REACTION::kNeutral) {
			if (a_subject && !a_subject->IsHostileToActor(a_player)) {
				const auto settings = Settings::GetSingleton();
				if (settings->onlyCombat && !a_player->IsInCombat()) {
					return fightReaction;
				}
				if (settings->ignoreCreatures && a_subject->HasKeyword(SimpleOffenceSuppression::actorTypeCreatureKYWD)) {
					return fightReaction;
				}
				if (settings->ignoreFriendlyFire && a_subject->formFlags.none(RE::TESForm::FormFlags::kIgnoreFriendlyHits)) {
					a_subject->formFlags.set(RE::TESForm::FormFlags::kIgnoreFriendlyHits);
				}
				return settings->newReaction;
			}
		}
		return fightReaction;
		
		
		return _GetFactionFightReactionFun(a_subject, a_player);
	}

	inline static REL::Hook _GetFactionFightReactionFun{ REL::ID(101661), 0x3AC, GetFactionFightReactionFunc };  // DONE
};

void MessageHandler(SFSE::MessagingInterface::Message* a_message)
{
	switch (a_message->type) {
	case SFSE::MessagingInterface::kPostLoad:
		SimpleOffenceSuppression::InstallOnPostLoad();
		break;
	case SFSE::MessagingInterface::kPostDataLoad:
		{
			SimpleOffenceSuppression::actorTypeCreatureKYWD = RE::TESForm::LookupByID<RE::BGSKeyword>(0x001469CF);
			REX::INFO("ActorTypeCreature keyword lookup {}", SimpleOffenceSuppression::actorTypeCreatureKYWD != nullptr ? "succeeded" : "failed");
		}
		break;
	default:
		break;
	}
}

SFSE_EXPORT constinit auto SFSEPlugin_Version = []() noexcept {
	SFSE::PluginVersionData data{};

	data.PluginVersion(Version::MAJOR);
	data.PluginName(Version::PROJECT);
	data.AuthorName("powerofthree");
	data.UsesSigScanning(false);
	data.UsesAddressLibrary(true);
	data.HasNoStructUse(false);
	data.IsLayoutDependent(true);
	data.CompatibleVersions({ SFSE::RUNTIME_LATEST });

	return data;
}();

SFSEPluginLoad(const SFSE::LoadInterface* a_sfse)
{
	SFSE::Init(a_sfse, { .trampoline = true });
	SFSE::GetMessagingInterface()->RegisterListener(MessageHandler);
	return true;
}
