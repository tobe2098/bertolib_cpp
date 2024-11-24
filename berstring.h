#ifndef BERTOLIB_STRING_LIBRARY_HEADER_ONLY
#define BERTOLIB_STRING_LIBRARY_HEADER_ONLY
#ifdef STRING_IMPLEMENTATION
#define STRLEN_IMPLEMENTATION
#endif
typedef unsigned long long size_t;

#ifdef STRLEN_IMPLEMENTATION

#else
size_t strlen(const char* str);
#endif

#endif