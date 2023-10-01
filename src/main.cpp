#include "Hooks.h"

void MessageHandler(SFSE::MessagingInterface::Message* a_message)
{
	switch (a_message->type) {
	case SFSE::MessagingInterface::kPostLoad:
		SimpleOffenceSuppression::InstallOnPostLoad();
		break;
	default:
		break;
	}
}

DLLEXPORT constinit auto SFSEPlugin_Version = []() noexcept {
	SFSE::PluginVersionData data{};

	data.PluginVersion(Version::MAJOR);
	data.PluginName(Version::PROJECT);
	data.AuthorName("powerofthree");
	data.UsesSigScanning(true);
	//data.UsesAddressLibrary(true);
	data.HasNoStructUse(true);
	//data.IsLayoutDependent(true);
	data.CompatibleVersions({ SFSE::RUNTIME_SF_1_7_29 });

	return data;
}();

DLLEXPORT bool SFSEAPI SFSEPlugin_Load(const SFSE::LoadInterface* a_sfse)
{
	SFSE::Init(a_sfse);

	logger::info("Game version : {}", a_sfse->RuntimeVersion().string());
	logger::info("Plugin version : {}", Version::NAME);

	const auto messaging = SFSE::GetMessagingInterface();
	messaging->RegisterListener(MessageHandler);

	return true;
}
