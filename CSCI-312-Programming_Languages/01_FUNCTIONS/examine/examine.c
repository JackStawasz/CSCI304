#include <stdio.h>

int main()
{
	char var = '.';
	char *varp = &var;
	while (1) {
		if (*varp == '\0') {
			putchar('\n');
		} else {
			putchar(*varp);
		}
		fflush(stdout);
		varp++;
	}
}
