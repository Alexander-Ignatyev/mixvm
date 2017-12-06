#include "machine_fixture.h"

#include <vm/mix_field_specification.h>

namespace mix {
class MachineLoadsTestSuite : public MachineFixture {
protected:
  int build_positive_value(byte a1, byte a2, byte i, byte f, byte c) {
    return Word(Sign::Positive, a1, a2, i, f, c).get_value();
  }

  int build_negative_value(byte a1, byte a2, byte i, byte f, byte c) {
    return Word(Sign::Negative, a1, a2, i, f, c).get_value();
  }
};

TEST_F(MachineLoadsTestSuite, lda) {
  set_memory_value(152, -73);
  machine.lda(make_instruction(cmd_lda, 152));

  EXPECT_EQ(-73, get_reg_a_value());
}

TEST_F(MachineLoadsTestSuite, lda_0_3_bytes) {
  const int value = build_negative_value(1, 2, 3, 4, 5);
  const int expected_value = build_negative_value(0, 0, 1, 2, 3);
  set_memory_value(152, value);
  machine.lda(make_instruction(cmd_lda, 152, {0, 3}));

  EXPECT_EQ(expected_value, get_reg_a_value());
}

TEST_F(MachineLoadsTestSuite, lda_3_4_bytes) {
  const int value = build_negative_value(1, 2, 3, 4, 5);
  const int expected_value = build_positive_value(0, 0, 0, 3, 4);
  set_memory_value(152, value);
  machine.lda(make_instruction(cmd_lda, 152, {3, 4}));

  EXPECT_EQ(expected_value, get_reg_a_value());
}

TEST_F(MachineLoadsTestSuite, lda_with_index_specification) {
  set_memory_value(152, -73);
  set_memory_value(177, -173);
  set_reg_i_value(2, 25);
  auto instruction = Instruction(Word::make_as_instruction(cmd_lda, 152, 2));
  machine.lda(instruction);

  EXPECT_EQ(-173, get_reg_a_value());
}

TEST_F(MachineLoadsTestSuite, ld1_with_index_specification) {
  set_memory_value(152, 11);
  set_memory_value(100, 111);
  set_reg_i_value(2, -52);
  auto instruction = Instruction(Word::make_as_instruction(cmd_ld1, 152, 2));
  machine.ld1(instruction);

  EXPECT_EQ(111, get_reg_i_value(1));
}

TEST_F(MachineLoadsTestSuite, ld1) {
  set_memory_value(152, 11);
  machine.ld1(make_instruction(cmd_ld1, 152));

  EXPECT_EQ(11, get_reg_i_value(1));
}

TEST_F(MachineLoadsTestSuite, ld2) {
  set_memory_value(152, 12);
  machine.ld2(make_instruction(cmd_ld2, 152));

  EXPECT_EQ(12, get_reg_i_value(2));
}

TEST_F(MachineLoadsTestSuite, ld3) {
  set_memory_value(152, 13);
  machine.ld3(make_instruction(cmd_ld3, 152));

  EXPECT_EQ(13, get_reg_i_value(3));
}

TEST_F(MachineLoadsTestSuite, ld4) {
  set_memory_value(152, 14);
  machine.ld4(make_instruction(cmd_ld4, 152));

  EXPECT_EQ(14, get_reg_i_value(4));
}

TEST_F(MachineLoadsTestSuite, ld5) {
  set_memory_value(152, 15);
  machine.ld5(make_instruction(cmd_ld5, 152));

  EXPECT_EQ(15, get_reg_i_value(5));
}

TEST_F(MachineLoadsTestSuite, ld6) {
  set_memory_value(152, 16);
  machine.ld6(make_instruction(cmd_ld6, 152));

  EXPECT_EQ(16, get_reg_i_value(6));
}

TEST_F(MachineLoadsTestSuite, ldx) {
  set_memory_value(152, -18);
  machine.ldx(make_instruction(cmd_ldx, 152));

  EXPECT_EQ(-18, get_reg_x_value());
}

TEST_F(MachineLoadsTestSuite, ldx_1_3_bytes) {
  const int value = build_negative_value(1, 2, 3, 4, 5);
  const int expected_value = build_positive_value(0, 0, 1, 2, 3);
  set_memory_value(152, value);
  machine.ldx(make_instruction(cmd_ldx, 152, {1, 3}));

  EXPECT_EQ(expected_value, get_reg_x_value());
}

TEST_F(MachineLoadsTestSuite, ldan) {
  set_memory_value(152, -73);
  machine.ldan(make_instruction(cmd_ldan, 152));

  EXPECT_EQ(73, get_reg_a_value());
}

TEST_F(MachineLoadsTestSuite, ldan_0_3_bytes) {
  const int value = build_negative_value(1, 2, 3, 4, 5);
  const int expected_value = build_positive_value(0, 0, 1, 2, 3);
  set_memory_value(152, value);
  machine.ldan(make_instruction(cmd_ldan, 152, {0, 3}));

  EXPECT_EQ(expected_value, get_reg_a_value());
}

TEST_F(MachineLoadsTestSuite, ldan_3_4_bytes) {
  const int value = build_negative_value(1, 2, 3, 4, 5);
  const int expected_value = build_negative_value(0, 0, 0, 3, 4);
  set_memory_value(152, value);
  machine.ldan(make_instruction(cmd_ldan, 152, {3, 4}));

  EXPECT_EQ(expected_value, get_reg_a_value());
}

TEST_F(MachineLoadsTestSuite, ld1n) {
  set_memory_value(152, 11);
  machine.ld1n(make_instruction(cmd_ld1n, 152));

  EXPECT_EQ(-11, get_reg_i_value(1));
}

TEST_F(MachineLoadsTestSuite, ld2n) {
  set_memory_value(152, 12);
  machine.ld2n(make_instruction(cmd_ld2n, 152));

  EXPECT_EQ(-12, get_reg_i_value(2));
}

TEST_F(MachineLoadsTestSuite, ld3n) {
  set_memory_value(152, 13);
  machine.ld3n(make_instruction(cmd_ld3n, 152));

  EXPECT_EQ(-13, get_reg_i_value(3));
}

TEST_F(MachineLoadsTestSuite, ld4n) {
  set_memory_value(152, 14);
  machine.ld4n(make_instruction(cmd_ld4n, 152));

  EXPECT_EQ(-14, get_reg_i_value(4));
}

TEST_F(MachineLoadsTestSuite, ld5n) {
  set_memory_value(152, 15);
  machine.ld5n(make_instruction(cmd_ld5n, 152));

  EXPECT_EQ(-15, get_reg_i_value(5));
}

TEST_F(MachineLoadsTestSuite, ld6n) {
  set_memory_value(152, 16);
  machine.ld6n(make_instruction(cmd_ld6n, 152));

  EXPECT_EQ(-16, get_reg_i_value(6));
}

TEST_F(MachineLoadsTestSuite, ldxn) {
  set_memory_value(152, 18);
  machine.ldxn(make_instruction(cmd_ldxn, 152));

  EXPECT_EQ(-18, get_reg_x_value());
}

TEST_F(MachineLoadsTestSuite, ldxn_1_3_bytes) {
  const int value = build_negative_value(1, 2, 3, 4, 5);
  const int expected_value = build_negative_value(0, 0, 1, 2, 3);
  set_memory_value(152, value);
  machine.ldxn(make_instruction(cmd_ldxn, 152, {1, 3}));

  EXPECT_EQ(expected_value, get_reg_x_value());
}

} // namespace mix
