#ifndef __MACRO_CONCAT_UTILS
#define __MACRO_CONCAT_UTILS

#define _CAT2(x,y) x ## y
#define CAT2(x,y) _CAT2(x,y)
#define CAT3(x,y,z) CAT2(x,CAT2(y,z))

#endif