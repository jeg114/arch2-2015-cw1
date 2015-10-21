/*! \mips_test_functions.h
Declarations of functions to use during testing.
*/
#ifndef mips_test_functions
#define mips_test_functions

#include "mips.h"

/*
32 bit instr from a string function code (ADD, SUB, JR..) an R-type instruction,
if that function is not included, behaviour undefined

*/
uint32_t R_type_instr(std::string instr, uint32_t rs, uint32_t rt, uint32_t rd);

/*
32 bit instr from a string function code (ADDI, SUBI, ..) an I-type instruction,
if that function is not included, behaviour undefined

*/
uint32_t I_type_instr(std::string instr, uint32_t rs, uint32_t rt, uint32_t imm);

#endif