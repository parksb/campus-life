## Project #3: Virtual Memory Simulator

### Due on 24:00, December 15 (Sunday)


### Goal
Implement a mini virtual memory system simulator.


### Problem Specification
- The framework provides an environment to simulate virtual memory and paging. Your task is to implement the key components of the simulator.

- In the simulator, we can have multiple processes in the system. Likewise PA2, each process is abstracted to simple `struct process`, and `struct process *current` points to the currently running process.
`struct list_head processes` is a list to be used as the ready queue of the system. These components leverage the `list_head` that was introduced in the PA2. So, you may utilize your experience from PA2.

- The framework accepts three main commands, which are `read`, `write`, and `switch`, and two supplementary commands, which are `show` and `exit`.

- `read` and `write` is to instruct the system to simulate the memory access. These commands are followed by VPN (virtual page number). For example;
  ```
	>> read 10    /* Read VPN 10 */
	>> write 0x10 /* Write to VPN 0x10 */
	```

- Each read and write request will be processed by the framework, and call `translate()` function to simulate the address translation in MMU.
Complete the function to translate VPN to PFN (page frame number) by walking through the page table of the current process.
If the given VPN cannot be translated or accessed using the current page table, return false to trigger the page fault mechanism in the framework.
*You should not alter/allocate/fixup the page table in this function* but just try the address translation with the current page table.

- When the translation is successful (i.e., return `true` from `translate()`, the framework will print out the translation result and continue accepting the command from the prompt.

- When the translation is unsuccessful, it is equivalent to issue a page fault in MMU. The framework will call `handle_page_fault()` to initiate the page fault handling. In this function, you need to inspect the situation causing the page fault, and resolve the fault accordingly. Thus, you may modify/allocate/fixup the page table in this function. Note that the entire virtual address space is supposed to be writable.

- You may switch the currently running process with `switch` command. Enter the command followed by the process id to switch, and then, the framework will call `switch_process()` to handle the request. Find the target process from the `processes` list, and if exists, do the context switching by replacing `@current` with it.

- If the target process does not exist, you need to fork a child process from @current. This implies you should allocate `struct process` for the child process and initialize it (including page table) accordingly. To duplicate the parent's address space, set up the PTE in the child's page table to map to the same PFN of the parent. You need to set up PTE property bits to support copy-on-write.

- `show` prompt command shows the page table of the current process.


### Tips and Restriction
- Implement features in an incremental way; implement the basic translation function first and get used to the page table/PTE manipulation first. And then move to implement the fork by duplicating the page table contents. You need to manipulate both PTEs of parent and child to support copy-on-write properly.
- As explained above, the entire address space is supposed to be writable. So, be careful to handle `writable` bit in the page table when you attach a page or shar it.
- Likewise previous PAs, printing out to stdout does not influence on the grading. So, feel free to print out debug message using `printf`.


### Submission / Grading
- Use [PAsubmit](https://sslab.ajou.ac.kr/pasubmit) for submission
	- 320 pts + 10 pts

- Code: ***pa3.c*** (300 pts)
  - Address translation (50 pts)
	- Fork (100 pts)
	- Copy-on-Write (150 pts)

- Document: One PDF document (20 pts) including;
	- Description how you implement address translation, fork, and copy-on-write
	- Lesson learned (if you have any)
	- No more than three pages
	- Otherwise you will get 0 pts for the report

- Git repository (10 pts)
	- Register http URL and with a deploy token and password.
	- Start the repository by cloning this repository.
	- Make sure the token is valid through December 20 (due + 4 slip days + 1 day)

- WILL NOT ANSWER THE QUESTIONS ABOUT THOSE ALREADY SPECIFIED ON THE HANDOUT.
