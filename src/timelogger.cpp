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

#include "time_logger.h"

TimeLogger timeLogger;

TimeLogger::TimeLogger() {}

void TimeLogger::openTimingLog(const std::string& filename) {
    timingLogUseFrameCount = false;
    timingLogFrameCount = 0;
    //use a frame counter rather than a time elapsed seconds counter if we're outputing to a PPM video file
    if(gGourceSettings.output_ppm_filename.size() > 0) timingLogUseFrameCount = true;
    if(!timingLogUseFrameCount) {
        //make a note of the start time of our recording if we're going to log time elapsed events to a timing log file
        struct timeval tp;
        gettimeofday(&tp, NULL);
        timingLogStartTimeMs = tp.tv_sec * 1000 + tp.tv_usec / 1000;
    }
    if(!filename.empty()) {
        timingLogFilename = filename;
        timingLog.open(timingLogFilename,std::ios::trunc);
        if(timingLog.is_open()) timingLogEnabled = true;
    }

}
void TimeLogger::closeTimingLog() {
    if(timingLogEnabled) timingLog.close();
}

void TimeLogger::writeTimingLog(const std::string& user, const std::string& action, const std::string& file) {
    if(timingLogEnabled) {
        if(timingLogUseFrameCount) {
            timingLog << timingLogFrameCount << "|" << user << "|" << action << "|" << file << "\n";
        } else {
            struct timeval tp;
            gettimeofday(&tp, NULL);
            float offset = ((tp.tv_sec * 1000 + tp.tv_usec / 1000) - timingLogStartTimeMs) / 1000.f;
            timingLog << offset << "|" << user << "|" << action << "|" << file << "\n";
        }
    }
}

void TimeLogger::setTimingLogFrameCount(int framecount) {
    timingLogFrameCount = framecount;
}

void TimeLogger::incTimingLogFrameCount() {
    timingLogFrameCount++;
}