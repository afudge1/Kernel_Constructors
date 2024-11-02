#ifndef STDC_DEFS_H
#define STDC_DEFS_H

// Define size_t for representing sizes
typedef unsigned long size_t;

// Define NULL pointer
#ifndef NULL
#define NULL ((void*)0)
#endif

// Offset of a member in a struct
#define offsetof(type, member) ((size_t)&((type *)0)->member)

#endif // STDC_DEFS_H
