/*
 *  mix_machine.h
 *  mixvm
 *
 *  Created by Alexander Ignatyev on 19.06.10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef MIX_MACHINE_H
#define MIX_MACHINE_H

#include "mix_word.h"
#include "mix_small_word.h"
#include "mix_printer.h"

namespace mix
{
	enum compare_enum
	{
		compare_less,
		compare_equal,
		compare_greater
	};
	
	enum commands_t
	{
		cmd_nop = 0,
		cmd_hlt = 5,
		cmd_lda = 8,
		cmd_ld1,
		cmd_ld2 = 10,
		cmd_ld3,
		cmd_ld4,
		cmd_ld5,
		cmd_ld6,
		cmd_ldx,
		cmd_ldan,
		cmd_ld1n,
		cmd_ld2n,
		cmd_ld3n,
		cmd_ld4n = 20,
		cmd_ld5n,
		cmd_ld6n,
		cmd_ldxn,
		cmd_sta,
		cmd_st1,
		cmd_st2,
		cmd_st3,
		cmd_st4,
		cmd_st5,
		cmd_st6 = 30,
		cmd_stx,
		cmd_stj,
		cmd_stz
		
	};
	
	typedef word big_register;
	typedef small_word small_register;
	
	struct Machine;
	typedef void (Machine::*do_statement)(const word &command);

	struct Machine
	{
		static const int SMALL_REGISTERS = 6;
		static const int MEMORY_WORDS = 4000;
		big_register reg_a;
		big_register reg_x;
		small_register reg_i[SMALL_REGISTERS];
		small_register reg_j;
		bool override;
		compare_enum compare_flag;
		bool halt;
		
		word memory[MEMORY_WORDS];
		
		Machine();
		void print_state(std::ostream &os);
		do_statement *get_statement(const word &data);
		void nothing(const word &data);	
		
		void nop(const word &data);	//0
		void hlt(const word &data);	//5
		
		void lda(const word &data);	//8
		void ld1(const word &data);	//9
		void ld2(const word &data);	//10
		void ld3(const word &data);	//11
		void ld4(const word &data);	//12
		void ld5(const word &data);	//13
		void ld6(const word &data);	//14
		void ldx(const word &data);	//15
		
		void ldan(const word &data);	//16
		void ld1n(const word &data);	//17
		void ld2n(const word &data);	//18
		void ld3n(const word &data);	//19
		void ld4n(const word &data);	//20
		void ld5n(const word &data);	//21
		void ld6n(const word &data);	//22
		void ldxn(const word &data);	//23
		void sta(const word &data);		//24
		void st1(const word &data);		//25
		void st2(const word &data);		//26
		void st3(const word &data);		//27
		void st4(const word &data);		//28
		void st5(const word &data);		//29
		void st6(const word &data);		//30
		void stx(const word &data);		//31
		void stj(const word &data);		//32
		void stz(const word &data);		//33
		
		void run(short initial_address);
	};
	
}

#endif //MIX_MACHINE_H
