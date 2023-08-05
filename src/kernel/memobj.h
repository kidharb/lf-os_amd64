#ifndef _MEMOBJ_H_INCLUDED
#define _MEMOBJ_H_INCLUDED

/**
 * A memory object is a piece of memory than can be mapped into userspace processes.
 *
 * In the most basic case, it's what is created for an mmap() syscall or
 * implicitly for each thread when creating a space for its stack.
 *
 * More complex uses of this include memory shared between multiple processes,
 * either like traditional shared memory for IPC purposes or reusing already
 * loaded shared objects.
 */
typedef void* memory_object;

#endif
