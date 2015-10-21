/*Computer architecture 2 - 2015 - Coursework 1
By: Jesús Erlantz García Condado
Username: jeg114
Date:17/10/2015
*/

#include "mips_test_functions.h"
#include "mips.h"
#include "mips_core.h"

using namespace std;


uint32_t R_type_instr(string instr, uint32_t rs, uint32_t rt, uint32_t rd){
	
	uint32_t function;
	
	if(instr == "ADDU"){
		function = 0x21;
	}
	
	uint32_t instr_code =
		(0ul << 26) // opcode = 0
		|
		(rs << 21) // srca = r4
		|
		(rt << 16) // srcb = r5
		|
		(rd << 11) // dst = r3
		|
		(0ul << 6) // shift = 0
		|
		(function << 0);

	return instr_code;
}

uint32_t I_type_instr(string instr, uint32_t rs, uint32_t rt, uint32_t imm){

	uint32_t opcode;

	if (instr == "ADDIU"){
		opcode = 0x9;
	}

	uint32_t instr_code =
		(opcode << 26) // opcode = 0
		|
		(rs << 21) // srca = r4
		|
		(rt << 16) // srcb = r5
		|
		(imm << 0);

	return instr_code;
}

uint32_t J_type_instr(string instr, uint32_t target){

	uint32_t opcode;

	if (instr == "J"){
		opcode = 0x2;
	}
	else if (instr == "JAL"){
		opcode = 0x3;
	}

	uint32_t instr_code =
		(opcode << 26) 
		|
		(target << 0);

	return instr_code;
}