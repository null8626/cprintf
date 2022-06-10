#include "cprintf.h"
#ifdef _WIN32
#  include <windows.h>
HANDLE _cprintf_handle = NULL;
WORD _cprintf_def_attr = 0;
WORD _cprintf_inverse_def_attr;
#else
#  include <string.h>
#endif
#include <ctype.h>
#include <stdio.h>
#ifdef _WIN32
static WORD possible_colors[] = { FOREGROUND_RED,   FOREGROUND_GREEN,
                                  FOREGROUND_BLUE,  BACKGROUND_RED,
                                  BACKGROUND_GREEN, BACKGROUND_BLUE };
static WORD retained_formats[] = { FOREGROUND_INTENSITY,
                                   BACKGROUND_INTENSITY,
                                   COMMON_LVB_UNDERSCORE };
static WORD
_cprintf_get_inverse(void) {
  WORD res = 0;
  unsigned char i;
  for (i = 0; i < 6; i++) {
    if ((_cprintf_def_attr & possible_colors[i]) == 0) {
      res |= possible_colors[i];
    }
  }
  for (i = 0; i < 3; i++) {
    if (_cprintf_def_attr & retained_formats[i]) {
      res |= retained_formats[i];
    }
  }
  return res;
}
CPRINTF_EXPORT unsigned char
_cprintf_init(void) {
  if (_cprintf_handle != NULL) return 1;
  if ((_cprintf_handle = GetStdHandle(-11)) == NULL) return 0;
  else if (_cprintf_def_attr != 0) return 1;
  CONSOLE_SCREEN_BUFFER_INFO info;
  if (GetConsoleScreenBufferInfo(_cprintf_handle, &info) == 0) return 0;
  _cprintf_def_attr = info.wAttributes;
  _cprintf_inverse_def_attr = _cprintf_get_inverse();
  return 1;
}
typedef struct {
    unsigned char char_code;
    WORD foreground;
    WORD background;
} colors_t;
static const colors_t colors[] = {
  {114,                          FOREGROUND_RED,BACKGROUND_RED                                                       },
  {103,                               FOREGROUND_GREEN,                  BACKGROUND_GREEN},
  {121,              FOREGROUND_RED | FOREGROUND_GREEN, BACKGROUND_RED | BACKGROUND_GREEN},
  { 98,                                FOREGROUND_BLUE,                   BACKGROUND_BLUE},
  {109,               FOREGROUND_RED | FOREGROUND_BLUE,  BACKGROUND_RED | BACKGROUND_BLUE},
  { 99,
   FOREGROUND_GREEN | FOREGROUND_BLUE,
   BACKGROUND_GREEN | BACKGROUND_BLUE                                                    },
  {119,
   FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE,
   BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE                                   }
};
#endif
static const char ansi_order[8] = { 'k', 'r', 'g', 'y', 'b', 'm', 'c', 'w' };
typedef struct {
    char ansi[20];
    unsigned char ansi_len;
    unsigned char input_size;
} ansi_context_t;
#ifdef _WIN32
typedef struct {
    WORD attr;
    unsigned char input_size;
    unsigned char colored;
} context_t;
#else
typedef ansi_context_t context_t;
#endif
static void
cprintf_ansi_parse(const char * str, ansi_context_t * out) {
  out->input_size = 1;
  const char l = tolower(str[0]);
  if (l == 'f' || l == 'b') {
    out->input_size = 2;
    unsigned char i = 0;
    while (i < 8) {
      if (ansi_order[i] == tolower(str[1])) {
        strcpy(out->ansi + out->ansi_len, "\x1b[");
        strcpy(out->ansi + out->ansi_len + 4, "m");
        out->ansi[out->ansi_len + 2] = '3' + (l == 'f');
        out->ansi[out->ansi_len + 3] = '0' + i;
        out->ansi_len += 5;
        if (l != str[0]) {
          strcpy(out->ansi + out->ansi_len - 1, ";1m");
          out->ansi_len += 2;
        }
        break;
      }
      i++;
    }
  } else if (l == 'i') {
    strcpy(out->ansi + out->ansi_len, "\x1b[7m");
    out->ansi_len += 4;
  }
  if (l == 'u') {
    strcpy(out->ansi + out->ansi_len, "\x1b[4m");
    out->ansi_len += 4;
  }
}
#ifndef _WIN32
#  define cprintf_parse cprintf_ansi_parse
#else
static void
cprintf_parse(const char * str, context_t * out) {
  out->input_size = 1;
  const char l = tolower(str[0]);
  if (l == 'f' || l == 'b') {
    out->input_size = 2;
    unsigned char i = 0;
    while (i < 7) {
      if (colors[i].char_code == tolower(str[1])) {
        out->colored = 1;
        if (l == 'f') {
          out->attr |= colors[i].foreground;
        } else {
          out->attr |= colors[i].background;
        }
        if (l != str[0])
          out->attr |= l == 'b' ? BACKGROUND_INTENSITY : FOREGROUND_INTENSITY;
        break;
      }
      i++;
    }
  } else if (l == 'i') {
    out->attr = inverse_def_attr;
  }
  if (l == 'u') {
    out->attr |= COMMON_LVB_UNDERSCORE;
  }
}
#endif
#define STATUS_NULL   0
#define STATUS_ESCAPE 1
#define STATUS_FMT    2
CPRINTF_EXPORT size_t
cprintf_ansi(char * str, const size_t size, const char * fmt, ...) {
  ansi_context_t ctx;
  va_list vl;
  va_start(vl, fmt);
  unsigned char status = STATUS_NULL;
  size_t copied = 0;
  size_t i = 0;
  char * c_ptr;
  char c;
  while ((c = fmt[i]) != 0 && copied < size) {
    i++;
    if (c == '\\') {
      if (status == STATUS_NULL) {
        status = STATUS_ESCAPE;
      } else {
        putchar('\\');
        status = STATUS_NULL;
      }
      continue;
    } else if (c == '%') {
      if (status == STATUS_ESCAPE) {
        str[copied] = '%';
        copied++;
        status = STATUS_NULL;
      } else {
        status = STATUS_FMT;
      }
      continue;
    } else if (status == STATUS_NULL) {
      if (copied == size) {
        return copied;
      }
      str[copied] = c;
      copied++;
      continue;
    }
    memset(&ctx, 0, sizeof(ansi_context_t));
    if (c == '{') {
      while (1) {
        cprintf_ansi_parse(fmt + i, &ctx);
        i += ctx.input_size;
        if (fmt[i] != ',') {
          return 0;
        }
        i++;
      }
      i++;
    } else {
      i--;
      cprintf_ansi_parse(fmt + i, &ctx);
      i += ctx.input_size;
    }
    for (c_ptr = &ctx.ansi[0]; copied < size && *c_ptr; c_ptr++) {
      str[copied] = *c_ptr;
      copied++;
    }
    for (c_ptr = va_arg(vl, char *); copied < size && *c_ptr; c_ptr++) {
      str[copied] = *c_ptr;
      copied++;
    }
    for (c_ptr = "\x1b[0m"; copied < size && *c_ptr; c_ptr++) {
      str[copied] = *c_ptr;
      copied++;
    }
    status = STATUS_NULL;
  }
  str[copied] = 0;
  return copied;
}
CPRINTF_EXPORT void
cprintf(const char * fmt, ...) {
#ifdef _WIN32
  if (_cprintf_init() == 0) return;
#endif
  context_t ctx;
  va_list vl;
  va_start(vl, fmt);
  unsigned char status = STATUS_NULL;
  size_t i = 0;
  char c;
  while ((c = fmt[i]) != 0) {
    i++;
    if (c == '\\') {
      if (status == STATUS_NULL) {
        status = STATUS_ESCAPE;
      } else {
        putchar('\\');
        status = STATUS_NULL;
      }
      continue;
    } else if (c == '%') {
      if (status == STATUS_ESCAPE) {
        putchar('%');
        status = STATUS_NULL;
      } else {
        status = STATUS_FMT;
      }
      continue;
    } else if (status == STATUS_NULL) {
      putchar(c);
      continue;
    }
    memset(&ctx, 0, sizeof(context_t));
    if (c == '{') {
      while (1) {
        cprintf_parse(fmt + i, &ctx);
        i += ctx.input_size;
        if (fmt[i] != ',') {
          return;
        }
        i++;
      }
      i++;
#ifdef _WIN32
      if (!ctx.colored) {
        ctx.attr |= _def_attr;
      }
      SetConsoleTextAttribute(_cprintf_handle, ctx.attr);
      printf("%s", va_arg(vl, char *));
      SetConsoleTextAttribute(_cprintf_handle, _cprintf_def_attr);
#else
      printf("%s%s\x1b[0m", ctx.ansi, va_arg(vl, char *));
#endif
    } else {
      i--;
      cprintf_parse(fmt + i, &ctx);
#ifdef _WIN32
      if (!ctx.colored) {
        ctx.attr |= _def_attr;
      }
      SetConsoleTextAttribute(_cprintf_handle, ctx.attr);
      printf("%s", va_arg(vl, char *));
      SetConsoleTextAttribute(_cprintf_handle, _cprintf_def_attr);
#else
      printf("%s%s\x1b[0m", ctx.ansi, va_arg(vl, char *));
#endif
      i += ctx.input_size;
    }
    status = STATUS_NULL;
  }
  va_end(vl);
}
