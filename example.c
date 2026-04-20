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
