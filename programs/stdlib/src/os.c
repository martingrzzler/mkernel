#include "os.h"

int os_getkeyblock()
{
	int val = 0;
	do
	{
		val = os_getKey();
	} while (val == 0);

	return val;
}

void os_terminal_readline(char *out, int max, bool output_while_typing)
{
	int i = 0;
	for (i = 0; i < max; i++)
	{
		char key = os_getkeyblock();
		// Carriage return
		if (key == 13)
		{
			break;
		}
		if (output_while_typing)
		{
			os_putchar(key);
		}

		if (key == 0x80 && i >= 1)
		{
			out[i - 1] = 0x00;
			// -2 because we will +1 when we go to continue
			i -= 2;
			continue;
		}
		out[i] = key;
	}
	out[i] = 0x00;
}