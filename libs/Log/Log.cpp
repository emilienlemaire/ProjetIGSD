//
// Created by Emilien Lemaire on 28/11/2019.
//

#include "Log.h"

Log::Level Log::m_Level;

void Log::printErr(const std::string& err, const std::string& file, int line) {
    if (m_Level >= LevelError) std::cout << "\033[31mError: \033[35m"<< file << ":" << line << ": \033[31m" << err << "\033[m" << std::endl;
}

void Log::printWarning(const std::string& warn, const std::string& file, int line) {
    if (m_Level >= LevelWarn) std::cout << "\033[33mWarning: \033[35m" << file << ":" << line << ": \033[33m" << warn << "\033[m" << std::endl;
}

void Log::printInfo(const std::string& info) {
    if (m_Level >= LevelInfo) std::cout << "\033[32mInfo: " << info << "\033[m" << std::endl;
}

void Log::setLevel(Log::Level level) {
    m_Level = level;
}

Log &Log::get() {
    static Log log;
    return log;
}

void Log::printDebug(const std::string &info) {
    if (m_Level >= LevelDebug) std::cout << "\033[35mDebug: " << info << "\033[m" << std::endl;
}
