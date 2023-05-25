#pragma once

// loader

#include <filesystem>
#include <string>

#include <Windows.h>

#include <ShlObj_core.h>
#include <mmsystem.h>
#include <mmddk.h>

#include <wil/resource.h>
#include <wil/stl.h>
#include <wil/win32_helpers.h>

#include <fmt/core.h>
#include <fmt/xchar.h>

// dll

#include <cstdarg>
#include <cstdint>
#include <filesystem>
#include <fstream>
#include <list>
#include <map>
#include <memory>
#include <mutex>
#include <ranges>
#include <source_location>
#include <string>
#include <string_view>
#include <system_error>
#include <unordered_set>

#include <Windows.h>
#include <detours.h>
#include <tlhelp32.h>

#include <wil/resource.h>
#include <wil/stl.h>
#include <wil/win32_helpers.h>

#include <fmt/core.h>
#include <fmt/format.h>
#include <fmt/xchar.h>

// #include <spdlog/spdlog.h>
// #include <toml.hpp>
// #include <tsl/ordered_map.h>
// 
// #include <RED4ext/RED4ext.hpp>
