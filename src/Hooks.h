#pragma once

#include "Settings.h"

namespace RE
{
	void* BGSScaleFormManager();
	void  ExecuteCommand(void* a_scaleformManager, const char* a_command);
}

namespace SimpleOffenceSuppression
{
	struct GetFactionFightReaction
	{
		static RE::FIGHT_REACTION                      thunk(RE::Actor* a_subject, RE::Actor* a_player);
		static inline REL::Relocation<decltype(thunk)> func;
	};

	class EventHandler :
		public ISingleton<EventHandler>,
		public RE::BSTEventSink<RE::MenuOpenCloseEvent>
	{
		RE::BSEventNotifyControl ProcessEvent(const RE::MenuOpenCloseEvent& a_event, RE::BSTEventSource<RE::MenuOpenCloseEvent>* a_eventSource) override;
	};

	void InstallOnPostLoad();
}
