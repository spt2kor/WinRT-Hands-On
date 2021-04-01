#include "pch.h"
#include "Logger.h"

std::fstream g_fs;

std::string get_date_string() {
    auto t = std::chrono::system_clock::now();
    auto as_time_t = std::chrono::system_clock::to_time_t(t);
    struct tm tm;
    static char some_buffer[50];
    gmtime_s(&tm, &as_time_t);
    std::strftime(some_buffer, sizeof(some_buffer), "%c", &tm);
    return std::string{ some_buffer };
}


