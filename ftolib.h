#ifndef FTOLIB_H
#define FTOLIB_H

#include <stdio.h>
#define FTO_VA_COUNT_(_, _18, _17, _16, _15, _14, _13, _12, _11, _10, _9, _8, _7, _6, _5, _4, _3, _2, _1, N, ...) N
#define FTO_VA_COUNT(...) FTO_VA_COUNT_(__VA_ARGS__, TOO_MANY_ARGS, 17, 16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0, 0)

#define FTO_EXPAND(x) x

#define FTO_GET_1ST(x, ...) (x)
#define FTO_GET_REST(x, ...) (__VA_ARGS__)

#define FTO_UNPAREN_1ST(x, ...) x
#define FTO_UNPAREN_REST(x, ...) __VA_ARGS__

#define FTO_FOREACH(M, ...)    FTO_FOREACH_(FTO_VA_COUNT(__VA_ARGS__), FTO_EXPAND(M), FTO_GET_REST(__VA_ARGS__))
#define FTO_FOREACH_(N, M, LIST)    FTO_FOREACH__(N, M, LIST)
#define FTO_FOREACH__(N, M, LIST)   FTO_FOREACH##N(M, LIST)

#define FTO_FOREACH0(M, LIST)
#define FTO_FOREACH1(M, LIST)   M LIST
#define FTO_FOREACH2(M, LIST)   FTO_EXPAND(M FTO_GET_1ST LIST), FTO_FOREACH1(M, FTO_GET_REST LIST)
#define FTO_FOREACH3(M, LIST)   FTO_EXPAND(M FTO_GET_1ST LIST), FTO_FOREACH2(M, FTO_GET_REST LIST)
#define FTO_FOREACH4(M, LIST)   FTO_EXPAND(M FTO_GET_1ST LIST), FTO_FOREACH3(M, FTO_GET_REST LIST)
#define FTO_FOREACH5(M, LIST)   FTO_EXPAND(M FTO_GET_1ST LIST), FTO_FOREACH4(M, FTO_GET_REST LIST)
#define FTO_FOREACH6(M, LIST)   FTO_EXPAND(M FTO_GET_1ST LIST), FTO_FOREACH5(M, FTO_GET_REST LIST)
#define FTO_FOREACH7(M, LIST)   FTO_EXPAND(M FTO_GET_1ST LIST), FTO_FOREACH6(M, FTO_GET_REST LIST)
#define FTO_FOREACH8(M, LIST)   FTO_EXPAND(M FTO_GET_1ST LIST), FTO_FOREACH7(M, FTO_GET_REST LIST)
#define FTO_FOREACH9(M, LIST)   FTO_EXPAND(M FTO_GET_1ST LIST), FTO_FOREACH8(M, FTO_GET_REST LIST)
#define FTO_FOREACH10(M, LIST)   FTO_EXPAND(M FTO_GET_1ST LIST), FTO_FOREACH9(M, FTO_GET_REST LIST)
#define FTO_FOREACH11(M, LIST)   FTO_EXPAND(M FTO_GET_1ST LIST), FTO_FOREACH10(M, FTO_GET_REST LIST)
#define FTO_FOREACH12(M, LIST)   FTO_EXPAND(M FTO_GET_1ST LIST), FTO_FOREACH11(M, FTO_GET_REST LIST)
#define FTO_FOREACH13(M, LIST)   FTO_EXPAND(M FTO_GET_1ST LIST), FTO_FOREACH12(M, FTO_GET_REST LIST)
#define FTO_FOREACH14(M, LIST)   FTO_EXPAND(M FTO_GET_1ST LIST), FTO_FOREACH13(M, FTO_GET_REST LIST)
#define FTO_FOREACH15(M, LIST)   FTO_EXPAND(M FTO_GET_1ST LIST), FTO_FOREACH14(M, FTO_GET_REST LIST)
#define FTO_FOREACH16(M, LIST)   FTO_EXPAND(M FTO_GET_1ST LIST), FTO_FOREACH15(M, FTO_GET_REST LIST)
#define FTO_FOREACH17(M, LIST)   FTO_EXPAND(M FTO_GET_1ST LIST), FTO_FOREACH16(M, FTO_GET_REST LIST)

typedef struct {
    void (*print)(const char* format, ...);
    void (*print_to)(FILE* stream, const char* format, ...);
} FTOParameterCheck;

struct FTOPrintable {
    enum {FTO_PRINTABLE_INT, FTO_PRINTABLE_BOOL, FTO_PRINTABLE_CHAR, FTO_PRINTABLE_STRING} type;
    union {
        int as_int;
        const char* as_str;
        _Bool as_bool;
        char as_char;
    };
};

struct FTOContext {
    FILE* stream;
    const char* format;
    size_t length;
};


#define TYPE_TO_ARG(x)  _Generic(x, \
                        int:   (struct FTOPrintable) {FTO_PRINTABLE_INT, .as_int = (int)(long)x}, \
                        _Bool: (struct FTOPrintable) {FTO_PRINTABLE_BOOL, .as_bool = !!x}, \
                        char:  (struct FTOPrintable) {FTO_PRINTABLE_CHAR, .as_char = (char)(long)x}, \
                        char*: (struct FTOPrintable) {FTO_PRINTABLE_STRING, .as_str = (const char*)(long long)x})

void fto_print_impl(const struct FTOContext* format, struct FTOPrintable args[], size_t arg_count);

#define FTO_PRINT_(...)    (_Generic(0, FTOParameterCheck: ((FTOParameterCheck){0}.print)(__VA_ARGS__), default: (void)0), \
                           fto_print_impl(&(struct FTOContext){stdout, FTO_UNPAREN_1ST(__VA_ARGS__, 0), sizeof FTO_GET_1ST(__VA_ARGS__, 0) - 1}, \
                                          _Generic(&(char[FTO_VA_COUNT(__VA_ARGS__) + 1]){0}, \
                                                     char(*)[1]: 0, \
                                                     default: (struct FTOPrintable[FTO_VA_COUNT(__VA_ARGS__) + 1]){FTO_FOREACH(TYPE_TO_ARG, FTO_UNPAREN_REST(__VA_ARGS__, 0))}), \
                                          FTO_VA_COUNT(__VA_ARGS__)))

#define FTO_PRINTLN_(...) FTO_PRINT_(FTO_UNPAREN_1ST(__VA_ARGS__, 0)"\n", __VA_ARGS__)

#define FTO_PRINT_TO_(out, ...) (_Generic(0, FTOParameterCheck: ((FTOParameterCheck){0}.print_to)(out, __VA_ARGS__), default: (void)0), \
                                fto_print_impl(&(struct FTOContext){out, FTO_UNPAREN_1ST(__VA_ARGS__, 0), sizeof FTO_GET_1ST(__VA_ARGS__, 0) - 1}, \
                                               _Generic(&(char[FTO_VA_COUNT(__VA_ARGS__) + 1]){0}, \
                                                          char(*)[1]: 0, \
                                                          default: (struct FTOPrintable[FTO_VA_COUNT(__VA_ARGS__) + 1]){FTO_FOREACH(TYPE_TO_ARG, FTO_UNPAREN_REST(__VA_ARGS__, 0))}), \
                                               FTO_VA_COUNT(__VA_ARGS__)))

#define FTO_PRINTLN_TO_(out, ...) FTO_PRINT_TO_(out, FTO_UNPAREN_1ST(__VA_ARGS__, 0)"\n", __VA_ARGS__)

#ifndef FTO_NO_NAMESPACE
#   define fto_print(...) FTO_PRINT_(__VA_ARGS__)
#   define fto_println(...) FTO_PRINTLN_(__VA_ARGS__)
#   define fto_print_to(...) FTO_PRINT_TO_(__VA_ARGS__)
#   define fto_println_to(...) FTO_PRINTLN_TO_(__VA_ARGS__)
#else
#   define print(...) FTO_PRINT_(__VA_ARGS__)
#   define println(...) FTO_PRINTLN_(__VA_ARGS__)
#   define print_to(...) FTO_PRINT_TO_(__VA_ARGS__)
#   define println_to(...) FTO_PRINTLN_TO_(__VA_ARGS__)
#endif

#endif
