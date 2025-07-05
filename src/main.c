#include "ft_malloc.h"

static inline void	init(void);

static t_context	ctx;

void	free(void *ptr)
{
	init();
	return;
}

void	*malloc(size_t size)
{
	init();
	return NULL;
}

void	*realloc(void *ptr, size_t size)
{
	init();
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
