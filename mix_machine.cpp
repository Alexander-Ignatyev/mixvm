/*
 *  mix_machine.cpp
 *  mixvm
 *
 *  Created by Alexander Ignatyev on 19.06.10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#include "mix_machine.h"
#include <iostream>
#include <math.h>

namespace mix
{	
	Machine::Machine()
	{
		memset(this, 0, sizeof(Machine));
	}
	
	void Machine::print_state(std::ostream &os)
	{
		os << "Register A: ";
		print_word(os, reg_a);
		os << std::endl;
		os << "Register X: ";
		print_word(os, reg_x);
		os << std::endl;
		for (int i = 0; i < SMALL_REGISTERS; ++i)
		{
			os << "Register I" << (i+1) << ":";
			print_small_word(os, reg_i[i]);
			os << std::endl;
		}
		
		os << "Register J:";
		print_small_word(os, reg_j);
		os << std::endl;
		
		os << "Override: " << override << std::endl;
		os << "CompareFlag: " << compare_flag << std::endl;
		for (int i = 0; i < MEMORY_WORDS; ++i)
		{
			os << "Memory[" << (i) << "]:";
			print_word(os, memory[i]);
			os << std::endl;
		}
	}
	
	do_statement *Machine::get_statement(const word &data)
	{
		static do_statement statements[] = {
			&Machine::nop, //0 
			&Machine::add, 
			&Machine::sub, 
			&Machine::mul, 
			&Machine::div,
			&Machine::hlt,
			&Machine::nothing,
			&Machine::nothing,
			&Machine::lda,
			&Machine::ld1,
			&Machine::ld2,	//10
			&Machine::ld3, 
			&Machine::ld4, 
			&Machine::ld5, 
			&Machine::ld6,
			&Machine::ldx,
			&Machine::ldan,
			&Machine::ld1n,
			&Machine::ld2n,
			&Machine::ld3n,
			&Machine::ld4n,	//20
			&Machine::ld5n, 
			&Machine::ld6n, 
			&Machine::ldxn, 
			&Machine::sta,
			&Machine::st1,
			&Machine::st2,
			&Machine::st3,
			&Machine::st4,
			&Machine::st5,
			&Machine::st6,	//30
			&Machine::stx, 
			&Machine::stj, 
			&Machine::stz, 
			&Machine::nothing,
			&Machine::nothing,
			&Machine::nothing,
			&Machine::nothing,
			&Machine::nothing,
			&Machine::nothing,
			&Machine::nothing,	//40
			&Machine::nothing, 
			&Machine::nothing, 
			&Machine::nothing, 
			&Machine::nothing,
			&Machine::nothing,
			&Machine::nothing,
			&Machine::nothing,
			&Machine::ena,
			&Machine::en1,
			&Machine::en2,	//50
			&Machine::en3, 
			&Machine::en4, 
			&Machine::en5, 
			&Machine::en6,
			&Machine::enx,
			&Machine::nothing,
			&Machine::nothing,
			&Machine::nothing,
			&Machine::nothing,
			&Machine::nothing,	//60
			&Machine::nothing,
			&Machine::nothing,
			&Machine::nothing	//63
		};
		
		return &statements[data.bytes[byte_c]];
	}
	
	void Machine::nothing(const word &data)
	{
		std::cerr << "mix: do_nothing!!!\n";
	}
	
	void Machine::nop(const word &data)	//0
	{
		print_command(std::cout, data, "nop");
		std::cout << std::endl;
	}
	
	void Machine::add(const word &data)	//1
	{
		print_command(std::cout, data, "add");
		std::cout << std::endl;
		
		int addr = get_address(data);
		
		value_type val = get_value(memory[addr], data.bytes[byte_f]);
		val += get_value(reg_a);
		set_value(val, reg_a, override);
	}
	
	void Machine::sub(const word &data)	//2
	{
		print_command(std::cout, data, "sub");
		std::cout << std::endl;
		
		int addr = get_address(data);
		value_type val = get_value(memory[addr], data.bytes[byte_f]) * -1;
		val += get_value(reg_a);
		set_value(val, reg_a, override);
	}
	
	void Machine::mul(const word &data)	//3
	{
		print_command(std::cout, data, "mul");
		std::cout << std::endl;
		
		int addr = get_address(data);
		
		long_value_type val1 = get_value(reg_a);
		long_value_type val2 = get_value(memory[addr], data.bytes[byte_f]);
		long_value_type val = val1*val2;
		set_long_value(val, reg_a, reg_x, override);
	}
	
	void Machine::div(const word &data)	//4
	{
		print_command(std::cout, data, "div");
		std::cout << std::endl;
		
		int addr = get_address(data);
		
		value_type val_reg_a = get_value(reg_a);
		value_type val_mem = get_value(memory[addr], data.bytes[byte_f]);
		if (abs(val_reg_a) < abs(val_mem))
		{
			long_value_type val = get_long_value(reg_a, reg_x);
			long_value_type quotient = val/val_mem;
			value_type remainder = val - quotient*val_mem;
			set_value((value_type)remainder, reg_x, override);
			reg_x.sign = reg_a.sign;
			set_value((value_type)quotient, reg_a, override);
		}
		else 
		{
			override = true;
		}

		
	}
	
	void Machine::hlt(const word &data)	//5
	{
		print_command(std::cout, data, "hlt");
		std::cout << std::endl;
		halt = true;
	}
	
	
	void Machine::lda(const word &data)	//8
	{
		print_command(std::cout, data, "lda");
		std::cout << std::endl;
		int addr = get_address(data);
		memset(&reg_a, 0, sizeof(reg_a));
		set_value(memory[addr], data.bytes[byte_f], reg_a);
		format_range fmt = decode_format(data.bytes[byte_f]);
		int count = DATA_BYTES_IN_WORD - fmt.high;
		if (count > 0)
		{
			right_shift(reg_a, count);
		}
	}
	
	void Machine::ld1(const word &data)	//9
	{
		print_command(std::cout, data, "ld1");
		std::cout << std::endl;
		int addr = get_address(data);
		value_type val = get_value(memory[addr]);
		set_value(val, reg_i[0], override);
	}
	
	void Machine::ld2(const word &data)	//10
	{
		print_command(std::cout, data, "ld2");
		std::cout << std::endl;
		int addr = get_address(data);
		value_type val = get_value(memory[addr]);
		set_value(val, reg_i[1], override);
	}
	
	void Machine::ld3(const word &data)	//11
	{
		print_command(std::cout, data, "ld3");
		std::cout << std::endl;
		int addr = get_address(data);
		value_type val = get_value(memory[addr]);
		set_value(val, reg_i[2], override);
	}
	
	void Machine::ld4(const word &data)	//12
	{
		print_command(std::cout, data, "ld4");
		std::cout << std::endl;
		int addr = get_address(data);
		value_type val = get_value(memory[addr]);
		set_value(val, reg_i[3], override);
	}
	
	void Machine::ld5(const word &data)	//13
	{
		print_command(std::cout, data, "ld5");
		std::cout << std::endl;
		int addr = get_address(data);
		value_type val = get_value(memory[addr]);
		set_value(val, reg_i[4], override);
	}
	
	void Machine::ld6(const word &data)	//14
	{
		print_command(std::cout, data, "ld6");
		std::cout << std::endl;
		int addr = get_address(data);
		value_type val = get_value(memory[addr]);
		set_value(val, reg_i[5], override);
	}
	
	void Machine::ldx(const word &data)	//15
	{
		print_command(std::cout, data, "ldx");
		std::cout << std::endl;
		int addr = get_address(data);
		memset(&reg_x, 0, sizeof(reg_x));
		set_value(memory[addr], data.bytes[byte_f], reg_x);
		format_range fmt = decode_format(data.bytes[byte_f]);
		int count = DATA_BYTES_IN_WORD - fmt.high;
		if (count > 0)
		{
			right_shift(reg_x, count);
		}
	}
	
	void Machine::ldan(const word &data)	//16
	{
		print_command(std::cout, data, "ldan");
		std::cout << std::endl;
		int addr = get_address(data);
		memset(&reg_a, 0, sizeof(reg_a));
		set_value(memory[addr], data.bytes[byte_f], reg_a);
		format_range fmt = decode_format(data.bytes[byte_f]);
		int count = DATA_BYTES_IN_WORD - fmt.high;
		if (count > 0)
		{
			right_shift(reg_a, count);
		}
		reg_a.sign = !reg_a.sign;
	}
	
	void Machine::ld1n(const word &data)	//17
	{
		print_command(std::cout, data, "ld1n");
		std::cout << std::endl;
		int addr = get_address(data);
		value_type val = get_value(memory[addr]);
		set_value(val * -1, reg_i[0], override);
	}
	
	void Machine::ld2n(const word &data)	//18
	{
		print_command(std::cout, data, "ld2n");
		std::cout << std::endl;
		int addr = get_address(data);
		value_type val = get_value(memory[addr]);
		set_value(val * -1, reg_i[1], override);
	}
	
	void Machine::ld3n(const word &data)	//19
	{
		print_command(std::cout, data, "ld3n");
		std::cout << std::endl;
		int addr = get_address(data);
		value_type val = get_value(memory[addr]);
		set_value(val * -1, reg_i[2], override);
	}
	
	void Machine::ld4n(const word &data)	//20
	{
		print_command(std::cout, data, "ld4n");
		std::cout << std::endl;
		int addr = get_address(data);
		value_type val = get_value(memory[addr]);
		set_value(val * -1, reg_i[3], override);
	}
	
	void Machine::ld5n(const word &data)	//21
	{
		print_command(std::cout, data, "ld5n");
		std::cout << std::endl;
		int addr = get_address(data);
		value_type val = get_value(memory[addr]);
		set_value(val * -1, reg_i[4], override);
	}
	
	void Machine::ld6n(const word &data)	//22
	{
		print_command(std::cout, data, "ld6n");
		std::cout << std::endl;
		int addr = get_address(data);
		value_type val = get_value(memory[addr]);
		set_value(val * -1, reg_i[5], override);
	}
	
	void Machine::ldxn(const word &data)	//23
	{
		print_command(std::cout, data, "ldxn");
		std::cout << std::endl;
		int addr = get_address(data);
		memset(&reg_x, 0, sizeof(reg_x));
		set_value(memory[addr], data.bytes[byte_f], reg_x);
		format_range fmt = decode_format(data.bytes[byte_f]);
		int count = DATA_BYTES_IN_WORD - fmt.high;
		if (count > 0)
		{
			right_shift(reg_x, count);
		}
		reg_x.sign = !reg_x.sign;
	}
	
	void Machine::sta(const word &data) //24
	{
		print_command(std::cout, data, "sta");
		std::cout << std::endl;
		int addr = get_address(data);
		format_range fmt = decode_format(data.bytes[byte_f]);
		int count = DATA_BYTES_IN_WORD - fmt.high;
		big_register tmp_reg = reg_a;
		if (count > 0)
		{
			left_shift(tmp_reg, count);
		}
		
		set_value(tmp_reg, data.bytes[byte_f], memory[addr]);
	}
	
	void Machine::st1(const word &data) //25
	{
		print_command(std::cout, data, "st1");
		std::cout << std::endl;
		
		int addr = get_address(data);
		value_type val = get_value(reg_i[0]);
		set_value(val, memory[addr], override);
	}
	
	void Machine::st2(const word &data) //26
	{
		print_command(std::cout, data, "st2");
		std::cout << std::endl;
		
		int addr = get_address(data);
		value_type val = get_value(reg_i[1]);
		set_value(val, memory[addr], override);
	}
	
	void Machine::st3(const word &data) //27
	{
		print_command(std::cout, data, "st3");
		std::cout << std::endl;
		
		int addr = get_address(data);
		value_type val = get_value(reg_i[2]);
		set_value(val, memory[addr], override);
	}
	
	void Machine::st4(const word &data) //28
	{
		print_command(std::cout, data, "st4");
		std::cout << std::endl;
		
		int addr = get_address(data);
		value_type val = get_value(reg_i[3]);
		set_value(val, memory[addr], override);
	}
	
	void Machine::st5(const word &data) //29
	{
		print_command(std::cout, data, "st5");
		std::cout << std::endl;
		
		int addr = get_address(data);
		value_type val = get_value(reg_i[4]);
		set_value(val, memory[addr], override);
	}
	
	void Machine::st6(const word &data) //30
	{
		print_command(std::cout, data, "st6");
		std::cout << std::endl;
		
		int addr = get_address(data);
		value_type val = get_value(reg_i[5]);
		set_value(val, memory[addr], override);
	}
	
	void Machine::stx(const word &data) //31
	{
		print_command(std::cout, data, "stx");
		std::cout << std::endl;
		
		int addr = get_address(data);
		format_range fmt = decode_format(data.bytes[byte_f]);
		int count = DATA_BYTES_IN_WORD - fmt.high;
		big_register tmp_reg = reg_x;
		if (count > 0)
		{
			left_shift(tmp_reg, count);
		}
		
		set_value(tmp_reg, data.bytes[byte_f], memory[addr]);
	}
	
	void Machine::stj(const word &data) //32
	{
		print_command(std::cout, data, "stj");
		std::cout << std::endl;
		
		int addr = get_address(data);
		value_type val = get_value(reg_j);
		set_value(val, memory[addr], override);
	}
	
	void Machine::stz(const word &data) //33
	{
		print_command(std::cout, data, "stz");
		std::cout << std::endl;
		
		int addr = get_address(data);
		word zero;
		memset(&zero, 0, sizeof(zero));
		set_value(zero, data.bytes[byte_f], memory[addr]);
		
	}
	
	void Machine::ena(const word &data) //48
	{
		switch (data.bytes[byte_f])
		{
			case 2:
				enta(data);
				break;
			case 3:
				enna(data);
				break;
			default:
				nothing(data);
				break;
		};
	}
	
	void Machine::en1(const word &data) //49
	{
		switch (data.bytes[byte_f])
		{
			case 2:
				ent1(data);
				break;
			case 3:
				enn1(data);
				break;
			default:
				nothing(data);
				break;
		};
	}
	
	void Machine::en2(const word &data) //50
	{
		switch (data.bytes[byte_f])
		{
			case 2:
				ent2(data);
				break;
			case 3:
				enn2(data);
				break;
			default:
				nothing(data);
				break;
		};
	}
	
	void Machine::en3(const word &data) //51
	{
		switch (data.bytes[byte_f])
		{
			case 2:
				ent3(data);
				break;
			case 3:
				enn3(data);
				break;
			default:
				nothing(data);
				break;
		};
	}
	
	void Machine::en4(const word &data) //52
	{
		switch (data.bytes[byte_f])
		{
			case 2:
				ent4(data);
				break;
			case 3:
				enn4(data);
				break;
			default:
				nothing(data);
				break;
		};
	}
	
	void Machine::en5(const word &data) //53
	{
		switch (data.bytes[byte_f])
		{
			case 2:
				ent5(data);
				break;
			case 3:
				enn5(data);
				break;
			default:
				nothing(data);
				break;
		};
	}
	
	void Machine::en6(const word &data) //54
	{
		switch (data.bytes[byte_f])
		{
			case 2:
				ent6(data);
				break;
			case 3:
				enn6(data);
				break;
			default:
				nothing(data);
				break;
		};
	}
	
	void Machine::enx(const word &data) //55
	{
		switch (data.bytes[byte_f])
		{
			case 2:
				entx(data);
				break;
			case 3:
				ennx(data);
				break;
			default:
				nothing(data);
				break;
		};
	}
	
	void Machine::enta(const word &data) //48, 2
	{
		print_command(std::cout, data, "enta");
		std::cout << std::endl;
		
		value_type val = (value_type)get_address(data);
		set_value(val, reg_a, override);
	}
	
	void Machine::ent1(const word &data) //49, 2
	{
		print_command(std::cout, data, "ent1");
		std::cout << std::endl;
		
		value_type val = (value_type)get_address(data);
		set_value(val, reg_i[0], override);
	}
	
	void Machine::ent2(const word &data) //50, 2
	{
		print_command(std::cout, data, "ent2");
		std::cout << std::endl;
		
		value_type val = (value_type)get_address(data);
		set_value(val, reg_i[1], override);
	}
	
	void Machine::ent3(const word &data) //51, 2
	{
		print_command(std::cout, data, "ent3");
		std::cout << std::endl;
		
		value_type val = (value_type)get_address(data);
		set_value(val, reg_i[2], override);
	}
	
	void Machine::ent4(const word &data) //52, 2
	{
		print_command(std::cout, data, "ent4");
		std::cout << std::endl;
		
		value_type val = (value_type)get_address(data);
		set_value(val, reg_i[3], override);
	}
	
	void Machine::ent5(const word &data) //53, 2
	{
		print_command(std::cout, data, "ent5");
		std::cout << std::endl;
		
		value_type val = (value_type)get_address(data);
		set_value(val, reg_i[4], override);
	}
	
	void Machine::ent6(const word &data) //54, 2
	{
		print_command(std::cout, data, "ent6");
		std::cout << std::endl;
		
		value_type val = (value_type)get_address(data);
		set_value(val, reg_i[5], override);
	}
	
	void Machine::entx(const word &data) //55, 2
	{
		print_command(std::cout, data, "entx");
		std::cout << std::endl;
		
		value_type val = (value_type)get_address(data);
		set_value(val, reg_x, override);
	}
	
	void Machine::enna(const word &data) //48, 3
	{
		print_command(std::cout, data, "enna");
		std::cout << std::endl;
		
		value_type val = (value_type)get_address(data);
		set_value(val, reg_a, override);
		reg_a.sign = !reg_a.sign;
	}
	
	void Machine::enn1(const word &data) //49, 3
	{
		print_command(std::cout, data, "enn1");
		std::cout << std::endl;
		
		value_type val = (value_type)get_address(data);
		set_value(val, reg_i[0], override);
		reg_i[0].sign = !reg_i[0].sign;
	}
	
	void Machine::enn2(const word &data) //50, 3
	{
		print_command(std::cout, data, "enn2");
		std::cout << std::endl;
		
		value_type val = (value_type)get_address(data);
		set_value(val, reg_i[1], override);
		reg_i[1].sign = !reg_i[1].sign;
	}
	
	void Machine::enn3(const word &data) //51, 3
	{
		print_command(std::cout, data, "enn3");
		std::cout << std::endl;
		
		value_type val = (value_type)get_address(data);
		set_value(val, reg_i[2], override);
		reg_i[2].sign = !reg_i[2].sign;
	}
	
	void Machine::enn4(const word &data) //52, 3
	{
		print_command(std::cout, data, "ent4");
		std::cout << std::endl;
		
		value_type val = (value_type)get_address(data);
		set_value(val, reg_i[3], override);
		reg_i[3].sign = !reg_i[3].sign;
	}
	
	void Machine::enn5(const word &data) //53, 3
	{
		print_command(std::cout, data, "enn5");
		std::cout << std::endl;
		
		value_type val = (value_type)get_address(data);
		set_value(val, reg_i[4], override);
		reg_i[4].sign = !reg_i[4].sign;
	}
	
	void Machine::enn6(const word &data) //54, 3
	{
		print_command(std::cout, data, "enn6");
		std::cout << std::endl;
		
		value_type val = (value_type)get_address(data);
		set_value(val, reg_i[5], override);
		reg_i[5].sign = !reg_i[5].sign;
	}
	
	void Machine::ennx(const word &data) //55, 3
	{
		print_command(std::cout, data, "ennx");
		std::cout << std::endl;
		
		value_type val = (value_type)get_address(data);
		set_value(val, reg_x, override);
		reg_x.sign = !reg_x.sign;
	}
	
	void Machine::run(short initial_address)
	{
		halt = false;
		set_address(reg_j.bytes, initial_address);
		while(!halt)
		{
			short command_addr = get_value(reg_j);
			inc(reg_j, override);
			do_statement statement = *get_statement(memory[command_addr]);
			(this->*statement)(memory[command_addr]);
		}
	}
}
