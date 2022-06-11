#ifndef CPRINTF_H
#define CPRINTF_H

#include <stdbool.h>
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

#ifdef _WIN32
#include <windows.h>
#define CPRINTF_STDOUT STD_OUTPUT_HANDLE
#define CPRINTF_STDERR STD_ERROR_HANDLE
typedef DWORD cprintf_fd_t;
#else
#include <stdio.h>
#define CPRINTF_STDOUT stdout
#define CPRINTF_STDERR stderr
typedef FILE * cprintf_fd_t;
#endif

#ifdef __cplusplus
extern "C"
{
#endif

    CPRINTF_EXPORT bool cprintf_use(const cprintf_fd_t type);
    CPRINTF_EXPORT size_t cprintf_ansi(char *str, const size_t size, const char *fmt, ...);
    CPRINTF_EXPORT void cprintf(const char *fmt, ...);

#ifdef __cplusplus
}
#endif

#endif
