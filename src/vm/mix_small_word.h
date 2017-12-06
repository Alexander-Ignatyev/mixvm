#ifndef MIX_SMALL_REGISTER_H
#define MIX_SMALL_REGISTER_H

#include "mix_byte.h"
#include "mix_field_specification.h"
#include "mix_generic_word.h"
#include "mix_sign.h"

#include <iosfwd>

namespace mix {
const int DATA_BYTES_IN_SMALL_REGISTER = 2;

class SmallWord : public GenericWord<2> {
public:
  bool inc();  // return true if overflowed
  void set_address(short addr);
};

} // namespace mix

#endif // MIX_SMALL_REGISTER_H
