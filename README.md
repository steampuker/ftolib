# ftolib - Formatted Text Output Library
## NOTE: The library is in very early state and is not ready for production use, even its name might change. Be careful when using it.

A proof-of-concept set of print macros that support Python-style formatting.

Automatically infers argument types (for now, only `int`, `_Bool`/`bool`, `char` and `char*` are supported).

## Usage

Include the `ftolib.h` and `ftolib.c` files in your project and compile them with a C11 compiler.

The API consists of 4 macros:
 - `fto_print(format_string, args...)` - formats `format_string` replacing `"{}"` with `args` and prints it to the standard output.
 - `fto_println(format_string, args...)` - same as print but appends a newline.
 - `fto_print_to(out, format_string, args...)` - same as `print` but instead outputs it to the `out` file stream.
 - `fto_println_to(out, format_string, args...)` - same as `println` but instead outputs it to the `out` file stream.

Defining `FTO_NO_NAMESPACE` before including the library header strips the `fto_` prefix from the macros above.

## Example

``` c
#include <stdbool.h>
#include "ftolib.h"

int main(void) {
    /* Printing without a newline */
    fto_print("Here are a few examples: ");

    /* Appending to the previous one and printing with a newline */
    /* bool and char need a cast, since C uses int by default */
    fto_println("int: {}, bool: {}, char: {}, string: {}", 21, (bool)(0), (char)('a'), "bazinga");

    /* Printing an error with println_to */
    fto_println_to(stderr, "Error: Bad coding style - {}", (bool)(1));
}
```

Output:
```
Here are a few examples: int: 21, bool: false, char: a, string: bazinga
Error: Bad coding style - true
```
## Limitations

For every macro, only 16 arguments are supported

This is still experimental, most of the features (positional arguments, additional formatting, float-to-string conversion, etc.) are missing.

It is also not optimized for performance (uses standard print functions instead of OS syscalls).

Still, I'd appreciate if you [open an issue](https://github.com/steampuker/print.c/issues).

## Related

This library takes inspiration from [fmt](https://github.com/fmtlib/fmt), Rust's [print!](https://doc.rust-lang.org/std/macro.print.html) and Python's [format strings]("https://docs.python.org/3/library/string.html#format-string-syntax").

## License

ftolib is dual-license under The Unlicense or MIT-0. See [LICENSE](https://github.com/steampuker/ftolib/blob/main/LICENSE) for details
