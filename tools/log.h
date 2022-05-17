//
// Created by linfeng on 2022/3/15.
//

#ifndef GODCC_LOG_H
#define GODCC_LOG_H

#include <cstdarg>
#include <cstdio>
#include <ctime>
#include "cstring"

#define _DEBUG
#define _INFO
#define _ERROR
#define _WARNING

void DEBUG(const char *fmt, ...);

void INFO(const char *fmt, ...);

void ERROR(const char *fmt,...);

void WARNING(const char *fmt, ...);

void get_time();

#endif//GODCC_LOG_H
