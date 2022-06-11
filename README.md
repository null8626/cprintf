# cprintf

Include this:
```c
// uncomment this next line if you're not using the DLL
// #define CPRINTF_DLL

#include <cprintf.h>
```
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

# Supported specifiers
| Format name       | Description                              |
|-------------------|------------------------------------------|
| `%fk`             | Changes the text color to black.         |
| `%fr`             | Changes the text color to red.           |
| `%fg`             | Changes the text color to green.         |
| `%fy`             | Changes the text color to yellow.        |
| `%fb`             | Changes the text color to blue.          |
| `%fm`             | Changes the text color to magenta.       |
| `%fc`             | Changes the text color to cyan.          |
| `%fw`             | Changes the text color to white.         |
| `%bk`             | Changes the background color to black.   |
| `%br`             | Changes the background color to red.     |
| `%bg`             | Changes the background color to green.   |
| `%by`             | Changes the background color to yellow.  |
| `%bb`             | Changes the background color to blue.    |
| `%bm`             | Changes the background color to magenta. |
| `%bc`             | Changes the background color to cyan.    |
| `%bw`             | Changes the background color to white.   |
| `%i`              | Inverts the background and text color.   |
| `%u`              | Adds an underline.                       

## Bold

You can make a text bold or background color brighter by capitalizing the format specifier. Example: `%FR`, `%BB`

# Combining formats
You can combine multiple formats too, with `%{...}`. Example:
- `%{fr,u}` combines `%fr` (red text) and `%u` (underline/underscore).

Invalid format specifier(s) will cause undefined behaviour.
Repeated combinations, or more than 3 combinations will cause undefined behaviour in POSIX builds.

# Download

Prebuilt (64-bit) binaries are available.

- [Windows](https://github.com/null8626/cprintf/releases/download/v1.1.0/cprintf-windows.zip)
- [macOS](https://github.com/null8626/cprintf/releases/download/v1.1.0/cprintf-macos.zip)
- [Linux](https://github.com/null8626/cprintf/releases/download/v1.1.0/cprintf-linux.zip)

# Building with CMake

To create the build files:

```console
cmake -B build .
cmake build
```

And then:

- For POSIX:

```console
cd build
make
```

- For Windows:

```console
msbuild build/cprintf.sln -noLogo -p:Configuration=Release
```

And the library files should be there in the `build/Release` directory.
