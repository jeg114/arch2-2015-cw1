/*Computer architecture 2 - 2015 - Coursework 1
By: Jesús Erlantz García Condado
Username: jeg114
Date:17/10/2015
*/

#include "mips.h"

using namespace std;

int main(){
	mips_mem_h mem = 0;
	mem = mips_mem_create_ram(4, 4);
	mips_cpu_h CPU = mips_cpu_create(mem);
	return 0;
}