# ftolib - Formatted Text Output Library

This is a single header library that brings support for print formatting that is similar to std::print from C++23 using macros.
Designed to be lightweight and portable.

## Getting Started

Compile this with a compiler that supports C11.

``` c
#include <stdbool.h>

#define FTO_IMPLEMENTATION
#include "ftolib.h"

int main(void) {
    /* Printing without a newline */
    fto_print("Here are a few examples: ");

    /*
    |   Appending to the previous one and printing with a newline
    |   bool and char need a cast, since C uses int by default
    |   '{{' and '}}' will be converted to '{' and '}' respectively
    */
    fto_println("{{ int: {}, float: {}, bool: {}, char: '{}', string: {} }}", 21, 9.0 + 10.0, (bool)(1 == 0), (char)('a'), "bazinga");

    /* Printing an error with println_to */
    fto_println_to(stderr, "Error: Bad coding style - {}", (bool)(1));
}
```

Output:
```
Here are a few examples: { int: 21, float: 19.000000, bool: false, char: 'a', string: bazinga }
Error: Bad coding style - true
```

## Usage

This library is stb-style, meaning you have to #define FTO_IMPLEMENTATION once in your project before including the header.
Defining `FTO_NO_NAMESPACE` before including the library header strips the `fto_` prefix from the macros (and will keep the original prefixed ones).

The API consists of 4 macros:
 - `fto_print(format_string, args...)` - formats `format_string` replacing `"{}"` with `args` and prints it to the standard output.
 - `fto_println(format_string, args...)` - same as print but appends a newline to format_string.
 - `fto_print_to(out, format_string, args...)` - same as `print` but instead outputs it to the `out` file stream.
 - `fto_println_to(out, format_string, args...)` - same as `println` but instead outputs it to the `out` file stream.

The following types are supported:
 - `int`        - prints a decimal number.
 - `float`      - prints a real number with a precision matching the one in printf.
 - `_Bool/bool` - prints "true"/"false" depending on the value. Note that boolean expressions in C are converted to integers, so you will need a cast if printing those. Until C23, `true` and `false` were also of type int.
 - `char`       - prints a character. Character literals are also of type int, so be careful.
 - `char*`      - prints a NULL-terminated string.

## Limitations

Every macro has a formal limit of 16 arguments. Once you exceed this limit, you'll get a message containing the TOO_MANY_ARGUMENTS. If you keep exceeding, the error might disappear but the behavior will be unpredictable.

At least on gcc, the syntax errors have really long messages. Prefer to use Language Server Protocol.

This library, as it is now, only supports automatic type inference for format strings. In the future, more features will be added (positional arguments, format specifiers, etc).

The library doesn't have a way to handle format errors. This is because it is impossible to report compile errors in C and having a runtime crash is not a viable option. Always check your format strings and the arguments or you will have a weird output.

Much like with printf, you'll have to use string literals or char arrays for the format string. Never use char pointers for the format, since the macros calculate the string length using `sizeof`. This also means you can include null characters in the format.

Happy programming!

## Related

This library is mostly a port of C++23 std::print and the [fmt](https://github.com/fmtlib/fmt).

It also takes inspiration from Rust's [print!](https://doc.rust-lang.org/std/macro.print.html) and Python's [format strings]("https://docs.python.org/3/library/string.html#format-string-syntax").

## License

ftolib is licensed under the MIT No Attribution license, see the LICENSE file for details.
