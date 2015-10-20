#include "mips.h"
#include "mips_instr.h"
#include "mips_cpu.h"

mips_error BLTZ(mips_cpu_h state, uint8_t rs, uint16_t imm){
	return mips_Success;
}

mips_error BGEZ(mips_cpu_h state, uint8_t rs, uint16_t imm){
	return mips_Success;
}

mips_error BLTZAL(mips_cpu_h state, uint8_t rs, uint16_t imm){
	return mips_Success;
}

mips_error BGEZAL(mips_cpu_h state, uint8_t rs, uint16_t imm){
	return mips_Success;
}

mips_error BEQ(mips_cpu_h state, uint8_t rs, uint8_t rt, uint16_t imm){
	return mips_Success;
}

mips_error BNE(mips_cpu_h state, uint8_t rs, uint8_t rt, uint16_t imm){
	return mips_Success;
}

mips_error BLEZ(mips_cpu_h state, uint8_t rs, uint8_t rt, uint16_t imm){
	return mips_Success;
}

mips_error BGTZ(mips_cpu_h state, uint8_t rs, uint8_t rt, uint16_t imm){
	return mips_Success;
}

mips_error ADDI(mips_cpu_h state, uint8_t rs, uint8_t rt, uint16_t imm){
	return mips_Success;
}

mips_error ADDIU(mips_cpu_h state, uint8_t rs, uint8_t rt, uint16_t imm){
	return mips_Success;
}

mips_error SLTI(mips_cpu_h state, uint8_t rs, uint8_t rt, uint16_t imm){
	return mips_Success;
}

mips_error SLTIU(mips_cpu_h state, uint8_t rs, uint8_t rt, uint16_t imm){
	return mips_Success;
}

mips_error ANDI(mips_cpu_h state, uint8_t rs, uint8_t rt, uint16_t imm){
	return mips_Success;
}

mips_error ORI(mips_cpu_h state, uint8_t rs, uint8_t rt, uint16_t imm){
	return mips_Success;
}

mips_error XORI(mips_cpu_h state, uint8_t rs, uint8_t rt, uint16_t imm){
	return mips_Success;
}

mips_error LUI(mips_cpu_h state, uint8_t rs, uint8_t rt, uint16_t imm){
	return mips_Success;
}

mips_error LB(mips_cpu_h state, uint8_t rs, uint8_t rt, uint16_t imm){
	return mips_Success;
}

mips_error LH(mips_cpu_h state, uint8_t rs, uint8_t rt, uint16_t imm){
	return mips_Success;
}

mips_error LWL(mips_cpu_h state, uint8_t rs, uint8_t rt, uint16_t imm){
	return mips_Success;
}

mips_error LW(mips_cpu_h state, uint8_t rs, uint8_t rt, uint16_t imm){
	return mips_Success;
}

mips_error LBU(mips_cpu_h state, uint8_t rs, uint8_t rt, uint16_t imm){
	return mips_Success;
}

mips_error LHU(mips_cpu_h state, uint8_t rs, uint8_t rt, uint16_t imm){
	return mips_Success;
}

mips_error LWR(mips_cpu_h state, uint8_t rs, uint8_t rt, uint16_t imm){
	return mips_Success;
}

mips_error SB(mips_cpu_h state, uint8_t rs, uint8_t rt, uint16_t imm){
	return mips_Success;
}

mips_error SH(mips_cpu_h state, uint8_t rs, uint8_t rt, uint16_t imm){
	return mips_Success;
}

mips_error SW(mips_cpu_h state, uint8_t rs, uint8_t rt, uint16_t imm){
	return mips_Success;
}

mips_error J(mips_cpu_h state, uint32_t target){
	return mips_Success;
}

mips_error JAL(mips_cpu_h state, uint32_t target){
	return mips_Success;
}

mips_error SLL(mips_cpu_h state, uint8_t rs, uint8_t rt, uint8_t rd, uint8_t sa, uint8_t function){
	return mips_Success;
}

mips_error SRL(mips_cpu_h state, uint8_t rs, uint8_t rt, uint8_t rd, uint8_t sa, uint8_t function){
	return mips_Success;
}

mips_error SRA(mips_cpu_h state, uint8_t rs, uint8_t rt, uint8_t rd, uint8_t sa, uint8_t function){
	return mips_Success;
}

mips_error SLLV(mips_cpu_h state, uint8_t rs, uint8_t rt, uint8_t rd, uint8_t sa, uint8_t function){
	return mips_Success;
}

mips_error SRLV(mips_cpu_h state, uint8_t rs, uint8_t rt, uint8_t rd, uint8_t sa, uint8_t function){
	return mips_Success;
}

mips_error SRAV(mips_cpu_h state, uint8_t rs, uint8_t rt, uint8_t rd, uint8_t sa, uint8_t function){
	return mips_Success;
}

mips_error JR(mips_cpu_h state, uint8_t rs, uint8_t rt, uint8_t rd, uint8_t sa, uint8_t function){
	return mips_Success;
}

mips_error JALR(mips_cpu_h state, uint8_t rs, uint8_t rt, uint8_t rd, uint8_t sa, uint8_t function){
	return mips_Success;
}

mips_error MFHI(mips_cpu_h state, uint8_t rs, uint8_t rt, uint8_t rd, uint8_t sa, uint8_t function){
	return mips_Success;
}

mips_error MTHI(mips_cpu_h state, uint8_t rs, uint8_t rt, uint8_t rd, uint8_t sa, uint8_t function){
	return mips_Success;
}

mips_error MFLO(mips_cpu_h state, uint8_t rs, uint8_t rt, uint8_t rd, uint8_t sa, uint8_t function){
	return mips_Success;
}

mips_error MTLO(mips_cpu_h state, uint8_t rs, uint8_t rt, uint8_t rd, uint8_t sa, uint8_t function){
	return mips_Success;
}

mips_error MULT(mips_cpu_h state, uint8_t rs, uint8_t rt, uint8_t rd, uint8_t sa, uint8_t function){
	return mips_Success;
}

mips_error MULTU(mips_cpu_h state, uint8_t rs, uint8_t rt, uint8_t rd, uint8_t sa, uint8_t function){
	return mips_Success;
}

mips_error DIV(mips_cpu_h state, uint8_t rs, uint8_t rt, uint8_t rd, uint8_t sa, uint8_t function){
	return mips_Success;
}

mips_error DIVU(mips_cpu_h state, uint8_t rs, uint8_t rt, uint8_t rd, uint8_t sa, uint8_t function){
	return mips_Success;
}

mips_error ADD(mips_cpu_h state, uint8_t rs, uint8_t rt, uint8_t rd, uint8_t sa, uint8_t function){
	return mips_Success;
}

mips_error ADDU(mips_cpu_h state, uint8_t rs, uint8_t rt, uint8_t rd, uint8_t sa, uint8_t function){
	state->GPReg[rd] = state->GPReg[rt] + state->GPReg[rs];
	return mips_Success;
}

mips_error SUB(mips_cpu_h state, uint8_t rs, uint8_t rt, uint8_t rd, uint8_t sa, uint8_t function){
	return mips_Success;
}

mips_error SUBU(mips_cpu_h state, uint8_t rs, uint8_t rt, uint8_t rd, uint8_t sa, uint8_t function){
	return mips_Success;
}

mips_error AND(mips_cpu_h state, uint8_t rs, uint8_t rt, uint8_t rd, uint8_t sa, uint8_t function){
	return mips_Success;
}

mips_error OR(mips_cpu_h state, uint8_t rs, uint8_t rt, uint8_t rd, uint8_t sa, uint8_t function){
	return mips_Success;
}

mips_error XOR(mips_cpu_h state, uint8_t rs, uint8_t rt, uint8_t rd, uint8_t sa, uint8_t function){
	return mips_Success;
}

mips_error SLT(mips_cpu_h state, uint8_t rs, uint8_t rt, uint8_t rd, uint8_t sa, uint8_t function){
	return mips_Success;
}

mips_error SLTU(mips_cpu_h state, uint8_t rs, uint8_t rt, uint8_t rd, uint8_t sa, uint8_t function){
	return mips_Success;
}

