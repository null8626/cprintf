#ifndef CPRINTF_H
#define CPRINTF_H
#include <stdarg.h>
#include <stddef.h>
#ifdef CPRINTF_DLL
#  ifdef CPRINTF_BUILDING
#    define CPRINTF_EXPORT __declspec(dllexport)
#  else
#    define CPRINTF_EXPORT __declspec(dllimport)
#  endif
#else
#  define CPRINTF_EXPORT
#endif
#ifdef __cplusplus
extern "C" {
#endif
#ifdef _WIN32
#  ifndef CPRINTF_BUILDING
  extern HANDLE _cprintf_handle;
  extern WORD _cprintf_def_attr;
  extern WORD _cprintf_inverse_def_attr;
#  endif
#  include <windows.h>
  CPRINTF_EXPORT unsigned char
  _cprintf_init(void);
#  define cprintf_scope           if (_cprintf_handle != NULL || cprintf_init())
#  define cprintf_color(code)     SetConsoleTextAttribute(_cprintf_handle, code 0)
#  define CPRINTF_RESET           _cprintf_def_attr |
#  define CPRINTF_INVERT          _cprintf_inverse_def_attr |
#  define CPRINTF_FG_BLACK        0 |
#  define CPRINTF_FG_WHITE        FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE |
#  define CPRINTF_BG_BLACK        0 |
#  define CPRINTF_BG_WHITE        BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE |
#  define CPRINTF_FG_RED          FOREGROUND_RED |
#  define CPRINTF_FG_GREEN        FOREGROUND_GREEN |
#  define CPRINTF_FG_YELLOW       FOREGROUND_RED | FOREGROUND_GREEN |
#  define CPRINTF_FG_BLUE         FOREGROUND_BLUE |
#  define CPRINTF_FG_MAGENTA      FOREGROUND_RED | FOREGROUND_BLUE |
#  define CPRINTF_FG_CYAN         FOREGROUND_BLUE | FOREGROUND_GREEN |
#  define CPRINTF_BG_RED          BACKGROUND_RED |
#  define CPRINTF_BG_GREEN        BACKGROUND_GREEN |
#  define CPRINTF_BG_YELLOW       BACKGROUND_RED | BACKGROUND_GREEN |
#  define CPRINTF_BG_BLUE         BACKGROUND_BLUE |
#  define CPRINTF_BG_MAGENTA      BACKGROUND_RED | BACKGROUND_BLUE |
#  define CPRINTF_BG_CYAN         BACKGROUND_BLUE | BACKGROUND_GREEN |
#  define CPRINTF_FG_BOLD         FOREGROUND_INTENSITY |
#  define CPRINTF_BG_BOLD         BACKGROUND_INTENSITY |
#  define CPRINTF_UNDERSCORE      COMMON_LVB_UNDERSCORE |
#  define CPRINTF_UNDERSCORE_ONLY _cprintf_def_attr | COMMON_LVB_UNDERSCORE |
#else
#  include <unistd.h>
#  define cprintf_scope
#  define cprintf_color(code)                                                  \
    write(1, "\x1b[" code "10m", sizeof("\x1b[" code "10"))
#  define CPRINTF_RESET           "0;"
#  define CPRINTF_INVERT          "7;"
#  define CPRINTF_FG_BLACK        "30;"
#  define CPRINTF_FG_WHITE        "37;"
#  define CPRINTF_BG_BLACK        "40;"
#  define CPRINTF_BG_WHITE        "47;"
#  define CPRINTF_FG_RED          "31;"
#  define CPRINTF_FG_GREEN        "32;"
#  define CPRINTF_FG_YELLOW       "33;"
#  define CPRINTF_FG_BLUE         "34;"
#  define CPRINTF_FG_MAGENTA      "35;"
#  define CPRINTF_FG_CYAN         "36;"
#  define CPRINTF_BG_RED          "41;"
#  define CPRINTF_BG_GREEN        "42;"
#  define CPRINTF_BG_YELLOW       "43;"
#  define CPRINTF_BG_BLUE         "44;"
#  define CPRINTF_BG_MAGENTA      "45;"
#  define CPRINTF_BG_CYAN         "46;"
#  define CPRINTF_FG_BOLD         "1;"
#  define CPRINTF_BG_BOLD         CPRINTF_FG_BOLD
#  define CPRINTF_UNDERSCORE      "4;"
#  define CPRINTF_UNDERSCORE_ONLY CPRINTF_UNDERSCORE
#endif
  CPRINTF_EXPORT size_t
  cprintf_ansi(char * str, const size_t size, const char * fmt, ...);
  CPRINTF_EXPORT void
  cprintf(const char * fmt, ...);
#ifdef __cplusplus
}
#endif
#endif
