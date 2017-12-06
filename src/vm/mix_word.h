#ifndef MIX_WORD_H
#define MIX_WORD_H

#include "mix_byte.h"
#include "mix_field_specification.h"
#include "mix_generic_word.h"
#include "mix_sign.h"

#include <iosfwd>

namespace mix {
class Word : public GenericWord<5> {
public:
  static Word make_as_instruction(byte cmd, short addr = 0, byte i = 0,
                                  FieldSpecification f = FieldSpecification::DEFAULT);

  Word() = default;
  Word(Sign sign, byte a1, byte a2, byte i, byte f, byte c);

  short get_address() const;
  void set_address(short address);

  byte get_operation_code() const;
  FieldSpecification get_field_specification() const;
  byte get_modification() const;
  byte get_specification() const;

  void print_instruction(std::ostream &os, const char *command_name) const;

  friend struct LongValue;
};

Word make_cmd(byte cmd, short addr = 0, FieldSpecification f = FieldSpecification::DEFAULT);

} // namespace mix

#endif // MIX_WORD_H
