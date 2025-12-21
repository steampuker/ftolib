#ifndef FTOLIB_H
#define FTOLIB_H

#include <stdio.h>

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
                        char*: (struct FTOPrintable) {FTO_PRINTABLE_STRING, .as_str = (const char*)(long)x})

void fto_print_impl(const struct FTOContext* format, struct FTOPrintable args[], size_t arg_count);

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
                                                       (struct FTOPrintable[FTO_VA_COUNT(__VA_ARGS__) - 1]) { FTO_FOREACH(TYPE_TO_ARG, FTO_GET_REST(__VA_ARGS__)) }, \
                                                       FTO_VA_COUNT(__VA_ARGS__) - 1)

#ifndef FTO_NO_NAMESPACE
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
#else
#    define print(...)               _Generic(0, \
                                      FTOParameterCheck: ((FTOParameterCheck){0}.print)(__VA_ARGS__), \
                                      default: FTO_SELECT_ON_VA(FTO_PRINT_ONE_, FTO_PRINT_MANY_, __VA_ARGS__)(stdout, FTO_GET_1ST(__VA_ARGS__), __VA_ARGS__))
#    define println(...)             _Generic(0, \
                                      FTOParameterCheck: ((FTOParameterCheck){0}.print)(__VA_ARGS__), \
                                      default: FTO_SELECT_ON_VA(FTO_PRINT_ONE_, FTO_PRINT_MANY_, __VA_ARGS__)(stdout, FTO_GET_1ST(__VA_ARGS__) "\n", __VA_ARGS__))
#    define print_to(out, ...)       _Generic(0, \
                                      FTOParameterCheck: ((FTOParameterCheck){0}.print_to)(out,__VA_ARGS__), \
                                      default: FTO_SELECT_ON_VA(FTO_PRINT_ONE_, FTO_PRINT_MANY_, __VA_ARGS__)(out, FTO_GET_1ST(__VA_ARGS__), __VA_ARGS__))
#    define println_to(out, ...)     _Generic(0, \
                                      FTOParameterCheck: ((FTOParameterCheck){0}.print_to)(out, __VA_ARGS__), \
                                      default: FTO_SELECT_ON_VA(FTO_PRINT_ONE_, FTO_PRINT_MANY_, __VA_ARGS__)(out, FTO_GET_1ST(__VA_ARGS__) "\n", __VA_ARGS__))
#endif
#endif
