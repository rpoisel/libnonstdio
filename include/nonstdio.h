#ifndef __NONSTDIO_H__
#define __NONSTDIO_H__ 1

#include <stdarg.h>

int non_snprintf(char* buf, size_t size, const char* fmt, ...);
int non_vsnprintf(char* buf, size_t size, const char* fmt, va_list args);

#endif /* __NONSTDIO_H__ */
