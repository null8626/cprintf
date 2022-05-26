#ifndef CPRINTF_H
#define CPRINTF_H

#include <stdarg.h>
#include <stddef.h>

#ifdef CPRINTF_DLL
#ifdef CPRINTF_BUILDING
#define CPRINTF_EXPORT __declspec(dllexport)
#else
#define CPRINTF_EXPORT __declspec(dllimport)
#endif
#else
#define CPRINTF_EXPORT
#endif

#ifdef __cplusplus
extern "C" {
#endif

CPRINTF_EXPORT size_t cprintf_ansi(char * str, const size_t size, const char * fmt, ...);
CPRINTF_EXPORT void cprintf(const char * fmt, ...);

#ifdef __cplusplus
}
#endif
#endif
