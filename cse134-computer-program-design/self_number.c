#include <stdio.h>

int main(void) 
{
	int output[5000] = {0};
	int div = 0;
	int rem = 0;
	int result = 0;

	for (int i = 1; i < 500; i++) 
	{
		if (i >= 1000) 
		{
			div = (i / 1000);
			rem = (i % 1000);
		}
		else if (i >= 100) 
		{
			div = (i / 100);
			rem = (i % 100);
		}
		else if (i >= 10) 
		{
			div = (i / 10);
			rem = (i % 10);
		}
		else 
		{
			div = i; // div = (i / 1)
			rem = (i % 1);
		}

		result = i + div + rem;
		output[result] = result;

		if (output[i] == 0) {
			printf("%d\n", i);
		}
	}
	
	return 0;
}