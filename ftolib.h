/*
MIT No Attribution

Copyright 2026 steampuker

Permission is hereby granted, free of charge, to any person obtaining a copy of this
software and associated documentation files (the "Software"), to deal in the Software
without restriction, including without limitation the rights to use, copy, modify,
merge, publish, distribute, sublicense, and/or sell copies of the Software, and to
permit persons to whom the Software is furnished to do so.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A
PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

#ifndef FTOLIB_H
#define FTOLIB_H

#include <stdio.h>

typedef struct {
    void (*print)(const char* format, ...);
    void (*print_to)(void* stream, const char* format, ...);
} FTOParameterCheck;

struct FTOPrintable {
    enum {FTO_PRINTABLE_INT, FTO_PRINTABLE_REAL, FTO_PRINTABLE_BOOL, FTO_PRINTABLE_CHAR, FTO_PRINTABLE_STRING} type;
    union {
        int as_int;
        double as_real;
        const char* as_str;
        _Bool as_bool;
        char as_char;
    } value;
};

struct FTOContext {
    FILE* stream;
    const char* format;
    size_t length;
};

#define FTO_TYPE_TO_ARG(x)  _Generic(x, \
                        int:   (struct FTOPrintable) {FTO_PRINTABLE_INT, {.as_int = _Generic(x, int: x, default: 0)}}, \
                        double: (struct FTOPrintable) {FTO_PRINTABLE_REAL, {.as_real = _Generic(x, double: x, default: 0)}}, \
                        _Bool: (struct FTOPrintable) {FTO_PRINTABLE_BOOL, {.as_bool = _Generic(x, _Bool: x, default: 0)}}, \
                        char:  (struct FTOPrintable) {FTO_PRINTABLE_CHAR, {.as_char = _Generic(x, char: x, default: 0)}}, \
                        char*: (struct FTOPrintable) {FTO_PRINTABLE_STRING, {.as_str = _Generic(x, char*: x, default: 0)}})

int fto_print_impl(const struct FTOContext* format, struct FTOPrintable args[], size_t arg_count);

#define FTO_PICK_18TH(a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15, a16, a17, a18, ...) a18
#define FTO_VA_COUNT(...) FTO_PICK_18TH(__VA_ARGS__, TOO_MANY_ARGS, 16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, _)

#define FTO_EXPAND(x) x

#define FTO_GET_1ST(...) FTO_GET_1ST_(__VA_ARGS__, _)
#define FTO_GET_1ST_(x, ...) x

#define FTO_GET_REST(x, ...) __VA_ARGS__

#define FTO_FOREACH(M, ...) FTO_FOREACH_(FTO_VA_COUNT(__VA_ARGS__), M, __VA_ARGS__)
#define FTO_FOREACH_(N, M, ...) FTO_FOREACH__(N, M, __VA_ARGS__)
#define FTO_FOREACH__(N, M, ...) FTO_FOREACH##N(M, __VA_ARGS__)

#define FTO_SELECT_ON_VA(A, B, ...) FTO_SELECT_ON_VA_(FTO_PICK_18TH(__VA_ARGS__, TOO_MANY_ARGS, MANY, MANY, MANY, MANY, MANY, MANY, MANY, MANY, MANY, MANY, MANY, MANY, MANY, MANY, MANY, ONE, _), A, B)
#define FTO_SELECT_ON_VA_(N, A, B) FTO_SELECT_ON_VA__(N, A, B)
#define FTO_SELECT_ON_VA__(N, A, B) FTO_SELECT_ON_##N(A, B)

#define FTO_SELECT_ON_ONE(A, B) A
#define FTO_SELECT_ON_MANY(A, B) B

#define FTO_FOREACH1(M, ...)  M (__VA_ARGS__)
#define FTO_FOREACH2(M, ...)  M (FTO_GET_1ST(__VA_ARGS__)), FTO_FOREACH1(M, FTO_GET_REST(__VA_ARGS__))
#define FTO_FOREACH3(M, ...)  M (FTO_GET_1ST(__VA_ARGS__)), FTO_FOREACH2(M, FTO_GET_REST(__VA_ARGS__))
#define FTO_FOREACH4(M, ...)  M (FTO_GET_1ST(__VA_ARGS__)), FTO_FOREACH3(M, FTO_GET_REST(__VA_ARGS__))
#define FTO_FOREACH5(M, ...)  M (FTO_GET_1ST(__VA_ARGS__)), FTO_FOREACH4(M, FTO_GET_REST(__VA_ARGS__))
#define FTO_FOREACH6(M, ...)  M (FTO_GET_1ST(__VA_ARGS__)), FTO_FOREACH5(M, FTO_GET_REST(__VA_ARGS__))
#define FTO_FOREACH7(M, ...)  M (FTO_GET_1ST(__VA_ARGS__)), FTO_FOREACH6(M, FTO_GET_REST(__VA_ARGS__))
#define FTO_FOREACH8(M, ...)  M (FTO_GET_1ST(__VA_ARGS__)), FTO_FOREACH7(M, FTO_GET_REST(__VA_ARGS__))
#define FTO_FOREACH9(M, ...)  M (FTO_GET_1ST(__VA_ARGS__)), FTO_FOREACH8(M, FTO_GET_REST(__VA_ARGS__))
#define FTO_FOREACH10(M, ...) M (FTO_GET_1ST(__VA_ARGS__)), FTO_FOREACH9(M, FTO_GET_REST(__VA_ARGS__))
#define FTO_FOREACH11(M, ...) M (FTO_GET_1ST(__VA_ARGS__)), FTO_FOREACH10(M, FTO_GET_REST(__VA_ARGS__))
#define FTO_FOREACH12(M, ...) M (FTO_GET_1ST(__VA_ARGS__)), FTO_FOREACH11(M, FTO_GET_REST(__VA_ARGS__))
#define FTO_FOREACH13(M, ...) M (FTO_GET_1ST(__VA_ARGS__)), FTO_FOREACH12(M, FTO_GET_REST(__VA_ARGS__))
#define FTO_FOREACH14(M, ...) M (FTO_GET_1ST(__VA_ARGS__)), FTO_FOREACH13(M, FTO_GET_REST(__VA_ARGS__))
#define FTO_FOREACH15(M, ...) M (FTO_GET_1ST(__VA_ARGS__)), FTO_FOREACH14(M, FTO_GET_REST(__VA_ARGS__))
#define FTO_FOREACH16(M, ...) M (FTO_GET_1ST(__VA_ARGS__)), FTO_FOREACH15(M, FTO_GET_REST(__VA_ARGS__))

#define FTO_PRINT_ONE_(out, fmt, ...) fto_print_impl(&(const struct FTOContext) {out, fmt, sizeof(fmt) - 1}, 0, 0)
#define FTO_PRINT_MANY_(out, fmt, ...) fto_print_impl(&(const struct FTOContext) {out, fmt, sizeof(fmt) - 1}, \
                                                       (struct FTOPrintable[FTO_VA_COUNT(__VA_ARGS__) - 1]) { FTO_FOREACH(FTO_TYPE_TO_ARG, FTO_GET_REST(__VA_ARGS__)) }, \
                                                       FTO_VA_COUNT(__VA_ARGS__) - 1)


#    define fto_print(...)           _Generic(0, \
                                      FTOParameterCheck: ((FTOParameterCheck){0}.print)(__VA_ARGS__), \
                                      default: FTO_SELECT_ON_VA(FTO_PRINT_ONE_, FTO_PRINT_MANY_, __VA_ARGS__)(stdout, FTO_GET_1ST(__VA_ARGS__), __VA_ARGS__))
#    define fto_println(...)         _Generic(0, \
                                      FTOParameterCheck: ((FTOParameterCheck){0}.print)(__VA_ARGS__), \
                                      default: FTO_SELECT_ON_VA(FTO_PRINT_ONE_, FTO_PRINT_MANY_, __VA_ARGS__)(stdout, FTO_GET_1ST(__VA_ARGS__) "\n", __VA_ARGS__))
#    define fto_print_to(out, ...)   _Generic(0, \
                                      FTOParameterCheck: ((FTOParameterCheck){0}.print_to)(out,__VA_ARGS__), \
                                      default: FTO_SELECT_ON_VA(FTO_PRINT_ONE_, FTO_PRINT_MANY_, __VA_ARGS__)(out, FTO_GET_1ST(__VA_ARGS__), __VA_ARGS__))
#    define fto_println_to(out, ...) _Generic(0, \
                                      FTOParameterCheck: ((FTOParameterCheck){0}.print_to)(out, __VA_ARGS__), \
                                      default: FTO_SELECT_ON_VA(FTO_PRINT_ONE_, FTO_PRINT_MANY_, __VA_ARGS__)(out, FTO_GET_1ST(__VA_ARGS__) "\n", __VA_ARGS__))
#ifdef FTO_NO_NAMESPACE
#    define print(...)               fto_print(__VA_ARGS__)
#    define println(...)             fto_println(__VA_ARGS__)
#    define print_to(out, ...)       fto_print_to(out, __VA_ARGS__)
#    define println_to(out, ...)     fto_println_to(out, __VA_ARGS__)
#endif

/* Implementation */

#ifdef FTO_IMPLEMENTATION
#include <string.h>
#include <stddef.h>

#define FTO_TEMP_STRING_SIZE 1024

static inline unsigned interpret_format(char buffer[], size_t leftover, struct FTOPrintable* arg) {
    int length;
    switch(arg->type) {
    case FTO_PRINTABLE_INT: {
            return snprintf(buffer, leftover, "%d", arg->value.as_int);
        }
    case FTO_PRINTABLE_REAL: {
            return snprintf(buffer, leftover, "%f", arg->value.as_real);
        }
    case FTO_PRINTABLE_BOOL: {
            const char* state = arg->value.as_bool ? "true" : "false";
            length = (arg->value.as_bool ? sizeof("true") : sizeof("false")) - 1;
            length = leftover < length ? leftover : length;
            memcpy(buffer, state, length);
            return length;
        }
    case FTO_PRINTABLE_CHAR:
            buffer[0] = arg->value.as_char; return 1;
    case FTO_PRINTABLE_STRING: {
            length = strlen(arg->value.as_str);
            length = leftover < length ? leftover : length;
            memcpy(buffer, arg->value.as_str, length);
            return length;
        }
    }
    return 0;
}

static inline ptrdiff_t memfind(const char* haystack, char needle, unsigned max_length) {
    char *found = memchr(haystack, needle, max_length);
    if(!found) return -1;
    return found - haystack;
}

static inline unsigned insufficient_format(char buffer[], size_t leftover) {
    static const char insufficient_arg[2] = "--";
    if(sizeof(insufficient_arg) < leftover) leftover = sizeof(insufficient_arg);

    memcpy(buffer, insufficient_arg, leftover);
    return leftover;
}

int fto_print_impl(const struct FTOContext* fstring, struct FTOPrintable args[], size_t arg_count) {
    int leftover = fstring->length, count = 0;
    unsigned current_arg = 0, offset = 0;

    while(leftover > 0) {
        int format_location = memfind(fstring->format + offset, '{', leftover);
        int closing = memfind(fstring->format + offset, '}', leftover);

        if((closing >= 0 && (unsigned)closing < (unsigned)format_location) &&
            fstring->format[offset + closing + 1] == '}') {
            count += fwrite(fstring->format + offset, sizeof(char), closing + 1, fstring->stream);
            leftover -= closing + 2;
            offset += closing + 2;
            continue;
        }

        if(format_location < 0)
            break;

        fwrite(fstring->format + offset, sizeof(char), format_location, fstring->stream);

        if(fstring->format[offset + format_location + 1] == '{') {
            fputc('{', fstring->stream);
            count += 1;
            leftover -= format_location + 2;
            offset += format_location + 2;
            continue;
        }

        if(closing < 0)
            closing = leftover;

        char temp[FTO_TEMP_STRING_SIZE];
        int cursor = 0;
        leftover -= closing + 1;
        offset += closing + 1;

        if(current_arg >= arg_count) {
            cursor = insufficient_format(temp, FTO_TEMP_STRING_SIZE);
            count += fwrite(temp, sizeof(char), cursor, fstring->stream);
        } else {
            cursor = interpret_format(temp, FTO_TEMP_STRING_SIZE, &args[current_arg]);
            current_arg += 1;
            count += fwrite(temp, sizeof(char), cursor, fstring->stream);
        }
    }

    if(leftover == fstring->length)
        return fwrite(fstring->format, sizeof(char), fstring->length, fstring->stream);
    else if(leftover > 0)
        fwrite(fstring->format + offset, sizeof(char), leftover, fstring->stream);

    return count;
}
#endif
#endif
