# cprintf

Portable C/C++ Library for printing colored text on the terminal with the C formatting style.
```c
cprintf("Hello, %fg world!\n", "green text!!!");
```
Don't want for the library to mess up with your `%`? Use this:
```c
cprintf("Hello, \\%fg", "world!");
```
Want for the library to act like [`chalk`](https://www.npmjs.com/package/chalk)? Use this!
```c
char result[100];

if (cprintf_ansi(result, 100, "Hello, %fg", "world!") == 0) {
  // error handling here. 
  // not necessary if you don't use
  // combined format specifiers.
}
```

Want to manually set the colors (just like every other console color library)? Do this!

```c
// using `cprintf_scope` here ensures that cprintf is initiated.
cprintf_scope {
  // use `cprintf_out` for `char *`s,
  // use `cprintf_out_size` for `char *`s with a known size stored in a `size_t`.
  // use `cprintf_out_literal` for string literals.
  cprintf_out_literal("Hello, ");
  cprintf_color(CPRINTF_FG_GREEN CPRINTF_UNDERLINE);
  cprintf_out_literal("World!\n");
  cprintf_color(CPRINTF_RESET);
}
```

# Supported specifiers
| Format name                                          | Macro name                 | Description                              | Extra notes                                                                        |
|------------------------------------------------------|----------------------------|------------------------------------------|------------------------------------------------------------------------------------|
| `%fk`                                                | `CPRINTF_FG_BLACK`         | Changes the text color to black.         | -                                                                                  |
| `%fr`                                                | `CPRINTF_FG_RED`           | Changes the text color to red.           | -                                                                                  |
| `%fg`                                                | `CPRINTF_FG_GREEN`         | Changes the text color to green.         | -                                                                                  |
| `%fy`                                                | `CPRINTF_FG_YELLOW`        | Changes the text color to yellow.        | -                                                                                  |
| `%fb`                                                | `CPRINTF_FG_BLUE`          | Changes the text color to blue.          | -                                                                                  |
| `%fm`                                                | `CPRINTF_FG_MAGENTA`       | Changes the text color to magenta.       | -                                                                                  |
| `%fc`                                                | `CPRINTF_FG_CYAN`          | Changes the text color to cyan.          | -                                                                                  |
| `%fw`                                                | `CPRINTF_FG_WHITE`         | Changes the text color to white.         | -                                                                                  |
| `%bk`                                                | `CPRINTF_BG_BLACK`         | Changes the background color to black.   | -                                                                                  |
| `%br`                                                | `CPRINTF_BG_RED`           | Changes the background color to red.     | -                                                                                  |
| `%bg`                                                | `CPRINTF_BG_GREEN`         | Changes the background color to green.   | -                                                                                  |
| `%by`                                                | `CPRINTF_BG_YELLOW`        | Changes the background color to yellow.  | -                                                                                  |
| `%bb`                                                | `CPRINTF_BG_BLUE`          | Changes the background color to blue.    | -                                                                                  |
| `%bm`                                                | `CPRINTF_BG_MAGENTA`       | Changes the background color to magenta. | -                                                                                  |
| `%bc`                                                | `CPRINTF_BG_CYAN`          | Changes the background color to cyan.    | -                                                                                  |
| `%bw`                                                | `CPRINTF_BG_WHITE`         | Changes the background color to white.   | -                                                                                  |
| `%i`                                                 | `CPRINTF_INVERT`           | Inverts the background and text color.   | -                                                                                  |
| `%u`                                                 | `CPRINTF_UNDERSCORE`       | Adds an underline.                       | If you use the macro on Windows and no other __color__ specifiers are provided (e.g: only `CPRINTF_UNDERSCORE`), no visible text will appear. To circumvent this, use `CPRINTF_UNDERSCORE_ONLY`. |
| -                                                    | `CPRINTF_UNDERSCORE_ONLY`  | Adds an underline.                       | This is the alias for `CPRINTF_UNDERSCORE` in non-Windows systems.                 |
| [see here](https://github.com/null8626/cprintf#bold) | `CPRINTF_BOLD`             | Self-explanatory.                        | -                                                                                  |

# Bold
You can make a text bold or background color brighter by capitalizing the format specifier. Example:
- `%FR` will output a bold, red text.
- `%BB` will output a bright, blue background.

# Combining formats
You can combine multiple formats too, with `%{...}`. Example:
- `%{fr,u}` combines `%fr` (red text) and `%u` (underline/underscore).

Invalid format specifier(s) will cause undefined behaviour.
Repeated combinations, or more than 3 combinations will cause undefined behaviour in POSIX builds.

# Download

Prebuilt (64-bit) binaries are available.

- [Windows (MSVC)](https://github.com/null8626/cprintf/releases/download/v1.0.0/libcprintf-windows-msvc.zip)
- [Windows (MinGW)](https://github.com/null8626/cprintf/releases/download/v1.0.0/libcprintf-windows-mingw.zip)
- [macOS](https://github.com/null8626/cprintf/releases/download/v1.0.0/libcprintf-macos.zip)
- [Linux](https://github.com/null8626/cprintf/releases/download/v1.0.0/libcprintf-linux.zip)

# Building with CMake

To create the build files:

```console
cmake -B build .
cmake build
```

And then:

- For MSVC:

```console
msbuild build/cprintf.sln -noLogo -noConLog -p:Configuration=Release
```