#include "os.h"
#include "stdlib.h"
#include "stdio.h"
#include "string.h"

int main(int argc, char **argv)
{
	print("Hi there elf\n");
	for (int i = 0; i < argc; i++)
	{
		printf("%s\n", argv[i]);
	}

		return 0;
}
