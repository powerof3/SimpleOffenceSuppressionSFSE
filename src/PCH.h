#pragma once

#include "RE/Starfield.h"
#include "SFSE/SFSE.h"

#include "REX/REX/Singleton.h"

#include <ClibUtil/simpleINI.hpp>
#include <ClibUtil/string.hpp>
#include <spdlog/sinks/basic_file_sink.h>
#include <xbyak/xbyak.h>

namespace logger = SFSE::log;
namespace string = clib_util::string;
namespace ini = clib_util::ini;

using namespace std::literals;

#include "Version.h"
