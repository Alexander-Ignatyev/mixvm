#include "mix_word.h"

#include <sstream>

namespace mix {
enum bytes_format { byte_a1 = 0, byte_a2 = 1, byte_i = 2, byte_f = 3, byte_c = 4 };

Word::Word(Sign sign, byte a1, byte a2, byte i, byte f, byte c) {
  this->sign = sign;
  this->bytes[byte_a1] = a1;
  this->bytes[byte_a2] = a2;
  this->bytes[byte_i] = i;
  this->bytes[byte_f] = f;
  this->bytes[byte_c] = c;
}

Word Word::make_as_instruction(byte cmd, short addr, byte i, FieldSpecification f) {
  Word result;
  result.sign = Sign::Positive;
  result.set_address(addr);
  result.bytes[byte_i] = i;
  result.bytes[byte_f] = f.encode();
  result.bytes[byte_c] = cmd;
  return result;
}

short Word::get_address() const {
  short address = 0;
  address += bytes[byte_a1] * VALUES_IN_BYTE;
  address += bytes[byte_a2];
  if (sign == Sign::Negative) {
    address *= -1;
  }
  return address;
}

void Word::set_address(short address) {
  bytes[0] = address / VALUES_IN_BYTE;
  bytes[1] = address - bytes[0] * VALUES_IN_BYTE;
}

byte Word::get_operation_code() const {
  return bytes[byte_c];
}

FieldSpecification Word::get_field_specification() const {
  return FieldSpecification::decode(bytes[byte_f]);
}

byte Word::get_modification() const {
  return bytes[byte_f];
}

byte Word::get_specification() const {
  return bytes[byte_i];
}

void Word::print_instruction(std::ostream &os, const char *command_name) const {
  os << command_name << "\t" << (unsigned)get_address() << "," << (unsigned)bytes[byte_i];
  FieldSpecification fmt = FieldSpecification::decode(bytes[byte_f]);
  os << "(" << (int)fmt.low << ":" << (int)fmt.high << ")";
}

Word make_cmd(byte cmd, short addr, FieldSpecification f) {
  return Word::make_as_instruction(cmd, addr, 0, f);
}

} // namespace mix
