#ifndef BERTO_LIB_MATH_LIBRARY_HEADER_ONLY
#define BERTO_LIB_MATH_LIBRARY_HEADER_ONLY

#ifdef __cplusplus
extern "C" {
#endif

// Declare the mod_hybrid function for C linkage
static inline int mod_hybrid(int n, int m);

#ifdef __cplusplus
}
#endif

// Define the mod_hybrid function
static inline int mod_hybrid(int n, int m) {
  int r = n % m;
  return (r < 0 ? r + m : r);
}

#endif  // MYLIB_H
