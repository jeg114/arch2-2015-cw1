/*Computer architecture 2 - 2015 - Coursework 1
		By: Jesús Erlantz García Condado
		Username: jeg114
		Date:17/10/2015
*/
#include "mips_core.h"
#include "mips.h"


using namespace std;


mips_cpu_h mips_cpu_create(mips_mem_h mem){
	mips_cpu_h new_cpu = new mips_cpu_impl (mem);
	return new_cpu;
}

mips_error mips_cpu_reset(mips_cpu_h state){
	state->pc = 0;
	state->LO = 0;
	state->HI = 0;
	for (int i = 0; i <= 31; i++){
		state -> GPReg[i] = 0;
	}
	//Can be unsuccesful??
	return mips_Success;
}

mips_error mips_cpu_get_register(mips_cpu_h state, unsigned index, uint32_t *value){
	if (index > 31){
		return mips_ErrorInvalidArgument;
	}
	else{
		*value = state->GPReg[index];
		return mips_Success;
	}
}

mips_error mips_cpu_set_register(mips_cpu_h state, unsigned index, uint32_t value){
	if (index > 31){
		return mips_ErrorInvalidArgument;
	}
	else{
		state->GPReg[index] = value;
		return mips_Success;
	}
}

mips_error mips_cpu_set_pc(mips_cpu_h state, uint32_t pc){
	if (pc % 4 != 0){
		return mips_ExceptionInvalidAlignment;
	}
	else{
		state->pc = pc;
		return mips_Success;
	}
}

mips_error mips_cpu_get_pc(mips_cpu_h state, uint32_t *pc){
	*pc = state->pc;
	return mips_Success;
}

void mips_cpu_free(mips_cpu_h state){
	if (state != NULL){
		delete state;
	}
}

uint32_t to_big_Endi(const uint8_t *pData)
{
	return
		(((uint32_t)pData[0]) << 24)
		|
		(((uint32_t)pData[1]) << 16)
		|
		(((uint32_t)pData[2]) << 8)
		|
		(((uint32_t)pData[3]) << 0);
}

mips_error mips_cpu_step(mips_cpu_h state){
	
	//Fetch Instruction

	uint8_t buffer[4];
	mips_error step_err = mips_mem_read(state->mem_handle, state->pc, 4,  buffer);
	uint32_t instr = to_big_Endi(buffer);
	if (step_err != mips_Success){
		return step_err;
	}
	else{
		//Decode Instruction
		uint8_t opcode = instr >> 26;
		if (opcode == 0){
			//R - Type Instr
			/*
			--- Opcode --- rs --- rt --- rd --- sa --- function ---
			--- 6 Bits ---  5 ---  5 ---  5 ---  5 ---    6     ---
			*/

			uint8_t rs = (instr >> 21) & 0x1f;
			uint8_t rt = (instr >> 16) & 0x1f;
			uint8_t rd = (instr >> 11) & 0x1f;
			uint8_t sa = (instr >> 6) & 0x1f;
			uint8_t function = instr & 0x1f;

			//Execute Appropriate function
			switch (function){
			case 0: return SLL(state, rs, rt, rd, sa, function);
			case 2: return SRL(state, rs, rt, rd, sa, function);
			case 3: return SRA(state, rs, rt, rd, sa, function);
			case 4: return SLLV(state, rs, rt, rd, sa, function);
			case 6: return SRLV(state, rs, rt, rd, sa, function);
			case 7: return SRAV(state, rs, rt, rd, sa, function);
			case 8: return JR(state, rs, rt, rd, sa, function);
			case 9: return JALR(state, rs, rt, rd, sa, function);
			case 16: return MFHI(state, rs, rt, rd, sa, function);
			case 17: return MTHI(state, rs, rt, rd, sa, function);
			case 18: return MFLO(state, rs, rt, rd, sa, function);
			case 19: return MTLO(state, rs, rt, rd, sa, function);
			case 24: return MULT(state, rs, rt, rd, sa, function);
			case 25: return MULTU(state, rs, rt, rd, sa, function);
			case 26: return DIV(state, rs, rt, rd, sa, function);
			case 27: return DIVU(state, rs, rt, rd, sa, function);
			case 32: return ADD(state, rs, rt, rd, sa, function);
			case 33: return ADDU(state, rs, rt, rd, sa, function);
			case 34: return SUB(state, rs, rt, rd, sa, function);
			case 35: return SUBU(state, rs, rt, rd, sa, function);
			case 36: return AND(state, rs, rt, rd, sa, function);
			case 37: return OR(state, rs, rt, rd, sa, function);
			case 38: return XOR(state, rs, rt, rd, sa, function);
			case 42: return SLT(state, rs, rt, rd, sa, function);
			case 43: return SLTU(state, rs, rt, rd, sa, function);
			default: return mips_ExceptionInvalidInstruction;
			}
		}
		else if (opcode >> 1 == 1){
			//J - Type Instr
			/*
			--- Opcode --- target ---
			--- 6 Bits ---   26   ---
			*/
			uint32_t target = instr & 0x3ffffff;

			switch (opcode){
			case 2: return J(state, target);
			case 3: return JAL(state, target);
			default: return mips_ExceptionInvalidInstruction;
			}

		}
		else if(opcode >> 2 != 2){	//Opcode 0010XX reserved for coprocessor instructions
			//I - Type Instr
			/*
			--- Opcode --- rs --- rt --- immediate ---
			--- 6 Bits ---  5 ---  5 ---     16    ---
			*/
			uint8_t rs = (instr >> 21) & 0x1f;
			uint8_t rt = (instr >> 16) & 0x1f;
			uint16_t imm = instr & 0xffff;

			switch (opcode){
			case 1:
				switch (rt){
				case 0: return BLTZ(state, rs, imm);
				case 1: return BGEZ(state, rs, imm);
				case 16: return BLTZAL(state, rs, imm);
				case 17: return BGEZAL(state, rs, imm);
				default: return mips_ExceptionInvalidInstruction;
				}
			case 4: return BEQ(state, rs, rt, imm);
			case 5: return BNE(state, rs, rt, imm);
			case 6: return BLEZ(state, rs, rt, imm);
			case 7: return BGTZ(state, rs, rt, imm);
			case 8: return ADDI(state, rs, rt, imm);
			case 9: return ADDIU(state, rs, rt, imm);
			case 10: return SLTI(state, rs, rt, imm);
			case 11: return SLTIU(state, rs, rt, imm);
			case 12: return ANDI(state, rs, rt, imm);
			case 13: return ORI(state, rs, rt, imm);
			case 14: return XORI(state, rs, rt, imm);
			case 15: return LUI(state, rs, rt, imm);
			case 32: return LB(state, rs, rt, imm);
			case 33: return LH(state, rs, rt, imm);
			case 34: return LWL(state, rs, rt, imm);
			case 35: return LW(state, rs, rt, imm);
			case 36: return LBU(state, rs, rt, imm);
			case 37: return LHU(state, rs, rt, imm);
			case 38: return LWR(state, rs, rt, imm);
			case 40: return SB(state, rs, rt, imm);
			case 41: return SH(state, rs, rt, imm);
			case 43: return SW(state, rs, rt, imm);
			default: return mips_ExceptionInvalidInstruction;
			}
		}
		else{
			return mips_ExceptionInvalidInstruction;
		}
	}
}


