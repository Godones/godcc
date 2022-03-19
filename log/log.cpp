//
// Created by linfeng on 2022/3/15.
//

#include "log.h"

void DEBUG(const char *fmt, ...) {
#ifdef _DEBUG
  printf("[DEBUG] ");
  printf("\033[35m");
  va_list args;
  va_start(args, fmt);
  vprintf(fmt, args);
  va_end(args);
  printf("\033[0m\n");
#endif
}

void INFO(const char *fmt, ...) {
#ifdef _INFO
  printf("[INFO] ");
  printf("\033[36m");
  va_list args;
  va_start(args, fmt);
  vprintf(fmt, args);
  va_end(args);
  printf("\033[0m\n");
#endif
}