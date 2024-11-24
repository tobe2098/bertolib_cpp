#if defined(__linux__) || defined(__APPLE__)
#include <endian.h>
#define MY_BYTE_ORDER    __BYTE_ORDER
#define MY_LITTLE_ENDIAN __LITTLE_ENDIAN
#define MY_BIG_ENDIAN    __BIG_ENDIAN
#elif defined(_WIN32)
#define MY_LITTLE_ENDIAN 1234
#define MY_BIG_ENDIAN    4321
#ifdef __GNUC__
#if defined(__i386__) || defined(__x86_64__) || defined(__amd64__)
#define MY_BYTE_ORDER MY_LITTLE_ENDIAN
#else
#define MY_BYTE_ORDER MY_BIG_ENDIAN
#endif
#else
#if defined(_M_IX86) || defined(_M_AMD64) || defined(_M_X64)
#define MY_BYTE_ORDER MY_LITTLE_ENDIAN
#else
#define MY_BYTE_ORDER MY_BIG_ENDIAN
#endif
#endif
#endif