#pragma once

#include "CoutSink.h"
#include "ExtraLogLevels.h"
#include "G3log/G3log.hpp"
#include "G3log/logworker.hpp"
#include "cinder/FileSystem.h"


// Mimic Cinder's Built-In logging style
#define G3_LOG_V(stream) LOG(VERBOSE) << stream
#define G3_LOG_D(stream) LOG(DBUG) << stream
#define G3_LOG_I(stream) LOG(INFO) << stream
#define G3_LOG_W(stream) LOG(WARNING) << stream
#define G3_LOG_E(stream) LOG(ERROR) << stream
#define G3_LOG_F(stream) LOG(FATAL) << stream

//! Debug macro to simplify logging an exception, which also prints the exception type
#define G3_LOG_EXCEPTION( str, exc )	\
{										\
G3_LOG_E( str << ", exception type: " << cinder::System::demangleTypeName( typeid( exc ).name() ) << ", what: " << exc.what() );	\
}

typedef std::shared_ptr<class G3log> G3logRef;

class G3log {

public:
	G3log(const std::string &appName, const ci::fs::path logFolder = "");
	~G3log();

private:
	std::unique_ptr<g3::LogWorker> logWorker;
	std::unique_ptr<g3::FileSinkHandle> fileHandle;
	std::unique_ptr<CoutSinkHandle> coutHandle;

	static void ReverseToOriginalFatalHandling();
	static void onFatalError(g3::FatalMessagePtr fatal_message);
};
