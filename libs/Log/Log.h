//
// Created by Emilien Lemaire on 28/11/2019.
//

#pragma once

#include <iostream>

class Log {
public:
    enum Level{
        LevelError = 0, LevelWarn, LevelInfo, LevelDebug
    };
private:
    static Log::Level m_Level;

public:
    static Log& get();
    static void setLevel(Log::Level level);
    static void printErr(const std::string& err, const std::string& file, int line);
    static void printWarning(const std::string& warn, const std::string& file, int line);
    static void printInfo(const std::string& info);
    static void printDebug(const std::string& info);
};

#define Error(x) Log::printErr(x, __FILE__, __LINE__)
#define Warn(x) Log::printWarning(x, __FILE__, __LINE__)
#define Info(x) Log::printInfo(x)
#define Debug(x) Log::printDebug(x)
