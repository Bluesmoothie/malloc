#include "ft_malloc.h"

static inline void	init(void);

static t_context	ctx;

void	free(void *ptr)
{
	init();
	(void)ptr;
	return;
}

void	*malloc(size_t size)
{
	init();
	(void)size;
	return NULL;
}

void	*realloc(void *ptr, size_t size)
{
	init();
	(void)ptr;
	(void)size;
	return NULL;
}

void	show_alloc_mem(void)
{
	return;
}

static inline void	init(void)
{
	if (!ctx.init)
		init_malloc(&ctx);
}
