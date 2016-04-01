#pragma once

// Note:
// To get stack traces on Windows release builds:
// Project Properties--> Linker--> Debugging--> Generate Debug Info : Optimize for Debugging / DEBUG

#include "ConsoleSink.h"
#include "ExtraLogLevels.h"
#include "G3log/G3log.hpp"
#include "G3log/logworker.hpp"
#include "cinder/FileSystem.h"
#include "cinder/System.h"

// Mimic Cinder's Built-In logging style
#define G3_LOG_V(stream) LOG(VERBOSE) << stream
#define G3_LOG_D(stream) LOG(DBUG) << stream
#define G3_LOG_I(stream) LOG(INFO) << stream
#define G3_LOG_W(stream) LOG(WARNING) << stream
#define G3_LOG_E(stream) LOG(G3_ERROR) << stream
#define G3_LOG_F(stream) LOG(FATAL) << stream

//! Debug macro to simplify logging an exception, which also prints the exception type
// This macro crashes clang-format
// clang-format off
#define G3_LOG_EXCEPTION( str, exc )	\
{										\
G3_LOG_E( str << ", exception type: " << cinder::System::demangleTypeName( typeid( exc ).name() ) << ", what: " << exc.what() );	\
}
// clang-format on

typedef std::shared_ptr<class G3log> G3logRef;

class G3log {

public:
	static G3logRef create(const std::string &appName, const ci::fs::path logFolder = "", bool redirectCinderLog = true);
	~G3log();

private:
	G3log(const std::string &appName, const ci::fs::path logFolder, bool redirectCinderLog);
	std::unique_ptr<g3::LogWorker> logWorker;
	std::unique_ptr<g3::FileSinkHandle> fileHandle;
	std::unique_ptr<CoutSinkHandle> coutHandle;

	static void ReverseToOriginalFatalHandling();
	static void onFatalError(g3::FatalMessagePtr fatal_message);
};
