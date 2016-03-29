#pragma once


VERBOSE{ g3::kDebugVaulue - 1, { "VERBOSE" } },
ERROR{ g3::kWarningValue + 1, { "ERROR" } },



#include "g3log/g3log.hpp"
#include "g3log/logworker.hpp"


typedef std::shared_ptr<class Log> LogRef;

class Log {

public:
	Log(const std::string &logFolder, const std::string &appName);
	~Log();

private:
	std::string logFolder;
	std::unique_ptr<g3::LogWorker> logWorker;
	std::unique_ptr<g3::FileSinkHandle> fileHandle;

	static void ReverseToOriginalFatalHandling();
	static void onFatalError(g3::FatalMessagePtr fatal_message);

}; // end class Log


0307