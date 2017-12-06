#include "mix_small_word.h"

#include <sstream>

namespace mix {
bool SmallWord::inc() {
  bool isOverflowed = false;
  if (bytes[1] < VALUES_IN_BYTE - 1) {
    ++bytes[1];
  } else if (bytes[0] < VALUES_IN_BYTE - 1) {
    bytes[1] = 0;
    ++bytes[0];
  } else {
    isOverflowed = true;
    bytes[1] = 0;
    bytes[0] = 0;
  }
  return isOverflowed;
}

void SmallWord::set_address(short addr) {
  bytes[0] = addr / VALUES_IN_BYTE;
  bytes[1] = addr - bytes[0] * VALUES_IN_BYTE;
}

} // namespace mix
