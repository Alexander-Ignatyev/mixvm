#include <iostream>
#include <fstream>

#include "mix_printer.h"
#include "mix_machine.h"

void test_vm()
{
	using namespace mix;
	std::ofstream ofs_start("start.txt");
	std::ofstream ofs_result1("result1.txt");
	std::ofstream ofs_result2("result2.txt");
	Machine vm;
	
	vm.memory[0] = make_cmd(	cmd_lda, 52);
	vm.memory[1] = make_cmd(	cmd_ldx, 50, encode_format(0, 3));
	vm.memory[2] = make_cmd(	cmd_ld1, 51);
	vm.memory[3] = make_cmd(	cmd_ld2, 51);
	vm.memory[4] = make_cmd(	cmd_ld3, 51);
	vm.memory[5] = make_cmd(	cmd_ld4, 51);
	vm.memory[6] = make_cmd(	cmd_ld5, 51);
	vm.memory[7] = make_cmd(	cmd_ld6, 51);
	vm.memory[8] = make_cmd(	cmd_nop);
	vm.memory[9] = make_cmd(	cmd_sta, 100);
	vm.memory[10] = make_cmd(	cmd_sta, 101, encode_format(1, 5));
	vm.memory[11] = make_cmd(	cmd_sta, 102, encode_format(5, 5));
	vm.memory[12] = make_cmd(	cmd_sta, 103, encode_format(2, 2));
	vm.memory[13] = make_cmd(	cmd_sta, 104, encode_format(2, 3));
	vm.memory[14] = make_cmd(	cmd_sta, 105, encode_format(0, 1));
	vm.memory[15] = make_cmd(	cmd_stx, 106, encode_format(3, 4));
	vm.memory[16] = make_cmd(	cmd_stz, 107, encode_format(3, 4));
	vm.memory[17] = make_cmd(	cmd_st1, 108);
	vm.memory[18] = make_cmd(	cmd_st2, 109);
	vm.memory[19] = make_cmd(	cmd_st3, 110);
	vm.memory[20] = make_cmd(	cmd_st4, 111);
	vm.memory[21] = make_cmd(	cmd_st5, 112);
	vm.memory[22] = make_cmd(	cmd_st6, 113);
	vm.memory[23] = make_cmd(	cmd_stj, 114);
	vm.memory[24] = make_cmd(	cmd_sta, 199);
	vm.memory[25] = make_cmd(	cmd_lda, 200);
	vm.memory[26] = make_cmd(	cmd_sta, 201);
	vm.memory[27] = make_cmd(	cmd_lda, 201, encode_format(5, 5));
	vm.memory[28] = make_cmd(	cmd_add, 201, encode_format(4, 4));
	vm.memory[29] = make_cmd(	cmd_add, 201, encode_format(3, 3));
	vm.memory[30] = make_cmd(	cmd_add, 201, encode_format(2, 2));
	vm.memory[31] = make_cmd(	cmd_add, 201, encode_format(1, 1));
	vm.memory[32] = make_cmd(	cmd_sta, 202);
	vm.memory[33] = make_cmd(	cmd_lda, 210);
	vm.memory[34] = make_cmd(	cmd_sub, 211);
	vm.memory[35] = make_cmd(	cmd_sta, 212);
	vm.memory[36] = make_cmd(	cmd_lda, 199);
	
	vm.memory[37] = make_cmd(	cmd_hlt);
	
	vm.memory[50] = make_word(POS_SIGN, 8, 0, 3, 5, 4);
	vm.memory[51] = make_word(POS_SIGN, 0, 0, 0, 11, 11);
	vm.memory[52] = make_word(POS_SIGN, 6, 7, 8, 9, 0);
	vm.memory[100] = make_word(NEG_SIGN, 1, 2, 3, 4, 5);
	vm.memory[101] = make_word(NEG_SIGN, 1, 2, 3, 4, 5);
	vm.memory[102] = make_word(NEG_SIGN, 1, 2, 3, 4, 5);
	vm.memory[103] = make_word(NEG_SIGN, 1, 2, 3, 4, 5);
	vm.memory[104] = make_word(NEG_SIGN, 1, 2, 3, 4, 5);
	vm.memory[105] = make_word(NEG_SIGN, 1, 2, 3, 4, 5);
	vm.memory[106] = make_word(NEG_SIGN, 1, 1, 1, 1, 1);
	vm.memory[107] = make_word(NEG_SIGN, 1, 1, 1, 1, 1);
	vm.memory[108] = make_word(NEG_SIGN, 1, 1, 1, 1, 1);
	vm.memory[109] = make_word(NEG_SIGN, 1, 1, 1, 1, 1);
	vm.memory[110] = make_word(NEG_SIGN, 1, 1, 1, 1, 1);
	vm.memory[111] = make_word(NEG_SIGN, 1, 1, 1, 1, 1);
	vm.memory[112] = make_word(NEG_SIGN, 1, 1, 1, 1, 1);
	vm.memory[113] = make_word(NEG_SIGN, 1, 1, 1, 1, 1);
	vm.memory[114] = make_word(NEG_SIGN, 1, 1, 1, 1, 1);
	vm.memory[200] = make_word(POS_SIGN, 1, 2, 3, 4, 5);
	vm.memory[210] = make_word(POS_SIGN, 0, 0, 0, 0, 30);
	vm.memory[211] = make_word(POS_SIGN, 0, 0, 0, 0, 50);
	
	vm.print_state(ofs_start);
	
	vm.run(0);
	
	vm.memory[0] = make_cmd(	cmd_ldan, 50);
	vm.memory[1] = make_cmd(	cmd_ldxn, 50, encode_format(0, 3));
	vm.memory[2] = make_cmd(	cmd_ld1n, 51);
	vm.memory[3] = make_cmd(	cmd_ld2n, 51);
	vm.memory[4] = make_cmd(	cmd_ld3n, 51);
	vm.memory[5] = make_cmd(	cmd_ld4n, 51);
	vm.memory[6] = make_cmd(	cmd_ld5n, 51);
	vm.memory[7] = make_cmd(	cmd_ld6n, 51);
	vm.memory[8] = make_cmd(	cmd_nop);
	vm.memory[9] = make_cmd(	cmd_hlt);
	
	vm.print_state(ofs_result1);
	
	vm.run(0);
	
	vm.print_state(ofs_result2);
}

int main (int argc, char * const argv[]) {
	test_vm();
    return 0;
}
