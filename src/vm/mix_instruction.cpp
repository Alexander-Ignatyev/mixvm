#include "mix_instruction.h"

#include <sstream>

namespace mix {

short Instruction::get_address() const {
  return word.get_address();
}

Instruction::Instruction(const Word &word) : word{word} {
}

byte Instruction::get_operation_code() const {
  return word.bytes[byte_c];
}

FieldSpecification Instruction::get_field_specification() const {
  return FieldSpecification::decode(word.bytes[byte_f]);
}

byte Instruction::get_modification() const {
  return word.bytes[byte_f];
}

byte Instruction::get_specification() const {
  return word.bytes[byte_i];
}

void Instruction::print_instruction(std::ostream &os, const char *command_name) const {
  os << command_name << "\t" << (unsigned)get_address() << "," << (unsigned)word.bytes[byte_i];
  FieldSpecification fmt = FieldSpecification::decode(word.bytes[byte_f]);
  os << "(" << (int)fmt.low << ":" << (int)fmt.high << ")";
}

} // namespace mix
