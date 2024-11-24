#include "bermath.h"

// Define the mod function
static inline int mod_i(int n, int m) {
  int r = n % m;
  return (r < 0 ? r + m : r);
}
// Define the mod function
static inline int branchless_max(int n, int m) {
  return m ^ ((n ^ m) & -(n < m));
}
static inline int branchless_min(int n, int m) {
  return n ^ ((n ^ m) & -(n < m));
}

static inline void invalid_generic(const char* str) {
  fprintf(stderr, str);
  abort();
}

inline int popcount(int n) {
  return 0;
}