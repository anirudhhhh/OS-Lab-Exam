Name: Anirudh
Roll No: 2401MC48
Set: Set 2

Question 1: Memory Protection (mprotect / munprotect)
- kernel/vm.c: Implemented mprotect() and munprotect() to validate alignment and bounds, toggle the PTE_W bit, and flush TLB via sfence_vma().
- kernel/defs.h: Declared prototypes for mprotect() and munprotect().
- kernel/syscall.h, kernel/syscall.c, kernel/sysproc.c: Added syscall numbers, dispatch table entries, and handlers to retrieve user arguments.
- user/user.h, user/usys.pl: Added user-level prototypes and syscall entry stubs.
- Makefile: Added $U/_prottest to UPROGS.
- user/prottest.c: Created test program checking read permissions, child fault killing on write, munprotect write restoration, and invalid inputs.

Question 2: Priority-Based CPU Scheduler
- kernel/proc.h: Added integer field priority (1-20) to struct proc.
- kernel/proc.c: Initialized priority to 10 in allocproc(), implemented ksetpriority() to update priority under process lock, and modified scheduler() to select the RUNNABLE process with the lowest priority value.
- kernel/defs.h: Declared prototype for ksetpriority().
- kernel/syscall.h, kernel/syscall.c, kernel/sysproc.c: Added SYS_set_priority number, table entry, and sys_set_priority() handler.
- user/user.h, user/usys.pl: Added user-level prototype and syscall entry stub for set_priority().
- Makefile: Added $U/_schedtest to UPROGS.
- user/schedtest.c: Created test program verifying parent creates children and higher priority processes finish CPU-bound loops first.

