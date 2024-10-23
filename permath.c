#include "permath.h"

int mod(int n, int m) {
  int r = n % m;
  // int r = n - (n / m) * m;
  // Ensure the result is always non-negative
  return (r < 0 ? r + m : r);
}