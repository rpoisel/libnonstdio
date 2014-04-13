#ifndef __NONSTDIO_H__
#define __NONSTDIO_H__ 1

#include <stdarg.h>

int non_sprintf(char* buf, const char* fmt, ...);
int non_vsprintf(char* buf, const char* fmt, va_list args);

#endif /* __NONSTDIO_H__ */
