#include "CinderG3log.h"


G3logRef G3log::create(const std::string &appName, const ci::fs::path logFolder) {
	return std::shared_ptr<G3log>(new G3log(appName, logFolder));
}


G3log::G3log(const std::string &appName, const ci::fs::path logFolder)
		: logWorker(g3::LogWorker::createLogWorker())
		, coutHandle(logWorker->addSink(std2::make_unique<CoutSink>(), &CoutSink::ReceiveLogMessage)) {

	// Only log to file if a folder is specified
	if (logFolder != "") {
		fileHandle = logWorker->addDefaultLogger(appName, logFolder.generic_string());
	}

// Verbose
// Dbug
// Info
// Warning
// Error
// Fatal

#if !defined(G3_MIN_LOG_LEVEL)
#if !defined(NDEBUG)
#define G3_MIN_LOG_LEVEL 0 // debug mode default is LEVEL_VERBOSE
#else
#define G3_MIN_LOG_LEVEL 2 // release mode default is LEVEL_INFO
#endif
#endif

#if (G3_MIN_LOG_LEVEL <= 0)
	g3::only_change_at_initialization::setLogLevel(VERBOSE, true);
#else
	g3::only_change_at_initialization::setLogLevel(VERBOSE, false);
#endif

#if (G3_MIN_LOG_LEVEL <= 1)
	g3::only_change_at_initialization::setLogLevel(DBUG, true);
#else
	g3::only_change_at_initialization::setLogLevel(DBUG, false);
#endif

#if (G3_MIN_LOG_LEVEL <= 2)
	g3::only_change_at_initialization::setLogLevel(INFO, true);
#else
	g3::only_change_at_initialization::setLogLevel(INFO, false);
#endif

#if (G3_MIN_LOG_LEVEL <= 3)
	g3::only_change_at_initialization::setLogLevel(WARNING, true);
#else
	g3::only_change_at_initialization::setLogLevel(WARNING, false);
#endif

#if (G3_MIN_LOG_LEVEL <= 4)
	g3::only_change_at_initialization::setLogLevel(ERROR, true);
#else
	g3::only_change_at_initialization::setLogLevel(ERROR, false);
#endif

#if (G3_MIN_LOG_LEVEL <= 5)
	g3::only_change_at_initialization::setLogLevel(FATAL, true);
#else
	g3::only_change_at_initialization::setLogLevel(FATAL, false);
#endif

	g3::initializeLogging(logWorker.get());
	g3::setFatalExitHandler(&G3log::onFatalError);

#if WIN32
	g3::setFatalPreLoggingHook([] { __debugbreak(); });
#endif
}

G3log::~G3log() {
	LOG(DBUG) << __FUNCTION__;
}

void G3log::ReverseToOriginalFatalHandling() {
#if !(defined(DISABLE_FATAL_SIGNALHANDLING))
	if (SIG_ERR == signal(SIGABRT, SIG_DFL))
		perror("signal - SIGABRT");

	if (SIG_ERR == signal(SIGFPE, SIG_DFL))
		perror("signal - SIGABRT");

	if (SIG_ERR == signal(SIGSEGV, SIG_DFL))
		perror("signal - SIGABRT");

	if (SIG_ERR == signal(SIGILL, SIG_DFL))
		perror("signal - SIGABRT");

	if (SIG_ERR == signal(SIGTERM, SIG_DFL))
		perror("signal - SIGABRT");
#endif
}

void G3log::onFatalError(g3::FatalMessagePtr fatal_message) {
	ReverseToOriginalFatalHandling();

	// maybe save your work here

	// now ready to exit, instead of reinventing the wheel we do it the G3log way
	g3::internal::pushFatalMessageToLogger(fatal_message);
}
