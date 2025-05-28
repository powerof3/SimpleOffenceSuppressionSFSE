#pragma once

#include "Settings.h"

namespace SimpleOffenceSuppression
{
	inline RE::BGSKeyword* actorTypeCreatureKYWD{ nullptr };

	class EventHandler :
		public REX::Singleton<EventHandler>,
		public RE::BSTEventSink<RE::MenuOpenCloseEvent>
	{
		RE::BSEventNotifyControl ProcessEvent(const RE::MenuOpenCloseEvent& a_event, RE::BSTEventSource<RE::MenuOpenCloseEvent>* a_eventSource) override;
	};

	void InstallOnPostLoad();
}
