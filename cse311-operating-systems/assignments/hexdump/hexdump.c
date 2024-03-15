/**
 * Hexadecimal dump
 * Digital Media 201700000 Park Seong-beom
 * 2018.3.19
 */

#include <stdio.h>
#include <ctype.h>
#include <string.h>

#ifndef HEXDUMP_COLS
#define HEXDUMP_COLS 4
#endif

#ifndef TEXT_MAX_LEN 
#define TEXT_MAX_LEN 255
#endif

void hexdump(void *mem)
{
	unsigned int i, j;
	unsigned int len;

	char text[TEXT_MAX_LEN];
	FILE *file;

	// get the text from the file
	file = fopen((char*)mem, "r");
	fgets(text, TEXT_MAX_LEN, file);
	fclose(file);

	len = strlen(text) - 1;

	for(i = 0; i < len + ((len % HEXDUMP_COLS) ? (HEXDUMP_COLS - len % HEXDUMP_COLS) : 0); i++)
	{
		//  print offset
		if(i % HEXDUMP_COLS == 0)
		{
			printf("0x%06x: ", i);
		}

		//  print hex data
		if(i < len)
		{
			printf("%02x ", 0xFF & (text)[i]);
		}
		else // end of block, just aligning for ASCII dump
		{
			printf("   ");
		}

		// print ASCII dump
		if(i % HEXDUMP_COLS == (HEXDUMP_COLS - 1))
		{
			for(j = i - (HEXDUMP_COLS - 1); j <= i; j++)
			{
				if(j >= len) // end of block, not really printing
				{
					putchar(' ');
				}
				else if(isprint(((text)[j]))) // printable char
				{
					putchar(0xFF & (text)[j]);        
				}
				else // other char
				{
					putchar('.');
				}
			}
			putchar('\n');
		}
	}
}

#ifdef HEXDUMP_TEST
int main(int argc, char *argv[])
{
	printf("%s\n", argv[1]); // print textfile name
	printf("--------------------\n");
	
	hexdump(argv[1]);

	return 0;
}
#endif
