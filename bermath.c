#include "bermath.h"

static inline uint32_t sign_extend(int32_t x) {
  union {
      // let us suppose long is twice as wide as int
      int64_t w;

      // should be hi,lo on a big endian machine
      struct {
#if defined(__BYTE_ORDER__) && __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
          int32_t lo, hi;
#elif defined(__BYTE_ORDER__) && __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
          int32_t hi, lo;
#else
#error "Endianess problem"
#endif
      };
  } z = { .w = x };

  return (uint32_t)z.hi;
}

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

inline int branchless_abs(int n) {
  // Works because for negative numbers left-shift fills with ones
  return (n ^ (n >> 31)) - (n >> 31);
}

inline int mod_2n(int m, int exp) {
  return m & ((1 << exp) - 1);
}

static inline void invalid_generic(const char* str) {
  fprintf(stderr, str);
  abort();
}

inline int branchless_mod(int n, int m) {
  int r = n - (n / m) * m;  // Compute remainder
  return r + (r < 0) * m;   // Add m if remainder is negative
}

inline int popcount64(uint64_t n) {
#if defined(__GNUC__)
  return __builtin_popcountll(n);
#elif defined(_MSC_Ver)
  return __popcnt64(n);
#elif defined(_DO_NOT_DEFINE)
  n = n - ((n >> 1) & 0x5555555555555555);
  // This essentially stores the evenly indexed bits in the right position and substracts them from n.
  // This makes every two bit pair store the number of ones in that bit pair, which can be at most 2 with storage space for 4.
  n = (n & 0x3333333333333333) + ((n >> 2) & 0x3333333333333333);
  // This line essentially adds the two-bit pairs to form four-bit groups that contain the sum of their original bits
  n = (n + (n >> 4)) & 0x0F0F0F0F0F0F0F0F;
  // Same but for a group of 8 bits. You want to mask to avoid counting outside the summed bitsets
  n = (n * 0x0101010101010101) >> 56;
  // Here we unroll all the 8-bit sets and add them together in the most significant 8 bits. Then we lower them to the least significant 8
  // bits.
  return n;
#else
  n = n - ((n >> 1) & 0x5555555555555555);
  n = (n & 0x3333333333333333) + ((n >> 2) & 0x3333333333333333);
  return (((n + (n >> 4)) & 0x0F0F0F0F0F0F0F0F) * 0x0101010101010101) >> 56;
#endif
}

inline int popcount32(uint32_t n) {
#if defined(__GNUC__)
  return __builtin_popcount(n);
#elif defined(_MSC_Ver)
  return __popcnt32(n);
#elif defined(_DO_NOT_DEFINE)
  n = n - ((n >> 1) & 0x55555555);
  // This essentially stores the evenly indexed bits in the right position and substracts them from n.
  // This makes every two bit pair store the number of ones in that bit pair, which can be at most 2 with storage space for 4.
  n = (n & 0x33333333) + ((n >> 2) & 0x33333333);
  // This line essentially adds the two-bit pairs to form four-bit groups that contain the sum of their original bits
  n = (n + (n >> 4)) & 0x0F0F0F0F;
  // Same but for a group of 8 bits. You want to mask to avoid counting outside the summed bitsets
  n = (n * 0x01010101) >> 24;
  // Here we unroll all the 8-bit sets and add them together in the most significant 8 bits. Then we lower them to the least significant 8
  // bits.
  return n;
#else
  n = n - ((n >> 1) & 0x55555555);
  n = (n & 0x33333333) + ((n >> 2) & 0x33333333);
  return (((n + (n >> 4)) & 0x0F0F0F0F) * 0x01010101) >> 24;
  // Here we unroll all the 8-bit sets and add them together in the most significant 8 bits. Then we lower them to the least significant 8
  // bits.
#endif
}

inline int next_power_2(int n) {
  n--;
  n |= n >> 1;
  n |= n >> 2;
  n |= n >> 4;
  n |= n >> 8;
  n |= n >> 16;
  return n + 1;
}

inline int prev_power_2(int n) {
  n |= n >> 1;
  n |= n >> 2;
  n |= n >> 4;
  n |= n >> 8;
  n |= n >> 16;
  return n - (n >> 1);
}

inline int is_power_2(int n) {
  return (n & (n - 1)) == 0;
}
