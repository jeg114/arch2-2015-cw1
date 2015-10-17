/*Computer architecture 2 - 2015 - Coursework 1
		By: Jesús Erlantz García Condado
		Username: jeg114
		Date:17/10/2015
*/

#include "mips.h"

struct mips_cpu_impl{
	//Program Counter
	uint32_t pc;

	//General Purpose Registers
	uint32_t GPReg[32];

	//Special registers for MUL / DIV instructions
	uint32_t LO;
	uint32_t HI;

	mips_mem_h mem_handle;

	mips_cpu_impl(mips_mem_h mem) : mem_handle(mem), pc(0), LO(0), HI(0){
		for (int i = 0; i <= 31; i++){
			GPReg[i] = 0;
		}
	}

};

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