/*Computer architecture 2 - 2015 - Coursework 1
		By: Jesús Erlantz García Condado
		Username: jeg114
		Date:17/10/2015
*/

#include "mips_core.h"
#include "mips.h"
#include "mips_instr.h"
#include "mips_internal.h"



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
	//Debug information
	if (state->debug_level >= 1){ fprintf(state->debug_out, "----------- NEW STEP -------- \n PC: 0x%08x \n", state->pc); }
	if (state->debug_level >= 4){
		fprintf(state->debug_out, "Registers: \n");
		for (int i = 0; i <= 31; i++){
			fprintf(state->debug_out, "$%i: 0x%08x \n", i, state->GPReg[i]);
		}
		fprintf(state->debug_out, "LO: 0x%08x \nHI: 0x%08x\n", state->LO, state->HI);
	}

	//Fetch Instruction
	uint8_t buffer[4];
	mips_error step_err = mips_mem_read(state->mem_handle, state->pc, 4,  buffer);

	if (state->debug_level >= 5){ fprintf(state->debug_out, "Err MemReadInstr: %4d\n", step_err); }

	uint32_t instr = to_big_Endi(buffer);

	if (state->debug_level >= 2){ fprintf(state->debug_out, "Instr: %#010x\n", instr); }

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

			if (state->debug_level >= 2){ fprintf(state->debug_out, "Type: R\n", instr); }

			uint8_t rs = (instr >> 21) & 0x1f;
			uint8_t rt = (instr >> 16) & 0x1f;
			uint8_t rd = (instr >> 11) & 0x1f;
			uint8_t sa = (instr >> 6) & 0x1f;
			uint8_t function = instr & 0x3f;

			if (state->debug_level >= 3){ fprintf(state->debug_out, "Op: 0x%2x    rs: %i   rt: %i   rd: %i   sa: %i   func: 0x%2x  \n", opcode, rs, rt, rd, sa, function); }

			//Execute Appropriate function
			switch (function){
			case 0:
				if (state->debug_level > 0){ fprintf(state->debug_out, "SLL"); }
				return SLL(state, rs, rt, rd, sa, function);
			case 2:
				if (state->debug_level > 0){ fprintf(state->debug_out, "SRL"); }
				return SRL(state, rs, rt, rd, sa, function);
			case 3:
				if (state->debug_level > 0){ fprintf(state->debug_out, "SRA"); }
				return SRA(state, rs, rt, rd, sa, function);
			case 4:
				if (state->debug_level > 0){ fprintf(state->debug_out, "SLLV"); }
				return SLLV(state, rs, rt, rd, sa, function);
			case 6:
				if (state->debug_level > 0){ fprintf(state->debug_out, "SRLV"); }
				return SRLV(state, rs, rt, rd, sa, function);
			case 7:
				if (state->debug_level > 0){ fprintf(state->debug_out, "SRAV"); }
				return SRAV(state, rs, rt, rd, sa, function);
			case 8:
				if (state->debug_level > 0){ fprintf(state->debug_out, "JR"); }
				return JR(state, rs, rt, rd, sa, function);
			case 9:
				if (state->debug_level > 0){ fprintf(state->debug_out, "JALR"); }
				return JALR(state, rs, rt, rd, sa, function);
			case 16:
				if (state->debug_level > 0){ fprintf(state->debug_out, "MFHI"); }
				return MFHI(state, rs, rt, rd, sa, function);
			case 17:
				if (state->debug_level > 0){ fprintf(state->debug_out, "MTHI"); }
				return MTHI(state, rs, rt, rd, sa, function);
			case 18:
				if (state->debug_level > 0){ fprintf(state->debug_out, "MFLO"); }
				return MFLO(state, rs, rt, rd, sa, function);
			case 19:
				if (state->debug_level > 0){ fprintf(state->debug_out, "MTLO"); }
				return MTLO(state, rs, rt, rd, sa, function);
			case 24:
				if (state->debug_level > 0){ fprintf(state->debug_out, "MULT"); }
				return MULT(state, rs, rt, rd, sa, function);
			case 25:
				if (state->debug_level > 0){ fprintf(state->debug_out, "MULTU"); }
				return MULTU(state, rs, rt, rd, sa, function);
			case 26:
				if (state->debug_level > 0){ fprintf(state->debug_out, "DIV"); }
				return DIV(state, rs, rt, rd, sa, function);
			case 27:
				if (state->debug_level > 0){ fprintf(state->debug_out, "DIVU"); }
				return DIVU(state, rs, rt, rd, sa, function);
			case 32:
				if (state->debug_level > 0){ fprintf(state->debug_out, "ADD"); }
				return ADD(state, rs, rt, rd, sa, function);
			case 33:
				if (state->debug_level > 0){ fprintf(state->debug_out, "ADDU"); }
				return ADDU(state, rs, rt, rd, sa, function);
			case 34:
				if (state->debug_level > 0){ fprintf(state->debug_out, "SUB"); }
				return SUB(state, rs, rt, rd, sa, function);
			case 35:
				if (state->debug_level > 0){ fprintf(state->debug_out, "SUBU"); }
				return SUBU(state, rs, rt, rd, sa, function);
			case 36:
				if (state->debug_level > 0){ fprintf(state->debug_out, "AND"); }
				return AND(state, rs, rt, rd, sa, function);
			case 37:
				if (state->debug_level > 0){ fprintf(state->debug_out, "OR"); }
				return OR(state, rs, rt, rd, sa, function);
			case 38:
				if (state->debug_level > 0){ fprintf(state->debug_out, "XOR"); }
				return XOR(state, rs, rt, rd, sa, function);
			case 42:
				if (state->debug_level > 0){ fprintf(state->debug_out, "SLT"); }
				return SLT(state, rs, rt, rd, sa, function);
			case 43:
				if (state->debug_level > 0){ fprintf(state->debug_out, "SLTU"); }
				return SLTU(state, rs, rt, rd, sa, function);
			default: return mips_ExceptionInvalidInstruction;
			}
		}
		else if (opcode >> 1 == 1){
			//J - Type Instr
			/*
			--- Opcode --- target ---
			--- 6 Bits ---   26   ---
			*/

			if (state->debug_level >= 2){ fprintf(state->debug_out, "Type: J\n", instr); }

			uint32_t target = instr & 0x3ffffff;

			switch (opcode){
			case 2: 
				if (state->debug_level > 0){ fprintf(state->debug_out, "J"); }
				return J(state, target);
			case 3: 
				if (state->debug_level > 0){ fprintf(state->debug_out, "JAL"); }
				return JAL(state, target);
			default: return mips_ExceptionInvalidInstruction;
			}

		}
		else if(opcode >> 2 != 2){	//Opcode 0010XX reserved for coprocessor instructions
			//I - Type Instr
			/*
			--- Opcode --- rs --- rt --- immediate ---
			--- 6 Bits ---  5 ---  5 ---     16    ---
			*/
			if (state->debug_level >= 2){ fprintf(state->debug_out, "Type: I\n", instr); }
			uint8_t rs = (instr >> 21) & 0x1f;
			uint8_t rt = (instr >> 16) & 0x1f;
			uint16_t imm = instr & 0xffff;

			switch (opcode){
			case 1:
				switch (rt){
				case 0:
					if (state->debug_level > 0){ fprintf(state->debug_out, "BLTZ"); }
					return BLTZ(state, rs, imm);
				case 1: 
					if (state->debug_level > 0){ fprintf(state->debug_out, "BGEZ"); }
					return BGEZ(state, rs, imm);
				case 16:
					if (state->debug_level > 0){ fprintf(state->debug_out, "BLTZAL"); }
					return BLTZAL(state, rs, imm);
				case 17: 
					if (state->debug_level > 0){ fprintf(state->debug_out, "BEGEZAL"); }
					return BGEZAL(state, rs, imm);
				default:
					return mips_ExceptionInvalidInstruction;
				}
			case 4:
				if (state->debug_level > 0){ fprintf(state->debug_out, "BEQ"); }
				return BEQ(state, rs, rt, imm);
			case 5:
				if (state->debug_level > 0){ fprintf(state->debug_out, "BNE"); }
				return BNE(state, rs, rt, imm);
			case 6:
				if (state->debug_level > 0){ fprintf(state->debug_out, "BLEZ"); }
				return BLEZ(state, rs, rt, imm);
			case 7:
				if (state->debug_level > 0){ fprintf(state->debug_out, "BGTZ"); }
				return BGTZ(state, rs, rt, imm);
			case 8:
				if (state->debug_level > 0){ fprintf(state->debug_out, "ADDI"); }
				return ADDI(state, rs, rt, imm);
			case 9:
				if (state->debug_level > 0){ fprintf(state->debug_out, "ADDIU"); }
				return ADDIU(state, rs, rt, imm);
			case 10:
				if (state->debug_level > 0){ fprintf(state->debug_out, "SLTI"); }
				return SLTI(state, rs, rt, imm);
			case 11:
				if (state->debug_level > 0){ fprintf(state->debug_out, "SLTIU"); }
				return SLTIU(state, rs, rt, imm);
			case 12:
				if (state->debug_level > 0){ fprintf(state->debug_out, "ANDI"); }
				return ANDI(state, rs, rt, imm);
			case 13:
				if (state->debug_level > 0){ fprintf(state->debug_out, "ORI"); }
				return ORI(state, rs, rt, imm);
			case 14:
				if (state->debug_level > 0){ fprintf(state->debug_out, "XORI"); }
				return XORI(state, rs, rt, imm);
			case 15:
				if (state->debug_level > 0){ fprintf(state->debug_out, "LUI"); }
				return LUI(state, rs, rt, imm);
			case 32:
				if (state->debug_level > 0){ fprintf(state->debug_out, "LB"); }
				return LB(state, rs, rt, imm);
			case 33:
				if (state->debug_level > 0){ fprintf(state->debug_out, "LH"); }
				return LH(state, rs, rt, imm);
			case 34:
				if (state->debug_level > 0){ fprintf(state->debug_out, "LWL"); }
				return LWL(state, rs, rt, imm);
			case 35:
				if (state->debug_level > 0){ fprintf(state->debug_out, "LW"); }
				return LW(state, rs, rt, imm);
			case 36:
				if (state->debug_level > 0){ fprintf(state->debug_out, "LBU"); }
				return LBU(state, rs, rt, imm);
			case 37:
				if (state->debug_level > 0){ fprintf(state->debug_out, "LHU"); }
				return LHU(state, rs, rt, imm);
			case 38:
				if (state->debug_level > 0){ fprintf(state->debug_out, "LWR"); }
				return LWR(state, rs, rt, imm);
			case 40:
				if (state->debug_level > 0){ fprintf(state->debug_out, "SB"); }
				return SB(state, rs, rt, imm);
			case 41:
				if (state->debug_level > 0){ fprintf(state->debug_out, "SH"); }
				return SH(state, rs, rt, imm);
			case 43:
				if (state->debug_level > 0){ fprintf(state->debug_out, "SW"); }
				return SW(state, rs, rt, imm);
			default: return mips_ExceptionInvalidInstruction;
			}
		}
		else{
			if (state->debug_level >= 2){ fprintf(state->debug_out, "Type: NONE (eg Coprocessor instructions opcode)\n"); }
			return mips_ExceptionInvalidInstruction;
		}
	}
}

mips_error mips_cpu_set_debug_level(mips_cpu_h state, unsigned level, FILE *dest){
	if (level == 0){
		state->debug_level = 0;
		return mips_Success;
	}
	else if(dest != NULL){
		state->debug_out = dest;
		state->debug_level = level;
		return mips_Success;
	}
	else{
		return mips_ErrorInvalidArgument;
	}
}

mips_error mips_cpu_impl::advPC(uint32_t offset){
	pc = pcN;
	pcN = pcN + (offset << 2);
	if (debug_level >= 2){
		fprintf(debug_out, "New PC: 0x%08x     Next PC: 0x%08x \n --------------------", pc, pcN);
	}
	else if (debug_level == 1){
		fprintf(debug_out, "New PC: 0x%08x\n --------------------", pc);
	}
	return mips_Success;
}
