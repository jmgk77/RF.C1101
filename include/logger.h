#pragma once

#include <Arduino.h>

#define LOG_FILE_NAME "/system.log"
#define LOG_MAX_FILE_SIZE 16384  // 16 KB
#define RAM_LOG_BUFFER_SIZE 4096 // 4 KB

void init_logger();
void log_printf(const char* format, ...);
void log_println(const String& msg);
void log_println(const char* msg);
String get_ram_logs();
String get_all_logs();
void clear_logs();
