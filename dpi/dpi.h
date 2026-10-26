
#ifndef DPI_H
#define DPI_H
 
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>

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
    if (spec == 'd') std::printf("%11d", (int)val);
    else if (spec == '0') std::printf("%d", (int)val);
    else if (spec == 'f') std::printf("%f", (double)val);    
    else if (spec == 'h' || spec == 'x') std::printf("%x", (int)val);
    else if (spec == 'b') std::printf("%d", (int)val);
    else if (spec == 'c') std::putchar((char)val);
    else std::cout << val;
}
template <size_t N>
inline void dpi_print_val(char spec, const wire (&w)[N]) {
    if (spec == 'b') {
        for (size_t i = 0; i < N; ++i) {
            std::putchar(const_cast<wire&>(w[N - 1 - i]).getVal());
        }
    } else if (spec == 'f') {
        unsigned long long num = 0;
        for (size_t i = 0; i < N && i < 64; ++i) {
            if (const_cast<wire&>(w[i]).getVal() == '1') num |= (1ULL << i);
        }
        double d_val = 0.0;
        std::memcpy(&d_val, &num, sizeof(d_val));
        std::printf("%f", d_val);
    } else if (spec == 'o') {
        bool has_x = false, has_z = false;
        for (size_t i = 0; i < N; ++i) {
            char c = const_cast<wire&>(w[i]).getVal();
            if (c == 'x' || c == 'X') has_x = true;
            else if (c == 'z' || c == 'Z') has_z = true;
        }
        if (has_x) { std::putchar('x'); return; }
        if (has_z) { std::putchar('z'); return; }
        unsigned long long num = 0;
        for (size_t i = 0; i < N && i < 64; ++i) {
            if (const_cast<wire&>(w[i]).getVal() == '1') num |= (1ULL << i);
        }
        std::printf("%llo", num);
    } else if (spec == 'd' || spec == '0') {
        bool has_x = false, has_z = false;
        for (size_t i = 0; i < N; ++i) {
            char c = const_cast<wire&>(w[i]).getVal();
            if (c == 'x' || c == 'X') has_x = true;
            else if (c == 'z' || c == 'Z') has_z = true;
        }
        int width = (spec == '0') ? 0 : 11;
        if (has_x || has_z) {
            char ch = has_x ? 'x' : 'z';
            if (width > 0) std::printf("%*c", width, ch);
            else std::putchar(ch);
            return;
        }
        unsigned long long num = 0;
        for (size_t i = 0; i < N && i < 64; ++i) {
            if (const_cast<wire&>(w[i]).getVal() == '1') num |= (1ULL << i);
        }
        if (width > 0) std::printf("%*llu", width, num);
        else std::printf("%llu", num);
    } else if (spec == 'h' || spec == 'x') {
        bool has_x = false, has_z = false;
        for (size_t i = 0; i < N; ++i) {
            char c = const_cast<wire&>(w[i]).getVal();
            if (c == 'x' || c == 'X') has_x = true;
            else if (c == 'z' || c == 'Z') has_z = true;
        }
        if (has_x || has_z) {
            char ch = has_x ? 'x' : 'z';
            int width = (N == 32) ? 8 : ((N == 16) ? 4 : 3);
            if (width > 0) std::printf("%*c", width, ch);
            else std::putchar(ch);
            return;
        }
        unsigned long long num = 0;
        for (size_t i = 0; i < N && i < 64; ++i) {
            if (const_cast<wire&>(w[i]).getVal() == '1') num |= (1ULL << i);
        }
        std::printf("%llx", num);
    } else {
        for (size_t i = 0; i < N; ++i) std::putchar(const_cast<wire&>(w[N - 1 - i]).getVal());
    }
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
            if (*(fmt + 1) == '0' && *(fmt + 2) == 'd') {
                dpi_print_val('0', first);
                display_internal(fmt + 3, rest...);
                return;
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
