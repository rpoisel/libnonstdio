#ifndef __NONSTDIO_H__
#define __NONSTDIO_H__ 1

#include <stdarg.h>

int func(const char* fmt, ...);
int vfunc(const char* fmt, va_list args);

#endif /* __NONSTDIO_H__ */
