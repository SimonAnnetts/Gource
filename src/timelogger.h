/*
    Copyright (C) 2019 Simon Annetts (simon@ateb.co.uk)

    This program is free software; you can redistribute it and/or
    modify it under the terms of the GNU General Public License
    as published by the Free Software Foundation; either version
    3 of the License, or (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef TIMELOGGER_H
#define TIMELOGGER_H

#include <string>
#include <iostream>
#include <fstream>
#include <sys/time.h>

#include "gource_settings.h"
#include "gource.h"

class TimeLogger {
public:
    TimeLogger();

    std::ofstream timingLog;

    long timingLogStartTimeMs;

    bool timingLogEnabled;

    std::string timingLogFilename;

    bool timingLogUseFrameCount;

    int timingLogFrameCount;

    void openTimingLog(const std::string& filename);

    void closeTimingLog();

    void writeTimingLog(const std::string& user, const std::string& action, const std::string& file);

    void setTimingLogFrameCount(int framecount);

    void incTimingLogFrameCount();

};

extern TimeLogger timeLogger;

#endif