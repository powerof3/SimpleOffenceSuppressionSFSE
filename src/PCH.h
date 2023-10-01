#pragma once

#include "RE/Starfield.h"
#include "SFSE/SFSE.h"

#include <ClibUtil/simpleINI.hpp>
#include <ClibUtil/singleton.hpp>
#include <ClibUtil/string.hpp>
#include <spdlog/sinks/basic_file_sink.h>
#include <xbyak/xbyak.h>

namespace logger = SFSE::log;
namespace string = clib_util::string;
namespace ini = clib_util::ini;

using namespace std::literals;
using namespace clib_util::singleton;

namespace stl
{
	using namespace SFSE::stl;
}

#define DLLEXPORT extern "C" [[maybe_unused]] __declspec(dllexport)

#include "Version.h"
