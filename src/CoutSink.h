#pragma once
#include "ExtraLogLevels.h"
#include "g3log/logmessage.hpp"
#include "g3log/logworker.hpp"
#include <iostream>
#include <string>

struct CoutSink {

	bool isXcodeColorSupported = false;

	CoutSink() {

// Support Xcode Colors, if it's available
// https://github.com/robbiehanson/XcodeColors
#ifdef CINDER_MAC
		const char *xcode_colors = getenv("XcodeColors");
		if (xcode_colors && (strcmp(xcode_colors, "YES") == 0)) {
			isXcodeColorSupported = true;

// Macros
#define XCODE_COLORS_ESCAPE "\033["
#define XCODE_COLORS_RESET_FG XCODE_COLORS_ESCAPE "fg;" // Clear any foreground color
#define XCODE_COLORS_RESET_BG XCODE_COLORS_ESCAPE "bg;" // Clear any background color
#define XCODE_COLORS_RESET XCODE_COLORS_ESCAPE ";"			// Clear any foreground or background color
		}
#endif

		// TODO Linux xterm color
		// http://stackoverflow.com/questions/2616906/how-do-i-output-coloured-text-to-a-linux-terminal
	}

	char const *GetColor(const LEVELS level) const {
		if (level.value == WARNING.value) {
			return "255,255,0"; // yellow
		}
		if (level.value == DBUG.value) {
			return "0,255,0"; // green
		}
		if ((level.value == ERROR.value) || g3::internal::wasFatal(level)) {
			return "255,0,0"; // red
		}
		return "255,255,255";
	}

	void ReceiveLogMessage(g3::LogMessageMover logEntry) {
		if (isXcodeColorSupported) {
			auto level = logEntry.get()._level;
			auto color = GetColor(level);

			
			
			
			// get the whole default-formatted message: logEntry.get().toString()
			
			// custom format
			std::cout << XCODE_COLORS_ESCAPE << "fg" << color << ";" << logEntry.get()._file << ":" << logEntry.get()._line << "\t" << logEntry.get()._message << XCODE_COLORS_RESET << std::endl;
		} else {
			std::cout << logEntry.get()._file << ":" << logEntry.get()._line << "\t" << logEntry.get()._message << std::endl;
		}
	}
};

using CoutSinkHandle = g3::SinkHandle<CoutSink>;