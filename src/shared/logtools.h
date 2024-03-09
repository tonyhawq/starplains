#pragma once

#include <fstream>
#include <string>

#include "Timer.h"

namespace logtools
{
	static std::ofstream defaultLog;
	static Timer time;

	// courtesy of https://stackoverflow.com/questions/8487986/file-macro-shows-full-path

	template <typename T, size_t S>
	inline constexpr size_t get_file_name_offset(const T(&str)[S], size_t i = S - 1)
	{
		return (str[i] == '/' || str[i] == '\\') ? i + 1 : (i > 0 ? get_file_name_offset(str, i - 1) : 0);
	}

	template <typename T>
	inline constexpr size_t get_file_name_offset(T(&str)[1])
	{
		return 0;
	}
	template <typename T, T v>
	struct const_expr_value
	{
		static constexpr const T value = v;
	};
}

// I LOVE COMPILE TIME I LOVE MACROS I WILL EAT THE BUGS
#define SPST_CONST_EXPR_VALUE(exp) ::logtools::const_expr_value<decltype(exp), exp>::value

#define __FILE_LEAF__ (&__FILE__[SPST_CONST_EXPR_VALUE(::logtools::get_file_name_offset(__FILE__))])

#define SP_OPEN_LOG() { std::ifstream sp_logtools_last_log("starplains-current.log");\
						 logtools::defaultLog.open("starplains-last.log");\
						 logtools::defaultLog << sp_logtools_last_log.rdbuf();\
						 logtools::defaultLog.close();\
						 sp_logtools_last_log.close(); }\
						 logtools::defaultLog.open("starplains-current.log"); logtools::time.reset()
#define SP_CLOSE_LOG() logtools::defaultLog.close()

#ifdef _DEBUG

#define SP_LOG_PREFIXED(prefix, str) logtools::defaultLog << logtools::time.time() << " [" << __FILE_LEAF__ << ":" << __LINE__ << "] " << prefix << ": " << str << std::endl

#define SP_DEBUG_LOG(str) SP_LOG_PREFIXED("Debug", str)
#define SP_DEBUG_LOGF(str, ...) SP_DEBUG_LOG(std::format(str, __VA_ARGS__))

#else

#define SP_LOG_PREFIXED(prefix, str) logtools::defaultLog << prefix << " [" << __FILE__ << ":" << __LINE__ << "] " << logtools::time.time() << ": " << str << '\n'

#define SP_DEBUG_LOG(str)
#define SP_DEBUG_LOGF(str)

#endif

#define SP_LOG(str) SP_LOG_PREFIXED("", str)
#define SP_LOGF(str, ...) SP_LOG(std::format(str, __VA_ARGS__))
#define SP_WARN(str) SP_LOG_PREFIXED("WARN", str)
#define SP_WARNF(str, ...) SP_WARN(std::format(str, __VA_ARGS__))
#define SP_FLUSH() logtools::defaultLog.flush();