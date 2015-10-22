/*Computer architecture 2 - 2015 - Coursework 1
By: Jesús Erlantz García Condado
Username: jeg114
Date:17/10/2015
*/
#define _CRT_SECURE_NO_DEPRECATE
#include "mips.h"


using namespace std;

int main(){
	mips_mem_h mem = mips_mem_create_ram(4, 4);
	mips_cpu_h cpu = mips_cpu_create(mem);


	uint32_t usign = 0xFFFFFFFF;
	uint32_t usign2 = 2;

	fprintf(stdout, "%#010x + %#010x\n %i\n", usign, usign2, usign + usign2);

	int debug;
	FILE* file_h = NULL;
	cout << "Set Debug level: " << endl;
	cin >> debug;
	if (debug > 0){
		string filename;
		cout << "Input file name for output / stderr / stdout, (if file not found it will be created)" << endl;
		cin >> filename;
		if (filename == "stderr"){
			file_h = stderr;
		}
		else if (filename == "stdout"){
			file_h = stdout;
		}
		else{
			file_h = fopen(filename.c_str(), "w");
		}
	}

	mips_cpu_set_debug_level(cpu, debug, file_h);

	mips_test_begin_suite();
	int testId = mips_test_begin_test("ADDU");

	uint32_t instr = 0x00221821;
	uint8_t buffer[4];
	buffer[0] = (instr >> 24) & 0xFF;
	buffer[1] = (instr >> 16) & 0xFF;
	buffer[2] = (instr >> 8) & 0xFF;
	buffer[3] = (instr >> 0) & 0xFF;
	mips_error err = mips_mem_write(mem, 0, 4, buffer);

	mips_cpu_set_register(cpu, 1, 5);
	mips_cpu_set_register(cpu, 2, 5);
	err = mips_cpu_step(cpu);

	uint32_t got;
	err = mips_cpu_get_register(cpu, 3, &got);
	mips_test_end_test(testId, (err == mips_Success) && (got == 10), "Testing 5+5 == 10");
	mips_test_end_suite();

	cin >> testId;

	return 0;
}

