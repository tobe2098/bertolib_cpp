#include "perstr.h"

size_t per_strlen(const char *ptr) {
  if (ptr == NULL) {
    return 0;
  }
  const char *i = ptr;
  while (*i != '\0') {
    ++i;
  }
  return i - ptr;
}