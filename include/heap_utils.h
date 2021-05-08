#ifndef __HEAP_UTIL_FUNCS
#define __HEAP_UTIL_FUNCS
	
	int getRight(int) __attribute__((weak));
	int getLeft(int) __attribute__((weak));
	int getParent(int) __attribute__((weak));
	int max(int, int) __attribute__((weak));
	int min(int, int) __attribute__((weak));

	inline int getRight(int i){	return (i<<1)+2; }
	inline int getLeft(int i){ return (i<<1)+1; }
	inline int getParent(int i){ return ((i-1)>>1)*(i!=0); }
	inline int max(int a, int b){ return (a>b)?a:b; }
	inline int min(int a, int b){ return (a<b)?a:b; }

#endif