#include "ft_malloc.h"
#include <stdio.h>

int	main(void)
{
	struct rlimit	rl;
	getrlimit(RLIMIT_DATA, &rl);
	printf("sysconf = %lu\n", sysconf(_SC_PAGESIZE));
	printf("cur = %lu max = %lu\n", rl.rlim_cur, rl.rlim_max);

	printf("ptr = %p\n", malloc(12));
	return 0;
}