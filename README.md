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
    /* error handling here. 
       not necessary if you don't use
       combined format specifiers. */
}
```

# Table of formats
| Format name | Description                              | Extra notes                                                                        |
|-------------|------------------------------------------|------------------------------------------------------------------------------------|
| `%fk`       | Changes the text color to black.         | Windows builds does not support this format.                                       |
| `%fr`       | Changes the text color to red.           | -                                                                                  |
| `%fg`       | Changes the text color to green.         | -                                                                                  |
| `%fy`       | Changes the text color to yellow.        | -                                                                                  |
| `%fb`       | Changes the text color to blue.          | -                                                                                  |
| `%fm`       | Changes the text color to magenta.       | -                                                                                  |
| `%fc`       | Changes the text color to cyan.          | -                                                                                  |
| `%fw`       | Changes the text color to white.         | -                                                                                  |
| `%bk`       | Changes the background color to black.   | Windows builds does not support this format.                                       |
| `%br`       | Changes the background color to red.     | -                                                                                  |
| `%bg`       | Changes the background color to green.   | -                                                                                  |
| `%by`       | Changes the background color to yellow.  | -                                                                                  |
| `%bb`       | Changes the background color to blue.    | -                                                                                  |
| `%bm`       | Changes the background color to magenta. | -                                                                                  |
| `%bc`       | Changes the background color to cyan.    | -                                                                                  |
| `%bw`       | Changes the background color to white.   | -                                                                                  |
| `%i`        | Inverts the background and text color.   | -                                          |
| `%u`        | Adds an underline.                       | In windows, if no color is provided (e.g: only `%u`), no visible text will appear. |

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

- [Windows (MSVC)](https://github.com/vierofernando/cprintf/releases/download/v1.0.0/libcprintf-windows-msvc.zip)
- [Windows (MinGW)](https://github.com/vierofernando/cprintf/releases/download/v1.0.0/libcprintf-windows-mingw.zip)
- [macOS](https://github.com/vierofernando/cprintf/releases/download/v1.0.0/libcprintf-macos.zip)
- [Linux](https://github.com/vierofernando/cprintf/releases/download/v1.0.0/libcprintf-linux.zip)

# Building locally

- Linux
```
make [...]
```
- macOS
```
make -f Macfile [...]
```
- Windows (GCC)
```
make WIN=yes [...]
```
- Windows (MSVC)
```
nmake /nologo /f VSMakefile [...]
```
- Windows (Clang)
```
nmake /nologo /f VSClangMakefile [...]
```

#### Additional optional arguments

| Format name | Description | Possible values |
|----|----|----|
| `CC` | The compiler used. `VSMakefile` and `VSClangMakefile` ignores this. | `gcc` (default), `clang` |
| `SHARED` | Whether to produce a shared/dynamic library. | `no` (default), `yes` |
