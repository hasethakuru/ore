#pragma once

#include "Core.h"
#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h"

namespace Ore {
	class API Log
	{
	public:
		static void Init();
		inline static  std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
		inline static  std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }
	private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;
	};
}

//Core Log Marcos
#define ORE_CORE_TRACE(...)		::Ore::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define ORE_CORE_INFO(...)		::Ore::Log::GetCoreLogger()->info(__VA_ARGS__)
#define ORE_CORE_WARN(...)		::Ore::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define ORE_CORE_ERROR(...)		::Ore::Log::GetCoreLogger()->error(__VA_ARGS__)
#define ORE_CORE_FATAL(...)		::Ore::Log::GetCoreLogger()->fatal(__VA_ARGS__)

//Client Log Macros
#define ORE_TRACE(...)		::Ore::Log::GetClientLogger()->trace(__VA_ARGS__)
#define ORE_INFO(...)		::Ore::Log::GetClientLogger()->info(__VA_ARGS__)
#define ORE_WARN(...)		::Ore::Log::GetClientLogger()->warn(__VA_ARGS__)
#define ORE_ERROR(...)		::Ore::Log::GetClientLogger()->error(__VA_ARGS__)
#define ORE_FATAL(...)		::Ore::Log::GetClientLogger()->fatal(__VA_ARGS__)