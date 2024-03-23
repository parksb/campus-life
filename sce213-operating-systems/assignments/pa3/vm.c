/**********************************************************************
 * Copyright (c) 2019
 *  Sang-Hoon Kim <sanghoonkim@ajou.ac.kr>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTIABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 **********************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <getopt.h>
#include <ctype.h>
#include <inttypes.h>
#include <strings.h>

#include "types.h"
#include "parser.h"

#include "list_head.h"
#include "vm.h"

bool quiet = false;

/**
 * Initial process.
 */
static struct process init = {
	.pid = 0,
};

/**
 * Current process. Should not be listed in the @processes
 */
struct process *current = &init;

/**
 * Ready queue. Put @current process to the tail of this list on
 * switch_process(). Don't forget to remove the switched process from the list.
 */
LIST_HEAD(processes);

/**
 * Sequentially allocate a page frame from the physical address space
 */
unsigned int alloc_page(void)
{
	static unsigned int __nr_allocated_pages = 0;
	return __nr_allocated_pages++;
}

extern bool translate(enum memory_access_type rw, unsigned int vpn, unsigned int *pfn);
extern bool handle_page_fault(enum memory_access_type rw, unsigned int vpn);
extern void switch_process(unsigned int pid);

/**
 * __access_memory
 *
 * DESCRIPTION
 *   Simulate the MMU in the processor.
 */
static bool __access_memory(enum memory_access_type rw, unsigned int vpn)
{
	unsigned int pfn;
	int ret;
	int nr_retries = 0;

	assert(vpn >= 0);
	/**
	 * We have NR_PTES_PER_PAGE entries in the outer table and so do for
	 * inner page table. Thus each process can have up to NR_PTES_PER_PAGE^2
	 * as its VPN
	 */
	assert(vpn < NR_PTES_PER_PAGE * NR_PTES_PER_PAGE);

	do {
		/* Ask to translate VPN */
		if (translate(rw, vpn, &pfn)) {
			/* Success on address translation */
			fprintf(stderr, "%3d --> %-3d\n", vpn, pfn);
			return true;
		}

		/**
		 * Failed to translate the address. Call OS to handle the page fault and
		 * restart the translation if the fault is successfully handled.
		 * Count the number of retries to prevent buggy translation.
		 */
		nr_retries++;
	} while ((ret = handle_page_fault(rw, vpn)) == true && nr_retries < 2);

	return ret;
}


/*************************************************************************/
/****************** THE INTERNAL OF THE FRAMEWORK BELOW ******************/
/*************************************************************************/

static void __init_system(void)
{
	/* Initialize the init process */
	INIT_LIST_HEAD(&init.list);
	bzero(&init.pagetable, sizeof(struct pagetable));
}

static bool strmatch(char * const str, const char *expect)
{
	return (strlen(str) == strlen(expect)) &&
			(strncmp(str, expect, strlen(expect)) == 0);
}

static void __show_pagetable(unsigned int start, unsigned int end)
{
	fprintf(stderr, "** PID %d ** \n", current->pid);

	for (int i = 0; i < NR_PTES_PER_PAGE; i++) {
		struct pte_directory *pd = current->pagetable.outer_ptes[i];

		if (!pd) continue;

		for (int j = 0; j < NR_PTES_PER_PAGE; j++) {
			struct pte *pte = &pd->ptes[j];

			if (quiet && !pte->valid) continue;
			fprintf(stderr, "%02d:%02d %c%c | %-3d\n", i, j,
				pte->valid ? 'v' : ' ',
				pte->writable ? 'w' : ' ',
				pte->pfn);
		}
		printf("\n");
	}
}

static void __do_simulation(FILE *input)
{
	char command[MAX_COMMAND_LEN] = {'\0'};

	__init_system();

	while (fgets(command, sizeof(command), input)) {
		char *tokens[MAX_NR_TOKENS] = { NULL };
		int nr_tokens = 0;

		/* Make the command lowercase */
		for (size_t i = 0; i < strlen(command); i++) {
			command[i] = tolower(command[i]);
		}

		if (parse_command(command, &nr_tokens, tokens) < 0) {
			continue;
		}
		if (nr_tokens == 0) continue;

		if (nr_tokens == 1) {
			if (strmatch(tokens[0], "exit")) break;
			if (strmatch(tokens[0], "show")) {
				__show_pagetable(0, 0);
			} else {
				printf("Unknown command %s\n", tokens[0]);
			}
		} else if (nr_tokens == 2) {
			if (strmatch(tokens[0], "switch") || strmatch(tokens[0], "s")) {
				switch_process(atoi(tokens[1]));
			} else if (strmatch(tokens[0], "read") || strmatch(tokens[0], "r")) {
				if (!__access_memory(READ, strtoimax(tokens[1], NULL, 0))) break;;
			} else if (strmatch(tokens[0], "write") || strmatch(tokens[0], "w")) {
				if (!__access_memory(WRITE, strtoimax(tokens[1], NULL, 0))) break;;
			} else {
				printf("Unknown command %s\n", tokens[0]);
			}
		} else {
			assert(!"Unknown command in trace");
		}

		if (!quiet) printf(">> ");
	}
}

static void __print_usage(const char * name)
{
	printf("Usage: %s {-q} {-f [workload file]}\n", name);
	printf("\n");
	printf("  -q: Run quietly\n\n");
}

int main(int argc, char * argv[])
{
	int opt;
	FILE *input = stdin;

	while ((opt = getopt(argc, argv, "qh")) != -1) {
		switch (opt) {
		case 'q':
			quiet = true;
			break;
		case 'h':
		default:
			__print_usage(argv[0]);
			return EXIT_FAILURE;
		}
	}

	if (!quiet && !argv[optind]) {
		printf("***************************************************************************\n");
		printf(" __      ____  __    _____ _                 _       _\n");
		printf(" \\ \\    / /  \\/  |  / ____(_)               | |     | |\n");
		printf("  \\ \\  / /| \\  / | | (___  _ _ __ ___  _   _| | __ _| |_ ___  _ __ \n");
		printf("   \\ \\/ / | |\\/| |  \\___ \\| | '_ ` _ \\| | | | |/ _` | __/ _ \\| '__|\n");
		printf("    \\  /  | |  | |  ____) | | | | | | | |_| | | (_| | || (_) | |   \n");
		printf("     \\/   |_|  |_| |_____/|_|_| |_| |_|\\__,_|_|\\__,_|\\__\\___/|_|\n");
		printf("\n");
		printf("                                              - SCE213 2019.12 -\n");
		printf("***************************************************************************\n");
	}

	if (argv[optind]) {
		if (!quiet) printf("Use file \"%s\" as input\n", argv[optind]);

		input = fopen(argv[optind], "r");
		if (!input) {
			fprintf(stderr, "No input file %s\n", argv[optind]);
			return EXIT_FAILURE;
		}
		quiet = true;
	} else {
		if (!quiet) printf("Use stdin as input\n");
	}

	if (!quiet) printf(">> ");

	__do_simulation(input);

	if (input != stdin) fclose(input);

	return EXIT_SUCCESS;
}
