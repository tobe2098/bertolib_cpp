#ifndef BERTO_LIB_MATH_LIBRARY_HEADER_ONLY
#define BERTO_LIB_MATH_LIBRARY_HEADER_ONLY
#include <stdio.h>
#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

// Declare the mod function for C linkage
static inline short              mod_s(short n, short m);
static inline unsigned short     mod_us(unsigned short n, unsigned short m);
static inline int                mod_i(int n, int m);
static inline unsigned int       mod_ui(unsigned int n, unsigned int m);
static inline long               mod_l(long n, long m);
static inline unsigned long      mod_ul(unsigned long n, unsigned long m);
static inline long long          mod_ll(long long n, long long m);
static inline unsigned long long mod_ull(unsigned long long n, unsigned long long m);

static inline float       mod_f(float n, float m);
static inline double      mod_d(double n, double m);
static inline long double mod_ld(long double n, long double m);

// Bitwise operations

static inline int popcount(int n);
static inline int clz(int n);
static inline int ctz(int n);
static inline int next_power_2(int n);
static inline int prev_power_2(int n);
static inline int is_power_2(int n);

static inline int branchless_max(int n, int m);
static inline int branchless_min(int n, int m);
static inline int branchless_abs(int n);

static inline int mask_allones(int n);
static inline int mask_rightNbits(int n);
static inline int mask_from_a_to_b(int n);

static inline void invalid_generic(const char* str);

#ifdef __cplusplus
}
#endif

#define mod(a, b)                          \
  _Generic((a),                            \
    short: mod_s((a), (b)),                \
    unsigned short: mod_us((a), (b)),      \
    int: mod_i((a), (b)),                  \
    unsigned int: mod_ui((a), (b)),        \
    long: mod_l((a), (b)),                 \
    unsigned long: mod_ul((a), (b)),       \
    long long: mod_ll((a), (b)),           \
    unsigned long long: mod_ull((a), (b)), \
    default: invalid_generic("There is no mod function for that combination of types."))

#endif  // MYLIB_H
