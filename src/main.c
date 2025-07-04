#include "ft_malloc.h"

void	free(void *ptr)
{
	ft_malloc_internal(FREE, ptr, 0);
	return;
}

void	*malloc(size_t size)
{
	return ft_malloc_internal(MALLOC, NULL, size);
}

void	*realloc(void *ptr, size_t size)
{
	return ft_malloc_internal(REALLOC, ptr, size);
}

void	show_alloc_mem(void)
{
	ft_malloc_internal(SHOW, NULL, 0);
	return;
}
