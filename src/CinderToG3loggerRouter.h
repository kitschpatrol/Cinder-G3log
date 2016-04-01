// This implements a Logger for cinder's build in logging sytem. It redirects and logs sent to cinder's system to G3.
// CinderG3log automatically overrides all default cinder loggers if the create method's redirectCinderLog flag is true.
// This is NOT performant, but allows logging calls compiled into static libraries to be captured correctly by G3logger

#pragma once

#include "CinderG3log.h"
#include "cinder/Log.h"

class CinderToG3loggerRouter : public ci::log::Logger {
public:
	void write(const ci::log::Metadata &meta, const std::string &text) override;

private:
	// helper for converting log levels
	static inline const LEVELS &cinderLogLevelToG3logLevel(ci::log::Level cinderLogLevel) {
		switch (cinderLogLevel) {
			case ci::log::LEVEL_VERBOSE:
				return VERBOSE;
				break;
			case ci::log::LEVEL_DEBUG:
				return DBUG;
				break;
			case ci::log::LEVEL_INFO:
				return INFO;
				break;
			case ci::log::LEVEL_WARNING:
				return WARNING;
				break;
			case ci::log::LEVEL_ERROR:
				return G3_ERROR;
				break;
			case ci::log::LEVEL_FATAL:
				return FATAL;
				break;
		}
	};
};

// Implementation

void CinderToG3loggerRouter::write(const ci::log::Metadata &meta, const std::string &text) {

	// Map Cinder level to G3 level
	const LEVELS &g3LogLevel = cinderLogLevelToG3logLevel(meta.mLevel);

	if (g3::logLevel(g3LogLevel)) {
		// //LogCapture(const char *file, const int line, const char *function, const LEVELS &level, const char *expression = "", g3::SignalType fatal_signal = SIGABRT, const char *dump = nullptr);
		// Send to G3log. (Pused to background worker on destruction.)
		LogCapture(meta.mLocation.getFileName().c_str(), meta.mLocation.getLineNumber(), meta.mLocation.getFunctionName().c_str(), g3LogLevel).stream() << text;

		// TODO fatal logs?
		// TODO some kind of flag on these?
	}
}
