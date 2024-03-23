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
#ifndef __VM_H__
#define __VM_H__

#include "types.h"

#define PTES_PER_PAGE_SHIFT 4
#define NR_PTES_PER_PAGE    (1 << PTES_PER_PAGE_SHIFT)

enum memory_access_type {
	READ = 0,
	WRITE,
};

struct pte {
	bool valid;
	bool writable;
	unsigned int pfn;
};

struct pte_directory {
	struct pte ptes[NR_PTES_PER_PAGE];
};

struct pagetable {
	struct pte_directory *outer_ptes[NR_PTES_PER_PAGE];
};

struct process {
	unsigned int pid;

	struct pagetable pagetable;

	struct list_head list;
};

#endif
