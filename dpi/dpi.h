
#ifndef DPI_H
#define DPI_H
 
#include <iostream>
#include <cstdio>
#include <cstdlib>

class wire; // forward declaration
#ifdef __cplusplus
extern "C" {
#endif
 

void finish();
 
#ifdef __cplusplus
}
#endif
 
#ifdef __cplusplus
inline void dpi_print_wire(char spec, const wire& w) {
    wire& non_const_w = const_cast<wire&>(w);
    char c = non_const_w.getVal();
    if (spec == 'b' || spec == 'c') {
        std::putchar(c);
    } else if (spec == 'd') {
        if (c == '0') std::printf("0");
        else if (c == '1') std::printf("1");
        else std::printf("%c", c);
    } else if (spec == 'h' || spec == 'x') {
        if (c == '0') std::printf("0");
        else if (c == '1') std::printf("1");
        else std::printf("%c", c);
    } else {
        std::putchar(c);
    }
}
inline void dpi_print_val(char spec, const wire& w) {
    dpi_print_wire(spec, w);
}

inline void dpi_print_val(char spec, const char* val) {
    std::printf("%s", val);
}

template <typename T>
inline void dpi_print_val(char spec, const T& val) {
    if (spec == 'd') std::printf("%d", (int)val);
    else if (spec == 'h' || spec == 'x') std::printf("%x", (int)val);
    else if (spec == 'b') std::printf("%d", (int)val);
    else if (spec == 'c') std::putchar((char)val);
    else std::cout << val;
}



// Base case: no arguments left
inline void display_internal(const char* fmt) {
    if (!fmt) return;
    while (*fmt) {
        std::putchar(*fmt++);
    }
}

// Recursive variadic template
template <typename T, typename... Args>
inline void display_internal(const char* fmt, const T& first, const Args&... rest) {
    if (!fmt) return;
    while (*fmt) {
        if (*fmt == '%' && *(fmt + 1) != '\0') {
            if (*(fmt + 1) == '%') {
                std::putchar('%');
                fmt += 2;
                continue;
            }
            char spec = *(fmt + 1);
            dpi_print_val(spec, first);
            display_internal(fmt + 2, rest...);
            return;
        }
        std::putchar(*fmt++);
    }
}

// Top-level display call matching SystemVerilog $display
template <typename... Args>
inline void display(const char* fmt, const Args&... args) {
    display_internal(fmt, args...);
    std::putchar('\n');
}

inline void display() {
    std::putchar('\n');
}
#endif

#endif // DPI_H
