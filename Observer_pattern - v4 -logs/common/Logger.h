#pragma once
#include <fstream>
#include <iostream>
#include <chrono>
#include <ctime>
#include <time.h>

using namespace std;

extern std::fstream g_fs;

std::string get_date_string();

#define Log(msg) g_fs << get_date_string()  <<"@"<<__LINE__<<":"<<":"<<__FUNCTION__<<"()["<<(std::this_thread::get_id())<<"] : "<<(msg) << endl;