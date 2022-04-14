//
// Created by linfeng on 2022/3/15.
//

#ifndef GODCC_LOG_H
#define GODCC_LOG_H

#include <cstdarg>
#include <cstdio>

#define _DEBUG
#define _INFO

void DEBUG(const char *fmt, ...);

void INFO(const char *fmt, ...);

#endif//GODCC_LOG_H
