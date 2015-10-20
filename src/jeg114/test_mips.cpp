/*Computer architecture 2 - 2015 - Coursework 1
By: Jesús Erlantz García Condado
Username: jeg114
Date:17/10/2015
*/

#include "mips.h"


using namespace std;

int main(){
	mips_mem_h mem = mips_mem_create_ram(4, 4);
	mips_cpu_h cpu = mips_cpu_create(mem);

	mips_test_begin_suite();
	int testId = mips_test_begin_test("ADDU");
	mips_cpu_set_register(cpu, 1, 5);
	mips_cpu_set_register(cpu, 2, 5);
	uint32_t instr = 0x00221821;
	mips_error err = mips_mem_write(mem, 0, 4, (uint8_t*) &instr);
	uint32_t got;
	err = mips_cpu_get_register(cpu, 3, &got);
	mips_test_end_test(testId, (err == mips_Success) && (got == 10), "Testing 5+5 == 10");
	mips_test_end_suite();

	cin >> testId;

	return 0;
}

